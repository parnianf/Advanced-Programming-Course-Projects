#include "GoodReads.hpp"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <map>
using namespace std;

enum type
{
  eWantToRead,
  eCurrentlyReading,
  eRead
};

User *GoodReads::findUserById(int id)
{
  for (int i = 0; i < users.size(); i++)
  {
    if (users[i].getId() == id)
    {
      return &users[i];
    }
  }
}

Book *GoodReads::findBookById(int id)
{
  for (int i = 0; i < books.size(); i++)
  {
    if (books[i].getId() == id)
    {
      return &books[i];
    }
  }
}

Author *GoodReads::findAuthorById(int id)
{
  for (int i = 0; i < authors.size(); i++)
    if (authors[i].getId() == id)
      return &authors[i];
}

void GoodReads::readFollowEdgesFile(string directoryName, string fileName)
{
  string word, line;
  vector<int> followingUsersId;
  vector<User *> followingUsers;
  string path = generateFilePath(directoryName, fileName);
  ifstream inputFile(path);
  if (!inputFile)
    cout << OPENING_FILE_ERROR << endl;
  stringstream fileInfo;
  fileInfo << inputFile.rdbuf();
  getline(fileInfo, line);

  while (getline(fileInfo, line))
  {
    stringstream lineInfo(line);
    vector<string> information;
    while (getline(lineInfo, word, FILE_SEPERATOR))
    {
      information.push_back(word);
    }
    User *user = findUserById(stoi(information[0]));
    followingUsersId = splitIds(information[1]);
    for (int i = 0; i < followingUsersId.size(); i++)
    {
      followingUsers.push_back(findUserById(followingUsersId[i]));
    }
    user->setFollowingId(followingUsers);
    followingUsers.clear();
  }
}

int GoodReads::countTotalNumberOfLikes()
{
  int total = 0;
  for (int i = 0; i < reviews.size(); i++)
  {
    total += reviews[i].getNumberOfLikes();
  }
  return total;
}

double GoodReads::getUserCredit(int id)
{
  User *user = findUserById(id);
  double a = 0, b = 0;
  if (countTotalNumberOfLikes() != 0)
  {
    a = (double)(user->countUserReviewLike()) / (double)countTotalNumberOfLikes();
  }
  if (reviews.size())
  {
    b = (double)(user->countUserReviews()) / (double)reviews.size();
  }
  double credit = (0.5) * (a + b);
  return credit;
}

void GoodReads::showAuthorInfo(int id)
{
  Author *author = findAuthorById(id);
  cout << author->toString();
  bool isTheFirstIterate = true;
  for (int i = 0; i < books.size(); i++)
  {
    if (books[i].getAuthorId() == id)
    {
      cout << books[i].toString(1);
    }
  }
}

void GoodReads::showSortedShelf(int id, string genre, string type)
{
  User *user = findUserById(id);
  multiset<Book> sortedBooks = user->sortingBooksInOrder(findTypeBooksByUserId(user, type));
  for (auto book : sortedBooks)
  {
    if ((book.getGenre()) == genre)
    {
      cout << book.toString(2) << BOOK_SHELF_SEPERATOR << endl;
    }
  }
  for (auto book : sortedBooks)
  {
    if (book.getGenre() != genre)
    {
      cout << book.toString(2) << BOOK_SHELF_SEPERATOR << endl;
    }
  }
}

BookTable GoodReads::findTypeBooksByUserId(User *user, string type)
{
  BookTable typeBooks;
  vector<Book *> shelfType;
  enum type bookType;
  if (type == WANT_TO_READ)
  {
    bookType = eWantToRead;
  }
  else if (type == CURRENTLY_READING)
  {
    bookType = eCurrentlyReading;
  }
  else if (type == READ)
  {
    bookType = eRead;
  }
  shelfType = user->getTypeList(bookType);
  for (int j = 0; j < shelfType.size(); j++)
  {
    for (int k = 0; k < books.size(); k++)
    {
      if (shelfType[j]->getId() == books[k].getId())
      {
        typeBooks.push_back(books[k]);
      }
    }
  }
  return typeBooks;
}

vector<Book *> GoodReads::setTypeShelf(vector<int> shelfType)
{
  vector<Book *> faveBooks;
  for (int i = 0; i < shelfType.size(); i++)
  {
    for (int j = 0; j < books.size(); j++)
    {
      if (shelfType[i] == books[j].getId())
      {
        faveBooks.push_back(&books[j]);
      }
    }
  }
  return faveBooks;
}

void GoodReads::recommendSecondApproach(int id)
{

  enum type booktype;
  vector<pair<double, int>> ratingAndId;
  vector<int> totalBestBooksOfFollowings;

  vector<User *> userFollowings = getAllFollowingsForUser(id);
  for (int i = 1; i < userFollowings.size(); i++)
  {
    vector<Book *> readBooksOfFollowing = userFollowings[i]->getTypeList(eRead);
    for (int j = 0; j < readBooksOfFollowing.size(); j++)
    {
      ratingAndId.push_back(make_pair(getRate(readBooksOfFollowing[j]), (readBooksOfFollowing[j])->getId()));
    }

    sort(ratingAndId.begin(), ratingAndId.end(), sortingScoreAndBook);
    for (int number = 0; (number < FOLLOWING_SELECTED_BOOKS_RANGE) && (number < ratingAndId.size()); number++)
    {
      totalBestBooksOfFollowings.push_back(ratingAndId[number].second);
    }
    ratingAndId.clear();
  }
  Book *mostRepeatedBook = findTheMostRepeatedBook(totalBestBooksOfFollowings);
  cout << mostRepeatedBook->toString(2);
  vector<Review *> bookReviews = mostRepeatedBook->getReview();
  cout << "Reviews:" << endl;
  for (int i = 0; i < bookReviews.size(); i++)
  {
    cout << bookReviews[i]->toString();
  }
}

Book *GoodReads::findTheMostRepeatedBook(vector<int> selectedBooksId)
{
  vector<pair<int, int>> bookIdAndCount;
  vector<int> allBookId;
  for (int i = 0; i < selectedBooksId.size(); i++)
  {
    int x = count(selectedBooksId.begin(), selectedBooksId.end(), selectedBooksId[i]);
    bookIdAndCount.push_back(make_pair(x, selectedBooksId[i]));
  }
  sort(bookIdAndCount.begin(), bookIdAndCount.end(), sortingVectorOfPair);
  return (findBookById(bookIdAndCount[0].second));
}

double GoodReads::getRate(Book *book)
{
  double rating = 0;
  vector<Review *> bookReviews = book->getReview();
  if (bookReviews.size())
  {
    for (int j = 0; j < bookReviews.size(); j++)
    {
      rating += ((bookReviews[j]->getRating()) * (getUserCredit(bookReviews[j]->getUserId())));
    }
    rating = rating / (double)bookReviews.size();
  }
  return rating;
}

double GoodReads::getScore(User *user, Book *book)
{
  double score = getRate(book);
  Genres genre = user->getFavoriteGenres();
  for (int i = 0; i < genre.size(); i++)
  {
    if (book->getGenre() == genre[i])
    {
      score += BOOK_IN_FAVORITE_GENRE_SCORE;
      break;
    }
  }

  return score;
}

void GoodReads::recommendBook(int id)
{
  multimap<double, int> scoreAndBookId;
  vector<pair<double, int>> scores;
  User *user = findUserById(id);
  vector<string> genres = user->getFavoriteGenres();

  for (int i = 0; i < books.size(); i++)
  {
    scores.push_back(make_pair(getScore(user, &books[i]), (&books[i])->getId()));
  }
  sort(scores.begin(), scores.end(), sortingScoreAndBook);
  Book *book = findBookById(scores[0].second);
  cout << book->toString(2);
  vector<Review *> bookReviews = book->getReview();
  multiset<Review> reviews_;
  cout << "Reviews:" << endl;
  for (int i = 0; i < bookReviews.size(); i++)
  {
    cout << bookReviews[i]->toString();
  }
}

vector<User *> GoodReads::getAllFollowingsForUser(int id)
{

  User *user = findUserById(id);
  vector<User *> followings;
  followings = user->getFollowings();
  vector<User *> userFollowings;
  userFollowings.push_back(user);
  makeFollowingList(userFollowings, followings);
  return userFollowings;
}

void GoodReads::makeFollowingList(vector<User *> &userFollowings, vector<User *> followingForEachUser)
{

  for (int i = 0; i < followingForEachUser.size(); i++)
  {
    if (find(userFollowings.begin(), userFollowings.end(), followingForEachUser[i]) != userFollowings.end())
    {
      continue;
    }
    userFollowings.push_back(followingForEachUser[i]);
    makeFollowingList(userFollowings, followingForEachUser[i]->getFollowings());
  }
}

void GoodReads ::setReviewsForUser()
{

  vector<Review *> userReviews;
  for (int i = 0; i < users.size(); i++)
  {
    for (int j = 0; j < reviews.size(); j++)
    {
      if (users[i].getId() == reviews[j].getUserId())
      {
        userReviews.push_back(&reviews[j]);
      }
    }
    users[i].setReviews(userReviews);
    userReviews.clear();
  }
}

void GoodReads ::showTheBestBook()
{
  BookTable books_ = books;
  sort(books_.begin(), books_.end(), sortByaverageRating);
  cout << books_[0].toString(2);
  cout << "Average Rating: " << fixed << setprecision(2) << books_[0].getAverageRating() << endl;
}

void GoodReads ::showTheBestReviewer()
{
  multimap<int, int, greater<int>> userAndLike;
  multimap<int, string, less<int>> authorIdAndName;
  int index = 0;
  for (int i = 0; i < users.size(); i++)
  {
    userAndLike.insert(pair<int, int>(users[i].countUserReviewLike(), users[i].getId()));
  }
  cout << findUserById(userAndLike.begin()->second)->userInfoToString();
  vector<int> favoriteAuthorsId = findUserById(userAndLike.begin()->second)->getFavoriteAuthorsId();
  cout << "Favorite Authors: ";
  for (int i = 0; i < favoriteAuthorsId.size(); i++)
  {
    authorIdAndName.insert(pair<int, string>(favoriteAuthorsId[i], findAuthorById(favoriteAuthorsId[i])->getName()));
  }
  for (auto it : authorIdAndName)
  {
    cout << it.second;
    if (index < favoriteAuthorsId.size() - 1)
    {
      cout << GENRES_SEPERATOR << ' ';
    }
    index++;
  }
  cout << endl
       << findUserById(userAndLike.begin()->second)->shelfInfoTostring();
}

void GoodReads ::setReviewsForBooks()
{
  vector<Review *> bookReviews;
  for (int i = 0; i < books.size(); i++)
  {
    for (int j = 0; j < reviews.size(); j++)
    {
      if (books[i].getId() == reviews[j].getBookId())
      {
        bookReviews.push_back(&reviews[j]);
      }
    }
    books[i].setReviews(bookReviews);
    bookReviews.clear();
  }
}

void GoodReads ::readFiles(string directoryName)
{
  readAuthorFile(directoryName, AUTHOR_FILE_NAME);
  readReviewsFile(directoryName, REVIEWS_FILE_NAME);
  readBookFile(directoryName, BOOKS_FILE_NAME);
  readUserFile(directoryName, USERS_FILE_NAME);
  readFollowEdgesFile(directoryName, FOLLOW_EDGES_FILE_NAME);
}

void GoodReads ::readReviewsFile(string directoryName, string fileName)
{
  string word, line;
  ReviewTable reviews_;
  string path = generateFilePath(directoryName, fileName);
  ifstream inputFile(path);
  if (!inputFile)
    cout << OPENING_FILE_ERROR << endl;
  stringstream fileInfo;
  fileInfo << inputFile.rdbuf();
  getline(fileInfo, line);

  while (getline(fileInfo, line))
  {
    stringstream lineInfo(line);
    vector<string> information;

    while (getline(lineInfo, word, FILE_SEPERATOR))
    {
      information.push_back(word);
    }

    Review review(stoi(information[0].c_str()), stoi(information[1].c_str()), stoi(information[2].c_str()),
                  stoi(information[3].c_str()), information[4], stoi(information[5].c_str()));
    reviews_.push_back(review);
  }
  reviews = reviews_;
}

void GoodReads::readBookFile(string directoryName, string fileName)
{
  string word, line;
  BookTable books_;
  string path = generateFilePath(directoryName, fileName);
  ifstream inputFile(path);
  if (!inputFile)
    cout << OPENING_FILE_ERROR << endl;
  stringstream fileInfo;
  fileInfo << inputFile.rdbuf();
  getline(fileInfo, line);
  while (getline(fileInfo, line))
  {
    stringstream lineInfo(line);
    vector<string> information;
    while (getline(lineInfo, word, FILE_SEPERATOR))
    {
      information.push_back(word);
    }

    Author *authorOfBook = findAuthorById(stoi(information[2].c_str()));
    Book book(stoi(information[0].c_str()), information[1], authorOfBook, information[3]);
    books_.push_back(book);
  }
  books = books_;
  setReviewsForBooks();
}

void GoodReads ::readAuthorFile(string directoryName, string fileName)
{
  string word, line;
  vector<Author> authors_;
  string path = generateFilePath(directoryName, fileName);
  ifstream inputFile(path);
  if (!inputFile)
    cout << OPENING_FILE_ERROR << endl;
  stringstream fileInfo;
  fileInfo << inputFile.rdbuf();
  getline(fileInfo, line);
  while (getline(fileInfo, line))
  {
    stringstream lineInfo(line);
    vector<string> information;
    while (getline(lineInfo, word, FILE_SEPERATOR))
    {
      information.push_back(word);
    }

    stringstream genre(information[6]);
    vector<string> genres;
    while (getline(genre, word, ID_SEPERATOR))
    {
      genres.push_back(word);
    }
    Author author(stoi(information[0].c_str()), information[1], information[2], information[3], stoi(information[4].c_str()), information[5], genres);
    authors_.push_back(author);
  }

  authors = authors_;
}

void GoodReads::readUserFile(string directoryName, string fileName)
{
  string word, line;
  vector<User> users_;
  string path = generateFilePath(directoryName, fileName);
  ifstream inputFile(path);
  if (!inputFile)
    cout << OPENING_FILE_ERROR << endl;
  stringstream fileInfo;
  fileInfo << inputFile.rdbuf();
  getline(fileInfo, line);
  while (getline(fileInfo, line))
  {
    stringstream lineInfo(line);
    vector<string> information;
    while (getline(lineInfo, word, FILE_SEPERATOR))
    {
      information.push_back(word);
    }

    vector<int> authorId = splitIds(information[4]);

    stringstream genre(information[5]);
    vector<string> genres;
    while (getline(genre, word, ID_SEPERATOR))
    {
      genres.push_back(word);
    }
    vector<int> wantToRead_ = splitIds(information[6]);
    vector<Book *> wantToRead = setTypeShelf(wantToRead_);

    vector<int> currentlyReading_ = splitIds(information[7]);
    vector<Book *> currentlyReading = setTypeShelf(currentlyReading_);

    vector<int> read_ = splitIds(information[8]);
    vector<Book *> read = setTypeShelf(read_);

    User user(stoi(information[0].c_str()), information[1], information[2], information[3], authorId, genres, wantToRead, currentlyReading, read);
    users_.push_back(user);
  }
  users = users_;
  setReviewsForUser();
}

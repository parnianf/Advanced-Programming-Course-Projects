#ifndef GOODREADS_H
#define GOODREADS_H "GOODREADS_H"

#include "User.hpp"
#include "Book.hpp"
#include "Review.hpp"
#include "Author.hpp"
#include "functions.hpp"

#define GENRES_SEPERATOR ','
#define FILE_SEPERATOR ','
#define ID_SEPERATOR '$'
#define WANT_TO_READ "want_to_read"
#define CURRENTLY_READING "currently_reading"
#define READ "read"
#define OPENING_FILE_ERROR "could not open the file"
#define AUTHOR_FILE_NAME "authors.csv"
#define REVIEWS_FILE_NAME "reviews.csv"
#define USERS_FILE_NAME "users.csv"
#define FOLLOW_EDGES_FILE_NAME "follow_edges.csv"
#define BOOKS_FILE_NAME "books.csv"
#define BOOK_SHELF_SEPERATOR "***"
#define BOOK_IN_FAVORITE_GENRE_SCORE 5
#define FOLLOWING_SELECTED_BOOKS_RANGE 3

typedef std::vector<Book> BookTable;
typedef std::vector<Review> ReviewTable;
class GoodReads
{

public:
  void readFiles(std::string directoryName);
  void readUserFile(std::string directoryName, std::string fileName);
  void readAuthorFile(std::string directoryName, std::string fileName);
  void readBookFile(std::string directoryName, std::string fileName);
  void readReviewsFile(std::string directoryName, std::string fileName);
  void setReviewsForBooks();
  void setReviewsForUser();
  void showTheBestBook();
  double getUserCredit(int id);
  void showTheBestReviewer();
  double getRate(Book *book);
  double getScore(User *user, Book *book);
  void recommendBook(int id);
  std::vector<User *> getAllFollowingsForUser(int id);
  void makeFollowingList(std::vector<User *> &userFollowings, std::vector<User *> followingForEachUser);
  void recommendSecondApproach(int id);
  Book *findTheMostRepeatedBook(std::vector<int> selectedBooksId);
  int countTotalNumberOfLikes();
  void showAuthorInfo(int id);
  void showSortedShelf(int id, std::string genre, std::string type);
  BookTable findTypeBooksByUserId(User *user, std::string type);
  std::vector<Book *> setTypeShelf(std::vector<int> shelfType);
  void readFollowEdgesFile(std::string directoryName, std::string fileName);

private:
  User *findUserById(int id);
  Book *findBookById(int id);
  Author *findAuthorById(int id);

  std::vector<Author> authors;
  std::vector<User> users;
  ReviewTable reviews;
  BookTable books;
};
#endif
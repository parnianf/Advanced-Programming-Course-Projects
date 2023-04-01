#include "User.hpp"
#include "Review.hpp"
#include <iostream>
#include <sstream>
using namespace std;
enum type
{
    eWantToRead,
    eCurrentlyReading,
    eRead
};

User::User(int id_, string name_, string placeOfBirth_, string memberSince_, vector<int> favoriteAuthorsId_, vector<string> favoriteGenres_,
           vector<Book *> wantToRead_, vector<Book *> currentlyReading_, vector<Book *> read_)
{
    id = id_;
    name = name_;
    placeOfBirth = placeOfBirth_;
    memberSince = memberSince_;
    wantToRead = wantToRead_;
    currentlyReading = currentlyReading_;
    read = read_;
    favoriteAuthorsId = favoriteAuthorsId_;
    favoriteGenres = favoriteGenres_;
}

void User::setReviews(vector<Review *> reviews_)
{
    reviews = reviews_;
}

int User::getId() { return id; }
string User::getName() { return name; }

string User::userInfoToString()
{
    stringstream userInfo;
    userInfo << "id: " << id << endl;
    userInfo << "Name: " << name << endl;
    userInfo << "Place of Birth: " << placeOfBirth << endl;
    userInfo << "Member Since: " << memberSince << endl;
    userInfo << "Favorite Genres: ";
    for (int index = 0; index < favoriteGenres.size(); index++)
    {
        userInfo << favoriteGenres[index];
        if (index < favoriteGenres.size() - 1)
        {
            userInfo << ", ";
        }
    }
    userInfo << endl;
    return userInfo.str();
}
string User::shelfInfoTostring()
{
    stringstream shelfInfo;
    shelfInfo << "Number of Books in Read Shelf: " << read.size() << endl;
    shelfInfo << "Number of Books in Want to Read Shelf: " << wantToRead.size() << endl;
    shelfInfo << "Number of Books in Currently Reading Shelf: " << currentlyReading.size() << endl;
    shelfInfo << "Number of Likes: " << countUserReviewLike() << endl;
    return shelfInfo.str();
}

vector<Book *> User::getTypeList(int choice)
{
    switch (choice)
    {
    case eWantToRead:
        return wantToRead;
    case eCurrentlyReading:
        return currentlyReading;
    case eRead:
        return read;
    }
}

multiset<Book> User::sortingBooksInOrder(const BookTable typeBooks)
{
    multiset<Book> sortedBooks;
    for (auto &book : typeBooks)
    {
        sortedBooks.insert(book);
    }
    return sortedBooks;
}

int User::countUserReviewLike()
{
    int numberOfLikes = 0;
    for (int i = 0; i < reviews.size(); i++)
    {
        numberOfLikes += reviews[i]->getNumberOfLikes();
    }

    return numberOfLikes;
}

void User::setFollowingId(vector<User *> followings_)
{
    followings = followings_;
}
int User::countUserReviews() { return reviews.size(); }
vector<int> User::getFavoriteAuthorsId() { return favoriteAuthorsId; }
Genres User::getFavoriteGenres() { return favoriteGenres; }
vector<User *> User::getFollowings() { return followings; }

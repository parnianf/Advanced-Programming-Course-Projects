#ifndef USER_H
#define USER_H "USER_H"

#include "Book.hpp"
#include <set>
typedef std::vector<std::string> Genres;
typedef std::vector<Book> BookTable;
class Review;

class User
{

public:
  User(int id_, std::string name_, std::string placeOfBirth_, std::string memberSince_, std::vector<int> favoriteAuthorsId_, std::vector<std::string> favoriteGenres_,
       std::vector<Book *> wantToRead_, std::vector<Book *> currentlyReading_, std::vector<Book *> read_);
  void setReviews(std::vector<Review *> reviews_);
  int getId();
  std::string getName();
  std::string userInfoToString();
  std::string shelfInfoTostring();
  std::vector<Book *> getTypeList(int choice);
  std::multiset<Book> sortingBooksInOrder(const BookTable typeBooks);
  int countUserReviewLike();
  void setFollowingId(std::vector<User *> followings_);
  int countUserReviews();
  std::vector<int> getFavoriteAuthorsId();
  Genres getFavoriteGenres();
  std::vector<User *> getFollowings();

private:
  int id;
  std::vector<int> favoriteAuthorsId;
  std::string placeOfBirth, name, memberSince;
  Genres favoriteGenres;
  std::vector<Book *> wantToRead;
  std::vector<Book *> currentlyReading;
  std::vector<Book *> read;
  std::vector<Review *> reviews;
  std::vector<User *> followings;
};
#endif
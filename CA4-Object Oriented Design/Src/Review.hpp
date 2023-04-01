#ifndef REVIEW_H
#define REVIEW_H "REVIEW_H"

#include <string>

class Review
{
public:
  Review(int id_, int bookId_, int userId_, double rating_, std::string date_, int numberOfLikes_);
  std::string toString();
  int getNumberOfLikes();
  int getUserId();
  int getBookId();
  int getRating();

private:
  int id, numberOfLikes;
  double rating;
  std::string date;
  int userId, bookId;
};

#endif
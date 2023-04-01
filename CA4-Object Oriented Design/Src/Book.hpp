#ifndef BOOK_H
#define BOOK_H "BOOK_H"

#include <string>
#include <vector>

class Author;
class Review;
class Book

{
public:
    Book(int id_, std::string title_, Author *author_, std::string genre_);
    int getAuthorId();
    int getId();
    std::string getName();
    std::string getGenre();
    std::vector<Review *> getReview();
    double getRating();
    void setReviews(std::vector<Review *> reviews_);
    std::string toString(int type);
    double getAverageRating();
    bool operator<(const Book &book) const;
    void setRating(double rate_);

private:
    int id;
    double rate;
    Author *author;
    std::string title, genre;
    std::vector<Review *> reviews;
};
#endif
#include "Book.hpp"
#include "Author.hpp"
#include "Review.hpp"
#include <sstream>
using namespace std;

Book::Book(int id_, string title_, Author *author_, string genre_)
{
    id = id_;
    title = title_;
    author = author_;
    genre = genre_;
}

int Book::getAuthorId() { return author->getId(); }
int Book::getId() { return id; }
string Book::getName() { return title; }
string Book::getGenre() { return genre; }
vector<Review *> Book::getReview() { return reviews; }
double Book::getRating() { return rate; }

void Book::setReviews(vector<Review *> reviews_)
{
    reviews = reviews_;
}

string Book::toString(int type = 1)
{
    stringstream bookInfo;
    switch (type)
    {
    case 1:
        bookInfo << "id: " << id << " "
                 << "Title: " << title << endl;
        break;
    case 2:
        bookInfo << "id: " << id << endl;
        bookInfo << "Title: " << title << endl;
        bookInfo << "Genre: " << genre << endl;
        bookInfo << "Author: " << author->getName() << endl;
    }
    return bookInfo.str();
}

double Book::getAverageRating()
{
    double averageRating = 0;
    for (int i = 0; i < reviews.size(); i++)
    {
        averageRating += reviews[i]->getRating();
    }
    return (averageRating / (double)reviews.size());
}

bool Book::operator<(const Book &book) const
{
    if (title == book.title)
    {
        return (id < book.id);
    }
    return (title < book.title);
}

void Book::setRating(double rate_)
{
    rate = rate_;
}
#include "Review.hpp"
#include <sstream>
using namespace std;

Review::Review(int id_, int bookId_, int userId_, double rating_, string date_, int numberOfLikes_)
{
    id = id_;
    bookId = bookId_;
    userId = userId_;
    rating = rating_;
    date = date_;
    numberOfLikes = numberOfLikes_;
}

string Review::toString()
{
    stringstream reviewOutput;
    reviewOutput << "id: " << id << " Rating: " << rating << " Likes: " << numberOfLikes << " Date: " << date << endl;
    return reviewOutput.str();
}
int Review::getNumberOfLikes() { return numberOfLikes; }
int Review::getUserId() { return userId; }
int Review::getBookId() { return bookId; }
int Review::getRating() { return rating; }

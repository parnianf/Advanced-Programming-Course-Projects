#ifndef AUTHOR_H
#define AUTHOR_H "AUTHOR_H"
#include <vector>
#include <string>

typedef std::vector<std::string> Genres;

class Author
{
public:
  Author(int id_, std::string name_, std::string gender_, std::string memberSince_, int yearOfBirth_, std::string placeOfBirth_,
         std::vector<std::string> genre_);
  int getId();
  std::string getName();
  std::string toString();

private:
  int id, yearOfBirth;
  std::string name, placeOfBirth, gender, memberSince;
  Genres genres;
};
#endif
#include "Author.hpp"
// #include<iostream>
#include <sstream>
#include <algorithm>
using namespace std;

#define GENRES_SEPERATOR ','

Author::Author(int id_, string name_, string gender_, string memberSince_, int yearOfBirth_, string placeOfBirth_, vector<string> genre_)
{
  id = id_;
  name = name_;
  gender = gender_;
  yearOfBirth = yearOfBirth_;
  placeOfBirth = placeOfBirth_;
  memberSince = memberSince_;
  genres = genre_;
}

int Author::getId() { return id; }

string Author::getName() { return name; }

string Author::toString()
{

  stringstream authorInfo;
  authorInfo << "id: " << id << endl;
  authorInfo << "Name: " << name << endl;
  authorInfo << "Year of Birth: " << yearOfBirth << endl;
  authorInfo << "Place of Birth: " << placeOfBirth << endl;
  authorInfo << "Member Since: " << memberSince << endl;
  authorInfo << "Genres: ";
  sort(genres.begin(), genres.end());
  for (int index = 0; index < genres.size(); index++)
  {
    authorInfo << genres[index];
    if (index < genres.size() - 1)
    {
      authorInfo << GENRES_SEPERATOR << ' ';
    }
  }
  authorInfo << endl
             << "Books:" << endl;
  return authorInfo.str();
}

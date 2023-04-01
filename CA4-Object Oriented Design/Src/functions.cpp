#include "functions.hpp"
#include "GoodReads.hpp"
#include "Book.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

bool sortByaverageRating(Book a, Book b)
{
  if (a.getAverageRating() == b.getAverageRating())
  {
    return (a.getId() > b.getId());
  }
  return (a.getAverageRating() > b.getAverageRating());
}
bool sortingScoreAndBook(const pair<double, int> &a, const pair<double, int> &b)
{
  if (a.first == b.first)
  {
    return (a.second < b.second);
  }
  return (a.first > b.first);
}

bool sortingVectorOfPair(const pair<int, int> &a, const pair<int, int> &b)
{
  if (a.first == b.first)
  {
    return (a.second < b.second);
  }
  return (a.first > b.first);
}

void doCommand(GoodReads &allInfo)
{

  string command, shelfType, genre;
  int id;

  while (cin >> command)
  {

    if (command == SHOW_AUTHOR_INFO)
    {
      cin >> id;
      allInfo.showAuthorInfo(id);
    }

    else if (command == SHOW_SORTED_SHELF)
    {
      cin >> id >> shelfType;
      string genre;
      getline(cin, genre);
      genre = genre.substr(1);
      allInfo.showSortedShelf(id, genre, shelfType);
    }
    else if (command == CREDIT)
    {
      cin >> id;
      double credit = allInfo.getUserCredit(id);
      cout << fixed << setprecision(6) << credit << endl;
    }
    else if (command == BEST_BOOK)
    {
      allInfo.showTheBestBook();
    }
    else if (command == BEST_REVIEWER)
    {
      allInfo.showTheBestReviewer();
    }
    else if (command == RECOMMEND_FIRST_APPROACH)
    {
      cin >> id;
      allInfo.recommendBook(id);
    }
    else if (command == RECOMMEND_SECOND_APPROACH)
    {
      cin >> id;
      allInfo.recommendSecondApproach(id);
    }
  }
}

string generateFilePath(string directoryName, string fileName)
{
  stringstream path;
  path << directoryName << '/' << fileName;
  return path.str();
}

vector<int> splitIds(string listOfId)
{
  vector<int> dividedIds;
  stringstream id(listOfId);
  string word;
  while (getline(id, word, ID_SEPERATOR))
  {
    dividedIds.push_back(stoi(word.c_str()));
  }
  return dividedIds;
}
#ifndef FUNCTIONS_H
#define FUNCTIONS_H "FUNCTIONS_H"

#include <vector>
#include <string>

#define SHOW_AUTHOR_INFO "show_author_info"
#define SHOW_SORTED_SHELF "show_sorted_shelf"
#define CREDIT "credit"
#define BEST_BOOK "best_book"
#define BEST_REVIEWER "best_reviewer"
#define RECOMMEND_FIRST_APPROACH "recommend_first_approach"
#define RECOMMEND_SECOND_APPROACH "recommend_second_approach"

class Book;
class GoodReads;

bool sortByaverageRating(Book a, Book b);
bool sortingVectorOfPair(const std::pair<int, int> &a, const std::pair<int, int> &b);
bool sortingScoreAndBook(const std::pair<double, int> &a, const std::pair<double, int> &b);
void doCommand(GoodReads &allInfo);
std::string generateFilePath(std::string directoryName, std::string fileName);
std::vector<int> splitIds(std::string listOfId);
#endif
#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<vector>
#include<map>

using namespace std;

#define SEPARATING_VALUES_SIGN ','
#define SEPARATING_HOUR_SIGN ':'
#define ERROR_IN_FINDING "COULD NOT FIND!"
#define COURSE_FILE_ARGUMENT 1
#define GRADES_FILE_ARGUMENT 2
#define ORIGIN_HOUR 5
#define BASE_GPA 17
#define MAX_UNITS_UNDER_BASE_GPA 20
#define MAX_UNITS_UPPER_BASE_GPA 24
#define FAILURE_GRADE_UNDER 10

struct Time {
	int h, m;
};

struct Schedule {
	string Day;
	Time Begin;
	Time End;
};

typedef vector<Schedule> ScheduleTable;
typedef vector<int> Prerequisites;

struct Course {
	int id;
	string name;
	int units;
	ScheduleTable listOFSchedules;
	Prerequisites prerequisites;
};


typedef vector<Course> CourseTable;
typedef map<int, float> gradeTable_t;
typedef map<string, int> courseNamesTable_t;
typedef vector<int> inOrderIds_t;
typedef multimap<int, float> unitsTable_t;
typedef float GPA_t;
typedef struct Course course_t;
typedef void output_t;
typedef int minute_t;
typedef string fileName_t;


unitsTable_t pairingUnitsAndGrade(CourseTable courses, fileName_t inputFileName);
gradeTable_t storingGrades(fileName_t fileName);
CourseTable readCourseInfo(fileName_t inputFileName);
CourseTable findTakeableCourses(CourseTable courses, gradeTable_t gradeMap);
CourseTable getIdGiveCourse(CourseTable courses, inOrderIds_t sortedCoursesId);
CourseTable getSuggestedCourses(CourseTable takeableCourses, GPA_t GPA);
courseNamesTable_t mapingNameAndId(CourseTable courses);
inOrderIds_t sortingCorsesIdInOrder(CourseTable takeableCourses);
GPA_t calculateGPA(CourseTable courses, fileName_t inputFileName);
output_t generateOutput(CourseTable takeableCourses);
output_t printingTakeableCourses(map<string, int> nameAndId);
minute_t timeToMinuteFromOrigin(int hour, int minute);
int countNumberOfLines(string inputFileName);
int giveNameGetUits(CourseTable courses, string name);
int giveIdGetUnits(CourseTable courses, int id);
int getMaximumNumbersOfUnits(GPA_t GPA);
vector<int> failedCourses(gradeTable_t gradeMap);
void makingSchedule(course_t &temp, ifstream& inputFile);
void makingPrerequisites(course_t &temp, ifstream& inputFile);
bool isPassTheCourse(int grade);
bool doesOverlapTime(course_t course1, course_t course2, int i, int k);
bool doesOverlapCourse(CourseTable acceptedCourses, course_t course);
bool hasTakenAndFailed(course_t course, gradeTable_t gradeMap);
bool hasTakenAllPrerequisitesCourses(course_t course, gradeTable_t gradeMap);
bool hasNotTakenTheCourseAndHasPrereq(course_t course, gradeTable_t gradeMap);
bool hasTakenThatCourse(gradeTable_t gradeMap, int id);
bool hasTakenThatCourse(gradeTable_t gradeMap, course_t course);
bool hasFailedTheCourse(course_t course, map<int, float> gradeMap);
bool doesNotNeedprerequisitesAndHasNotTaken(course_t course, gradeTable_t gradeMap);

int main(int argc, char* argv[]) {
	CourseTable allCourses, takeableCourses, suggestedCourse;
	allCourses = readCourseInfo(argv[COURSE_FILE_ARGUMENT]);
	gradeTable_t gradeMap = storingGrades(argv[GRADES_FILE_ARGUMENT]);
	takeableCourses = findTakeableCourses(allCourses, gradeMap);
	GPA_t GPA = calculateGPA(allCourses, argv[GRADES_FILE_ARGUMENT]);
	suggestedCourse = getSuggestedCourses(takeableCourses, GPA);
	generateOutput(suggestedCourse);
}

void printingTakeableCourses(map<string, int> nameAndId) {
	for (auto it : nameAndId)
		cout << it.second << endl;
}

void generateOutput(CourseTable takeableCourses) {
	map<string, int> nameAndId;
	nameAndId = mapingNameAndId(takeableCourses);
	printingTakeableCourses(nameAndId);

}

courseNamesTable_t mapingNameAndId(CourseTable courses) {
	courseNamesTable_t nameAndId;
	for (int i = 0; i < courses.size(); i++) {
		nameAndId[courses[i].name] = courses[i].id;
	}
	return nameAndId;
}

int getMaximumNumbersOfUnits(GPA_t GPA) {
	if (GPA >= BASE_GPA)
		return MAX_UNITS_UPPER_BASE_GPA;
	return MAX_UNITS_UNDER_BASE_GPA;
}

minute_t timeToMinuteFromOrigin(int hour, int minute) {
	return (((hour - ORIGIN_HOUR) * 60) + minute);
}

bool doesOverlapCourse(CourseTable sortedCourses, course_t course) {
	for (int i = 0; i < (course.listOFSchedules).size(); i++) {
		for (int j = 0; j < sortedCourses.size(); j++) {
			for (int k = 0; k < sortedCourses[j].listOFSchedules.size(); k++) {
				if (course.listOFSchedules[i].Day == sortedCourses[j].listOFSchedules[k].Day) {
					if (doesOverlapTime(course, sortedCourses[j], i, k))
						return true;
				}
			}
		}
	}
	return false;
}


bool doesOverlapTime(course_t course, course_t acceptedCourse, int i, int k) {

	if (((timeToMinuteFromOrigin(course.listOFSchedules[i].Begin.h, course.listOFSchedules[i].Begin.m) >=
		timeToMinuteFromOrigin(acceptedCourse.listOFSchedules[k].Begin.h, acceptedCourse.listOFSchedules[k].Begin.m)) &&
		(timeToMinuteFromOrigin(course.listOFSchedules[i].Begin.h, course.listOFSchedules[i].Begin.m) <
		(timeToMinuteFromOrigin(acceptedCourse.listOFSchedules[k].End.h, acceptedCourse.listOFSchedules[k].End.m)))) ||
			((timeToMinuteFromOrigin(acceptedCourse.listOFSchedules[k].Begin.h, acceptedCourse.listOFSchedules[k].Begin.m) >=
				timeToMinuteFromOrigin(course.listOFSchedules[i].Begin.h, course.listOFSchedules[i].Begin.m)) &&
				(timeToMinuteFromOrigin(acceptedCourse.listOFSchedules[k].Begin.h, acceptedCourse.listOFSchedules[k].Begin.m) <
					timeToMinuteFromOrigin(course.listOFSchedules[i].End.h, course.listOFSchedules[i].End.m)))) {
		return true;
	}
	return false;

}

CourseTable getIdGiveCourse(CourseTable courses, vector<int> sortedCoursesId) {
	CourseTable sortedCourses;
	for (int i = 0; i<sortedCoursesId.size(); i++) {
		for (int j = 0; j<courses.size(); j++) {
			if (sortedCoursesId[i] == courses[j].id) {
				sortedCourses.push_back(courses[j]);
			}
		}

	}
	return sortedCourses;
}

CourseTable getSuggestedCourses(CourseTable takeableCourses, GPA_t GPA) {
	inOrderIds_t sortedCoursesId = sortingCorsesIdInOrder(takeableCourses);
	vector<int>idListOfSuggestedCourses;
	CourseTable listOfSuggestedCourses = getIdGiveCourse(takeableCourses, sortedCoursesId);
	CourseTable sortedCourses;
	int numberOfUnits = 0;
	for (int i = 0; i < listOfSuggestedCourses.size(); i++) {

		if (!doesOverlapCourse(sortedCourses, listOfSuggestedCourses[i])) {
			if ((numberOfUnits + listOfSuggestedCourses[i].units) > getMaximumNumbersOfUnits(GPA)) {
				break;
			}
			sortedCourses.push_back(listOfSuggestedCourses[i]);
			numberOfUnits += listOfSuggestedCourses[i].units;
		}
	}
	return sortedCourses;
}

inOrderIds_t sortingCorsesIdInOrder(CourseTable takeableCourses) {
	vector<int> gettingSorted;
	multimap<int, int, greater<int> > unitsAndId;
	map<string, int> nameAndId;
	map<int, int, greater<int>> rangeOfUnits;
	CourseTable sortedCoursesInOrder;
	for (int i = 0; i < takeableCourses.size(); i++) {
		unitsAndId.insert(pair <int, int>(takeableCourses[i].units, takeableCourses[i].id));
	}

	for (auto it : unitsAndId) {
		rangeOfUnits[it.first] = it.second;
	}

	for (auto it : rangeOfUnits) {
		if (unitsAndId.count(it.first) > 1) {
			for (int i = 0; i < takeableCourses.size(); i++) {
				if (it.first == takeableCourses[i].units) {
					nameAndId[takeableCourses[i].name] = takeableCourses[i].id;
				}
			}
		}
	}
	for (auto it : rangeOfUnits) {
		if (unitsAndId.count(it.first) > 1) {
			for (auto itNI : nameAndId) {
				if (giveNameGetUits(takeableCourses, itNI.first) == it.first) {
					gettingSorted.push_back(itNI.second);
				}
			}
		}
		else {
			gettingSorted.push_back(it.second);
		}
	}


	return gettingSorted;
}

int giveNameGetUits(CourseTable courses, string name) {

	for (int i = 0; i < courses.size(); i++) {
		if (courses[i].name == name)
			return (courses[i].units);
	}
	cout << ERROR_IN_FINDING << endl;
	return 0;

}

GPA_t calculateGPA(CourseTable courses, fileName_t inputFileName) {
	unitsTable_t gradeAndUnits = pairingUnitsAndGrade(courses, inputFileName);
	float GPA = 0;
	int totalUnits = 0;
	for (auto it : gradeAndUnits) {
		GPA += (it.first * it.second);
	}
	for (auto it : gradeAndUnits) {
		totalUnits += (it.first);
	}
	return(GPA / totalUnits);

}


unitsTable_t pairingUnitsAndGrade(CourseTable courses, fileName_t inputFileName) {
	gradeTable_t gradesMap = storingGrades(inputFileName);

	unitsTable_t unitsAndGradesMap;
	for (auto it : gradesMap) {
		unitsAndGradesMap.insert(pair <int, float>(giveIdGetUnits(courses, it.first), it.second));
	}
	return unitsAndGradesMap;
}

int giveIdGetUnits(CourseTable courses, int id) {
	for (int i = 0; i < courses.size(); i++) {
		if (courses[i].id == id) {
			return (courses[i].units);
		}
	}
	cout << ERROR_IN_FINDING << endl;
	return 0;
}


int countNumberOfLines(fileName_t inputFileName) {
	ifstream inputFile(inputFileName);
	return (count(istreambuf_iterator<char>(inputFile), istreambuf_iterator<char>(), '\n'));
}

CourseTable readCourseInfo(string inputFileName) {
	CourseTable listOFCourses;
	ifstream inputFile(inputFileName);
	string dd;
	int id;
	getline(inputFile, dd);
	int i = 1;
	while (i < countNumberOfLines(inputFileName)) {
		struct Course dars1;
		int  units;
		string name, day;
		char separatingValueSign = SEPARATING_VALUES_SIGN;
		inputFile >> id >> separatingValueSign;
		dars1.id = id;
		getline(inputFile, name, separatingValueSign);
		dars1.name = name;
		inputFile >> units >> separatingValueSign;
		dars1.units = units;
		makingSchedule(dars1, inputFile);
		inputFile >> separatingValueSign;
		makingPrerequisites(dars1, inputFile);
		listOFCourses.push_back(dars1);
		i++;
	}
	return listOFCourses;
}

void makingSchedule(course_t &temp, ifstream& inputFile) {

	ScheduleTable tempScheduleList;
	char end;
	while (1) {
		struct Schedule tempSchedule;
		string day;
		int beginHour, beginMinute, endHour, endMinute, pre;
		char endOFLine, separatingHourSign = SEPARATING_HOUR_SIGN, separatingValueSign = SEPARATING_VALUES_SIGN;
		getline(inputFile, day, '-');
		tempSchedule.Day = day;
		inputFile >> beginHour >> separatingHourSign >> beginMinute >> separatingValueSign >> endHour >> separatingHourSign >> endMinute;
		tempSchedule.Begin.h = beginHour;
		tempSchedule.Begin.m = beginMinute;
		tempSchedule.End.h = endHour;
		tempSchedule.End.m = endMinute;
		tempScheduleList.push_back(tempSchedule);
		temp.listOFSchedules = tempScheduleList;
		endOFLine = inputFile.peek();
		if (endOFLine == SEPARATING_VALUES_SIGN)
			break;
		inputFile >> endOFLine;

	}
}

void makingPrerequisites(course_t &temp, ifstream& inputFile) {
	Prerequisites tempPrerequisites;
	int pre;
	char endLine;
	while (1) {
		inputFile >> pre;
		temp.prerequisites.push_back(pre);
		endLine = inputFile.peek();
		if (endLine == '\n')
			break;
		inputFile >> endLine;
	}
}

gradeTable_t storingGrades(fileName_t inputFileName) {
	ifstream inputFile(inputFileName);
	string firstLine;
	int id;
	char separatingValueSign = SEPARATING_VALUES_SIGN;
	float grade;
	getline(inputFile, firstLine);
	gradeTable_t gradeMap;
	while (inputFile.good()) {
		inputFile >> id >> separatingValueSign >> grade;
		gradeMap[id] = grade;
	}
	return gradeMap;
}

CourseTable findTakeableCourses(CourseTable courses, gradeTable_t gradeMap) {
	CourseTable takeableCoursesList;
	for (int i = 0; i<courses.size(); i++) {
		if (hasTakenAndFailed(courses[i], gradeMap))
			takeableCoursesList.push_back(courses[i]);
		if (hasNotTakenTheCourseAndHasPrereq(courses[i], gradeMap))
			takeableCoursesList.push_back(courses[i]);
		if (doesNotNeedprerequisitesAndHasNotTaken(courses[i], gradeMap)) {
			takeableCoursesList.push_back(courses[i]);
		}
	}
	return takeableCoursesList;
}

bool doesNotNeedprerequisitesAndHasNotTaken(course_t course, gradeTable_t gradeMap) {
	if ((course.prerequisites[0] == 0) && (!hasTakenThatCourse(gradeMap, course)))
		return true;
	return false;
}

vector<int> failedCourses(map<int, float> gradeMap) {
	vector<int> failedCoursesId;
	for (auto it : gradeMap) {
		if (!isPassTheCourse(it.second))
			failedCoursesId.push_back(it.first);
	}
	return failedCoursesId;
}

bool isPassTheCourse(int grade) {
	if (grade<FAILURE_GRADE_UNDER)
		return false;
	return true;
}

bool hasTakenAllPrerequisitesCourses(course_t course, gradeTable_t gradeMap) {

	for (int i = 0; i < course.prerequisites.size(); i++) {
		if (!hasTakenThatCourse(gradeMap, course.prerequisites[i])) {
			return false;
		}
	}
	for (int i = 0; i<course.prerequisites.size(); i++) {
		if (!isPassTheCourse(gradeMap[course.prerequisites[i]]))
			return false;
	}
	return true;
}

bool hasTakenThatCourse(gradeTable_t gradeMap, int id) {
	for (auto it : gradeMap) {
		if (id == it.first)
			return true;
	}
	return false;
}

bool hasTakenThatCourse(gradeTable_t gradeMap, course_t course) {
	for (auto it : gradeMap) {
		if (course.id == it.first)
			return true;
	}
	return false;
}

bool hasTakenAndFailed(course_t course, gradeTable_t gradeMap) {
	if (hasTakenThatCourse(gradeMap, course) && hasFailedTheCourse(course, gradeMap))
		return true;
	return false;
}

bool hasFailedTheCourse(course_t course, gradeTable_t gradeMap) {
	vector<int> failedCoursesId = failedCourses(gradeMap);
	for (int i = 0; i < failedCoursesId.size(); i++) {
		if (course.id == failedCoursesId[i])
			return true;
	}
	return false;
}

bool hasNotTakenTheCourseAndHasPrereq(course_t course, gradeTable_t gradeMap) {
	if (!(hasTakenThatCourse(gradeMap, course)) && hasTakenAllPrerequisitesCourses(course, gradeMap))
		return true;
	return false;
}

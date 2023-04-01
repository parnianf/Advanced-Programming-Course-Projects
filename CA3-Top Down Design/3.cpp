#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<vector>
#include<map>
#include<sstream>

using namespace std;

#define SEPARATING_VALUES_SIGN ','
#define SEPARATING_HOUR_SIGN ':'
#define FILE_NAME "semester"
#define FILE_EXTENSION ".sched"
#define ERROR_IN_FINDING "COULD NOT FIND!"
#define INCREASE_GPA_PERCENT 5
#define FILE_NUMBER_START 1
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
typedef vector<int> idList_t;
typedef multimap<int, float> unitsTable_t;
typedef float GPA_t;
typedef struct Course course_t;
typedef void output_t;
typedef int minute_t;
typedef string fileName_t;


unitsTable_t pairingUnitsAndGrade(CourseTable courses, fileName_t inputFileName);
gradeTable_t updatingGradingMap(CourseTable takenCourses);
gradeTable_t storingGrades(fileName_t fileName);
CourseTable readCourseInfo(fileName_t inputFileName);
CourseTable findTakeableCourses(CourseTable courses, gradeTable_t gradeMap);
CourseTable getIdGiveCourse(CourseTable courses, inOrderIds_t sortedCoursesId);
CourseTable getSuggestedCourses(CourseTable takeableCourses, GPA_t GPA, CourseTable& takenCoursesUntilNow);
CourseTable updatingTakeableCourses(CourseTable takeableCoursesBefore, CourseTable suggestedCoursesForThisSemester);
CourseTable findTakeableCoursesForEachSemester(CourseTable courses, gradeTable_t gradeMap);
courseNamesTable_t mapingNameAndId(CourseTable courses);
inOrderIds_t sortingCorsesIdInOrder(CourseTable takeableCourses);
idList_t giveCoursesGetId(CourseTable courses);
GPA_t calculateGPA(CourseTable courses, fileName_t inputFileName);
GPA_t estimateGPAForEachSemester(GPA_t currentGPA);
output_t writeOnFile(courseNamesTable_t nameAndId, fileName_t outputFilename);
output_t generateOutput(CourseTable takeableCourses, fileName_t outputFilename);
course_t getIdGiveCourse(CourseTable courses, int courseId);
minute_t timeToMinuteFromOrigin(int hour, int minute);
int countNumberOfLines(string inputFileName);
int giveNameGetUits(CourseTable courses, string name);
int giveIdGetUnits(CourseTable courses, int id);
int getMaximumNumbersOfUnits(GPA_t GPA);
fileName_t generateNameOfOutput(int semesterNumber);
vector<int> failedCourses(gradeTable_t gradeMap);
void makeSuggestedCoursesForEachSemester(CourseTable courses, gradeTable_t gradeMap, GPA_t GPA);
void makingSchedule(course_t &temp, ifstream& inputFile);
void makingPrerequisites(course_t &temp, ifstream& inputFile);
bool isPassTheCourse(float grade);
bool doesOverlapTime(course_t course1, course_t course2, int i, int k);
bool doesOverlapCourse(CourseTable acceptedCourses, course_t course);
bool hasTakenAndFailed(course_t course, gradeTable_t gradeMap);
bool hasTakenAllPrerequisitesCourses(course_t course, gradeTable_t gradeMap,bool isFailurePossible);
bool hasNotTakenTheCourseAndHasPrereq(course_t course, gradeTable_t gradeMap,bool isFailurePossible);
bool hasTakenThatCourse(gradeTable_t gradeMap, int id);
bool hasTakenThatCourse(gradeTable_t gradeMap, course_t course);
bool hasFailedTheCourse(course_t course, map<int, float> gradeMap);
bool doesNotNeedprerequisitesAndHasNotTaken(course_t course, gradeTable_t gradeMap);


int main(int argc, char* argv[]) {
	CourseTable allCourses = readCourseInfo(argv[COURSE_FILE_ARGUMENT]);
	gradeTable_t gradeMap = storingGrades(argv[GRADES_FILE_ARGUMENT]);
	GPA_t GPA = calculateGPA(allCourses, argv[GRADES_FILE_ARGUMENT]);
	makeSuggestedCoursesForEachSemester(allCourses, gradeMap, GPA);
}

CourseTable findTakeableCoursesForEachSemester(CourseTable courses, gradeTable_t gradeMap) {
	CourseTable takeableCoursesList;
  bool isFailurePossible=false;
	for (int i = 0; i < courses.size(); i++) {
		if (hasTakenAllPrerequisitesCourses(courses[i], gradeMap,isFailurePossible))
			takeableCoursesList.push_back(courses[i]);
		if (doesNotNeedprerequisitesAndHasNotTaken(courses[i], gradeMap)) {
			takeableCoursesList.push_back(courses[i]);
		}
	}
	return takeableCoursesList;
}

void makeSuggestedCoursesForEachSemester(CourseTable allCourses, gradeTable_t gradeMap, GPA_t GPA) {
	CourseTable listOfSuggestedCourses, suggestedCoursesForThisSemester, remainCourses, takenCoursesUntilNow;
	CourseTable takeableCourses = findTakeableCourses(allCourses, gradeMap);
	int semesterNumber = FILE_NUMBER_START;
	for (auto it : gradeMap) {
		if (isPassTheCourse(it.second))
			takenCoursesUntilNow.push_back(getIdGiveCourse(allCourses, it.first));
	}
	while (takeableCourses.size() > 0) {
		suggestedCoursesForThisSemester = getSuggestedCourses(takeableCourses, GPA, takenCoursesUntilNow);
		GPA = estimateGPAForEachSemester(GPA);
		remainCourses = updatingTakeableCourses(allCourses, takenCoursesUntilNow);
		gradeMap = updatingGradingMap(takenCoursesUntilNow);
		takeableCourses = findTakeableCoursesForEachSemester(remainCourses, gradeMap);
		generateOutput(suggestedCoursesForThisSemester, generateNameOfOutput(semesterNumber));
		semesterNumber++;
	}
}

gradeTable_t updatingGradingMap(CourseTable takenCourses) {
	map<int, float> updatedGradingMap;
	for (int i = 0; i < takenCourses.size(); i++)
		updatedGradingMap[takenCourses[i].id] = 20;
	return updatedGradingMap;
}


fileName_t generateNameOfOutput(int semesterNumber) {
	stringstream fileName;
	fileName << FILE_NAME << semesterNumber << FILE_EXTENSION;
	return fileName.str();
}

courseNamesTable_t mapingNameAndId(CourseTable courses) {
	courseNamesTable_t nameAndId;
	for (int i = 0; i < courses.size(); i++) {
		nameAndId[courses[i].name] = courses[i].id;
	}
	return nameAndId;
}

output_t writeOnFile(courseNamesTable_t nameAndId, fileName_t outputFilename) {
	ofstream outputfile(outputFilename);
	for (auto it : nameAndId)
		outputfile << it.second << endl;
}

output_t generateOutput(CourseTable takeableCourses, fileName_t outputFilename) {
	courseNamesTable_t nameAndId;
	nameAndId = mapingNameAndId(takeableCourses);
	writeOnFile(nameAndId, outputFilename);

}

CourseTable updatingTakeableCourses(CourseTable allCoursesBefore, CourseTable takenCourses) {
	CourseTable updatedTakeableCourses;
	bool isInTakenCourses = false;
	for (int i = 0; i < allCoursesBefore.size(); i++) {
		for (int j = 0; j < takenCourses.size(); j++) {
			isInTakenCourses = false;
			if (allCoursesBefore[i].id == takenCourses[j].id) {
				isInTakenCourses = true;
				break;
			}
		}
		if (!isInTakenCourses) {
			updatedTakeableCourses.push_back(allCoursesBefore[i]);
		}
	}

	return updatedTakeableCourses;
}

vector<int> giveCoursesGetId(CourseTable courses) {
	vector<int> coursesId;
	for (int i = 0; i < courses.size(); i++) {
		coursesId.push_back(courses[i].id);
	}
	return coursesId;
}


GPA_t estimateGPAForEachSemester(float currentGPA) {
	return(currentGPA * (INCREASE_GPA_PERCENT + 100) / 100);
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

CourseTable getSuggestedCourses(CourseTable takeableCourses, GPA_t GPA, CourseTable& takenCoursesUntilNow) {
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
			takenCoursesUntilNow.push_back(getIdGiveCourse(takeableCourses, listOfSuggestedCourses[i].id));
			numberOfUnits += listOfSuggestedCourses[i].units;
		}
	}
	return sortedCourses;
}


course_t getIdGiveCourse(CourseTable courses, int courseId) {

	for (int j = 0; j < courses.size(); j++) {
		if (courseId == courses[j].id) {
			return courses[j];
		}
	}
	cout << ERROR_IN_FINDING << endl;
}

CourseTable getIdGiveCourse(CourseTable courses, idList_t sortedCoursesId) {
	CourseTable sortedCourses;
	for (int i = 0; i < sortedCoursesId.size(); i++) {
		for (int j = 0; j < courses.size(); j++) {
			if (sortedCoursesId[i] == courses[j].id) {
				sortedCourses.push_back(courses[j]);
			}
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
	char end;
	while (1) {
		inputFile >> pre;
		temp.prerequisites.push_back(pre);
		end = inputFile.peek();
		if (end == '\n')
			break;
		inputFile >> end;
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
  bool isFailurePossible = true;
	CourseTable takeableCoursesList;
	for (int i = 0; i<courses.size(); i++) {
		if (hasTakenAndFailed(courses[i], gradeMap))
			takeableCoursesList.push_back(courses[i]);
		if (hasNotTakenTheCourseAndHasPrereq(courses[i], gradeMap,isFailurePossible))
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

bool isPassTheCourse(float grade) {
	if (grade<FAILURE_GRADE_UNDER)
		return false;
	return true;
}

bool hasTakenAllPrerequisitesCourses(course_t course, gradeTable_t gradeMap,bool isFailurePossible) {
	for (int i = 0; i < course.prerequisites.size(); i++) {
		if (!hasTakenThatCourse(gradeMap, course.prerequisites[i])) {
			return false;
		}
	}
  	if(isFailurePossible){
		for (int i = 0; i<course.prerequisites.size(); i++) {
			if (!isPassTheCourse(gradeMap[course.prerequisites[i]]))
				return false;
		}
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

bool hasNotTakenTheCourseAndHasPrereq(course_t course, gradeTable_t gradeMap,bool isFailurePossible) {
	if (!(hasTakenThatCourse(gradeMap, course)) && hasTakenAllPrerequisitesCourses(course, gradeMap,isFailurePossible))
		return true;
	return false;
}

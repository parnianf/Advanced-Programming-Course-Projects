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
typedef struct Course course_t;
typedef void output_t;
typedef string fileName_t;
typedef vector<int> idList_t;


gradeTable_t storingGrades(fileName_t fileName);
CourseTable readCourseInfo(fileName_t inputFileName);
CourseTable findTakeableCourses(CourseTable courses, gradeTable_t gradeMap);
courseNamesTable_t mapingNameAndId(CourseTable courses);
int countNumberOfLines(string inputFileName);
vector<int> failedCourses(gradeTable_t gradeMap);
void makingSchedule(course_t &temp, ifstream& inputFile);
void makingPrerequisites(course_t &temp, ifstream& inputFile);
bool isPassTheCourse(float grade);
bool hasTakenAndFailed(course_t course, gradeTable_t gradeMap);
bool hasTakenAllPrerequisitesCourses(course_t course, gradeTable_t gradeMap);
bool hasNotTakenTheCourseAndHasPrereq(course_t course, gradeTable_t gradeMap);
bool hasTakenThatCourse(gradeTable_t gradeMap, int id);
bool hasTakenThatCourse(gradeTable_t gradeMap, course_t course);
bool hasFailedTheCourse(course_t course, map<int, float> gradeMap);
bool doesNotNeedprerequisitesAndHasNotTaken(course_t course, gradeTable_t gradeMap);
output_t printingTakeableCourses(map<string, int> nameAndId);
output_t generateOutput(CourseTable takeableCourses);

int main(int argc, char* argv[]) {

	CourseTable allCourses = readCourseInfo(argv[COURSE_FILE_ARGUMENT]);
	gradeTable_t gradeMap = storingGrades(argv[GRADES_FILE_ARGUMENT]);
	CourseTable takeableCourses = findTakeableCourses(allCourses, gradeMap);
	generateOutput(takeableCourses);

}

output_t printingTakeableCourses(courseNamesTable_t nameAndId) {
	for (auto it : nameAndId)
		cout << it.second << endl;
}

output_t generateOutput(CourseTable takeableCourses) {
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

int countNumberOfLines(fileName_t inputFileName) {
	ifstream inputFile(inputFileName);
	return (count(istreambuf_iterator<char>(inputFile), istreambuf_iterator<char>(), '\n'));
}

CourseTable readCourseInfo(string inputFileName) {
	CourseTable listOFCourses;
	ifstream inputFile(inputFileName);
	string firstLine;
	int id;
	getline(inputFile, firstLine);
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
	while (1) {
		struct Schedule tempSchedule;
		string day;
		int beginHour, beginMinute, endHour, endMinute;
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
	map<int, float> gradeMap;
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

bool isPassTheCourse(float grade) {
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

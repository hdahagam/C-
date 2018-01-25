//HW3
//Due: 11:59PM, September 6 (Friday)
// Source : Roger Chen
#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;

class course {
public:
	string name;
	int section;
	int credits;
	course() {}
	course(string n, int s, int c) { name = n; section = s; credits = c; }
	bool operator<(course c) { return (name < c.name); }
	bool operator==(course c) { return (name == c.name); }
};
void add_student(map<int, map<int, list<course> * >> &DB, int id);
void remove_student(map<int, map<int, list<course> * >> &DB, int id);
void add_course(map<int, map<int, list<course> * >> &DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017
																						  //All courses in the list should be sorted according to name (increasing order)

void drop_course(map<int, map<int, list<course> * >> &DB, int semester, int id, course c);
void print_student_semester_courses(map<int, map<int, list<course> * >> &DB, int semester, int id);
void print_student_all_courses(map<int, map<int, list<course> * >> &DB, int id);
void print_DB(map<int, map<int, list<course> * >> &DB);
int main() {
	map<int, map<int, list<course> *>> DB;
	add_student(DB, 11111);
	course C1("CIS554", 1, 3), C2("CSE674", 1, 3), C3("MAT296", 8, 4), C4("WRT205", 5, 3);

	add_course(DB, 20171, 11111, C1);
	add_course(DB, 20171, 11111, C4);
	add_course(DB, 20171, 11111, C3);
	add_course(DB, 20171, 11111, C2);
	print_student_semester_courses(DB, 20171, 11111);

	drop_course(DB, 20171, 11111, C1);
	print_student_semester_courses(DB, 20171, 11111);

	add_course(DB, 20172, 11111, C2);
	add_course(DB, 20172, 11111, C4);
	add_course(DB, 20172, 11111, C3);
	add_course(DB, 20172, 11111, C1);
	print_student_all_courses(DB, 11111);

	add_student(DB, 11112);
	add_course(DB, 20171, 11112, C2);
	add_course(DB, 20171, 11112, C4);
	add_course(DB, 20171, 11112, C3);
	add_course(DB, 20171, 11112, C1);
	print_student_semester_courses(DB, 20171, 11112);

	add_course(DB, 20172, 11112, C2);
	add_course(DB, 20172, 11112, C4);
	add_course(DB, 20172, 11112, C3);
	add_course(DB, 20172, 11112, C1);
	print_student_semester_courses(DB, 20172, 11112);

	print_student_all_courses(DB, 11112);

	print_DB(DB);
	remove_student(DB, 11111);
	print_DB(DB);
	getchar();
	getchar();
	return 0;
}

void add_student(map<int, map<int, list<course> * >> &DB, int id) {
	if (DB.find(id) == DB.end()) {
		std::map<int, list<course> *> M1;
		DB[id] = M1;
	}
}

void remove_student(map<int, map<int, list<course> * >> &DB, int id) {
	if (DB.find(id) != DB.end()) {
		DB.erase(id);
	}
}
void add_course(map<int, map<int, list<course> * >> &DB, int semester, int id, course c) {
	if (DB.find(id) != DB.end()) {
		bool courseCheck = false;
		if (DB[id][semester] != nullptr) {
			list<course> *coursesList = DB[id][semester];
			list<course>::iterator courseIt;
			if (coursesList != nullptr) {
				for (courseIt = coursesList->begin(); courseIt != coursesList->end(); courseIt++) {
					if (courseIt->name == c.name) {
						courseCheck = true;
						break;
					}
				}
			}
			if (!courseCheck) {
				coursesList->push_back(c);
				coursesList->sort();
			}
		}
		else {
			list<course> *coursesList = new list<course>();
			coursesList->push_back(c);
			coursesList->sort();
			map<int, list<course> *> studentCourseList = DB[id];
			studentCourseList[semester] = coursesList;
			DB[id] = studentCourseList;
		}
	}
} //20171 Spring semester of 2017; 20172: Fall semester of 2017

void drop_course(map<int, map<int, list<course> * >> &DB, int semester, int id, course c) {
	if (DB.find(id) != DB.end()) {
		if (DB[id][semester] != nullptr) {
			DB[id][semester]->remove(c);
		}
	}
}

void print_student_semester_courses(map<int, map<int, list<course> * >> &DB, int semester, int id) {
	if (DB.find(id) != DB.end()) {
		list<course>::iterator it;
		if (DB[id][semester] != nullptr) {
			cout << "\nstudent id = " << id;
			cout << "\nsemester = " << semester << "\n";
			list<course> *courses = DB[id][semester];
			for (it = courses->begin(); it != courses->end(); it++) {
				cout << it->name << " " << it->section << " " << it->credits << "  ";
			}
		}
	}
	cout << "\n";
}

void print_student_all_courses(map<int, map<int, list<course> * >> &DB, int id) {
	if (DB.find(id) != DB.end()) {
		list<course>::iterator it;
		cout << "\nstudent id = " << id;
		if (DB.find(id) != DB.end()) {
			map<int, list<course> *>::iterator courseIt;
			for (courseIt = DB[id].begin(); courseIt != DB[id].end(); courseIt++) {
				cout << "\nsemester = " << courseIt->first << "\n";
				list<course> *courses = courseIt->second;
				for (it = courses->begin(); it != courses->end(); it++) {
					cout << it->name << " " << it->section <<
						" " << it->credits << "  ";
				}
			}
		}
	}
	cout << "\n";
}

void print_DB(map<int, map<int, list<course> * >> &DB) {
	map<int, map<int, list<course> *>>::iterator dataBaseIt;
	for (dataBaseIt = DB.begin(); dataBaseIt != DB.end(); dataBaseIt++) {
		cout << "\nstudent id = " << dataBaseIt->first;
		map<int, list<course> *> sem = dataBaseIt->second;

		map<int, list<course> *>::iterator semesterIt;
		for (semesterIt = sem.begin(); semesterIt != sem.end(); semesterIt++) {
			list<course>* courseList = semesterIt->second;
			list<course>::iterator it;
			cout << "\nsemester = " << semesterIt->first << "\n";
			if (courseList != NULL) {
				for (it = courseList->begin(); it != courseList->end(); it++) {
					cout << it->name <<
						" " << it->section << " " << it->credits << "  ";
				}
			}
		}
	}
	cout << "\n";
}

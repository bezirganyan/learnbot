// Headers from the standard library
#include <iostream>
#include <string>

// Headers from this project
#include "server.hpp"

int main(){
	Server server;
	cout << "New server created" << endl;
	int option = 0;
	while (option != -1) {
		cout << "Select action (type -1 to exit):" << endl;
		cout << "1. Add new user" << endl;
		cout << "2. Create new course" << endl;
		cout << "3. Register student for a course" << endl;
		cout << "4. Add homework for a course" << endl;
		//cout << "5. Get all courses of given student" << endl << endl;
		cin >> option;
		switch(option) {
			case 1:
			{
				std::string name;
		        std::string surname;
		        std::string ID;
		        std::string email;
		        cout << "Name of the user: ";
				cin >> name;
				cout << "Surname of the user: ";
				cin >> surname;
				cout << "ID of the user: ";
				cin >> ID;
				cout << "Email of the user: ";
				cin >> email;
				server.addUser(name, surname, ID, email);
				cout << endl << "Succesfully added user" << endl << endl; // For future exception handling
				break;
			}
			case 2:
			{
				std::string course_name;
				std::string course_id;
				int course_limit;
				cout << "Name of the course: ";
				cin >> course_name;
				cout << "ID of the course: ";
				cin >> course_id;
				cout << "Student limit of the course: ";
				cin >> course_limit;
				cout << endl;
				server.createCourse(course_name, course_id, course_limit);
				break;
			}
			case 3:
			{
				std::string name;
				std::string course_id;
				cout << "Name of the student: ";
				cin >> name;
				cout << "Course name: ";
				cin >> course_id;
				Student s = *server.userTable.retrieve(server.userTree.find(name)->id[0]);
				cout << s.getName();
				server.registerForCourse(s, course_id);
				break;
			}
			case 4:
			{
				std::string course_name;
				int number;
				std::string title;
				std::string description;
				int dueday;
				std::string duemonth;
				int dueyear;
				cout << "Course name: ";
				cin >> course_name;
				cout << "Homework number ";
				cin >> number;
				cout << "Homework title: ";
				cin >> title;
				cout << "Homework description (single string): ";
				cin >> description;
				cout << "Homework duedate (DD/Month name/YYYY): ";
				cin >> dueday >> duemonth >> dueyear;
				cout << endl << endl;
				server.addHW(number, title, description, dueday, duemonth, dueyear, course_name);
				break;
			}
			/*case 5:
			{
				std::string name;
				cin >> name;
				Student s = *server.userTable.retrieve(server.userTree.find(name)->id[0]);
				cout << "Names of courses taken by student " << name << endl << server.getStudentCourses(s);
				break;
			}*/
		}
	}
	/*server.addUser("Tigran", "Sedrakyan", "A09150139", "tigran_sedrakyan@edu.aua.am");
	Student s = *server.userTable.retrieve(server.userTree.find("Tigran")->id[0]);
	//cout << s.getHashID();
	server.createCourse("Mechanics", "CS240", 45);
	server.createCourse("Calculus3", "CS250", 45);
	server.registerForCourse(s, "CS240");
	server.registerForCourse(s, "CS250");
	server.addHW(1, "HW1", "This is HW1", 20, "September", 2016, server.availableCourses()[0]);
	//server.getHW(s, "Mechanics", "HW1");
	cout << server.getStudentCourses(s);*/
}

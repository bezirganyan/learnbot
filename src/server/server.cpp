// Headers from this projects
#include "server.hpp"

// Headers from the standartd library
#include <typeinfo>

std::vector<Course> Server::availableCourses()
{
	return courses;
}

void Server::addUser(std::string name, std::string surname,
	       	std::string id, std::string email)
{
	Student *s = new Student(name, surname, id, email);
	userTable.insert(s);
	userTree.insert(name, s->getHashID());
}

void Server::createCourse(std::string name, std::string id, int limit)
{
	Course c;
	c.set_name(name);
	c.set_id(id);
	c.set_limit(limit);
	courses.push_back(c);
}

void Server::registerForCourse(Student &s, std::string name)
{
	for (int i = 0; i < courses.size(); i++) {
		if (courses[i].get_name() == name) {
			s.addCourse(courses[i]);
			courses[i].addStudent(&s);
		}
	}
}

void Server::addHW(int number, std::string title, std::string description,
		int day, std::string month, int year, std::string course_name)
{
	Homework h(title, description);
	h.setNumber(number);
	h.setDeadline(day, month, year);
	for (int i = 0; i < courses.size(); i++){
		if (courses[i].get_name() == course_name) {
			courses[i].pushHW(h);
		}
	}
}

std::string Server::getHW(Student s, std::string coursename, std::string title)
{
	//std::string str;
	/*for (int i = 0; i < s.getCourses().size(); i++) {
		if (s.getCourses()[0].get_name() == coursename) {
			str += "Title: "
			+ s.getCourses()[0].getHW(title).getTitle() + "Description: "
			+ s.getCourses()[0].getHW(title).getDescription();
			//+ "Deadline: " + c.getHW(title).getDeadline().print();
		}
	}*/
	//return s.getCourses()[0].getHW(title);
	//return str;
}

std::string Server::getStudentCourses(Student s)
{
	std::string str;
	for (int i = 0; i < s.getCourses().size(); i++) {
		str += s.getCourses()[i].get_name() + "\n";
	}
	return str;
}

// Headers from this project
#include "../data_structures/HashTable/HashTable.hpp"
#include "../data_structures/BinSearchTree/BinSearchTree.hpp"
//#include "hw_db.cpp"
//#include "course.hpp"
#include "student.hpp"
//#include "user.hpp"

//Headers fromm the standard library
#include <vector>

class Server{
	public:
		HashTable userTable;
		BinSearchTree userTree;
		std::vector<Course> courses;
	public:
		std::vector<Course> availableCourses();
		void addUser(std::string name, std::string surname, std::string id, std::string email);
		void createCourse(std::string name, std::string id, int limit);
		void registerForCourse(Student &, std::string);
		void addHW(int number, std::string title, std::string description,
				   int day, std::string month, int year, std::string course_name);
		std::string getHW(Student, std::string, std::string);
		std::string getStudentCourses(Student s);
};

/*int main(){
	Server server;
	server.addUser("Tigran", "Sedrakyan", "A09150139", "tigran_sedrakyan@edu.aua.am");
	Student s = *server.userTable.retrieve(server.userTree.find("Tigran")->id[0]);
	//cout << s.getHashID();
	server.createCourse("Mechanics", "CS240", 45);
	server.createCourse("Calculus3", "CS250", 45);
	server.registerForCourse(s, "CS240");
	server.registerForCourse(s, "CS250");
	server.addHW(1, "HW1", "This is HW1", 20, "September", 2016, server.availableCourses()[0]);
	//server.getHW(s, "Mechanics", "HW1");
	cout << server.getStudentCourses(s);
}
*/
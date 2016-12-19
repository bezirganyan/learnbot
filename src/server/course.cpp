#include "course.hpp"

void Course::addStudent(Student *s) {
	students.push_back(s);
	vector<Assignment> temp;
	Assignment sample;
	sample.setTitle("");
	sample.setDescription("");
	sample.setDeadline(0, " ", 0);
	temp.push_back(sample);
	grades.push_back(temp);
	//cout << grades[0].size() << endl;
	
	for (int i = 0; i < grades.size(); i++) {
		//cout << "Done" << endl;
		temp[i].setTitle("");
		temp[i].setDescription("");
		temp[i].setDeadline(0, " ", 0);
		temp[i].setGrade(-1);
		//cout << temp[i].getTitle() << endl;
	}
	/*for (int i = 0; i < grades[0].size(); i++) {
		cout << grades[0][i].getTitle();
	}*/

}

void Course::set_name(std::string name)
{
    course_name = name;
}

void Course::set_id(std::string id)
{
    course_id = id;
}

void Course::set_limit(int l)
{
    limit = l;
    students.reserve(2*limit);
}

/*void Course::set_instructor(Instructor i)
{
    //instructor = i;
}*/

/*void Course::set_ta(TA t)
{
    //ta = t;
}*/

void Course::insert_lesson_day(Date d)
{
    lesson_days.push_back(d);
}

void Course::pushHW(Homework h)
{
	std::vector<Assignment> v;
	for (int i = 0; i < students.size(); i++) {
		grades[i].push_back(h);
		cout << "pushed" << endl;
	}
}

Assignment Course::getHW(std::string title) {
	//std::vector<Assignment> temp = grades[0];
	//cout << grades[0].size();
	/*for (int i = 0; i < grades[0].size(); i++) {
		if (temp[i].getTitle() == title) {
			return grades[0][i];
		}
	}*/
}

std::string Course::get_name()
{
    return course_name;
}

std::string Course::get_id()
{
    return course_id;
}

//int main(){}
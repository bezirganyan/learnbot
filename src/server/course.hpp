//#include "student.hpp"
#pragma once
#include "hw_db.cpp"
//#include "student.hpp"
#include <vector>
#include <string>
using namespace std;
class Student;

class Course
{
    private:
        std::string course_name;
        std::string course_id;
        int limit;
        std::vector<Student*> students;
        //Instructor instructor;
        //TA ta;
        std::vector<Date> lesson_days;
        std::vector<vector<Assignment>> grades;
        
    public:
        void addStudent(Student*);
        void set_name(std::string);
        void set_id(std::string);
        void set_limit(int);
        //void set_instructor(Instructor);
        //void set_ta(TA);
        void insert_lesson_day(Date);
        void pushHW(Homework);
        Assignment getHW(std::string);
        std::string get_name();
        std::string get_id();
};
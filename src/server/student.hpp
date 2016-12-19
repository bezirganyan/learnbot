// Headers from this project
#pragma once
#include "user.hpp"
#include "course.hpp"

class Student : public User
{
        private:
                // Private data members
                int m_year_of_study;
                std::vector<Course> m_courses;
                std::string m_faculty;
        public:
                // Public member functions
                Student(std::string name, std::string surname, std::string id, std::string email) : User(name, surname, id, email){}
                std::vector<std::string> getCourses() const;
                int getYearOfStudy() const noexcept;
                std::string getFaculty() const noexcept;
                void setYearOfStudy(int);
                void setFaculty(std::string);
                void addCourse(Course);
                //void removeCourse(std::string);
                std::vector<Course> getCourses();

};

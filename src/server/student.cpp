// Headers from this project
#include "student.hpp"

/*std::vector<Course> Student::getCourses() const
{
        return m_courses;
}*/

int Student::getYearOfStudy() const noexcept
{
        return m_year_of_study;
}

std::string Student::getFaculty() const noexcept
{
        return m_faculty;
}

void Student::setYearOfStudy(int y)
{
        m_faculty = y;
}

void Student::setFaculty(std::string n)
{
        m_faculty = n;
}

void Student::addCourse(Course c)
{
        m_courses.push_back(c);
}

/*void Student::removeCourse(std::string n)
{
        for (int i = 0; i < m_courses.size(); i++) {
                if (m_courses[i].get_name() == n) {
                        m_courses.erase(m_courses.begin() + n)
                }
        }
}
*/

std::vector<Course> Student::getCourses(){
        return m_courses;
}
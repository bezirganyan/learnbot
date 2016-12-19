#include <iostream>
#include <vector>

using namespace std;



//Supplementary class
struct Date{
	int day;
	string month;
	int year;
	void print(){
		cout << day << " " << month << " " << year << endl;
	}
};



//Base class
class Assignment{
	protected:
		string title;
		string description;
		int grade;
		Date deadline;
	public:
		Assignment() {
			title = "";
			description = "";
		}
		Assignment(string t, string d) {
			title = t;
			description = d;
		}

		void setTitle(string t){
			title = t;
		}

		void setDescription(string d){
			description = d;
		}

		void setDeadline(int day, string month, int year){
			deadline.day = day;
			deadline.month = month;
			deadline.year = year;
		}

		void setGrade(int g){
			grade = g;
		}

		string getTitle(){
			return title;
		}

		string getDescription(){
			return description;
		}

		int getGrade(){
			return grade;
		}

		Date getDeadline(){
			return deadline;
		}



};

/*Assignment::Assignment(){
	title = "";
	description = "";
}

Assignment::Assignment(string t, string d) {
	title = t;
	description = d;
}

void Assignment::setTitle(string t){
	title = t;
}

void Assignment::setDescription(string d){
	description = d;
}

void Assignment::setDeadline(int day, string month, int year) {
	deadline.day = day;
	deadline.month = month;
	deadline.year = year;
}

void Assignment::setGrade(int g) {
	grade = g;
}

string Assignment::getTitle(){
	return title;
}

string Assignment::getDescription(){
	return description;
}

int Assignment::getGrade(){
	return grade;
}

Date Assignment::getDeadline(){
	return deadline;
}
*/

//Inherited from Assignment
class Homework: public Assignment{
	private:
		int number;
	public:
		//Homework(string t, string d);
		Homework(string t, string d) : Assignment(t, d){}
		void setNumber(int n) {
			number = n;
		}
		int getNumber() {
			return number;
		}
};

/*Homework::Homework(string t, string d) : Assignment(t, d) {

}

void Homework::setNumber(int n) {
	number = n;
}

int Homework::getNumber(){
	return number;
}
*/


//Other types of Assignments

/*class Other: public Assignment {

};*/



//template <class T>
class HWDataBase{
	private:
		vector<Homework> db;
	public:
		HWDataBase();
		void insert(Homework h){
			db.push_back(h);
		}
		/*void editTitle(int, string);
		void editDescription(int, string);
		void editDeadline(int, int, string, int);
		void editGrade(int, int);
		void remove(int);*/
		void print() {
			vector<Homework> :: iterator i;
			for (i = db.begin(); i != db.end(); i++){
				cout << "Number: " << i->getNumber() << endl << "Title: " << i->getTitle() << endl << "Description: " << i->getDescription() << endl << "Deadline: ";
				i->getDeadline().print();
				cout << "Grade: " << i->getGrade();
				cout << endl << endl;
			}
		}
};

/*HWDataBase::HWDataBase(){

}

void HWDataBase::insert(Homework h){
	db.push_back(h);
}

void HWDataBase::editTitle(int index, string title) {
	db[index-1].setTitle(title);
}

void HWDataBase::editDescription(int index, string description) {
	db[index-1].setDescription(description);
}

void HWDataBase::editDeadline(int index, int day, string month, int year) {
	db[index-1].setDeadline(day, month, year);
}

void HWDataBase::editGrade(int index, int grade) {
	db[index-1].setGrade(grade);
}

void HWDataBase::remove(int index) {
	db.erase(db.begin() + index);
}*/


//main
/*int main(){
	Homework h1("HW1", "This is HW1");
	h1.setGrade(50);
	h1.setNumber(1);
	h1.setDeadline(12, "January", 2016);
	//cout << "Number: " << h.getNumber() << endl << "Title: " << h.getTitle() << endl << "Description: " << h.getDescription() << endl;
	Homework h2("HW2", "This is HW2");
	h2.setNumber(2);
	h2.setDeadline(12, "January", 2016);

	Homework h3("HW3", "This is HW3");
	h3.setNumber(3);
	h3.setDeadline(12, "January", 2016);

	Homework h4("HW4", "This is HW4");
	h4.setNumber(4);
	h4.setDeadline(12, "January", 2016);

	HWDataBase d;
	d.insert(h1);
	d.insert(h2);
	d.insert(h3);
	d.insert(h4);
	d.remove(4);
	d.editTitle(3, "awdawdawd");
	d.editDescription(2, "Adawdawdaw");
	d.editDeadline(3, 15, "January", 2016);
	d.print();
}*/
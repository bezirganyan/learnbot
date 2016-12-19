// Headers from the standard library
#pragma once
#include <string>
#include "course.hpp"

class User
{
	protected:
		// Protected data members
		const std::string m_name;
		const std::string m_surname;
		const std::string m_ID;
		const int m_hash_id;
		const std::string m_email;
	public:
		// Public member functions
		std::string getName() const noexcept;
		std::string getSurname() const noexcept;
		std::string getID() const noexcept;
		std::string getEmail() const noexcept;
		int getHashID();
	public:
		// Public constructor & destructor
		User(std::string, std::string, std::string, std::string);
		//~User();
};

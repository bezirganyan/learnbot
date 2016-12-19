// Headers from this project
#include "user.hpp"

std::string User::getName() const noexcept
{
        return m_name;
}

std::string User::getSurname() const noexcept
{
        return m_surname;
}

std::string User::getID() const noexcept
{
        return m_ID;
}

int User::getHashID()
{
        if (m_ID.substr(0, 3) == "A09" && m_ID.size() == 9) {
                return std::stoi(m_ID.substr(3, 6));
        }
        throw "Invalid ID format";
}

std::string User::getEmail() const noexcept
{
        return m_email;
}

User::User(std::string n, std::string s, std::string i, std::string e)
        :m_name(n)
        , m_surname(s)
        , m_ID(i)
        , m_hash_id(getHashID())
        , m_email(e)
{
}

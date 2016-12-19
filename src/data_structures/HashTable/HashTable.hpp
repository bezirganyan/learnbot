// Headers from this project
//#include "user.hpp"
#include <vector>
#include "../../server/user.hpp"
#include "../../server/student.hpp"

class HashTable
{
        private:
                // Private data members
                std::vector<Student*> table;

        public:
                // Public member functions
                void insert(Student*);
                Student *retrieve(int);
                void remove(int);

        public:
                // Public operator overload
                //User &operator[] (int);

        public:
                // Public constructor & destructor
                /*HashTable();
                ~HashTable();*/
};

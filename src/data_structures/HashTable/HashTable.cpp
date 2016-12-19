// Headers from this project
#include "HashTable.hpp"

void HashTable::insert(Student *u) {
        if (u->getHashID() > int(table.size())) {
                table.resize(u->getHashID(), nullptr);
        }
        table[u->getHashID()] = u;
}

Student *HashTable::retrieve(int id){
        return table[id];
}

void HashTable::remove(int id)
{
        delete table[id];
        table.erase(table.begin() + id);
}

/*HashTable::HashTable() {
        table = new std::vector<User*>
}*/

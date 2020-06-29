#include "database.h"

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void Database::Add(const Date& t_date, const std::string& t_event) {
    auto& on_date = _database.at(t_date);
    on_date.push_back(t_event);
}

void Database::Print(ostream& t_os) const {
    for (const auto& [date, events] : _database) {
        for (const auto& event : events) {
            t_os << date << " " << event << endl;
        }
    }
}

int Database::RemoveIf( std::function<bool(const Date&, const std::string&)> ) {
    
}
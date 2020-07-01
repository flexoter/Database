#include "database.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <iostream>

using namespace std;

using DatePair = pair<Date, string>;
void Database::Add(
    const Date& t_date, 
    const std::string& t_event) {
        _database.insert(make_pair(t_date, t_event));
    }

ostream& operator<<(
    ostream& t_os,
    const DatePair& t_p) {
        t_os << t_p.first << " " << t_p.second;
        return t_os;
}

void Database::Print(ostream& t_os) const {
    copy(
        _database.begin(),
        _database.end(),
        ostream_iterator<DatePair>(t_os, "\n"));
}

int Database::RemoveIf(
    std::function<bool(
        const Date&,
        const std::string&)> t_pred) {
        unsigned int erased{0};
        for (
            auto it = _database.begin();
            it != _database.end();
            it++) {
                Date date{it->first};
                string event{it->second};
                if ( t_pred( date, event ) ) {
                    erased++;
                    _database.erase(it);
                    continue;
                }
        }
        return erased;
}

std::vector<DatePair>
Database::FindIf(
    std::function<bool(
        const Date&,
        const std::string&)> t_pred) const {
        vector<DatePair> found;
        for (
            auto it = _database.begin();
            it != _database.end();
            it++) {
                Date date{it->first};
                string event{it->second};
                if ( t_pred(date, event) ) {
                    found.push_back(make_pair(date, event));
                    continue;
                }
        }
        return found;
}

DatePair Database::Last(const Date& t_date) const {
    const auto last = _database.upper_bound(t_date);
    if ( last == _database.begin() ) {
        throw invalid_argument(
            string{"Given date is greater "}
            + string{"than all of the data base elements"});
    }
    return (*prev(last));
}
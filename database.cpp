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
        auto& on_date{_database[t_date]};
        const auto exists = find(
            on_date.begin(),
            on_date.end(),
            t_event);
        if ( exists == on_date.end() ) {
            on_date.push_back(t_event);
        }
    }

void Database::Print(ostream& t_os) const {
    for (const auto& [date, events] : _database) {
        for (const string& event : events) {
            t_os << date << " " << event << endl;
        }
    }
}

int Database::RemoveIf(
    std::function<bool(
        const Date&,
        const std::string&)> t_pred) {
        unsigned int erased{0};
        for (auto it = _database.begin(); it != _database.end(); it++) {
            Date date{it->first};
            const auto to_erase = remove_if(
                it->second.begin(),
                it->second.end(),
                [date, t_pred] (const auto& s) { return t_pred(date, s); });
            erased += distance(to_erase, it->second.end());
            if ( to_erase == it->second.begin() ) {
                it = _database.erase(it);
                if ( it != _database.end() ) {
                    it++;
                }
                if ( _database.size() == 0 ) {
                    break;
                }
                continue;
            }
            it->second.erase(to_erase, it->second.end());
        }
        return erased;
}

std::vector<DatePair>
Database::FindIf(
    std::function<bool(
        const Date&,
        const std::string&)> t_pred) const {
        vector<DatePair> found;
        for (auto it = _database.begin(); it != _database.end(); it++) {
            Date date{it->first};
            vector<string> events;
            copy_if(
                it->second.begin(),
                it->second.end(),
                back_inserter(events),
                [date, t_pred] (const auto& s) { return t_pred(date, s); });
            transform(
                events.begin(),
                events.end(),
                back_inserter(found),
                [date] (const string& s) { return make_pair(date, s); });
                events.clear();
        }
        return found;
}

DatePair Database::Last(const Date& t_date) const {
    auto found = _database.upper_bound(t_date);
    if ( found == _database.begin() ) {
        throw std::invalid_argument(
            string{"Given date is greater "}
            + string{"than all of the data base elements"});
    }
    found = prev(found);
    return make_pair(found->first, found->second.back());
}
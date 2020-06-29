#include "database.h"

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

using DatePair = pair<Date, vector<string> >;
void Database::Add(
    const Date& t_date, 
    const std::string& t_event) {
        auto& on_date{_database[t_date]};
        on_date.push_back(t_event);
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
            if ( t_pred(date, string{""}) ) {
                erased = it->second.size();
                it = _database.erase(it);
                continue;
            }
            const auto to_erase = remove_if(
                it->second.begin(),
                it->second.end(),
                [date, t_pred] (const auto& s) { return t_pred(date, s); });
            erased = distance(to_erase, it->second.end());
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
            if ( t_pred(date, string{""}) ) {
                found.push_back(make_pair(date, it->second));
                continue;
            }
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
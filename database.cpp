#include "database.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <iostream>

using namespace std;

void Database::Add(
    const Date& t_date, 
    const std::string& t_event) {
        const auto inserted{
            _database[t_date].insert(t_event)};
        if ( inserted.second ) {
            _order[t_date].push_back(t_event);
        }
    }

void Database::Print(ostream& t_os) const {
    for (const auto& [date, events] : _order) {
        for (const string& event : events) {
            t_os << date << " " << event << endl;
        }
    }
}

void Database::RemoveSetContainer(
    const map<Date, vector<std::string>::iterator >& t_erased) {
        if ( t_erased.empty() ) {
            _database.clear();
        }
        for (const auto& [date, _] : t_erased) {
            const auto erase_it{
                _database.find(date)};
            _database.erase(erase_it);
            auto& on_date = _database[date];
            const auto& from_order = _order.at(date);
            copy(
                from_order.begin(),
                from_order.end(),
                inserter(on_date, on_date.begin()));
        }
    }

void Database::RemoveVectorContainer(
    const map<Date, vector<std::string>::iterator >& t_erased) {
        for (const auto& [date, it] : t_erased) {
            auto& on_date = _order.at(date);
            on_date.erase(on_date.begin(), it);
        }
    }

int Database::RemoveIf(
    std::function<bool(
        const Date&,
        const std::string&)> t_pred) {
        unsigned int erased{0};
        map<Date, vector<std::string>::iterator > erased_map;
        for (
            auto it = _order.begin();
            it != _order.end();
            ) {
                Date date{it->first};
                const auto to_erase = stable_partition(
                    it->second.begin(),
                    it->second.end(),
                    [date, t_pred]
                    (const auto& s)
                    { return t_pred(date, s); }
                );
                const auto erased_number{
                    distance(it->second.begin(), to_erase)
                };
                erased += erased_number;
                if ( erased_number > 0 ) {
                    if ( erased_number == it->second.size() ) {
                        it = _order.erase(it);
                    } else {
                        erased_map[date] = to_erase;
                        it++;
                    }
                    continue;
                }
                it++;
            }
        RemoveVectorContainer(erased_map);
        RemoveSetContainer(erased_map);
        return erased;
}

std::vector<std::pair<Date, std::string> >
Database::FindIf(
    std::function<bool(
        const Date&,
        const std::string&)> t_pred) const {
        vector<std::pair<Date, std::string> > found;
        vector<string> events;
        for (
            auto it = _order.begin();
            it != _order.end();
            it++) {
                Date date{it->first};
                copy_if(
                    it->second.begin(),
                    it->second.end(),
                    back_inserter(events),
                    [date, t_pred]
                    (const auto& s)
                    { return t_pred(date, s); });
                transform(
                    events.begin(),
                    events.end(),
                    back_inserter(found),
                    [date]
                    (const string& s)
                    { return make_pair(date, s); });
                events.clear();
        }
        return found;
}

std::pair<Date, std::string>
Database::Last(const Date& t_date) const {
    auto found = _order.upper_bound(t_date);
    if ( found == _order.begin() ) {
        throw std::invalid_argument(
            string{"Given date is smaller "}
            + string{"than all of the data base elements"});
    }
    found = prev(found);
    return make_pair(found->first, found->second.back());
}
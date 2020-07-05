#ifndef H_DATABASE
#define H_DATABASE

#include "date.h"

#include <string>
#include <vector>
#include <map>
#include <set>
#include <functional>


class Database {

    public:

        void Add(
            const Date&,
            const std::string&);
        void Print(std::ostream&) const;
        void RemoveSetContainer(
            const std::vector<Date>&);
        int RemoveIf(
            std::function<bool(
                const Date&,
                const std::string&)> );
        std::vector<std::pair<Date, std::string> >
        FindIf(
            std::function<bool(
                const Date&,
                const std::string&)> ) const;
        std::pair<Date, std::string>
        Last(const Date&) const;

    private:

        std::map<Date, std::set<std::string> > _database;
        std::map<Date, std::vector<std::string> > _order;


};

std::ostream& operator<<(
    std::ostream& t_os, 
    const std::pair<Date, std::vector<std::string>>& t_v);

#endif /*H_DATABASE*/
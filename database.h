#ifndef H_DATABASE
#define H_DATABASE

#include "date.h"

#include <string>
#include <vector>
#include <map>
#include <functional>


class Database {

    public:

        void Add(
            const Date&,
            const std::string&);
        void Print(std::ostream&) const;
        int RemoveIf(
            std::function<bool(
                const Date&,
                const std::string&)> );
        using DatePair = std::pair<Date, std::string>;
        std::vector<DatePair>
        FindIf(
            std::function<bool(
                const Date&,
                const std::string&)> ) const;
        DatePair Last(const Date&) const;

    private:

        std::map<Date, std::vector<std::string> > _database;


};

std::ostream& operator<<(
    std::ostream& t_os, 
    const pair<Date, std::vector<std::string>>& t_v);

#include "database.cpp"

#endif /*H_DATABASE*/
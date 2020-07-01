#ifndef H_DATABASE
#define H_DATABASE

#include "date.h"

#include <string>
#include <vector>
#include <map>
#include <functional>


class Database {

    public:

        void Add(const Date&, const std::string&);
        void Print(ostream&) const;
        int RemoveIf( std::function<bool(const Date&, const std::string&)> );
        using DatePair = pair<Date, std::string>;
        std::vector<DatePair>
        FindIf( std::function<bool(const Date&, const std::string&)> ) const;
        DatePair Last(const Date&) const;

    private:

        std::multimap<Date, std::string> _database;


};

#include "database.cpp"

#endif /*H_DATABASE*/
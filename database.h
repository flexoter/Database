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
        std::vector<std::string> FindIf( std::function<bool(const Date&, const std::string&)> ) const;
        std::string Last(const Date&) const;

    private:

        map<Date, std::vector<std::string> > _database;


};

#endif /*H_DATABASE*/
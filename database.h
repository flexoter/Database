#ifndef H_DATABASE
#define H_DATABASE

#include "date.h"

#include <string>
#include <vector>
#include <map>


class Database {

    public:

        void Add(const Date& t_date, const std::string& t_event);
        void Print() const;
        int RemoveIf( bool t_pred(const Date&, const std::string&) );
        std::vector<std::string> FindIf(bool t_pred(const Date&, const std::string&)) const;
        std::string Last(const std::string& t_date) const;

    private:

        map<Date, std::vector<std::string> > _database;


};

#include "date.cpp";

#endif /*H_DATABASE*/
#ifndef H_DATE
#define H_DATE

#include <string>
#include <vector>
#include <iostream>

class Date {

    public:
        Date();
        Date(const Date&);
        Date(int, int, int);

        int GetYear() const;
        int GetMonth() const;
        int GetDay() const;
        char GetSep() const;

    private:
        const int _year{0};
        const int _month{0};
        const int _day{0};
        const char _sep{'-'};

};

Date ParseDate(std::istream&);
std::ostream& operator<<(std::ostream&, const Date&);
std::ostream& operator<<(
    std::ostream&,
    const std::pair<Date, std::vector<std::string>>&);
std::ostream& operator<<(
    std::ostream&,
    const std::pair<Date, std::string>&);
bool operator<(const Date&, const Date&);
bool operator<=(const Date&, const Date&);
bool operator>(const Date&, const Date&);
bool operator>=(const Date&, const Date&);
bool operator==(const Date&, const Date&);
bool operator!=(const Date&, const Date&);

#include "date.cpp"

#endif /*H_DATE*/
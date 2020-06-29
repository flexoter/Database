#ifndef H_DATE
#define H_DATE

#include <string>
#include <iostream>

class Date {

    public:
        Date();
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
bool operator<(const Date&, const Date&);
bool operator<=(const Date&, const Date&);
bool operator>(const Date&, const Date&);
bool operator>=(const Date&, const Date&);
bool operator==(const Date&, const Date&);
bool operator!=(const Date&, const Date&);


#include "date.cpp"

#endif /*H_DATE*/
#ifndef H_DATE
#define H_DATE

#include <string>
#include <iostream>

class Date {

    public:
        Date();
        Date(int t_year, int t_month, int t_day);

        int GetYear() const;
        int GetMonth() const;
        int GetDay() const;

    private:
        const int _year{0};
        const int _month{0};
        const int _day{0};

};

Date ParseDate(std::istream& t_is);
std::ostream& operator<<(std::ostream& t_os, const Date& t_date);


#endif /*H_DATE*/
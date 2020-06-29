#include "date.h"

#include <string>
#include <algorithm>

using namespace std;

Date::Date()
    : _year(0), _month(0), _day(0), _sep('-') {}

Date::Date(int t_year, int t_month, int t_day)
    : _year(t_year), _month(t_month), _day(t_day) {}

int Date::GetYear() const {
    return _year;
}

int Date::GetMonth() const {
    return _month;
}

int Date::GetDay() const {
    return _day;
}

char Date::GetSep() const {
    return _sep;
}

bool IsDigit(string::iterator t_it1, string::iterator t_it2) {
    if ( t_it2 == t_it2 ) {
        return false;
    }
    unsigned int digits = count_if(t_it1, t_it2, 
                [](const char& c) { return isdigit(c); });
    if (digits != distance(t_it1, t_it2)) {
        return false;
    }
    return true;
}

Date ParseDate(istream& t_is) {
    int year{0}, month{0}, day{0};
    string from_stream{""};
    getline(t_is, from_stream, '-');
    if (!IsDigit(from_stream.begin(), from_stream.end())) {
        throw invalid_argument("Given date has wrong format");
    }
    year = stoi(from_stream);
    if (year < 0 || year > 9999) {
        throw invalid_argument("Year has to be in range [0, 9999]");
    }
    getline(t_is, from_stream, '-');
    if (!IsDigit(from_stream.begin(), from_stream.end())) {
        throw invalid_argument("Given date has wrong format");
    }
    month = stoi(from_stream);
    if (month < 1 || year > 12) {
        throw invalid_argument("Month has to be in range [1, 12]");
    }
    getline(t_is, from_stream, ' ');
    if (!IsDigit(from_stream.begin(), from_stream.end())) {
        throw invalid_argument("Given date has wrong format");
    }
    day = stoi(from_stream);
    if (year < 1 || year > 31) {
        throw invalid_argument("Day has to be in range [1, 31]");
    }
    return Date(year, month, day);
}

std::ostream& operator<<(std::ostream& t_os, const Date& t_date) {
    char separator = t_date.GetSep();
    t_os << t_date.GetYear() << separator << t_date.GetMonth() << separator << t_date.GetDay();
}

bool operator<(const Date& t_d1, const Date& t_d2) {
    if ( t_d1.GetYear() == t_d2.GetYear() ) {
        if ( t_d1.GetMonth() == t_d2.GetMonth() ) {
            return t_d1.GetDay() < t_d2.GetDay();
        }
        return t_d1.GetMonth() < t_d2.GetMonth();
    }
    return t_d1.GetYear() < t_d2.GetYear();
}

bool operator<=(const Date& t_d1, const Date& t_d2) {
    if ( t_d1.GetYear() == t_d2.GetYear() ) {
        if ( t_d1.GetMonth() == t_d2.GetMonth() ) {
            return t_d1.GetDay() <= t_d2.GetDay();
        }
        return t_d1.GetMonth() < t_d2.GetMonth();
    }
    return t_d1.GetYear() < t_d2.GetYear();
}

bool operator>(const Date& t_d1, const Date& t_d2) {
    if ( t_d1.GetYear() == t_d2.GetYear() ) {
        if ( t_d1.GetMonth() == t_d2.GetMonth() ) {
            return t_d1.GetDay() > t_d2.GetDay();
        }
        return t_d1.GetMonth() > t_d2.GetMonth();
    }
    return t_d1.GetYear() > t_d2.GetYear();
}

bool operator>=(const Date& t_d1, const Date& t_d2) {
    if ( t_d1.GetYear() == t_d2.GetYear() ) {
        if ( t_d1.GetMonth() == t_d2.GetMonth() ) {
            return t_d1.GetDay() >= t_d2.GetDay();
        }
        return t_d1.GetMonth() > t_d2.GetMonth();
    }
    return t_d1.GetYear() > t_d2.GetYear();
}

bool operator==(const Date& t_d1, const Date& t_d2) {
    if ( t_d1.GetYear() == t_d2.GetYear() ) {
        if ( t_d1.GetMonth() == t_d2.GetMonth() ) {
            return t_d1.GetDay() == t_d2.GetDay();
        }
    }
    return false;
}

bool operator!=(const Date& t_d1, const Date& t_d2) {
    if ( t_d1.GetYear() != t_d2.GetYear() ) {
        if ( t_d1.GetMonth() != t_d2.GetMonth() ) {
            return t_d1.GetDay() != t_d2.GetDay();
        }
    }
    return false;
}
#ifndef DATEBASE_H
#define DATEBASE_H

#include "CommonHeaders.h"

class Date {
private:
    int year_, month_, day_;
    /* Check and Parse Date */
    void ParseDate(const std::string& date);

public:
    Date(const std::string& date_str);
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    /* Format YYYY-MM-DD */
    std::string ToString() const;
};

bool operator<(const Date& lhs, const Date& rhs);

class Database {
private:
    std::map<Date, std::set<std::string>> data_;
public:
    void AddEvent(const Date& date, const std::string& event);
    bool DeleteEvent(const Date& date, const std::string& event);
    int DeleteDate(const Date& date);
    std::set<std::string> Find(const Date& date) const;
    void Print() const;
};

#endif // DATEBASE_H
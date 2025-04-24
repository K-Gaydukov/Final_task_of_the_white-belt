#include "DateBase.h"

/*      Date class      */

/* Check and Parse Date */
void Date::ParseDate(const std::string& date) {
    std::stringstream ss(date);
    char dash1 = ' ', dash2 = ' ';
    /* Check Date Format YYYY-MM-DD */
    if (!(ss >> year_ >> dash1 >> month_ >> dash2 >> day_) ||
        dash1 != '-' || dash2 != '-' || 
        ss.peek() != EOF) {
            throw std::invalid_argument("Wrong date format: " + date);
    }
    /* Check correct Month */
    if (month_ < 1 || month_ > 12) {
        throw std::invalid_argument("Month value is invalid: " + std::to_string(month_));
    }
    /* Check correct Day */
    if (day_ < 1 || day_ > 31) {
        throw std::invalid_argument("Day value is invalid: " + std::to_string(day_));
    }
}
/* Constructor */
Date::Date(const std::string& date_str) {
    ParseDate(date_str);
}

int Date::GetYear() const { return year_; }
int Date::GetMonth() const { return month_; }
int Date::GetDay() const { return day_; }
    
/* Format YYYY-MM-DD */
std::string Date::ToString() const {
    std::stringstream ss;
    ss << std::setw(4) << std::setfill('0') << year_ << "-" 
        << std::setw(2) << std::setfill('0') << month_ << "-" 
        << std::setw(2) << std::setfill('0') << day_;
    return ss.str();
}

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() != rhs.GetYear()) {return lhs.GetYear() < rhs.GetYear();}
    if (lhs.GetMonth() != rhs.GetMonth()) {return lhs.GetMonth() < rhs.GetMonth();}
    return lhs.GetDay() < rhs.GetDay();
}

/*      Database class      */

/* Add event to the date */
void Database::AddEvent(const Date& date, const std::string& event) {
    data_[date].insert(event);
}

/* Del specific event */
bool Database::DeleteEvent(const Date& date, const std::string& event) {
    if (data_.count(date) && data_[date].count(event)) {
        data_[date].erase(event);
        if (data_[date].empty()) {
            data_.erase(date);
        }
        return true;
    } 
    return false;
}

/* Del all events */
int Database::DeleteDate(const Date& date) {
    size_t count = data_.count(date) ? data_[date].size() : 0;
    if (count > 0) {
        data_.erase(date);
    }
    return count;
}

/* Find events on the date */
std::set<std::string> Database::Find(const Date& date) const {
    if (data_.count(date)) {
        return data_.at(date);
    }
    return {};
}

/* Print all events */
void Database::Print() const {
    for (const auto& [date, events] : data_) {
        for (const auto& event : events) {
            std::cout << date.ToString() << " " <<  event << std::endl;
        }
    }
}
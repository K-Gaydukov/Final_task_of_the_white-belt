#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <iomanip>

/* Check and Parse Date */
void ParseDate(const std::string& date, int& year, int& month, int& day) {
    std::stringstream ss(date);
    char dash1 = ' ', dash2 = ' ';
    /* Check Date Format YYYY-MM-DD */
    if (!(ss >> year >> dash1 >> month >> dash2 >> day) ||
        dash1 != '-' || dash2 != '-' || 
        ss.peek() != EOF) {
            throw std::invalid_argument("Wrong date format: " + date);
    }
    /* Check correct Month */
    if (month < 1 || month > 12) {
        throw std::invalid_argument("Month value is invalid: " + std::to_string(month));
    }
    /* Check correct Day */
    if (day < 1 || day > 31) {
        throw std::invalid_argument("Day value is invalid: " + std::to_string(day));
    }
}

std::string NormalizeDate(const std::string& date) {
    int year, month, day;
    ParseDate(date, year, month, day);
    std::stringstream ss;
    ss << std::setw(4) << std::setfill('0') << year << "-" <<
          std::setw(2) << std::setfill('0') << month << "-" << 
          std::setw(2) << std::setfill('0') << day;
    return ss.str();
}

void Add(const std::string& date, const std::string& event,
         std::map<std::string, std::set<std::string>>& dataBase) {
    /* Check Date */
    int year, month, day;
    ParseDate(date, year, month, day);
    
    dataBase[date].emplace(event);
}

void Del(const std::string& date, const std::string& event, 
         std::map<std::string, std::set<std::string>>& dataBase) {
    /* Check Date */
    int year, month, day;
    ParseDate(date, year, month, day);

    if (event.empty()) {
        /* Del all events */
        size_t count = dataBase.count(date) ? dataBase[date].size() : 0;
        if (count > 0) {
            dataBase.erase(date);
        }
        std::cout << "Deleted " << count << " events" << std::endl;
    } else {
        /* Del specific event */
        if (dataBase.count(date) && dataBase[date].count(event)) {
            dataBase[date].erase(event);

            if (dataBase[date].empty()) {
                dataBase.erase(date);
            }

            std::cout << "Deleted successfully" << std::endl;
        } else {
            std::cout << "Event not found" << std::endl;
        }
    }
}

void Find(const std::string& date, 
          const std::map<std::string, std::set<std::string>>& dataBase) {
    /* Check Date */
    int year, month, day;
    ParseDate(date, year, month, day);

    if (dataBase.count(date)) {
        for (const auto& event : dataBase.at(date)) {
            std::cout << event << std::endl;
        }
    }
}

void Print(const std::map<std::string, std::set<std::string>>& dataBase) {
    for (const auto& [date, events] : dataBase) {
        for (const auto& event : events) {
            std::cout << date << " " <<  event << std::endl;
        }
    }
}

int main() {
    std::map<std::string, std::set<std::string>> dataBase;
    std::string str;
    
    while (std::getline(std::cin, str)){
        
        if (!str.empty()) {

            try {
                std::stringstream ss(str);
                std::string command, date, event;
                ss >> command;

                if (command == "Add") {
                    ss >> date >> event;
                    if (date.empty() || event.empty()) {
                        throw std::invalid_argument("Wrong event format");
                    }
                    Add(NormalizeDate(date), event, dataBase);
                } else if (command == "Del") {
                    ss >> date >> event;
                    if (date.empty()) {
                        throw std::invalid_argument("Wrong date format");
                    }
                    Del(NormalizeDate(date), event, dataBase);
                } else if (command == "Find") {
                    ss >> date;
                    if (date.empty()) {
                        throw std::invalid_argument("Wrong date format");
                    }
                    Find(NormalizeDate(date), dataBase);
                } else if (command == "Print") {
                    Print(dataBase);
                } else {
                    throw std::invalid_argument("Unknown command: " + command);
                }

            } catch (std::invalid_argument& ex) {
                std::cout << ex.what() << std::endl;
                return 1;
            }

        }
    }
    return 0;
}
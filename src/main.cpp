#include "DateBase.h"

int main() {
    Database db;
    std::string command;
    
    while (std::getline(std::cin, command)){
        
        if (command.empty()) { continue; }

        try {
            std::stringstream ss(command);
            std::string cmd, date, event;
            ss >> cmd;

            if (cmd == "Add") {
                ss >> date >> event;
                db.AddEvent(Date(date), event);

            } else if (cmd == "Del") {
                ss >> date;
                if (ss >> event) {
                    if (db.DeleteEvent(Date(date), event)) {
                        std::cout << "Deleted successfully\n";
                    } else {
                        std::cout << "Event not found\n";
                    }
                } else {
                    int count = db.DeleteDate(Date(date));
                    std::cout << "Deleted " << count << " events\n";
                }

            } else if (cmd == "Find") {
                ss >> date;
                for (const auto& event: db.Find(Date(date))) {
                    std::cout << event << '\n';
                }

            } else if (cmd == "Print") {
                db.Print();
            } else {
                throw std::invalid_argument("Unknown command: " + cmd);
            }

        } catch (std::invalid_argument& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    return 0;
}
#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

string ParseEvent(istream& is) {
    string event{""};
    getline(is, event);
    if (!event.empty()) {
        if (event.find_first_of(
            string(" \" ")) != string::npos) {
            cout << "Given event contains symbol of \"\"";
        }
    }
    return event;
}

void TestAll();


ostream& operator<<(
    ostream& t_os, 
    const pair<Date, vector<string>>& t_v) {
        for (const string& s : t_v.second) {
            t_os << t_v.first << " " << s << endl;
        }
    return t_os;
}

const vector<string> input{
        "10",
        "ALL_BUSES",
        "BUSES_FOR_STOP Marushkino",
        "STOPS_FOR_BUS 32K",
        "NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo",
        "NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo",
        "BUSES_FOR_STOP Vnukovo",
        "NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo",
        "NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo",
        "STOPS_FOR_BUS 272",
        "ALL_BUSES",
    };

int main() {
    TestAll();

    Database db;

    // for (string line; getline(cin, line); ) {
    for (const string& line : input) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print(cout);
        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](
                const Date& date,
                const string& event) {
                    return condition->Evaluate(date, event);
                };
            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        } else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](
                const Date& date,
                const string& event) {
                    return condition->Evaluate(date, event);
                };
            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        } else if (command == "Last") {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            } catch (invalid_argument&) {
                cout << "No entries" << endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw logic_error("Unknown command: " + command);
        }
    }

    return 0;
}

void TestParseEvent() {
    {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
    }
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");
}
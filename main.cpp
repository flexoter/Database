#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

#include "database.cpp"
#include "date.cpp"
#include "condition_parser.cpp"
#include "node.cpp"
#include "token.cpp"
#include "test_runner.cpp"
#include "database_test.cpp"

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

using namespace std;

string ParseEvent(istream& is) {
    string event{""};
    is >> ws;
    getline(is, event);
    if (!event.empty()) {
        if (event.find_first_of(
            string(" \" ")) != string::npos) {
        }
    }
    return event;
}

const vector<string> test1{
        "Add 2017-11-6 z",
        // "Add 2017-11-19 Monday",
        // "Add 2017-11-13 sport event",
        // "Add 2017-11-10 weekly meeting",
        // "Add 2017-11-7 sport event",
        // "Print",
        // // "Find event != \"Weekly meeting\"",
        "Del",
        // // "Last 2017-11-20",
        "Print",
        // "Last 2017-11-30",
        // "Last 2017-11-01"
    };

const vector<string> test2{
        "Add 2017-01-01 New Year",
        "Add 2017-03-08 Holiday",
        "Add 2017-01-01 Holiday",
        "Last 2016-12-31",
        "Last 2017-01-01",
        "Last 2017-06-01",
        "Add 2017-05-09 Holiday"
    };

const vector<string> test3{
        "Add 2017-01-01 Holiday",
        "Add 2017-03-08 Holiday",
        "Add 2017-01-01 New Year",
        "Find event == \"sport event\"",
        "Add 2017-05-09 Holiday1"
    };

const vector<string> test4{
        "Add 2017-06-01 1st of June",
        "Add 2017-06-01 1st of June",
        "Add 2017-07-08 8th of July",
        "Add 2017-07-08 Someone's birthday",
        "Print",
        "Del date == 2017-07-08",
        "Print"
    };

const vector<string> test5{
    "Add 2017-01-01 event3",
    "Add 2017-01-01 event2",
    "Add 2017-01-01 event1",
    "Find date == 2017-1-1"
};

vector<vector<string> > tests{
    test1,
    test2,
    test3,
    test4
};

void TestAll();

int main() {

    // TestAll();

    Database db;

    // for (string line; getline(cin, line); ) {
    for (const string& line : test4) {
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

void TestAll() {
    TestRunner Tr;
    Tr.RunTest(TestDbAdd, "Add Method Test");
    Tr.RunTest(TestDbFind, "FindIf Method Test");
    Tr.RunTest(TestDbLast, "Last Method Test");
    Tr.RunTest(TestDatabase, "RemoveIf Method Test");
}
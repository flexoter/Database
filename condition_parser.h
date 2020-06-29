#ifndef H_CONDITION_PARSER
#define H_CONDITION_PARSER

#include "node.h"

#include <memory>
#include <iostream>

using namespace std;

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();

#include "node.cpp"

#endif /*H_CONDITION_PARSER*/
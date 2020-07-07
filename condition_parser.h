#ifndef H_CONDITION_PARSER
#define H_CONDITION_PARSER

#include "node.h"

#include <memory>
#include <iostream>

using namespace std;

std::shared_ptr<Node> ParseCondition(std::istream& is);

#endif /*H_CONDITION_PARSER*/
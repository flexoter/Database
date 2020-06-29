#ifndef H_TOKEN
#define H_TOKEN

#include <sstream>
#include <vector>

using namespace std;

enum class TokenType {
  DATE,
  EVENT,
  COLUMN,
  LOGICAL_OP,
  COMPARE_OP,
  PAREN_LEFT,
  PAREN_RIGHT,
};

struct Token {
  const string value;
  const TokenType type;
};

vector<Token> Tokenize(istream& cl);

#include "token.cpp"

#endif /*H_TOKEN*/
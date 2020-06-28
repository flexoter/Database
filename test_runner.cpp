#include <sstream>
#include <exception>
#include <vector>
#include "test_runner.h"

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  os << "{";
  bool first = true;
  for (const auto& x : v) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u
       << " hint: " << hint;
    throw runtime_error(os.str());
  }
}

template<class T>
bool operator!=(const std::vector<T>& t_v1, const std::vector<T>& t_v2) {
  size_t v_size = t_v1.size();
  if (v_size != t_v2.size()) {
    return true;
  }
  for (size_t i = 0; i < v_size; i ++) {
    if (t_v1[i] != t_v2[i]) {
      return true;
    }
  }
  return false;
}

inline void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

template <class TestFunc>
void TestRunner::RunTest(TestFunc func, const string& test_name) {
  try {
	  func();
	  cerr << test_name << " OK" << endl;
	} catch (runtime_error& e) {
	  ++fail_count;
	  cerr << test_name << " fail: " << e.what() << endl;
	}
}

TestRunner::~TestRunner() {
  if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
}
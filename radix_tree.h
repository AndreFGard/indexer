#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <list>
using namespace std;


struct radnode {
    string s;
    map<char, radnode*> m;
    int occurrences;

    // Constructor with an initializer list
    radnode(const string st) : s(st), occurrences(0) {}
};

inline char isprefix(string &a, string&b);
inline int comparer(string &a, string &b);



inline void inserthelp(radix &rt, string s);
inline void test();
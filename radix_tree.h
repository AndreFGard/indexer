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

class radix {
    public:
        radnode *head;
        string st;

        radix();
        ~radix();

        radnode *insert(radnode *parentp, string &s, int addoccurences);
        radnode *insert(string s);

        radnode *find(string s);
        list<string> traverse(radnode &p, string &depth_indent, string &currstring);
        inline list<string> traverse(radnode &p, string base_string);
        list<string> find_by_prefix(string prefix);

};

inline void inserthelp(radix &rt, string s);
inline void test();
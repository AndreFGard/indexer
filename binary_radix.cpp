#include <string>
#include <map>
#include <stdio.h>
using namespace std;
struct radnode {
    string s;
    map<char, radnode*> m;
    int occurrences;

    // Constructor with an initializer list
    radnode(const string& st) : s(st), occurrences(0) {}
};

struct binary_radix {
    radnode head;
    string st;

    // Constructor with initializer list
    binary_radix() : head(""), st("") {}
};


#define EQUAL -1
int comparer(string &a, string &b){
	int i = 0, size = a.size();
	for (; i < size; i++){
		if (a[i] != b[i]) {
			i--;
			break;
		}
	}

	if (i < size){
		return i;
	}
	else if (i == size){
		//no differences found
		if (size == b.size()){
			//they are equal
			return EQUAL;
		}
		else return i; //from i onwards, put the string in a new node.

	}
	return i;
}



int insert(binary_radix &r, radnode &parent, string &s) {
    int res = comparer(parent.s, s);
    if (res == EQUAL) {
        parent.occurrences++;
        return 0;
    } else if (res == PREFIX) {
        s = s.substr(res);
    }

    if (parent.m.find(s[0]) != parent.m.end()) {
        insert(r, *(parent.m[s[0]]), s);
    } else {
        radnode *newnode = new radnode(s);
        parent.m.insert({s[0], newnode});
    }
    return 0;
}

int main(){

	return 0;
}
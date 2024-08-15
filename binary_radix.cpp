#include <string>
#include <map>
#include <stdio.h>
using namespace std;
struct radnode {
    string s;
    map<char, radnode*> m;
    int occurrences;

    // Constructor with an initializer list
    radnode(const string st) : s(st), occurrences(0) {}
};

struct binary_radix {
    radnode head;
    string st;

    // Constructor with initializer list
    binary_radix() : head(""), st("") {}
};

static radnode NOTFOUND("e");

#define EQUAL -1
int comparer(string &a, string &b){
	int i = 0;
    const int size = a.size(), sizeb = b.size();
	for (; i < size; i++){
        //this does stop if b < a
		if ((a[i] != b[i]) || i == sizeb ) {
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



int insert(binary_radix &r, radnode &parent, string &s, int addoccurences   ) {
    int cmp = comparer(parent.s, s);
    string temp;
    if (cmp == EQUAL) {
        parent.occurrences++;
        parent.occurrences+= addoccurences;
        return 0;
    } else if (cmp == s.size()) {
        //we are gonna have to split the current node's string in index cmp--, cz it's larger than s
        cmp--;
        temp = parent.s.substr(cmp, parent.s.size() - cmp);
        parent.s.resize(cmp + 1);
        
        int tempoccurences = parent.occurrences -1;
        parent.occurrences = 0;
        //create new node with the truncated-out string
        insert(r, parent, temp, tempoccurences);
        return 0;

    } else {
        s = s.substr(cmp, s.size() - cmp);
    }

    if (parent.m.find(s[0]) != parent.m.end()) {
        insert(r, *(parent.m[s[0]]), s, 0);
    } else {
        radnode *newnode = new radnode(s);
        parent.m.insert({s[0], newnode});
    }
    return 0;
}

inline char isprefix(string &a, string&b){
    return a.size() <= b.size()? a == b.substr(0, a.size()) : 0;
}

radnode *findparent(binary_radix &r, string &s){
    radnode &h = r.head;
    radnode *haddr  = &r.head;
    radnode *prevad = &NOTFOUND;
    
    for (;;){
        auto search = (h.m.find(s[0]));
        radnode *parentaddress = (search->second);
        if (search != h.m.end()){

            radnode &parent = *parentaddress;
            if (isprefix(parent.s, s)){
                //if they are equal
                if (parent.s.size() == s.size())
                    return (prevad);
                else { //move on
                    prevad = haddr;
                    haddr = parentaddress;
                    h = *parentaddress;
                }

            }
            else return prevad;
        }
        else return prevad;
    }
    return &NOTFOUND;
}

void inserthelp(binary_radix &br, string s){
    auto parentaddr = findparent(br, s);
    radnode &parent = *parentaddr;
    // if (parentaddr != &NOTFOUND){
    //     insert(br, parent, s, 0);
    // }
    // else insert(br, br.head, s, 0);
    insert(br,br.head,s,0);
}
int main(){
    string a = "eae";
    string b = "ea";
    string c = ("eael");
    int j = comparer(a, b);
    binary_radix br;
    inserthelp(br, b);
    inserthelp(br, a);
    inserthelp(br, c);

	return 0;
}
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

struct binary_radix {
    radnode *head;
    std::string st;

    // Regular constructor
    binary_radix() : head(new radnode("")), st("") {}

    // Destructor to clean up allocated memory
    ~binary_radix() {
        delete head;
    }
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



radnode *insert(binary_radix &br, radnode *parentp, string &s, int addoccurences) {
    radnode &parent = *parentp;
    
    int cmp = comparer(parent.s, s);
    string temp;
    if (cmp == EQUAL) {
        parent.occurrences++;
        parent.occurrences+= addoccurences;
        return parentp;
    } else if (cmp < parent.s.size()) {
        //we are gonna have to split the current node's string in index cmp--, cz it's larger than s
        //temp = parent.s.substr(cmp, parent.s.size() - cmp);
        temp = parent.s;
        parent.s.resize(cmp );

        
        int tempoccurences = parent.occurrences -1;
        parent.occurrences = 0;

        // I had trouble learning how to make a struct constructor with a pointer to map, sorry for all of the copy-by-value
        map<char, radnode *> tempmap = parent.m;
        parent.m.clear();
        //create new node with the parent's truncated string and move the old map of children to it
        radnode *newlocation = insert(br, parentp, temp, tempoccurences);
        newlocation->m = tempmap; //~_~ 

        
        //leave s to be inserted here as usual
    }
        s = s.substr(cmp, s.size() - cmp);


    if (parent.m.find(s[0]) != parent.m.end()) {
        insert(br, (parent.m[s[0]]), s, 0);
    } else {
        radnode *newnode = new radnode(s);
        newnode->occurrences = 1;
        parent.m.insert({s[0], newnode});
        return newnode;
    }
    return parentp;
}

inline char isprefix(string &a, string&b){
    return a.size() <= b.size()? a == b.substr(0, a.size()) : 0;
}

radnode *findparent(binary_radix &br, string &s){
    radnode &h = *(br.head);
    radnode *haddr  = br.head;
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
    //auto parentaddr = findparent(br, s);
    //radnode &parent = *parentaddr;
    // if (parentaddr != &NOTFOUND){
    //     insert(br, parent, s, 0);
    // }
    // else insert(br, br.head, s, 0);
    insert(br,br.head,s,0);
}

list<string> traverse(radnode &p, string &depth_indent, string &currstring){
    //traversal
    vector<radnode *> q;
    list<string> foundNodes;
    foundNodes.push_back(p.s);
    depth_indent.append("\t");
    for (auto son: p.m){
        q.push_back(son.second);
        currstring.append(son.second->s);
        foundNodes.push_back(currstring);
        cout << depth_indent << "|-"<<son.second->occurrences<<  ": " <<  currstring<< endl;
        foundNodes.splice(foundNodes.end(), traverse(*(son.second), depth_indent, currstring));

        currstring.resize(currstring.size() - son.second->s.size());
    }
    
    depth_indent.resize(depth_indent.size() -1);
    return foundNodes;
}

void test(binary_radix &br){
    vector<string> nodes {"teste", "testembau", "testemb", "testembaulers", "testemcaulers", "terte", "artes"};
    for (string &s: nodes) inserthelp(br, s);
    string indent(""); string currentstring("");
    list<string> foundNodes = traverse(*(br.head), indent, currentstring);
    for (string &s : nodes){
        int found = 0;
        for (string &fs: foundNodes){
            if (fs == s) {
                found = 1;
                break;}
        }
        if (!found){
            cout << "NOT FOUND: " << s <<endl;
        }
    }
}

int main(){
    string a = "eae";
    binary_radix br;
    inserthelp(br, a);
    inserthelp(br, (string) "eae");
    inserthelp(br, (string) "eae");
    inserthelp(br, (string) "eb");
    inserthelp(br, (string) "eb");inserthelp(br, (string) "eb"); inserthelp(br, (string) "eb"); inserthelp(br, (string) "eb");
    inserthelp(br, (string) "eaele");
    string c; string d;
    test(br);

	return 0;
}
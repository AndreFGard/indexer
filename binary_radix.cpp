#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <list>
#define EQUAL -1
using namespace std;
struct radnode {
    string s;
    map<char, radnode*> m;
    int occurrences;

    // Constructor with an initializer list
    radnode(const string st) : s(st), occurrences(0) {}
};

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

class radix {
public:
    radnode *head;
    std::string st;
    // Regular constructor
    radix() : head(new radnode("")), st("") {}

    ~radix() {
        delete head;
    }

    radnode *insert(radnode *parentp, string &s, int addoccurences) {
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
            radnode *newlocation = insert(parentp, temp, tempoccurences);
            newlocation->m = tempmap; //~_~ 

            
            //leave s to be inserted here as usual
        }
            s = s.substr(cmp, s.size() - cmp);


        if (parent.m.find(s[0]) != parent.m.end()) {
            insert((parent.m[s[0]]), s, 0);
        } else {
            radnode *newnode = new radnode(s);
            newnode->occurrences = 1;
            parent.m.insert({s[0], newnode});
            return newnode;
        }
        return parentp;
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

};

static radnode NOTFOUND("e");

inline char isprefix(string &a, string&b){
    return a.size() <= b.size()? a == b.substr(0, a.size()) : 0;
}

radnode *findparent(radix &rt, string &s){
    radnode &h = *(rt.head);
    radnode *haddr  = rt.head;
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

void inserthelp(radix &rt, string s){
    //auto parentaddr = findparent(rt, s);
    //radnode &parent = *parentaddr;
    // if (parentaddr != &NOTFOUND){
    //     insert(rt, parent, s, 0);
    // }
    // else insert(rt, rt.head, s, 0);
    rt.insert(rt.head,s,0);
}


void test(){
    string a = "eae";
    radix rt;
    inserthelp(rt, a);
    inserthelp(rt, (string) "eae");
    inserthelp(rt, (string) "eae");
    inserthelp(rt, (string) "eb");
    inserthelp(rt, (string) "eb");inserthelp(rt, (string) "eb"); inserthelp(rt, (string) "eb"); inserthelp(rt, (string) "eb");
    inserthelp(rt, (string) "eaele");
    string c; string d;

    
    vector<string> nodes {"teste", "testembau", "testemb", "testembaulers", "testemcaulers", "terte", "artes"};
    for (string &s: nodes) inserthelp(rt, s);
    string indent(""); string currentstring("");
    list<string> foundNodes = rt.traverse(*(rt.head), indent, currentstring);
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
int main() {test();}


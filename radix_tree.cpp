#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <list>
#define EQUAL_STRINGS -1
using namespace std;
#include "radix_tree.h"

inline int comparer(string &a, string &b){
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
			return EQUAL_STRINGS;
		}
		else return i; //from i onwards, put the string in a new node.
	}
	return i;
}

inline char isprefix(string &a, string&b){
    return a.size() <= b.size()? a == b.substr(0, a.size()) : 0;
}


//radix
    // Regular constructor
    radix::radix() : head(new radnode("")), st(""), size(0), nodes(0) {}

    radix::~radix() {
        queue<radnode *> q;
        radnode *cur = head;
        q.push(head);
        while (!q.empty()){
            cur = q.front(); q.pop();
            for (auto s: cur->m){
                q.push(s.second);
            }
            delete cur;
        }
    }

    radnode *radix::insert(radnode *parentp, string &s, int addoccurences) {
        radnode &parent = *parentp;
        
        int cmp = comparer(parent.s, s);
        string temp;
        if (cmp == EQUAL_STRINGS) {
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
            nodes++;
            parent.m.insert({s[0], newnode});
            return newnode;
        }
        return parentp;
    }

    //returns the node that matches the string sequence, it might have been added to the tree or not
    radnode* radix::find(string s){
        radnode *parent = head;
        while(s.size() != 0){
            char beg = s[0];
            if (parent->m.find(beg) != parent->m.end()){
                int oldParentSize = parent->s.size();
                parent = (parent->m[beg]);
                
                if (isprefix(parent->s, s)){
                    s = s.substr(parent->s.size(), s.size()-parent->s.size());
                } else return nullptr;
                
            }
            else return nullptr;
        }
        return parent;
    }

    list<string> radix::traverse(radnode &p, string &depth_indent, string &currstring){
        //traversal
        vector<radnode *> q;
        list<string> foundNodes;
        
        depth_indent.append("\t");
        for (auto son: p.m){
            q.push_back(son.second);

            currstring.append(son.second->s);
            foundNodes.push_back(currstring);
            cout << depth_indent << "|-"<<son.second->occurrences<<  ": " <<  currstring<< endl;
            foundNodes.splice(foundNodes.end(), 
                            traverse(*(son.second), depth_indent, currstring));

            currstring.resize(currstring.size() - son.second->s.size());
        }
        
        depth_indent.resize(depth_indent.size() -1);
        return foundNodes;
    }
    inline list<string> radix::traverse(radnode &p, string base_string) { 
        string a(""); return traverse(p,a,base_string);
    }

    list<string> radix::find_by_prefix(string prefix){
        list<string> founds;
        radnode *source = find(prefix);
        if (source == nullptr) return founds;
        return traverse(*source, prefix);
    }

    radnode* radix::insert(string s){
        size++;
        return radix::insert(head, s, 0);
    }

//;

inline void inserthelp(radix &rt, string s){
    rt.insert(rt.head,s,0);
}


inline void test(){
    radix rt;
    string a = "eae";
    inserthelp(rt, a);
    inserthelp(rt, (string) "eae");
    inserthelp(rt, (string) "eae");
    inserthelp(rt, (string) "eb");
    inserthelp(rt, (string) "eb");inserthelp(rt, (string) "eb"); inserthelp(rt, (string) "eb"); inserthelp(rt, (string) "eb");
    inserthelp(rt, (string) "eaele");
    string c; string d;

    
    vector<string> nodes {"teste", "testembau", "testemb","teste", "testembaulers", "testemcaulers", "terte", "artes"};
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
        cout << s << " " << rt.find(s)->occurrences << endl;
        if (!found){
            cout << "\tNOT FOUND: " << s <<endl;
        }
    }
    string prefix = "te";
    list<string> found_by_prefix = rt.find_by_prefix(prefix);
    cout << "found by the prefix \'te\':" << endl;
    for (string &s: found_by_prefix){
        cout << s << endl;
    }

    
}

#include <dirent.h>
#include <iostream>
#include <sys/types.h>
#include <stdlib.h>
#include <queue>

#include <unistd.h> //for getopt
using namespace std;
#include <string>
#include "radix_tree.h"


int main(int argc, char *argv[]) {
	queue<string> q;
	DIR *dirstream;
	const string path = "./";
	q.push(path);
	radix rt;
	
	//get options:
	char option = 0, use_tree = 1;
	while ((option = getopt(argc, argv, "t")) != -1){
		switch (option){
		case  't':
			use_tree = 1; break;
		default: puts("unrecognized option");
		}
	}

	while(!q.empty()){
		struct dirent *ep;
		string &currdir = q.front(); q.pop();
		dirstream = opendir(currdir.c_str());

		if (dirstream != nullptr){
			while ((ep = readdir(dirstream))){
				if(ep->d_name[0] == '.') continue;

				else if (ep->d_type == DT_DIR){
					string newdir = currdir + ep->d_name + "/"; 
					cout << "d " << newdir << endl;
					q.push(newdir);
					if (use_tree) rt.insert(ep->d_name);
				}
				else if (ep->d_type == DT_REG){ 
					cout << "f "<<currdir << ep->d_name << endl;
					if (use_tree) rt.insert(ep->d_name);
				}
			}


		}
	}

	if (use_tree){
		cout << "ready to search\n";
		string query("");
		cin >> query;
		while (!query.empty()){
			radnode *result = rt.find(query);
			if (result != nullptr) cout << "found!: " << result->s << endl;
			cin >> query;
		}
	}

}
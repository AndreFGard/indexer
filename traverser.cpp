#include <dirent.h>
#include <iostream>
#include <sys/types.h>
#include <stdlib.h>
#include <queue>

#include <unistd.h> //for getopt
using namespace std;
#include <string>
#include "radix_tree.h"


void get_options(int argc, char *argv[], char *use_tree, string &path){
	char option  = 0;
	while ((option = getopt(argc, argv, "t")) != -1){
		switch (option){
		case  't':
			*use_tree = 1; break;
		default: fprintf(stderr, "unrecognized option %c\n", option);
		}
	}
	if (optind < argc){
		path = (string) argv[optind];
		if (path.back() != '/' )
			path.insert(path.end(), '/');
	}
}

int main(int argc, char *argv[]) {
	queue<string> q;
	DIR *dirstream;
	
	char option = 0, use_tree = 0;
	string path = "./";
	
	radix rt;
	
	//get options:
	get_options(argc, argv, &use_tree, path);
	q.push(path);

	while(!q.empty()){
		struct dirent *ep;
		string currdir = q.front(); q.pop();
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
			closedir(dirstream);


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
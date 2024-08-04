#include <dirent.h>
#include <iostream>
#include <sys/types.h>
#include <stdlib.h>
#include <queue>

using namespace std;
#include <string>

int main() {
	queue<string> q;
	DIR *dirstream;
	const string path = "./";
	q.push(path);

	while(!q.empty()){
		struct dirent *ep;

		string &currdir = q.front(); q.pop();
		dirstream = opendir(currdir.c_str());


		if (dirstream != NULL){
			while ((ep = readdir(dirstream))){
				if(ep->d_name[0] == '.') continue;


				if (ep->d_type == DT_DIR){
					string newdir = currdir + ep->d_name + "/"; 
					printf("dir %s\n", newdir.c_str());
					q.push(newdir);
				}
				else if (ep->d_type == DT_REG) 
					printf("file %s%s\n",currdir.c_str(), ep->d_name);
			}


		}
	}


}
#include <iostream>
#include "radix_tree.h"
#include <string>
#include <time.h>
using namespace std;

int main(){
    radix rt;
    string src;
    cin >> src;
    time_t start = time(nullptr);

    while (src != "$$ENDOFPROGRAM"){
        rt.insert(src);
        cin >> src;
    }
    time_t after_insertion = time(nullptr);
    cout << "finish insertion in " << after_insertion - start << endl;

    cin >> src;
    int success = 1;
    while (src != "$$ENDOFPROGRAM"){
        //cout << ((rt.find(src) != nullptr) ? 1: (success = 0) )<< endl;
        if (rt.find(src) == nullptr) success = 0;
        cin >> src;
    }
    time_t after_search = time(nullptr);
    cout << "finish search in " << after_search - after_insertion << endl;
    cout << "success: "<< success << endl;
    cout << "number of nodes: " << rt.nodes << " number of strings added: " << rt.size << endl;
}
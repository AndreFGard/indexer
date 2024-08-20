#include <vector>
#include <iostream>
#include <string>       
using namespace std;

#include "predecessor.h"

template<class T>
predecessorPath<T>::predecessorPath(void){
    size = 0;
}

//returns a READ ONLY reference to the vector of dads
template<class T>
const vector<T*>& predecessorPath<T>::getPreds(int sonidx){
    path.clear();
    int dadidx = pred[sonidx].pred;

    while (dadidx != sonidx){
        path.push_back(&(pred[dadidx].val));
        sonidx = dadidx;
        dadidx = pred[sonidx].pred;
        
    }
    return path;
}

template<class T> int
predecessorPath<T>::addSon(T &son, int dadidx){
    pred.push_back(prednode(son, dadidx));
    return pred.size() -1;
}

int ___testpred(){
    predecessorPath<string> p;
    string pai = "pai", son = "son", gson = "gson";
    p.addSon(pai, 0);
    p.addSon(son, 0);
    p.addSon(gson, 1);
    for (auto n: p.getPreds(2)){
        cout << *n << " ";
    }

    cout << endl;

}
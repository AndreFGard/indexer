template<typename T>
struct prednode{
    T val;
    int pred;

    prednode(T &value, int predidx){
        val = value;
        pred = predidx;
    }
};


template<class T> class predecessorPath
{
    vector<prednode<T>> pred;
    int size;
    vector<T*> path;
public:
    predecessorPath(void);
    const vector<T*> &getPreds(int sonidx);
    int addSon(T &son, int dadidx);

};
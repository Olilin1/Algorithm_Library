#ifndef SEGMENT_TREE_HPP
#define SEGMENT_TREE_HPP

#include<vector>
#include <functional>

template<class T>
class Segment_Tree{

int leftMin, rightMax;
std::vector<T> internal;
std::function<T(T,T)> merge;

void compute(int at, int l, int r, const std::vector<T>& v){
    if(l == r){
        internal[at] = v[l];
        return;
    }
    int mid = (l+r)/2;
    compute(at*2 + 1, l, mid, v);
    compute(at*2 + 2, mid+1, r, v);

    internal[at] = merge(internal[at*2+1], internal[at*2+2]);
}

T search(int at, int l, int r, int currL, int currR){
    if(currL >= l && currR <= r) return internal[at];

    int mid = (currL + currR) / 2;
    if(r <= mid) return search(at*2+1, l, r, currL, mid);
    else if(l >= mid+1) return search(at*2+2, l, r, mid+1, currR);

    return merge(search(at*2+1, l, r, currL, mid), search(at*2+2, l, r, mid+1, currR));
}

public:

Segment_Tree(const std::vector<T>& v, std::function<T(T,T)> mergeFunc){
    internal.resize(v.size()*4);
    merge = mergeFunc;
    leftMin = 0;
    rightMax = v.size()-1;
    compute(0, leftMin, rightMax, v);
}

T Query(int left, int right){
    return search(0, left, right, leftMin, rightMax);
}

};

#endif
/*
AUTHOR: Oliver Lindgren
*/

#include<iostream>
#include"MST.hpp"

using namespace std;

int main(){
    int n, m;

    while(cin >> n >> m){
        if(n == 0) return 0;
        std::vector<std::pair<long long int, std::pair<size_t, size_t>>> edges(m);
    
        for(int i = 0; i < m; i++){
            cin >> edges[i].second.first >> edges[i].second.second >> edges[i].first;
        }

        auto x = mst(n, edges);

        if(x.second.size() != n-1) cout << "Impossible\n";
        else{
            cout << x.first << '\n';
            for(auto& a : x.second){
                if(a.first > a.second){ 
                    swap(a.first, a.second);
                }
            }
            sort(x.second.begin(), x.second.end());
            for(auto a : x.second) cout << a.first << ' ' <<a.second << '\n';
        }
    }

    

}
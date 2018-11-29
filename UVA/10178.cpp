#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

struct dsu{

    vector < int > parent , rank ;
    dsu(int n){
        parent = rank = vector < int > (n + 1, 0);
        for(int i = 1 ; i <= n ; i++) parent[i] = i ;
    }
    int find_set(int v){
        if(v == parent[v]) return v;
        return parent[v] = find_set(parent[v]) ;
    }
    void link(int u , int v){
        if(rank[u] > rank[v]) swap(u , v);
        parent[u] = v ;
        if(rank[u] == rank[v]) rank[v] ++ ;
    }
    bool union_set(int u , int v){
         u = find_set(u) , v = find_set(v) ;
         if(u != v)
              link(u , v) ;
         return u != v;
    }
};

int vis[256] ;
int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;


    int n , e ;
    while(cin >> n >> e){

            dsu tree(n);
            memset(vis , 0 , sizeof vis) ;
            int cnt = 1;

            for(int i = 0 ; i < e;  i++){
                   char c1 , c2;
                   cin >> c1 >> c2 ;
                   if(!vis[c1]) vis[c1] = cnt ++ ;
                   if(!vis[c2]) vis[c2] = cnt ++ ;
                   tree.union_set(vis[c1] , vis[c2]);
            }

            set < int > se ;
            for(int i =  1 ; i <= n ; i++)
                   se.insert(tree.find_set(i));

            int c = se.size() ;
            cout << 1 + c + e - n << endl ;
    }

    return 0;
}

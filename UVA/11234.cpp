/*
	Idea : https://github.com/AbdelrahmanRamadan/competitive-programming/blob/master/UVA/11234%20-%20Expressions.cpp
*/

#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

vector < vector < int > > G ;
string s ;

string bfs(int src){

     string ret = "";

     queue < int > Q ;
     Q.push(src);
     while(!Q.empty()){
          int u = Q.front() ;
          Q.pop() ;
          ret += s[u] ;
          for(auto v : G[u]){
               Q.push(v);
          }
     }
     reverse(ret.begin() , ret.end());
     return ret ;
}

int main() {

    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int t ; cin >> t ;

    while(t--){
          cin >> s;

          int n = s.size() ;

          G.clear() ;
          G.resize(n);

          stack < int > st;

          for(int i = 0 ; i < n ; i++){
                if(islower(s[i])) st.push(i);
                else{
                      int a = st.top() ;
                      st.pop();
                      int b = st.top();
                      st.pop() ;
                      G[i].push_back(b);
                      G[i].push_back(a);
                      st.push(i);
                }
          }

          cout << bfs(n - 1) << endl ;
    }



    return 0;
}

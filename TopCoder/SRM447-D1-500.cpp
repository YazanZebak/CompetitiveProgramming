/*
    MinCut : https://github.com/MohamedNabil97/CompetitiveProgramming/blob/master/TopCoder/SRM447-D1-500.cpp
    DP     : https://apps.topcoder.com/wiki/display/tc/SRM+447
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 100 ;
int cap[N][N];
vector < int > parent ;
int n ;

int bfs(int src , int sink){

    parent = vector < int > (n , -1) ;

    parent[src] = -2 ;
    queue < pair < int , int > > Q ;
    Q.push({src , INT_MAX});

    while(!Q.empty()){
         auto p = Q.front() ;
         Q.pop() ;
         int u = p.first , flow = p.second ;
         for(int i = 0 ; i < n ; i++){
                if(parent[i] != -1 || cap[u][i] <= 0) continue ;
                parent[i] = u ;
                int new_flow = min(flow , cap[u][i]) ;
                if(i == sink) return new_flow ;
                Q.push({i , new_flow});
         }
    }

    return 0 ;
}

int minCut(int src , int sink){


    int flow = 0 , new_flow = 0 ;
    while( (new_flow = bfs(src , sink)) ){
          flow += new_flow ;
          int cur = sink;
          while(cur != src){
               int prev = parent[cur];
               cap[prev][cur] -= new_flow ;
               cap[cur][prev] += new_flow ;
               cur = prev ;
          }
    }

    return flow ;
}

class PeopleYouMayKnow{

public:
   int maximalScore(vector <string> friends, int person1, int person2){

       n = (int)friends.size() ;

       memset(cap , 0 , sizeof cap);

       vector < int > ve1 , ve2 ;

       for(int i = 0 ; i < n ; i++){
              if(friends[person1][i] == 'Y') ve1.push_back(i) , cap[person1 + n][i] = cap[i + n][person1] = 1 ;
              if(friends[i][person2] == 'Y') ve2.push_back(i) , cap[person2 + n][i] = cap[i + n][person2] = 1 ;
              cap[i][i + n] = 1 ;
       }

       for(auto i : ve1){
             for(auto j : ve2){
                   if(friends[i][j] == 'Y'){
                        cap[i + n][j] = 1 ;
                        cap[j + n][i] = 1 ;
                   }
             }
       }

       cap[person1][person1 + n] = 1 << 30  ;
       cap[person2][person2 + n] = 1 << 30  ;

       n = 2 * n ;

       return minCut(person1 , person2) ;
   }

};


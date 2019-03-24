/*
    Idea : 
      - let's divide the problem into subproblems 
      - the first one is for each team we need to calculate the probability to solve i problem [1...m].
      - we can do that easily by pick or leave topdown and save it in dp[team_id][num_problems]. 
      - now we want to solve the orginal problem.
      - let's try for each team can solve from 1 to m problem we already calc the answer for this before.
      - we keep the maximum number of problems solved by each team lately to check if the champion solved at least n problem or not.
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
typedef long long ll ;
using namespace std;

int m , t , n ;
double p[1001][35];
double memo[1001][35];
double dp[1001][40];

double solve(int i , int cnt , int j){

    if(i == m){
         return (cnt == 0) ;
    }
    if(cnt < 0) return 0 ;

    double &ret = memo[i][cnt] ;
    if(ret == ret) return ret ;

    double c1 = p[j][i] * solve(i + 1 , cnt - 1 , j);
    double c2 = (1 - p[j][i]) * solve(i + 1,  cnt , j) ;

    return ret = c1 + c2 ;
}

double solve(int i , int mx){

     if(i == t){
           return mx >= n;
     }

     double &ret = memo[i][mx];
     if(ret == ret) return ret ;

     ret = 0 ;
     for(int j = 1 ; j <= m ; j++){
          ret += (dp[i][j] * solve(i + 1 , max(mx , j))) ;
     }

     return ret ;
}

int main()
{
    //ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    while(cin >> m >> t >> n){

          if(!m && !t && !n) break ;


          memset(dp , 0 , sizeof dp);

          for(int i = 0 ; i < t ; i++){
              for(int j = 0 ; j < m ; j++){
                   cin >> p[i][j];
              }
          }

          for(int i = 0 ; i < t ; i++){
               memset(memo , -1 , sizeof memo);
               for(int j = 1 ; j <= m ; j++){
                    dp[i][j] = solve(0 , j , i);
               }
          }


          memset(memo , -1 , sizeof memo);
          printf("%.3f\n",solve(0 , 0));
    }


    return 0;
}

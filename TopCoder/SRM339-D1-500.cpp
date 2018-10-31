#include <bits/stdc++.h>
typedef long long ll ;
using namespace std ;

double memo[51][1001][12];
class TestBettingStrategy {

public :

    int s ;
    double winProb ;

    double winProbability(int sum , int goalSum , int rounds , int prob){
          memset(memo , -1 , sizeof memo) ;
          s = goalSum ;
          winProb = prob * 1.0 / 100.0 ;
          return solve(rounds , sum , 0);
    }

    double solve(int i , int sum , int val){

           if(sum >= s) return 1;
           if(i == 0) return 0 ;

           int bet = (1 << val);
           if(bet > sum) return 0 ;

           double &ret = memo[i][sum][val] ;
           if(ret == ret) return ret ;

           double c1 = winProb * solve(i - 1 , sum + bet , 0) ;
           double c2 = (1.0 - winProb) * solve(i - 1 , sum - bet , val + 1) ;

           return ret = c1 + c2;
    }
};

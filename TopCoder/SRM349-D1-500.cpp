#include <bits/stdc++.h>
typedef long long ll ;
using namespace std ;

ll memo[35][35] ;
class DiceGames{

public :

    vector < int > ve ;
    ll countFormations(vector < int > sides){
       memset(memo , -1 , sizeof memo);
       ve = sides ;
       sort(ve.begin() , ve.end());
       return solve(0 , 1);
    }

    ll solve(int i , int last){
       if(i == ve.size()) return 1;
       ll &ret = memo[i][last] ;
       if(ret != -1) return ret ;
       ret = 0 ;
       for(int j = last ; j <= ve[i] ; j++){
             ret += solve(i + 1 , j) ;
       }
       return ret ;
    }

};

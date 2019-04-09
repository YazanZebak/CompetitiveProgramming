#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int n ;
vector < int > ve;
double memo[51][51] ;

double solve(int i , int j){

    if(i > j) return 0 ;

    double &ret = memo[i][j] ;
    if(ret == ret) return ret ;

    int c1 = ve[i] - solve(i + 1 , j);
    int c2 = ve[j] - solve(i , j - 1) ;
    return ret = max(c1 , c2);
}

class BagsOfGold{

    int netGain(vector <int> bags){

        memset(memo , -1 , sizeof memo);
        ve = bags ;
        n = ve.size() ;

        return (int)solve(0 , n - 1) ;
    }

};

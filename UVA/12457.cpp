#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;


int n ;
double p ;
double memo[50][50] ;

double solve(int i , int win){

    if(i == 2 * n - 1)
          return (win >= n);

    double &ret = memo[i][win];
    if(ret == ret) return ret;

    double c1 = p * solve(i + 1 , win + 1) ;
    double c2 = (1.0 - p) * solve(i + 1 , win) ;

    return ret = c1 + c2;
}

int main()
{
    ios::sync_with_stdio(false) ;

    int t ; cin >> t;

    while(t--){
          memset(memo , -1 , sizeof memo) ;
          cin >> n >> p ;
          cout << fixed << setprecision(2) <<  solve(0 , 0) << endl ;
    }

    return 0;
}

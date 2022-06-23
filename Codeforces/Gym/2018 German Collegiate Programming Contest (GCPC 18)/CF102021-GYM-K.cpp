/*
    Idea:
        - lets try all the valid subsets and keep the sum of each set + 10 (5 src + 5 dest) also we need cnt for size of the set.
        - if the set sum's with min/max overlap is smaller/greater than the total distance trash the answer.
        - else we can do binary search on how much we want to not overlap : sum - mid * (cnt + 1) >= g
        - O(1) mid = sum - g / cnt + 1.
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int n , d ;
vector < int > ve;

double memo[61][61][1500];

double solve(int i , int sum , int cnt){

    if(sum > 1500) return -1 ;
    if(i == n) {
          if(sum < d) return -1 ;
          if(sum - 5.0 * (cnt + 1) > d) return -1;
          return (sum - d) * 1.0 / (cnt + 1);
    }

    double &ret = memo[i][cnt][sum];
    if(ret == ret) return ret;

    ret = solve(i + 1 , sum , cnt);
    ret = max(ret , solve(i + 1 , sum + ve[i] , cnt + 1)) ;

    return ret;
}


int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0);

    cin >> n >> d ;

    for(int i = 0 ; i < n ; i++){
          int x ; cin >> x ;
          ve.push_back(x);
    }

    memset(memo , -1 , sizeof memo);

    double res = solve(0 , 10 , 0);

    if(res < 0) return cout << "impossible" << endl , 0 ;

    cout << fixed << setprecision(7) << res << endl ;

    return 0;
}

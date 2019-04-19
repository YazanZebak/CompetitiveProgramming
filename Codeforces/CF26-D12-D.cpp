/*
    Idea :
        - https://stackoverflow.com/questions/25281005/calculating-probability-for-funprob
        - https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Codeforces/CF26-D12-D.txt
        - https://codeforces.com/blog/entry/610
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    ll n , m , k ;
    cin >> n >> m >> k ;

    if(m > n + k)
        return cout << 0 << endl , 0;

    double res = 1 ;

    for(int i = 0 ; i <= k ; i++){
         res *= (m - i) ;
         res /= (n + i + 1) ;
    }

    cout << fixed << setprecision(6) << 1 - res << endl ;

    return 0;
}

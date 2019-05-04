/*
    idea :
        - let m be the minimum number of stones in a pile, and let x be the number of piles with m stones.
        - Alice can win if and only if x <= n/2.
        - https://codeforces.com/blog/entry/66878
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int n ; cin >> n ;

    vector < int > ve ;

    for(int i = 0 ; i < n ; i++){
          int x ; cin >> x ;
          ve.push_back(x);
    }
    sort(ve.begin() , ve.end()) ;

    int res = ve[0] ^ ve[n / 2] ;

    if(res) cout << "Alice" << endl ;

    else cout << "Bob" << endl ;


    return 0;
}

/*
    Idea : https://github.com/abdullaAshraf/Problem-Solving/blob/master/UVA/1362.cpp
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

string s ;
const ll mod = 1000000000 ;
ll memo[301][301];

ll solve(int i , int j) {

    if(i == j)
        return 1 ;

    ll &ret = memo[i][j] ;
    if(ret != -1) return ret ;

    ret = 0 ;

    if(s[i] != s[j]) return 0 ;

    for(int k = i +  1 ; k <= j ; k ++)
        if(s[i] == s[k])
            ret = ( ret +  solve(i + 1 , k - 1) * solve(k , j) ) % mod ;


    return ret ;
}


int main() {

    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    while(cin >> s) {
        memset(memo , -1 , sizeof memo);
        cout << solve(0 , s.size() - 1) << endl ;
    }



    return 0;
}

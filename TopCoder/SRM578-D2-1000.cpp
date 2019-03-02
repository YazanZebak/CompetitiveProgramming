/*
    Idea :
        - for each cell i between [0 , n - 1] we either can take or not.
        - except when a cell i come in end of interval [L , R].
        - in this case we must take it unless there is another cell j such that j != i and j is between[L , R].
        - record for each i it's intervals that's make the solution easier.

*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int n ;
const int mod = 1e9 + 7 ;
vector < vector < pair < int , int > > > interval(301) ;
int memo[302][302];

int solve(int i , int last) {

    if(i == n)
        return 1;

    int &ret = memo[i][last] ;

    if(ret != -1)
        return ret ;

    ret = 0 ;

    for(auto j : interval[i]) {
        if(i == j.second) {
            if(j.first <= last && j.second >= last)  continue ;

            else {
                int c1 = solve(i + 1 , i) % mod ;
                ret += c1 ;
                return ret %= mod ;
            }
        }
    }

    int c1 = solve(i + 1 , last) % mod ;
    int c2 = solve(i + 1 , i) % mod ;

    return ret = (c1 + c2) % mod ;
}

class WolfInZooDivTwo {

public :


    int count(int N , vector < string > L , vector < string > R) {

        n = N ;
        string s1 = "" , s2 = "" ;
        for(auto i : L) s1 += i ;
        for(auto i : R) s2 += i ;

        vector < int > le , ri ;

        le = get(s1) ;
        ri = get(s2) ;

        memset(memo , -1 , sizeof  memo) ;

        for(int i = 0 ; i < n ; i++) {
            for(int j = 0 ; j < (int)le.size() ; j++) {
                if(le[j] <= i && ri[j] >= i) interval[i].push_back({le[j] , ri[j]});
            }
        }

        return solve(0 , n);
    }

    int convert(string s) {

        if(s.back() == ' ') s.pop_back() ;

        int ret = 0 ;
        for(int i = 0 ; i < (int)s.size() ; i++)
            ret = ret * 10 + (s[i] - '0') ;
        return ret ;
    }

    vector < int > get(string s) {

        vector < int > ret ;
        for(int i = 0 ; i < (int)s.size() ; i++) {
            int j = i ;
            while(j < (int)s.size() && isdigit(s[j])) j ++ ;
            ret.push_back(convert(s.substr(i  , j - i)));
            i = j ;
        }

        return ret ;
    }
};

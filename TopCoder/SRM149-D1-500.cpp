#include <bits/stdc++.h>
typedef long long ll ;
using namespace std ;

ll memo[51];
unordered_map < string , int > exist ;
class MessageMess {
public :

    string s , ans = "";

    string restore(vector < string > dictionary , string message) {

        for(auto str : dictionary) exist[str] = 1 ;
        s = message;
        memset(memo , -1 , sizeof memo);

        ll res = solve(0);

        if(!res) return "IMPOSSIBLE!" ;
        if(res > 1) return "AMBIGUOUS!" ;
        build(0) ;
        ans.pop_back() ;
        return ans ;
    }

    ll solve(int i) {
        if(i == (int)s.size()) return 1 ;
        ll &ret = memo[i] ;
        if(ret != -1) return ret ;
        ret = 0 ;
        string str ;
        for(int j = i ; j < (int)s.size() ; j++) {
            str.push_back(s[j]) ;
            if(exist[str])
                ret += solve(j + 1) ;
        }
        return ret ;
    }

    void build(int i) {
        if(i == (int)s.size()) return ;
        ll optimal = memo[i] ;
        string str ;
        ll c = 0  ;
        for(int j = i ; j < (int)s.size() ; j++) {
            str.push_back(s[j]);
            if(exist[str]) {
                c += solve(j + 1);
                if(c == optimal) {
                    ans = ans + str + " " ;
                    build(j + 1);
                    break ;
                }
            }
        }
    }
};


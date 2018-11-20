#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;


bool check(string &s) {
    for(int i = 0 ; i < s.size() - 1;  i++)
        if(s[i] == s[i + 1]) return false ;
    return (s.back() != s.front());
}

int main() {
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int t ;
    cin >> t ;

    while(t--) {

        string s ;
        cin >> s ;
        int n = s.size() ;

        if(check(s)) {
            cout << "yes" << endl ;
            continue ;
        }

        int R = 0 , G = 0 , cnt = 0 ;
        for(int i = 0 ; i < n ; i++) {
            if(s[i] == s[(i + 1) % n] && s[i] == 'R') cnt++ , R = max(R , cnt) ;
            else cnt = 0 ;
        }
        if(R > 2) {
            cout << "no" << endl ;
            continue ;
        }
        cnt = 0 ;
        for(int i = 0 ; i < n ; i++) {
            if(s[i] == s[(i + 1) % n] && s[i] == 'G') cnt ++ , G = max(G , cnt) ;
            else cnt = 0 ;
        }
        if(G > 2) {
            cout << "no" << endl ;
            continue ;
        }
        int l = -1 , r = -1 , ok = 0 ;
        for(int i = 0 ; i < n ; i++) {
            if(s[i] == s[(i + 1) % n]) {
                if(l == -1) l = i + 1 ;
                else if(r == -1) r = i  ;
                else ok = 1;
            }
        }

        if(ok) {
            cout << "no" << endl;
            continue ;
        }

        reverse(s.begin() + l , s.begin() + r + 1) ;

        cout << (check(s) ? "yes" : "no") << endl ;


    }


    return 0;
}

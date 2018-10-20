#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;


int mat[10003][12];
map < pair < int , int > , int > exist ;
hash < string > strHash;

vector < string > split(string &s) {

    vector < string > ret ;
    string str ;
    for(auto c : s) {
        if(c == ',') {
            ret.push_back(str);
            str.clear() ;
        } else str.push_back(c) ;
    }
    ret.push_back(str);
    return ret ;
}

int main() {

    int n , m ;

    while(cin >> n >> m) {

        while(getchar() != '\n') ;

        for(int i = 0 ; i < n ; i++) {
            string s ;
            getline(cin , s) ;
            vector < string > vs = split(s) ;
            for(int j = 0 ; j < m ; j++) mat[i][j] = strHash(vs[j]) ;
        }

        bool ok = 0 ;
        int r1 = 0 , r2 = 0 , c1 = 0 , c2 = 0 ;

        for(int j = 0 ; j < m && !ok ; j++) {
            for(int k = j + 1 ; k < m && !ok ; k++) {
                for(int i = 0 ; i < n && !ok ; i++) {

                    pair < int , int > p = make_pair( mat[i][j] , mat[i][k] );

                    if(!exist.count(p)) exist[p] = i ;

                    else {
                        r1 = exist[p] + 1 ;
                        r2 = i + 1;
                        c1 = j + 1 ;
                        c2 = k + 1;
                        ok = 1 ;
                    }
                }
                exist.clear();
            }
        }

        if(ok)
            printf("NO\n%d %d\n%d %d\n",r1,r2,c1,c2) ;
        else
            printf("YES\n");
    }

    return 0;
}

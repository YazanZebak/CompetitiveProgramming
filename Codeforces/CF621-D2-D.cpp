/*
    Idea:
     - the maximum range of long double is 1.18973 * 10^4932, which is greater than 200^200 = 1.6 * 10^460
     - with this information we can implement the problem easily
     - log(x^y^z) = y ^ z * log(x)
     - (x^y)^z = (x^(y*z)) , log((x^y)^z) = y * z * log(x)
     - soluation by complex numbers :
     - https://codeforces.com/blog/entry/23196?#comment-275965
     - https://codeforces.com/contest/621/submission/15789501
*/
#include <bits/stdc++.h>
typedef long long ll ;
typedef long double ld ;
using namespace std;

vector < ld > val ;

vector < string > ve = {"x^y^z" , "x^z^y" , "(x^y)^z",
                        "y^x^z" , "y^z^x" , "(y^x)^z",
                        "z^x^y" , "z^y^x" , "(z^x)^y"};

ld calc(string s) {
    ld a , b , c;
    if(s[0] == '(') {
        a = val[s[1] - 'x'];
        b = val[s[3] - 'x'];
        c = val[s[6] - 'x'];
        return b * c * log(a) ;
    }
    else {
        a = val[s[0] - 'x'];
        b = val[s[2] - 'x'];
        c = val[s[4] - 'x'];
        return pow(b , c) * log(a) ;
    }
}


int main() {

    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    for(int i = 0 ; i < 3; i++){
         ld x ; cin >> x ;
         val.push_back(x);
    }

    ld ans = -1;
    int id = -1 ;

    for(int i = 0 ; i < 12 ; i++){
          ld t = calc(ve[i]) ;
          if(t > ans){
              ans = t ;
              id = i ;
          }
    }

    cout << ve[id] << endl ;

    return 0;
}

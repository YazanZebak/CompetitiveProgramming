#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

vector < int > prefixFunc(string str){
     int m = (int)str.size() ;
     vector < int > ret = vector < int > (m , 0) ;
     for(int i = 1 , k = 0 ; i < m ; i++){
             while(k > 0 && str[i] != str[k])
                  k = ret[k - 1] ;
             ret[i] = (str[i] == str[k] ? ++k : k);
     }
     return ret;
}


int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int t ; cin >> t ;
    int c = 1 ;
    while(t--){
          int n ; cin >> n ;
          string  s ; cin >> s ;
          cout << "Test case #" << c++ << endl ;

          vector < int > F = prefixFunc(s);
          for(int i = 1 ; i < n ; i++){
                 int len = i + 1 ;
                 if(len % (len - F[i]) == 0){
                      int k = len / (len - F[i]);
                      if(k == 1) continue ;
                      cout << len << " " << len / (len - F[i]) << endl ;
                 }
          }
    }


    return 0;
}

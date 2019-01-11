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
vector < int > kmp(string str , string pat){
      int n = (int)str.size() ;
      int m = (int)pat.size() ;
      vector < int > ret ;
      vector < int > prefix = prefixFunc(pat) ;
      for(int i = 0 , k = 0 ; i < n ; i++){
            while(k > 0 && str[i] != pat[k])
                  k = prefix[k - 1] ;
            if(pat[k] == str[i]) k++ ;
            if(k == m){
                  ret.push_back(i - m + 1) ;
                  k = prefix[k - 1] ;
            }
      }
      return ret ;
}


int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int t ; cin >> t ;
    while(t--){
          int n ; cin >> n ;
          vector < int > ve;
          for(int i = 0 ; i < n ; i++){
               int x ; cin >> x;
               ve.push_back(x) ;
          }
          string pat ; cin >> pat;
          string str = "" ;
          for(int i = 1 ; i < n ; i++){
                 if(ve[i - 1] < ve[i]) str.push_back('G') ;
                 if(ve[i - 1] > ve[i]) str.push_back('L') ;
                 if(ve[i - 1] == ve[i]) str.push_back('E') ;
          }

          bool res = (int)kmp(str , pat).size() != 0 ;

          cout << (res ? "YES" : "NO") << endl ;
    }


    return 0;
}

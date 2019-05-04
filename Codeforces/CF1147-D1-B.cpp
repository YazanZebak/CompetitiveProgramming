#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

vector < int > prefixFunction(string s){

    int m = (int)s.size() ;
    vector < int > ret(m , 0) ;

    for(int i = 1 , k = 0 ; i < m ; i++){
          while(k > 0 && s[k] != s[i])
                k = ret[k - 1] ;
          ret[i] = (s[i] == s[k] ? ++k : k) ;
    }
    return ret ;
}

vector < int > kmp(string str , string pat){

      int n = (int)str.size() ;
      int m = (int)pat.size() ;

      vector < int > ret ;
      vector < int > prefix = prefixFunction(pat);

      for(int i = 0 , k = 0 ; i < n ; i++){
            while(k > 0 && pat[k] != str[i])
                k = prefix[k - 1];

            if(pat[k] == str[i]) k++ ;

            if(k == m){
                  ret.push_back(i - m + 1) ;
                  k = prefix[k - 1];
            }
      }

      return ret ;
}


int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int n , m ;

    cin >> n >> m ;

    vector < vector < int > > ve(n + 1 ) ;

    for(int i = 0 ; i < m ; i++){
            int x , y ;
            cin >> x >> y ;
            if(x > y) swap(x , y) ;
            int jump = y - x ;
            ve[x].push_back(jump) ;
            ve[y].push_back(n - jump) ;
    }

    string res = "" ;

    for(int i = 1 ; i <= n ; i++){
         ve[i].push_back(-1) ;
         sort(ve[i].begin() , ve[i].end());
         for(auto j : ve[i])
               res += to_string(j);
    }

    vector < int > ans = kmp(res + res , res) ;

    if(ans.size() > 2)
           cout << "Yes" << endl ;
    else
           cout << "No" << endl ;


    return 0;
}

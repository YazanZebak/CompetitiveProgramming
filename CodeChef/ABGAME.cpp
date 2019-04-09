/*
    Idea : https://discuss.codechef.com/t/abgame-editorial/21024
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;


int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int t ; cin >> t ;

    while(t--){
         string s ; cin >> s ;
         int n = s.size() ;

         vector < int > pile ;
         int a , b ;

         int cnt = 0 ;
         bool turn = 1 ;
         a = b = 0 ;

         for(int i = 0 ; i < n ; i++){
                if(s[i] == '.') continue ;

                int j = i + 1 ;
                while(j < n && s[j] == '.') j++ ;
                cnt = (j - i - 1) ;

                if(cnt < 0) continue ;


                if(j < n && s[i] != s[j]) pile.push_back(cnt);

                else {
                     if(s[i] == 'A') a += cnt ;
                     else b += cnt ;
                }

                i = j ;
         }

         if(a > b) cout << "A" << endl ;

         else if(a < b) cout << "B" << endl ;

         else{

              if(pile.empty()){
                   cout << "B" << endl ;
                   continue ;
              }

              int res = pile[0] ;
              for(int i = 1 ; i < pile.size() ; i++) res ^= pile[i];

              if(!res) cout << "B" << endl  ;
              else cout << "A" << endl ;
         }

    }

    return 0;
}

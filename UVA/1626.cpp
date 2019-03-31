#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

string s ;
int memo[101][101];

int solve(int i , int j){

   if(i == j) return 1 ;
   if(i > j) return 0 ;

   int &ret = memo[i][j] ;
   if(ret != -1) return ret ;

   ret = INT_MAX ;
   if( (s[i] == '(' && s[j] == ')') || (s[i] == '[' && s[j] == ']'))
        ret = min(ret , solve(i + 1 , j - 1));

   for(int k = i ; k < j ; k++)
       ret = min(ret , solve(i , k) + solve(k + 1 , j));

   return ret ;
}

vector < int > res ;
void build(int i , int j){
     if(i > j) return ;
     if(i == j){
          res.push_back(i);
          return ;
     }
     int optimal = solve(i , j);

     if( (s[i] == '(' && s[j] == ')') || (s[i] == '[' && s[j] == ']')){
           int c1 = solve(i + 1 , j - 1);
           if(c1 == optimal){
                build(i + 1 , j - 1);
                return ;
           }
     }

     for(int k = i ; k < j ; k++){
          int c1 = solve(i , k) + solve(k + 1 , j);
          if(c1 == optimal){
              build(i , k) ;
              build(k + 1 , j);
              return ;
          }
     }

}


int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int t ; cin >> t ;
    getline(cin , s);
    while(t--){
          memset(memo , -1 , sizeof memo);
          res.clear() ;
          getline(cin , s);
          getline(cin , s);
          int n = s.size() ;
          solve(0 , n - 1) ;
          build(0 , n - 1) ;
          sort(res.begin() , res.end());
          int j = 0 ;
          for(int i = 0 ; i < s.size() ; i++){
               if(j < res.size() && res[j] == i){
                    j++ ;
                    if(s[i] == ')' || s[i] == '(')
                          cout << "()"  ;
                    else
                         cout << "[]" ;
               }
               else cout << s[i] ;
          }
          cout << endl ;
          if(t) cout << endl ;
    }

    return 0;
}

#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int h , w , k ;
const int mod = 1e9 + 7 ;
int memo[105][10] ;

int solve(int height , int pos){

    if(height == 0) return pos == k ;

    int &ret = memo[height][pos] ;
    if(ret != -1) return ret ;

    ret = 0 ;
    for(int i = 0 ; i < (1 << (w - 1)) ; i++){
          vector < int > temp ;
          for(int j = 0  ; j < w - 1 ; j++)
               if(i & (1 << j)) temp.push_back(j) ;

          bool flag = false ;
          for(int j = 1 ; j < temp.size() ; j++)
               if(temp[j - 1] + 1 == temp[j]) flag = true ;

          if(flag) continue ;

          int cur = pos ;
          for(int j = 0 ; j < temp.size() ; j++){
                if(temp[j] == cur){
                       cur ++ ;
                       break;
                }
                if(temp[j] + 1 == cur){
                      cur -- ;
                      break ;
                }
          }
          ret += solve(height - 1 , cur);
          ret %= mod ;
    }

    return ret ;
}

int main(){

    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    cin >> h >> w >> k ;
    k-- ;
    memset(memo , -1 , sizeof memo) ;
    cout << solve(h , 0) << endl ;

    return 0;
}

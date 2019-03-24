/*
	Idea: 
		- we want to count number of strings such that the number of paths between 0 and n - 1 even number 
		- the number of paths is even if and only if the string contain two muddy cells or more as a substring 
		- or X cells of dry cells as substring such that X % 3 == 0 
		- with this two properties we can count the number of valid string using dp_ranges easily.
		- keep flag to check if one of the properties is true.
		- keep last to form the string in alternative way. (avoid duplicate)
		- cnt to make sure we used excatly muddyCount muddy cell.
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const ll mod = 555555555 ;
ll memo[556][556][2][2];
int n ;

ll solve(int i , int cnt , bool flag , bool last){

    if(i == n){
          return (flag && cnt == 0 && last == 1) ;
    }
    if(cnt < 0) return 0 ;

    ll &ret = memo[i][cnt][flag][last];
    if(ret != -1) return ret ;

    ret = 0 ;
    for(int j = i ; j < n ; j++){
            if(last){
               ret += solve(j + 1 , cnt - (j - i + 1) , (flag || (j - i + 1) >= 2) , !last);
               ret %= mod ;
            }
            else{
                ret += solve(j + 1 , cnt , (flag || (j - i + 1) % 3 == 0) , !last);
                ret %= mod ;
            }
    }

    return ret ;
}


class MuddyRoad2{

public:
   int theCount(int N, int muddyCount){
       n = N ;
       memset(memo , -1 , sizeof memo);
       return solve(0 , muddyCount , 0 , 0) ;
   }

};


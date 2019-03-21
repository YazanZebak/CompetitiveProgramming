/*
	Idea : 
		- We will search n by binary search , such function is monotone.
		- Because the amount of numbers with exactly k 1-bits on a segment n + 2 ... 2·(n + 1) more or equal than amount of such numbers on segment n + 1 ... 2·n. 
		- Last statement is correct, because of n + 1 and 2·(n + 1) have equals number of 1-bits.
		- let's define F(X) is the count of numbers that have k 1-bits in it's binary from [1 to X].
		- we can calculate F(X) using dp_digit  https://codeforces.com/blog/entry/53960
		- it is sufficient to check that F(2 * mid) - F(mid) >= m.
		- Combinatorics Soluation : https://codeforces.com/blog/entry/12369 
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 64 ;
bitset < N > b ;
ll m , k ;
ll memo[N][N][2];

ll solve(int i , int cnt , bool flag){

   if(i == -1){
       return cnt == k ;
   }

   ll &ret = memo[i][cnt][flag];
   if(ret != -1) return ret;

   if(flag)
       return ret = solve(i - 1 , cnt + 1 , flag) + solve(i - 1 , cnt , flag);


   ll c1 = solve(i - 1 , cnt , b[i] == 1);
   ll c2 = 0 ;

   if(b[i] == 1)
      c2 = solve(i - 1 , cnt + 1 , flag);

   return ret = c1 + c2 ;
}

bool check(ll mid){

    ll r = 2 * mid , l = mid ;

    b = r ;
    memset(memo , -1 , sizeof memo);
    ll c1 = solve(N - 1 , 0 , 0);

    b = l ;
    memset(memo , -1 , sizeof memo);
    ll c2 = solve(N - 1 , 0 , 0);

    return c1 - c2 >= m ;
}

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    cin >> m >> k ;


    ll low = 1 , high = 1e18 , res = -1 ;

    while(low <= high){
         ll mid = (low + high)/2 ;
         if(check(mid))
            res = mid ,  high = mid - 1 ;
         else
            low = mid + 1 ;
    }

    cout << res << endl ;



    return 0;
}
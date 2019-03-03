/*

	Idea:
		- Editorial Link : https://codeforces.com/blog/entry/9425
		- segment tree soluation is too slow , so we can use sparse table insted 
		- I chose to solve the problem using this cool method : https://codeforces.com/blog/entry/21802?#comment-264915
		- plus a counter array to check in O(1) if our gcd(l , r) is exist in the range [l , r]  
		
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 3 * 1e5 + 10 ;

int n ;
vector < int > ve ;
int pre[N] , suf[N] , cnt[1000003] ;
vector < int > ans ;

bool check(int mid){

    ans.clear() ;
    memset(cnt , 0 , sizeof cnt) ;

    for(int i = 0 ; i < n ; i += mid){
          int l = i , r = min(n - 1 , i + mid - 1) ;

          pre[l] = ve[l] ;
          for(int j = l + 1 ; j <= r; j ++)
               pre[j] = __gcd(pre[j - 1] , ve[j]);

          suf[r] = ve[r];
          for(int j = r - 1 ; j >= l ; j--)
                suf[j] = __gcd(suf[j + 1] , ve[j]) ;
    }

    for(int i = 0 ; i < mid - 1 ; i++)
           cnt[ve[i]] ++ ;

    int l = 0 , r = mid - 1 ;


    while(r < n){

         cnt[ve[r]] ++ ;

         int g = __gcd(suf[l] , pre[r]);
         if(cnt[g]) {
             ans.push_back(l) ;
         }

         cnt[ve[l]] -- ;
         l++ ;
         r++ ;
    }

    return !ans.empty() ;
}

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    cin >> n ;

    for(int i = 0 ; i < n ; i++){
         int x ; cin >> x;
         ve.push_back(x) ;
    }

    int low = 1 , high = n  , res = -1 ;

    while(low <= high){
          int mid = (low + high) / 2 ;
          if(check(mid))
                res = mid , low = mid + 1;
          else
               high = mid - 1;
    }

    check(res) ;

    cout << ans.size() << " " << res - 1 << endl ;
    for(auto i : ans) cout << i + 1 << " " ;

    return 0;
}
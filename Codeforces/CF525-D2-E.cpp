#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int n , k ;
ll s ;
vector < ll > ve1 , ve2 ;
ll fact[20] ;
vector < pair < int , ll > > se1 ;
unordered_map < ll , ll > cnt[26] ;

void solve(int i , int k1 , ll sum){

     if(i == ve1.size()){
          se1.push_back({k1 , sum}) ;
          return ;
     }

     solve(i + 1 , k1 , sum);

     if(sum <= s - ve1[i])
          solve(i + 1 , k1 , sum + ve1[i]) ;

     if(ve1[i] <= 18 && sum <= s - fact[ve1[i]])
           solve(i + 1 , k1 + 1 , sum + fact[ve1[i]]);
}

void solve2(int i , int k1 , ll sum){

     if(i == ve2.size()){
           cnt[k1][sum]++ ;
           return ;
     }

     solve2(i + 1 , k1 , sum) ;

     if(sum <= s - ve2[i])
          solve2(i + 1, k1 , sum + ve2[i]);
     if(ve2[i] <= 18 && sum <= s - fact[ve2[i]])
         solve2(i + 1 , k1 + 1 , sum + fact[ve2[i]]);
}


int main()
{

    fact[0] = fact[1] = 1;
    for(ll i = 2 ; i < 19 ; i++)
         fact[i] = fact[i - 1] * i ;

    scanf("%d%d",&n,&k);
    scanf("%lld",&s);



    for(int i = 0 ; i < n ; i++){
         int x ; scanf("%d",&x);

         if(i < n / 2) ve1.push_back(x) ;
         else ve2.push_back(x) ;
    }

    solve(0 , 0 , 0) ;

    solve2(0 , 0 , 0);

    ll res = 0 ;

    for(auto p : se1){
         int k1  = p.first ;
         ll s1 = p.second ;

         int j = k - k1 ;
         for(int i = 0 ; i <= j ; i++)
                 res += cnt[i][s - s1] ;
    }

    printf("%lld\n",res);

    return 0;
}

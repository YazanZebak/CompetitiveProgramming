/*
	Idea : https://discuss.codechef.com/t/songshop-editorial/22352
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

struct data {
    ll album , value , price  ;
    data(){}
    data(ll album , ll value , ll price) : album(album) , value(value) , price(price) {}
};

vector < data > ve ;
vector < pair < int , int > > temp[1001];

ll memo[2002][1001] ;

ll solve(int i , int price){

   if(i >= (int)ve.size())
        return 0;

   ll &ret = memo[i][price];
   if(ret != -1) return ret ;

   ll c1 = solve(i + 1 , price) , c2 = 0 ;

   if(price >= ve[i].price){
         c2 = ve[i].value + solve(i + ve[i].album + 1 , price - ve[i].price);
   }

   return ret = max(c1 , c2) ;
}

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    ll n , m , p ;

    cin >> n >> m >> p ;

    vector < ll > cnt(m + 1 , 0) ;
    vector < ll > great(m + 1 , 0) ;

    for(int i = 0 ; i < n ; i++){
          ll x , y , z ;
          cin >> x >> y >> z ;
          cnt[x] ++ ;
          great[x] += z ;
          temp[x].push_back({z , y});
    }


    for(int i = 1 ; i <= m ; i++){
          int x ; cin >> x ;
          if(cnt[i] == 0) continue ;
          ve.push_back(data(cnt[i] , great[i] , x));
          for(auto j : temp[i]){
               ve.push_back(data(0 , j.first , j.second )) ;
          }
    }


    memset(memo , -1 , sizeof memo);

    cout << solve(0 , p) << endl ;



    return 0;
}

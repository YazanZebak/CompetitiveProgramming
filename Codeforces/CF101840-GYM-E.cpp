/*
	Idea:
		- for each prime number let it equal to 5 
		- for each two primes number let it equal to 3
		- each path has value of 3 or 25 we can add it to the answer
		- now to calc number of paths we need to keep number of which that has value of #ones or #prime or #two_primes 
		- we can merge two_primes paths with ones paths and vice versa
		- we can merge primes paths with the other primes paths
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 1e5 + 1 ;
vector < int > primes ;
bitset < N > isprime ;

void sieve(){
    isprime.set();
    isprime[0] = isprime[1] = 0;
    primes.emplace_back(2);
    for(int i = 3 ; i * i < N ; i += 2)
        if(isprime[i]) for(int j = i * 2 ; j < N ; j += i) isprime[j] = 0 ;
    for(int i = 3 ; i < N ; i += 2) if(isprime[i]) primes.emplace_back(i);
}


bool is_prime(int n){
     if(n % 2 == 0) return n == 2 ;
     if(n >= N) return false ;
     return isprime[n];
}

bool tprime(int w){
    int cnt = 0 ;
    int PF_idx = 0 , PF = primes[0];
    while(PF * PF <= w){
          while(w % PF == 0) {
               w /= PF ;
               cnt++;
               if(cnt > 2) return false;
          }
          PF = primes[++PF_idx];
    }
    if(w > 1) cnt++;
    return cnt == 2 ;
}


vector <  vector < pair < int , int > > >G;

int sub[N] , par[N] ;
bitset < N > blocked ;

void get_size(int u , int p){
     sub[u] = 1 ;
     par[u] = p ;
     for(auto e : G[u]){
          int v = e.first ;
          if(blocked[v] || v == p) continue ;
          get_size(v , u);
          sub[u] += sub[v];
     }
}

int ones , cnt_p , cnt_tp;

ll dfs(int u , int p , ll ret){

    ll res = 0 ;

    if(ret == 1) res += cnt_tp ;
    if(ret == 3 || ret == 25) res += ones , res++ ;
    if(ret == 5) res += cnt_p ;

    for(auto e : G[u]){
          int v = e.first , w = e.second ;
          if(blocked[v] || v == p) continue ;
          res += dfs(v , u , ret * w);
    }

    return res ;
}



void update(int u , int p , ll ret){

    if(ret == 1)  ones++ ;
    if(ret == 3 || ret == 25) cnt_tp ++ ;
    if(ret == 5) cnt_p++;

    for(auto e : G[u]){
          int v = e.first , w = e.second ;
          if(blocked[v] || v == p) continue ;
          update(v , u , ret * w) ;
    }
}

ll solve(int u){

    ll ret = 0;
    ones = cnt_p = cnt_tp = 0 ;
    for(auto e : G[u]){
         int v = e.first , w = e.second ;
         if(blocked[v]) continue ;
         ret += dfs(v , u , w );
         update(v , u , w );
    }

    return ret ;
}

ll get_centroid(int src){

    get_size(src , src);

    int centroid = src , best = sub[src] ;
    queue < int > Q ;
    Q.push(centroid);

    while(!Q.empty()){
           int u = Q.front();
           Q.pop() ;

           int size = sub[src] - sub[u];
           for(auto e : G[u]){
                int v = e.first ;
                if(blocked[v] || v == par[u]) continue ;
                size = max(size , sub[v]);
                Q.push(v);
           }
           if(best > size){
                best = size ;
                centroid = u ;
           }
    }

    blocked[centroid] = true ;


    ll res = solve(centroid);

    for(auto e : G[centroid]){
          int v = e.first ;
          if(blocked[v]) continue;
          res += get_centroid(v);
    }

    return res ;
}


int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0);

    freopen("evaluations.in" , "r" , stdin);

    sieve() ;

    int t ; cin >> t ;

    int c = 1 ;

    while(t--){
          int n ; cin >> n ;

          G.clear() ;
          G.resize(n + 1);

          for(int i = 0 ; i < n - 1 ; i++){
              int u , v , w ;
              cin >> u >> v >> w ;

              if(is_prime(w)) w = 5;
              else if(tprime(w)) w = 3;

              G[u].emplace_back(v , w);
              G[v].emplace_back(u , w);
          }

          blocked = 0 ;

          cout << "Case " << c++ << ": " ;

          cout << get_centroid(1) << endl ;
    }


    return 0;
}
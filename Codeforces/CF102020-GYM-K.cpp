#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int Nmax = 5 * 1e6 + 10 ;
bitset < Nmax > isprime  ;
vector < int > primes ;

void sieve(){
    isprime.set();
    primes.push_back(2);
    for(int i = 3 ; i * i < Nmax ; i += 2)
         if(isprime[i]) for(int j = i * 2 ; j < Nmax ; j += i) isprime[j] = 0 ;
    for(int i = 3 ; i < Nmax ; i += 2) if(isprime[i]) primes.push_back(i);
}


const int N = 1e5 + 10  ;
const ll inf = 1e18 ;

struct edge{
    ll to , w , cap ;
    edge();
    edge(int to , ll w , int cap) : to(to) , w(w) , cap(cap) {}
    bool operator < (const edge &e) const {
         if(w != e.w) return w > e.w ;
         return cap < e.cap ;
    }
};
int src , trg ;
vector < edge > G[N];

ll dijstra(int mid){

    vector < ll > dist(N , inf);
    priority_queue < edge > Q ;

    dist[src] = 0  ;
    Q.push(edge(src , 0 , 0));

    while(!Q.empty()){

        auto e = Q.top() ;
        Q.pop();

        int u = e.to ;
        ll weight = e.w ;

        if(weight > dist[e.to]) continue ;

        for(auto e : G[u]){
              ll v = e.to , cap = e.cap , w = e.w ;

              if(cap < mid) continue ;

              if(dist[v] > dist[u] + w){
                    dist[v] = dist[u] + w ;
                    Q.push(edge(v , dist[v] , e.cap));
              }
        }
    }

    return dist[trg] == inf ? 0 : dist[trg] ;
}

int main()
{
  //  ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    primes.push_back(1);
    sieve();

    int n , m ;
    scanf("%d%d%d%d",&n,&m,&src,&trg);

    for(int i = 0 ; i < m ; i ++){
          int u , v , cap , w ;
          scanf("%d%d%d%d",&u,&v,&cap,&w);
          G[u].push_back(edge(v , w , cap));
    }

    ll low = 0 , high = primes.size() - 1 , res = 0 ;
    while(low <= high){
         int mid = (low + high)/2 ;
         if(dijstra(primes[mid]))
             res = primes[mid] , low = mid + 1 ;
         else
             high = mid - 1 ;
    }

    printf("%lld %lld\n",res,dijstra(res) * 1LL * res);


    return 0;
}

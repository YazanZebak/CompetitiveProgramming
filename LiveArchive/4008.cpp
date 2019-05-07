#include <bits/stdc++.h>
typedef long long ll ;
using namespace std ;

const int N = 1000001 ;
vector < int > primes ;
bitset < N > isprime ;
char s[N];

void sieve(){
    isprime.set() ;
    primes.push_back(2);
    for(int i = 3 ; i * i <= N ; i += 2){
         if(isprime[i]) for(int j = i * 2 ; j <= N ; j += i) isprime[j] = 0 ;
    }
    for(int i = 3 ; i <= N ; i += 2) if(isprime[i]) primes.push_back(i);
}

int factorialPrimePower(int n , int p){
	int ret = 0;
    while(n){
         ret += (n / p) ;
         n /= p;
    }
	return ret ;
}

ll bigMod(ll x , ll y , ll m){
	ll res = 1 ;
	while(y){
		 if(y & 1)
		 	  res = (res * x) % m ;
		 y /= 2 ;
		 x = (x * x) % m ;
	}
	return res ;
}

int main(){

    sieve();

    while(scanf("%s",s) == 1){

        int n = strlen(s);

        vector < int > cnt(30 , 0) ;
        for(int i = 0 ; i < n ; i++) cnt[s[i] - 'a'] ++;

        vector < int > res(primes.size() , 0);

        for(int i = 0 ; i < primes.size() ; i++){
            res[i] += factorialPrimePower(n , primes[i]);
            for(int j = 0 ; j < 26 ; j++) res[i] -= factorialPrimePower(cnt[j] , primes[i]);
        }

        int mn = min(res[0] , res[2]);
        res[0] -= mn;
        res[2] -= mn;

        int ans = 1;
        for(int i = 0 ; i < primes.size() ; i++){
             ans *= bigMod(primes[i] , res[i] , 10);
             ans %= 10 ;
        }

        printf("%d\n",ans);
    }

    return 0 ;
}

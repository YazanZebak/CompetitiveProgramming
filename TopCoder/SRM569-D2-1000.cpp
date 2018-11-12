#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int Nmax = 1001;
vector < int > primes ;
bitset < Nmax > isprime ;

void sieve() {
    isprime.set() ;
    isprime[0] = isprime[1] = 0;
    primes.push_back(2) ;
    for(int i = 3 ; i * i < Nmax ; i += 2)
        for(int j = i * 2;  j < Nmax ; j += i) isprime[j] = 0 ;
    for(int i = 3 ; i < Nmax ; i += 2) if(isprime[i]) primes.push_back(i) ;
}

const int mod = 1e9 + 9 ;
int dp[2][101][170];

int idx(int n) {
    return lower_bound(primes.begin() , primes.end() , n) - primes.begin() ;
}

class MegaFactorialDiv2 {

public :

    int countDivisors(int N, int K) {

        sieve() ;

        memset(dp , 0 , sizeof dp);

        bool curN = 0;

        for(int i = 1 ; i <= N ; i++) {
            curN ^= 1;
            memset(dp[curN] , 0 , sizeof dp[curN]) ;
            int n = i ;
            int PF_idx = 0 , PF = primes[PF_idx];
            while(PF * PF <= n) {
                while(n % PF == 0) n /= PF , dp[curN][0][PF_idx] ++ ;
                PF = primes[++PF_idx];
            }
            if(n > 1) dp[curN][0][idx(n)] ++;
            for(int j = 1 ; j <= K ; j++) {
                for(int k = 0 ; k < primes.size() ; k++)
                    dp[curN][j][k] = (dp[curN][j - 1][k] + dp[curN ^ 1][j][k]) % mod;
            }
        }

        ll result = 1 ;
        for(int i = 0 ; i < primes.size() ; i++)
            result *= (dp[curN][K][i] + 1) , result %= mod ;

        return (int)result ;
    }
};

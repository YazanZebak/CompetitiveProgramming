#include <bits/stdc++.h>
typedef long long ll ;
using namespace std ;

ll Ceil(ll a, ll b){
   return (a + b - 1) / b ;
}

const int N = 1e6 + 10 ;
vector < int > divisor[N];
bitset < N > isprime ;


int main() {

    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0) ;

    ll low , high ;
    cin >> low >> high ;

    isprime.set();
    isprime[1] = isprime[0] = 0 ;

    for(int i = 2 ; i < N ; i++){
           if(isprime[i]){
                 for(int j = i * 2 ; j < N ; j += i)
                      isprime[j] = false ;
                 for(ll x = Ceil(low , i) * i ; x <= high ; x += i)
                      primes[x - low].push_back(i);
           }
    }

    ll res = 0;

    for(ll x = low ; x <= high ; x++){
          vector < int > arr ;
          ll temp = x ;
          for(auto prime : primes[x - low]){
                 int cnt = 0;
                 while(temp % prime == 0) cnt++ , temp /= prime ;
                 arr.emplace_back(cnt);
          }
          if(temp > 1) arr.emplace_back(1);
          sort(arr.begin() , arr.end());
          while(!arr.empty()){
                 ll sum = 1;
                 for(auto i : arr)
                       sum *= (i + 1);
                 res += sum ;
                 arr.back() -- ;
                 if(arr.back() == 0) arr.pop_back() ;
                 sort(arr.begin(), arr.end());
          }

    }

    cout << res << endl ;

    return 0;
}

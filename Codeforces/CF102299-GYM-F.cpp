/*
	Idea:
		- the final solution is the multiplication of the unique prime factor of b after simplifying the fractions.
		- https://www.quora.com/What-is-the-proof-that-a-fraction-has-a-finite-representation-in-base-b-if-and-only-if-the-denominator-has-only-prime-factors-as-b
		- now how to get the prime factor for b <= 1e18 
		- one of the algorithms is pollard_rho and millar_rabin.
		- the other way is similar to this approach : https://codeforces.com/blog/entry/22317
		- let's factorize the number up to 1e6 after this we have three cases 
		- [b is prime] , [b is square of prime b = p1 * p1] , [b is multiple of two primes p1 * p2]
		- for the first and the third case it's just b so we multiply our answer by b (p1 and p2 is unique so we need both of them and we have them as b)
		- for the second case we get the square root and multiply it to the answer (we can get the root by binary search)
		- make sure you print 2 in case b equal 1. 
*/
#include <bits/stdc++.h>
typedef long long ll ;
typedef long double ld ;
using namespace std ;
  
default_random_engine engine(time(nullptr));
 
ll random(ll lower, ll upper) {
  uniform_int_distribution<ll> distribution(lower, upper);
  return distribution(engine);
}
 
ll mult64(ll a, ll b, ll m) {
  a %= m, b %= m;
  ll ret = 0;
  for (; b; b >>= 1) {
    if (b & 1)
      ret = (ret + a) % m;
    a = (a + a) % m;
  }
  return ret;
}
 
ll fpow(ll a, ll p, ll mod) {
  ll res = 1;
  for (; p; p >>= 1) {
    if (p & 1)
      res = mult64(res, a, mod);
    a = mult64(a, a, mod);
  }
  return res;
}
 
bool miller_rabin(ll n, ll b) {
  ll m = n - 1, cnt = 0;
  while (~m & 1)
    m >>= 1, ++cnt;
  ll ret = fpow(b, m, n);
  if (ret == 1 || ret == n - 1)
    return true;
  --cnt;
  while (cnt >= 0) {
    ret = mult64(ret, ret, n);
    if (ret == n - 1)
      return true;
    --cnt;
  }
  return false;
}
 
const int BASIC[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
 
bool prime_test(ll n) {
  if (~n & 1)
    return n == 2;
  if (n == 1)
    return false;
  if (n == 3)
    return true;
  if (n == 3215031751ll)
    return false;
  for (int i = 0; i < 12 && BASIC[i] < n; ++i)
    if (!miller_rabin(n, BASIC[i]))
      return false;
  return true;
}
 
ll pollard_rho(ll n, ll seed) {
  ll x, y;
  x = y = random(1, n - 1);
  ll head = 1, tail = 2;
  while (true) {
    x = mult64(x, x, n);
    x = (x + seed) % n;
    if (x == y)
      return n;
    ll d = __gcd(max(x - y, y - x), n);
    if (1 < d && d < n)
      return d;
    if (++head == tail)
      y = x, tail <<= 1;
  }
}
 
void factorize(ll n, unordered_set < ll > &divisor) {
  if (n == 1)
    return;
  if (prime_test(n))
    divisor.insert(n);
  else {
    ll d = n;
    while (d >= n)
      d = pollard_rho(n, random(1, n - 1));
    factorize(n / d, divisor);
    factorize(d, divisor);
  }
}

int main() {
 
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0) ;
 
 
    ll a , b ;
 
    cin >> a >> b ;
 
 
    ll g = __gcd(a , b);
 
    a /= g ;
    b /= g ;
 
    if(b == 1){
        cout << 2 << endl ;
        return 0 ;
    }
 
    unordered_set < ll > se ;
    factorize(b , se);
 
    ll ans = 1 ;
    for(auto i : se){
          ans = ans * 1LL * i ;
    }
 
    cout << ans << endl ;
 
    return 0 ;
}
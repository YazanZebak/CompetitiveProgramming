/*
    Editorial : https://discuss.codechef.com/t/subsets-editorial/28722
*/
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 20 ;
int n, m ;
ll F[1 << N];
bool can[40][40];
vector < int > masks  ;

void f(int i = 0, int mask = 0) {

    if(i == m) {
        masks.push_back(mask);
        return ;
    }

    bool ok = 1 ;
    for(int j = 0 ; j < i ; j++) {
        if(can[i][j])
            continue ;
        if((mask & (1 << j))) {
            ok = 0 ;
            break ;
        }
    }

    if(ok)
        f(i + 1, mask | (1 << i));
    f(i + 1, mask);
}

void g(int i = m, int mask = 0) {

    if(i == n) {
        F[mask] = 1 ;
        return ;
    }

    int ii = i - m;
    bool ok = 1;
    for(int j = m ; j < i ; j++) {
        int jj = j - m ;
        if(can[i][j])
            continue ;
        if((mask & (1 << jj))) {
            ok = 0 ;
            break ;
        }
    }

    if(ok)
        g(i + 1, mask | (1 << ii));
    g(i + 1, mask);
}


bool check(int a, int b) {
    unordered_map < int, int > cnt ;
    for(int i = 2 ; i * i <= a ; i++) {
        while(a % i == 0) {
            cnt[i] ++;
            a /= i ;
            if(cnt[i] >= 3)
                return false ;
        }
    }
    if(a > 1)
        cnt[a]++ ;
    for(int i = 2 ; i * i <= b ; i++) {
        while(b % i == 0) {
            cnt[i]++ ;
            b /= i ;
            if(cnt[i] >= 3)
                return false ;
        }
    }
    if(b > 1)
        cnt[b]++;
    return cnt[b] <= 2 ;
}

int main() {


    int t ; scanf("%d",&t);

    while(t--) {

        masks.clear() ;
        memset(can, 0, sizeof can);
        memset(F, 0, sizeof F);

        vector < int > ve ;

        scanf("%d",&n);

        for(int i = 0 ; i < n ; i++) {
            int x ; scanf("%d",&x);
            ve.push_back(x);
        }

        if(n == 1) {
            puts("2");
            continue ;
        }

        m = n / 2 ;

        for(int i = 0 ; i < n ; i++) {
            for(int j = i + 1 ; j < n ; j++) {
                can[i][j] = can[j][i] = check(ve[i], ve[j]);
            }
        }

        f(), g();

        int m2 = (n + 1) / 2;

        for(int i = 0; i < m2 ; ++i)
            for(int mask = 0 ; mask < (1 << m2); ++mask){
                if(mask & (1 << i))
                    F[mask] += F[mask ^ (1<<i)];
            }

        ll res = 0 ;

        vector < bool > vis(1 << m , 0);

        for(auto mask : masks){

              if(vis[mask]) continue ;
              vis[mask] = 1 ;

              int cur = (1 << m2) - 1 ;

              for(int i = 0 ; i < m ; i++){

                  if((mask & (1 << i)) == 0) continue ;

                  for(int j = m ; j < n ; j++){
                         if(can[i][j]) continue ;
                         int jj = j - m ;
                         if(cur & (1 << jj)) cur ^= (1 << jj);
                  }
              }

              res += F[cur];
        }

        printf("%lld\n",res);
    }

    return 0 ;
}



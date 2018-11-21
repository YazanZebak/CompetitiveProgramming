#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 12 ;
int dp[1 << N][N];
int memo[12][1 << N][99];

void preprocessing() {
    memset(dp , 0 , sizeof dp);
    for(int mask = 0 ; mask < (1 << N) ; mask++) {
        for(int j = 0 ; j < 12 ; j++) {
            for(int k = 0 ; k < 12 ; k++) {
                if(!(mask & (1 << k))) continue;
                if(j > k) dp[mask][j]++;
            }
        }
    }
}

int n , k ;
int solve(int i , int mask , int cnt) {

    if(i == n) return (cnt == k) ;
    int &ret = memo[i][mask][cnt] ;
    if(ret != -1) return ret ;

    ret = 0 ;
    for(int j = 0 ; j < n ; j++){
        if(mask & (1 << j)) continue ;
        ret += solve(i + 1 , mask | (1 << j) , cnt + dp[mask][j]);
    }

    return ret ;
}


int main() {

    preprocessing();

    int t ; scanf("%d",&t);

    while(t--) {
        memset(memo , -1 , sizeof memo);
        scanf("%d%d",&n,&k);
        printf("%d\n",solve(0 , 0 , 0));
    }

    return 0;
}

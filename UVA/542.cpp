#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

double dp[17][40];
int p[16][16] ;

void build(int l = 0 , int r = 15 , int k = 1){

     if(l == r) return (void) (dp[l][k] = 1) ;

     int mid = (l + r)/2 ;
     build(l , mid , 2 * k ) ;
     build(mid + 1 , r , 2 * k + 1) ;

     for(int i = l ; i <= mid ; i++)
       for(int j = mid + 1 ; j <= r ; j++){
          dp[i][k] += dp[i][2 * k] * dp[j][2 * k + 1] * p[i][j] / 100 ;
          dp[j][k] += dp[j][2 * k + 1] * dp[i][2 * k] * p[j][i] / 100 ;
       }
}


int main()
{
    memset(dp , 0 , sizeof dp) ;

    char name[16][100] ;
    for(int i = 0 ; i < 16 ; i++)
         cin >> name[i] ;

    for(int i = 0 ; i < 16 ; i++)
       for(int j = 0 ; j < 16 ; j++)
            cin >> p[i][j] ;

    build() ;

    for(int i = 0; i < 16 ; i++)
        printf("%-10s p=%.2f%\n",name[i] ,dp[i][1] * 100) ;


    return 0;
}

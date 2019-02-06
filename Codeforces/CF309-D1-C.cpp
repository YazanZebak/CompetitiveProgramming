#include <bits/stdc++.h>
typedef long long ll  ;
using namespace std;

vector < int > arr ;
int cnt[40] ;

int main() {
    int n , m ;

    scanf("%d%d",&n,&m) ;

    for(int i = 0 ; i < n ; i++) {
        int x ; scanf("%d",&x);
        arr.push_back(x) ;
    }
    for(int i = 0 ; i < m ; i++) {
        int x ; scanf("%d",&x);
        cnt[x] ++ ;
    }
    int res =0 ;

    for(int i = 0 ; i < n && cnt[0] ; i++)
          if(arr[i] & 1)
               arr[i] -- , cnt[0] -- , res ++ ;

    sort(arr.begin() , arr.end());


    for(int i = 0 ; i < arr.size() ; i++) {
        for(int j = 0 ; j < 31 ; j++) {

            if( (1 << j) > arr[i] ) break;

            else if(cnt[j]) {
                int div = arr[i] / (1 << j) ;
                res += min(cnt[j] , div);
                arr[i] -= (min(cnt[j] , div) * (1 << j)) ;
                cnt[j] -= min(cnt[j] , div) ;
                j = -1 ;
            }

        }
    }

    printf("%d\n",res) ;



    return 0;
}

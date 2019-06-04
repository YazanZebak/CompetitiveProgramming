// Sol : https://lscct.com/challenge/2018solution.pdf
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 5005 ;

int n, opp[N], pts[N], type[N], seen[N];

int find_best(int T){

    int np = pts[T] + 3 , rank = 1;
    for(int i = 1 ; i <= n ; i++){
           if(i == T || opp[i] == T) continue ;
           seen[i] =  0 ;
           if(pts[i] > np) type[i] = 0 , rank++ ;
           else if(pts[i] + 3 <= np) type[i] = 0 ;
           else if(pts[i] == np) type[i] = 1 ;
           else type[i] = 2 ;
    }

    if(pts[opp[T]] > np) rank++ ;

    for(int i = 1 ; i <= n ; i++){
           if(i == T || opp[i] == T || seen[i]) continue;
           seen[i] = seen[opp[i]] = 1 ;
           int ta = type[i] , tb = type[opp[i]];
           if(ta > tb) swap(ta , tb);
           if(ta == 1) rank++ ;
    }

    return rank;
}

int find_worst(int T){

    int np = pts[T]  , rank = 1;
    for(int i = 1 ; i <= n ; i++){
           if(i == T || opp[i] == T) continue ;
           seen[i] =  0 ;
           if(pts[i] >= np) type[i] = 0 , rank++;
           else if(pts[i] + 3 < np) type[i] = 0 ;
           else if(pts[i] + 1 == np) type[i] = 1 ;
           else type[i] = 2 ;
    }

    if(pts[opp[T]] + 3 >= np) rank++ ;

    for(int i = 1 ; i <= n ; i++){
           if(i == T || opp[i] == T || seen[i]) continue;
           seen[i] = seen[opp[i]] = 1 ;
           int ta = type[i] , tb = type[opp[i]];
           if(ta > tb) swap(ta , tb);
           if(tb == 0) continue ;
           if(ta == 1 && tb == 1) rank += 2 ;
           else rank ++ ;
    }

    return rank;
}

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    cin >> n ;

    for(int i = 1 ; i <= n / 2 ; i++){
          int a , b;
          cin >> a >> b;
          opp[a] = b ;
          opp[b] = a ;
    }

    for(int i = 1 ; i <= n ; i++){
          int x , y ;
          cin >> pts[i] >> x >> y ;
    }

    for(int i = 1 ; i <= n ; i++){
          cout << find_best(i) << " " << find_worst(i) << endl ;
    }

    return 0;
}

/*
    Idea:
       - let I be the number of inversion of the given permutation
       - clearly E(0) = 1 , E(1) = 1
       - it is clear that after a Jeff's step inversions will become lower by 1
       - it is clear that after a Furik's step inversions will be lower by 1 with probability of 0.5 , and greater by 1 with probability of 0.5.
       - E(I) = 2 + E(I - 1 + 1) * 0.5 + E(I - 1 - 1) * 0.5
       - E(I) = E(I - 2) + 4
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int n ; cin >> n ;

    vector < int > a ;

    for(int i = 0 ; i < n ; i++){
         int x ; cin >> x ;
         a.push_back(x);
    }

    int cnt = 0 ;
    for(int i = 0 ; i < n ; i++)
        for(int j = i + 1 ; j < n ; j++)
              if(a[j] < a[i]) cnt ++ ;

   cout << fixed << setprecision(6) << (double)((cnt/2)*4 + (cnt % 2)) << endl ;

    return 0;
}

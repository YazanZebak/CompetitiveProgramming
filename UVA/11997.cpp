#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

ll arr1[760] , arr2[760];
int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int k ;
    while(cin >> k){

          for(int i = 0 ; i < k ; i++)
                 cin >> arr1[i] ;



          for(int i = 1 ; i < k ; i++){

                 for(int j = 0 ; j < k ; j++)
                       cin >> arr2[j] ;


                 sort(arr2 , arr2 + k);

                 priority_queue < pair < ll , int > , vector < pair < ll , int > > , greater < pair < ll , int > > > Q ;

                 for(int j = 0 ; j < k ; j++)
                       Q.push({arr1[j] + arr2[0] , 0});

                 for(int j = 0 ; j < k ; j++){
                        auto p = Q.top() ;
                        Q.pop() ;

                        arr1[j] = p.first  ;
                        Q.push({arr1[j] - arr2[p.second] + arr2[p.second + 1], p.second + 1});
                 }
          }

          cout << arr1[0] ;
          for(int i = 1 ; i < k ; i++)
             cout << " " << arr1[i] ;
          cout << endl ;
    }

    return 0;
}

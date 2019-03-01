/*
    Idea :
        - sort the boxes in increasing number of apples.
        - for each consecutive pair [0 , 1][2 , 3][4 , 5]...[2i , 2i + 1] choose the box with the largest oranges
        - make sure to add the box which contains the largest number of apples
        - It's easy to see that by some examples the conditions of the task are fulfilled.
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int t ; cin >> t ;

    while(t--){
         int n ; cin >> n ;
         vector < pair < pair < int , int > , int > > ve ;
         for(int i = 0  ; i < 2 * n - 1 ; i++){
                int x , y ;
                cin >> x >> y ;
                ve.push_back({{x , y} , i});
         }

         sort(ve.begin() , ve.end());

         vector < int > res ;

         res.push_back(ve.back().second) ;

         for(int i = 0 ; i < 2 * n ; i += 2){
               if(ve[i].first.second > ve[i + 1].first.second)
                   res.push_back(ve[i].second) ;
               else
                   res.push_back(ve[i + 1].second) ;
         }

         cout << "YES" << endl ;
         cout << res[0] + 1 ;
         for(int i = 1 ; i < n ; i++) cout << " " << res[i] + 1 ;
         cout << endl ;
    }


    return 0;
}

/*
    Editorial Link : https://codeforces.com/blog/entry/45912
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int n ; cin >> n ;

    vector < int > a , b;

    for(int i = 0 ; i < n ; i++) {
          int x ; cin >> x;
          a.push_back(x);
    }

    for(int i = 0 ; i < n ; i++){
          int x ; cin >> x ;
          b.push_back(x);
    }


    deque < int > mn , mx ;


    ll res = 0 ;
    for(int i = 0 , j = 0 ; i < n ; i++){

          while(!mx.empty() && a[mx.back()] <= a[i]) mx.pop_back();
          while(!mn.empty() && b[mn.back()] >= b[i]) mn.pop_back();

          mx.push_back(i) ;
          mn.push_back(i) ;

          while(j <= i && a[mx.front()] - b[mn.front()] > 0){
                j++ ;
                while(!mx.empty() && mx.front() < j) mx.pop_front() ;
                while(!mn.empty() && mn.front() < j) mn.pop_front() ;
          }
          if(!mx.empty() && !mn.empty() && a[mx.front()] == b[mn.front()]) res += min(mx.front() , mn.front()) - j + 1 ;
    }

    cout << res << endl ;

    return 0;
}

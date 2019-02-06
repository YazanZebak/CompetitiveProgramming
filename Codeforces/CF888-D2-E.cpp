#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int n , m ;
vector < int > ve1 , ve2 ;
vector < int > se1 , se2 ;

void solve(int i , int sum){

    if(i == ve1.size()){
          se1.push_back(sum);
          return ;
    }

    solve(i + 1, (sum + ve1[i]) % m);
    solve(i + 1, sum) ;
}

void solve1(int i , int sum){

    if(i == ve2.size()){
          se2.push_back(sum);
          return ;
    }

    solve1(i + 1 , (sum + ve2[i]) % m);
    solve1(i + 1 , sum);
}


int main()
{
    ios::sync_with_stdio(false) ;

    cin >> n >> m  ;

    for(int i = 0 ; i < n ; i ++){
          int x ; cin >> x;
          if(i < n / 2) ve1.push_back(x) ;
          else ve2.push_back(x) ;
    }

    solve(0 , 0) ;
    solve1(0 , 0) ;


    sort(se1.begin() , se1.end());
    //sort(se2.begin() , se2.end());

    int res = 0  ;


    for(auto x : se2){
       int t = m - 1 - x;

       int i = upper_bound(se1.begin() , se1.end() , t) - se1.begin() - 1 ;
       if(i < 0) continue ;

       res = max(res , x + se1[i]) ;
    }

    cout << res << endl ;



    return 0;
}

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n ;
vector < pair < pair < int , int > , pair < int , int > >  > v ;
int memo[105][2001];

int f(int i , int t)
{
     if(i == n) return 0 ;

     int &ret = memo[i][t] ;

     if(ret != -1) return ret ;

     int c1 = f(i + 1 , t) ;
     int c2 = -1;

     if(t + v[i].first.second < v[i].first.first)
          c2 = f(i + 1 , t + v[i].first.second) + v[i].second.first ;

     return ret = max(c2 , c1);
}


vector < int > res ;
void bulid_output(int i , int t)
{
    if(i == n) return ;

    int c1 = f(i + 1 , t);
    int c2 = -1 ;

    if(t + v[i].first.second < v[i].first.first)
          c2 = f(i + 1,  t + v[i].first.second) + v[i].second.first ;

    int optimal = f(i , t);
    if(c2 == optimal){
         res.push_back(v[i].second.second);
         bulid_output(i + 1 , t + v[i].first.second);
    }
    else{
         bulid_output(i + 1 , t);
    }

}

int main()
{


    scanf("%d",&n);

    for(int i = 0 ; i < n ; i++){
          int t , d, p ;
          scanf("%d%d%d",&t,&d,&p);
          v.push_back( { {d , t} , {p , i + 1} } );
    }

    sort(v.begin() , v.end());

    memset(memo , -1 , sizeof(memo));

    cout << f(0 , 0) << endl ;

    bulid_output(0 , 0);

    cout << res.size() << endl;

    for(int i = 0 ; i < res.size() ; i++) cout << res[i] << " " ;


    return 0;
}

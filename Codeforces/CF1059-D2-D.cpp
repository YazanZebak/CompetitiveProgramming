// Sol : https://codeforces.com/blog/entry/62238?#comment-462316
#include <bits/stdc++.h>
typedef long long ll ;
typedef long double ld ;
using namespace std;


typedef pair < ll , ll > point ;

const double eps = 1e-8 ;

int n ;
vector < point > ve;

double f(double x){
     double r = 0 ;
     for(int i = 0 ; i < n ; i++){
            double d = (x - ve[i].first) * (x - ve[i].first) * 1.0;
            d += (ve[i].second * ve[i].second * 1.0);
            d /= 2.0;
            d /= (ve[i].second * 1.0);
            r = max(r , d);
     }
     return r;
}

int main() {

    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    cin >> n ;

    bool pos = 0 , neg = 0 ;

    for(int i = 0 ; i < n ; i++){
          ll x, y;
          cin >> x >> y;
          ve.push_back(point(x , y));
          if(y > 0) pos = 1 ;
          else neg = 1;
    }

    if(pos && neg) return cout << -1 << endl , 0;
    if(neg) for(int i = 0 ; i < n ; i++) ve[i].second = -ve[i].second;

    double l = -1e8 , r = 1e8 ;

    while(r - l > eps){
          double g = l + (r - l) / 3.0 , h = l + 2.0 * (r - l) / 3.0;

          if(f(g) < f(h))
              r = h;
          else
              l = g;
    }

    cout << fixed << setprecision(10) << f(l) << endl;

    return 0;
}

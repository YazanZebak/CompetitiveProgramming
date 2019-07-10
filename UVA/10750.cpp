/*
	Idea : find the mid point between the cloeset pair
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;
typedef complex<double> point ;

#define X real()
#define Y imag()
#define vec(a, b) ((b) - (a))
#define length(a) (hypot((a).Y,(a).X))

const double eps = 1e-8 ;
const double inf = 1e18 ;

int dcmp(double a, double b){
    if(fabs(a - b) <= eps) return 0 ;
    return (a < b ? -1 : 1);
}

struct cmpX{
    bool operator ()(const point &a, const point &b){
         if(dcmp(a.X, b.X) != 0)
              return dcmp(a.X , b.X) < 0 ;
         return dcmp(a.Y, b.Y) < 0 ;
    }
};

struct cmpY{
    bool operator ()(const point &a, const point &b){
         if(dcmp(a.Y, b.Y) != 0)
             return dcmp(a.Y, b.Y) < 0;
         return dcmp(a.X, b.X) < 0 ;
    }
};

point solve(vector<point> &events){
      double d = inf ;
      multiset<point, cmpY> active;
      sort(events.begin(), events.end(), cmpX());

      point res ;

      int i = 0;
      for(int j = 0 ; j < (int)events.size() ; j++){
           while(i < j && events[j].X - events[i].X > d)
              active.erase(active.find(events[i++]));

           auto l = active.lower_bound(point(-inf , events[j].Y - d));
           auto r = active.lower_bound(point(-inf , events[j].Y + d));
           for( ; l != r ; l++){

                 if(d > length(events[j] - *l)){
                        res = (events[j] + *l) / 2.0 ;
                        d = length(events[j] - *l);
                 }
           }

           active.insert(events[j]);
      }

      return res;
}


int main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0) ;

    int t ; cin >> t ;

    while(t--){
           int n ; cin >> n ;
           vector<point> ve;
           for(int i = 0 ; i < n ; i++){
                  double x, y ;
                  cin >> x >> y;
                  ve.push_back(point(x, y));
           }
           point ans = solve(ve);

           cout << fixed << setprecision(3) << ans.X << " " << ans.Y << endl;
           if(t) cout << endl ;
    }


    return 0;
}

#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

typedef complex < double > point ;
#define X real()
#define Y imag()

#define length(v) (hypot((v).Y , (v).X))
#define dot(v , u)      ( (conj(v) * (u)).X )
#define cross(v , u)    ( (conj(v) * (u)).Y )

double distToSegment( point p0 , point p1 , point p2 , point &res) {

    double d1 , d2 ;
    point v1 = p1 - p0 , v2 = p2 - p0 ;

    if( (d1 = dot(v1 , v2) ) < 0){
        res = p0 ;
        return length(p2 - p0) ;
    }
    if( (d2 = dot(v1 , v1) ) < d1){
        res = p1 ;
        return length(p2 - p1) ;
    }

    double t = d1 / d2 ;
    res = (p0 + v1 * t) ;
    return length(p2 - (p0 + v1 * t) );
}

int main() {
    ios::sync_with_stdio(false) ;


    double x , y ;

    while(cin >> x >> y){
         point m(x , y) ;
         int n ; cin >> n ;
         vector < point > seg ;
         for(int i = 0 ; i < n + 1 ; i++){
                cin >> x >> y;
                seg.push_back(point(x , y)) ;
         }

         point res = seg[0];
         double dist = 1e18 ;
         for(int i = 0 ; i < n ; i++){
                point temp ;
                double t ;
                if( (t = distToSegment(seg[i] , seg[i + 1] , m , temp)) < dist){
                        dist = t ;
                        res = temp ;
                }
         }

         cout << fixed << setprecision(4) << res.X << endl << res.Y << endl ;
    }

    return 0;
}

#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

typedef complex < double > point ;
#define X real()
#define Y imag()

#define length(v) (hypot((v).Y , (v).X))
#define dot(v , u)      ( (conj(v) * (u)).X )
#define cross(v , u)    ( (conj(v) * (u)).Y )

const double eps = 1e-8 ;

bool intersectSegments(point a , point b , point c , point d , point &intersect) {

    double d1 = cross(a - b , d - c) , d2 = cross(a - c , d - c) , d3 = cross(a - b , a - c) ;
    if(fabs(d1) < eps)
        return false ; // Parllel || identical

    double t1 = d2/d1 , t2 = d3/d1 ;
    intersect = a + (b - a) * t1 ;

    if(t1 < -eps || t1 > 1 + eps || t2 < -eps || t2 > 1 + eps)
        return false ;
    return true ;
}

pair < double , point > findCircle(point a , point b , point c) {
    //create median , vector , its prependicular
    point m1 = (b + a) * 0.5 , v1 = b - a , pv1 = point(v1.Y , -v1.X);
    point m2 = (b + c) * 0.5 , v2 = b - c , pv2 = point(v2.Y, -v2.X);
    point end1 = m1 + pv1 , end2 = m2 + pv2 , center;
    intersectSegments(m1 , end1 , m2 , end2 , center);
    return make_pair( length(a - center) , center );
}

const int N = 100001 ;
point pnts[N] , r[3] , cen ;
double rad ;
int ps , rs;

void MEC() {
    if(ps == 0 && rs == 2) {
        cen = (r[0] + r[1])/2.0;
        rad = length(r[0] - cen);
    }
    else if(rs == 3) {
        pair < double , point > p = findCircle(r[0] , r[1] , r[2]);
        cen = p.second;
        rad = p.first;
    }
    else if(ps == 0) {
        cen = r[0];
        rad = 0;
    }
    else {
        ps--;
        MEC();

        if(length(pnts[ps] - cen) > rad) {
            r[rs++] = pnts[ps];
            MEC();
            rs--;
        }

        ps++;
    }
}


int main()
{
    int t ; scanf("%d",&t);

    while(t--){

         int n ; scanf("%d",&n) ;
         ps = n , rs = 0 ;

         for(int i = 0 ; i < n ; i++){
              double x , y ;
              scanf("%lf%lf",&x,&y) ;
              pnts[i] = point(x , y) ;
         }
         random_shuffle(pnts , pnts + n);

         MEC() ;


         printf("%.2f\n",rad) ;
         printf("%.2f %.2f\n",cen.X,cen.Y) ;
    }


    return 0;
}

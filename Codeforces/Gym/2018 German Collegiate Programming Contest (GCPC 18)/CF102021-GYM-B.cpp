/*
	Idea:
		- Compute tangents of the red circle going through start and end.
		- Compute the length of circle segments between the touching points L1,2, R1,2.
		- Find the minimum length of the four paths start → L1,2 → R1,2 → end.
		- Find a tangent : https://stackoverflow.com/questions/1351746/find-a-tangent-point-on-circle#
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

typedef complex < double > point ;

#define X real()
#define Y imag()

#define length(v) (hypot((v).Y , (v).X))
#define normalize(v) (v)/length(v)

#define dot(v , u)      ( (conj(v) * (u)).X )
#define cross(v , u)    ( (conj(v) * (u)).Y )

#define vec(p1 , p2)  ((p2) - (p1))

#define lengthSqr(p) dot(p , p)

const double PI = acos(-1);

point rotate(point p, double A) {
    return p * polar(1.0, A);
}

point tangent(point p1, point c, double r, int sign) {

    point p_to_c = vec(p1, c);

    double dist = length(p_to_c);
    double alpha = asin(r / dist);
    double side = sqrt(dist*dist - r*r);

    point pt1;

    pt1 = rotate(p_to_c, sign * alpha);
    pt1 = normalize(pt1);
    pt1 *= side;

    point ret  = p1 + pt1;
    return ret ;
}

int main() {

    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)  ;

    double x, y, r ;
    cin >> x >> y ;
    point p1(x, y) ;
    cin >> x >> y ;
    point p2(x, y);
    cin >> x >> y >> r ;
    cin >> x >> y >> r ;
    point c(x, y);

    point pt1 = tangent(p1, c, r, 1);
    point pt2 = tangent(p1, c, r, -1);

    point pt3 = tangent(p2, c, r, 1);
    point pt4 = tangent(p2, c, r, -1);

    double res = INT_MAX ;

    vector < point > v1 = {pt1, pt2}, v2 = {pt3, pt4} ;

    for(auto i : v1) {
        for(auto j : v2) {
            double d =  length(vec(i, j));
            double theta = acos(1 - d * d  / (2 * r * r));
            double len = r * theta ;
            double tot = length(vec(p1 , i)) + len + length(vec(j , p2)) ;
            res = min(res , tot);
        }
    }


    cout << fixed << setprecision(10) << res  << endl ;

    return 0;
}
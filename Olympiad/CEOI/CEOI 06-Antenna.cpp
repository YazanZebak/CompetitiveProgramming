/*
	Idea: 
		- binary search on the radius and then we can solve the problem on a fixed r 
		- the remaining of the solution is https://www.geeksforgeeks.org/angular-sweep-maximum-points-can-enclosed-circle-given-radius/
		- more explaination is in this video https://youtu.be/gXn2yUHpvRE?t=2151 to minute 50  
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

typedef pair < double , double > point ;

#define X first
#define Y second

int n, k;
vector < point > p ;

const double pi = acos(-1);

bool check(double r) {

    for(int i = 0 ; i < n ; i++){

        vector < pair < double , int > > events;

        for(int j = 0 ; j < n ; j++){
              if(i == j) continue ;
              double dx = p[j].X - p[i].X , dy = p[j].Y - p[i].Y ;
              double dist = sqrt(dx * dx + dy * dy);

              if(dist > 2 * r) continue ;

              double a = atan2(dy , dx);
              double b = acos( dist / (2 * r) ) ;

              events.emplace_back(a - b , 1);
              events.emplace_back(a + b , -1);
              events.emplace_back(a - b + 2 * pi , 1);
              events.emplace_back(a + b + 2 * pi , -1);
        }

        sort(events.begin() , events.end());

        int cnt = 1;
        for(auto i : events){
              cnt += i.second ;
              if(cnt >= k) return true;
        }

    }

    return false;
}

int main(){

   ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0);

   cin >> n >> k ;

   for(int i = 0 ; i < n ; i++){
        double x , y ;
        cin >> x >> y ;
        p.push_back(point(x, y));
   }

   double low = 0 , high = 1e6 , res = 0 ;
   for(int i = 0 ; i < 30 ; i++){
         double mid = (low + high) / 2 ;
         if(check(mid))
               res = mid , high = mid ;
         else
              low = mid ;
   }

   cout << fixed << setprecision(4) << res << endl ;

   return 0;
}

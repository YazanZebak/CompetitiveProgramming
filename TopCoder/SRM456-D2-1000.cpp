#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

class CutSticks{

public :

     int c , Kth ;
     vector < double > ve ;

     double maxKth(vector < int > sticks , int C , int K){

            for(auto i : sticks) ve.push_back(i) ;
            c = C ;
            Kth = K  ;

            double low = 0 , high = *max_element(sticks.begin() , sticks.end()) ;
            for(int i = 0 ; i < 100 ; i++){
                   double mid = low + (high - low)/2 ;
                  if(check(mid))
                       low = mid  ;
                  else
                      high = mid;
            }
            return low ;
     }

     bool check(double mid){
          ll rnk = 0 ;
          ll rem = c ;

          for(int i = 0 ; i < ve.size() ; i++){
               if(rnk >= Kth) break ;
               ll produce ;
               if(ve[i] / mid > (double)Kth) produce = Kth ;
               else produce = ve[i] / mid ;

               if(produce) rnk++ ;
               if(produce >= 2){
                      rnk += min(produce - 1 , rem);
                      rem -= min(produce - 1 , rem);
               }
          }
          return rnk >= Kth ;
     }
};

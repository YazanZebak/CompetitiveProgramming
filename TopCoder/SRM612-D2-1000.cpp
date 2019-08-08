#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

ll memo[70][50];
vector < int > powers ;

ll solve(int bit , int carry){

    if(bit == powers.size()) return 1 ;

    ll &ret = memo[bit][carry];
    if(ret != -1) return ret ;

    ll val = powers[bit] + carry ;

    ret = solve(bit + 1 , val / 2);

    if(val > 0) ret += solve(bit + 1 , (val - 1) / 2);

    return ret ;
}

class PowersOfTwo{

public :

     ll count(vector<ll> p){

         for(int i = 0 ; i < 60 ; i++){
               powers.push_back(std::count(p.begin() , p.end() , 1LL << i)) ;
         }

         memset(memo , -1 , sizeof memo);

         return solve(0 , 0);
     }
};

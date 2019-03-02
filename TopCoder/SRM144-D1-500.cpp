/*
    Idea:
        - for this cases[S & U , S & !U , !S & !U] we can do counting method with some case handling
        - 1) [S & U] keep the last taken element and start from last + 1
        - 2) [S & !U] keep the last taken element and start from it
        - 3) for each blank we can try all the numbers from [1 , choices]
        - for the other last case [!S & U] we can calculate the answer using P(n , r) = n!/(n - r)!
        - finally the result is sorting the answers for each list in non-descending order

*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

ll memo[10][105][2][2];
int n , m ;

ll solve(int i , int last , bool srt , bool uni) {

    if(i == n)
        return 1;

    ll &ret = memo[i][last][srt][uni];
    if(ret != -1) return ret ;

    ret = 0 ;

    for(int j = last + uni ; j <= m ; j++) {
        ret += solve(i + 1 , (srt ? j : 1) , srt , uni) ;
    }

    return ret ;
}

ll get(ll mm , ll nn) {
    ll ret = 1 ;
    for(ll i = mm ; i >= mm - nn + 1 ; i--) ret *= i ;
    return ret ;
}

class Lottery {

public :

    vector < string > sortByOdds(vector < string > rules) {

        vector < pair < ll , string >  > ret ;

        for(auto str : rules) {
            stringstream ss(str);
            string name ;
            getline(ss , name , ':') ;
            ss >> m >> n ;

            char c1 , c2 ;
            bool sorted , unique ;
            ss >> c1 >> c2 ;

            sorted = (c1 == 'T');
            unique = (c2 == 'T');

            if(!sorted && unique) {

                ret.push_back({get(m , n) , name});
            }
            else {

                memset(memo , -1 , sizeof memo);
                ret.push_back({solve(0 , (unique ? 0 : 1) , sorted , unique) , name});
            }

        }


        sort(ret.begin() , ret.end());
        vector < string > vs ;
        for(auto i : ret) vs.push_back(i.second) ;
        return vs;
    }

};


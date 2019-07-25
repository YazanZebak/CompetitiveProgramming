// Idea : https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/SPOJ/SPOJ_CEPC08B.txt
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;
const int inf = INT_MAX ;

int main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0) ;

    int t ; cin >> t ;

    while(t--){
        int n , q ;
        cin >> n >> q ;
        vector < int > ve;
        vector < pair < int , int > > window ;
        for(int i = 0 ; i < n ; i++){
              int x ; cin >> x;
              ve.push_back(x);
              window.push_back({x , i});
        }

        sort(window.begin() , window.end());

        vector < pair < int , int > > res ;
        int cnt = 1;
        res.push_back({0 , cnt});

        for(int i = 0 ; i < n ; i++){
             vector < int > idx ;
             int j = i ;
             while(j < n && window[j].first == window[i].first)
                  idx.push_back(window[j++].second);

             for(int k = 0 ; k < idx.size() ; k++){
                   int t = k + 1 ;
                   while(t < idx.size() && idx[t] == idx[t - 1] + 1) t++;
                   t--;

                   int cur = idx[k] , prev = cur - 1 , nxt = idx[t] + 1;
                   if(cur && ve[prev] > ve[cur] && nxt < n && ve[nxt] > ve[cur]) cnt++;
                   else if((cur == 0 || ve[prev] < ve[cur]) && (nxt == n || ve[nxt] < ve[cur])) cnt--;

                   k = t ;
             }

             res.push_back({window[i].first, cnt});
             i = j - 1;
        }

        while(q--){
             int h ; cin >> h;
             auto it = upper_bound(res.begin() , res.end() , make_pair(h , inf));
             it-- ;
             cout << it->second ;
             if(q) cout << " " ;
        }

        cout << endl;
    }



    return 0;
}

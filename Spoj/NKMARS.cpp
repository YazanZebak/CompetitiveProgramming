#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

struct event{
    int idx, type;
    event() {}
    event(int idx, int type) : idx(idx) , type(type) {}
};
struct point{ int x , y; };

const int N = 1e4 + 10 ;
const int ST = 0 , EN = 1 ;
point rects[N][2];
bool isActive[N];
event events_v[2 * N], events_h[2 * N];

bool cmpX(event a, event b){
    return rects[a.idx][a.type].x < rects[b.idx][b.type].x ;
}
bool cmpY(event a, event b){
    return rects[a.idx][a.type].y < rects[b.idx][b.type].y ;
}


int main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0) ;

    int n ; cin >> n ;
    int cntE = 0 ;

    for(int i = 0 ; i < n ; i++ , cntE += 2){
         cin >> rects[i][0].x >> rects[i][0].y;
         cin >> rects[i][1].x >> rects[i][1].y;
         events_v[cntE] = event(i , ST), events_v[cntE + 1] = event(i , EN);
         events_h[cntE] = event(i , ST), events_h[cntE + 1] = event(i , EN);
    }

    sort(events_v , events_v + cntE , cmpX);
    sort(events_h , events_h + cntE , cmpY);

    isActive[events_v[0].idx] = 1;
    ll ans = 0 ;

    for(int i = 1 ; i < cntE ; i++){
        event cur = events_v[i], prev = events_v[i - 1];
        int cnt = 0, first_rect, delta_x, delta_y;

        if((delta_x = rects[cur.idx][cur.type].x - rects[prev.idx][prev.type].x) == 0){
            isActive[cur.idx] = (cur.type == ST);
            continue ;
        }

        for(int j = 0; j < cntE ; j++){
             if(!isActive[events_h[j].idx]) continue;

             if(events_h[j].type == ST){
                  if(cnt++ == 0)
                     first_rect = j ;
             }
             else if(--cnt == 0){
                  delta_y =  rects[events_h[j].idx][EN].y - rects[events_h[first_rect].idx][ST].y  ;
                  ans += delta_x * delta_y ;
             }
        }

        isActive[cur.idx] = (cur.type == ST);
    }

    cout << ans << endl ;

    return 0;
}

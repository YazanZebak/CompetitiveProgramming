// idea : https://github.com/MohamedNabil97/CompetitiveProgramming/blob/master/SPOJ/SHORTCUT.cpp

#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

struct event {
    int x, y, t ;
    event() {}
    event(int x, int y, int t) : x(x), y(y), t(t) {}
};

bool cmpX(event a, event b) {
    if(a.x != b.x)
        return a.x < b.x ;
    return a.y < b.y;
}

bool cmpY(event a, event b) {
    if(a.y != b.y)
        return a.y < b.y ;
    return a.x < b.x ;
}



int main() {

    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    int t ;
    cin >> t ;

    while(t--) {
        int n ;
        cin >> n ;
        string s ;
        cin >> s ;

        int x = 0, y = 0 ;
        int j = 0 ;

        vector < event > events ;

        events.push_back(event(x, y, j));

        for(auto i : s) {
            if(i == 'N')
                y++ ;
            if(i == 'S')
                y-- ;
            if(i == 'W')
                x-- ;
            if(i == 'E')
                x++ ;

            j++ ;
            events.push_back(event(x, y, j));
        }

        int mn = 1000000000, st, en ;
        char ch ;


        sort(events.begin(), events.end(), cmpX);

        for(int i = 1 ; i < events.size()  ; i++) {

            if(events[i].x != events[i - 1].x)
                continue ;

            if(abs(events[i].t - events[i - 1].t) <= 1)
                continue ;

            int dist = abs(events[i].y - events[i - 1].y);
            int l = min(events[i].t, events[i - 1].t);
            int r = max(events[i].t, events[i - 1].t);
            char w = (events[i].t < events[i - 1].t ? 'S' : 'N');

            if(dist < mn)
                mn = dist, st = l, en = r, ch = w;

            else if(dist == mn) {
                if(st > l)
                    st = l, en = r, ch = w;

                else if(st == l && en < r)
                    en = r,  ch = w;
            }

        }

        sort(events.begin(), events.end(), cmpY);

        for(int i = 1 ; i < events.size()  ; i++) {

            if(events[i].y != events[i - 1].y)
                continue ;

            if(abs(events[i].t - events[i - 1].t) <= 1)
                continue ;

            int dist = abs(events[i].x - events[i - 1].x);
            int l = min(events[i].t, events[i - 1].t);
            int r = max(events[i].t, events[i - 1].t);
            char w = (events[i].t < events[i - 1].t ? 'W' : 'E');

            if(dist < mn)
                mn = dist, st = l, en = r, ch = w;

            else if(dist == mn) {
                if(st > l)
                    st = l, en = r, ch = w;

                else if(st == l && en < r)
                    en = r,  ch = w;
            }

        }

        cout << mn << " " << st << " " << en << " " << ch << endl ;
    }


    return 0;
}

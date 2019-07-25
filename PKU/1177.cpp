// Sol : https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/PKU/PKU_1177.txt
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 25000;
int cnt[N];

int query(int l, int r) {
    int ret = 0 ;
    for(int i = l ; i < r; i++)
        ret += (cnt[i] != 0);
    return ret ;
}

void update(int l, int r, int val) {
    for(int i = l ; i < r ; i++)
        cnt[i] += val;
}

struct event {
    int idx, type;
    int l, r;
    event() {}
    event(int idx, int type, int l, int r) : idx(idx), type(type), l(l), r(r) {}
    bool operator < (const event &e){
         if(idx != e.idx)
                return idx < e.idx ;
         return type < e.type ;
    }
};

const int shft = 10000;

int sweep(vector < event > events) {

    memset(cnt , 0 , sizeof cnt);
    int ans = 0 ;

    for(auto i : events) {
        if(i.type == 0) {
            ans += (i.r - i.l) - query(i.l, i.r );
            update(i.l, i.r , 1);
        }
        else {
            update(i.l, i.r  , -1);
            ans += (i.r - i.l) - query(i.l, i.r);
        }
    }

    return ans ;
}

int main() {

    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0) ;

    int n ;
    cin >> n ;

    vector < event > eventX, eventY ;

    for(int i = 0 ; i < n ; i++) {
        int x0, y0, x1, y1 ;
        cin >> x0 >> y0 >> x1 >> y1;
        x0 += shft, y0 += shft, x1 += shft, y1 += shft;
        eventX.push_back(event(x0, 0, y0, y1));
        eventX.push_back(event(x1, 1, y0, y1));
        eventY.push_back(event(y0, 0, x0, x1));
        eventY.push_back(event(y1, 1, x0, x1));
    }

    sort(eventX.begin(), eventX.end());
    sort(eventY.begin(), eventY.end());

    cout << sweep(eventX) + sweep(eventY) << endl ;

    return 0;
}

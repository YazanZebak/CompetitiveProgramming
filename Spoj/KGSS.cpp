#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 1e5 + 2 ;

struct node {
    int mx1 , mx2 ;
    node(int mx1 , int mx2) : mx1(mx1) , mx2(mx2) {}
    node() {
        mx1 = mx2 = 0 ;
    }
} tree[N << 2];

int n ;
vector < int > ve ;

void merge(int p) {
    tree[p].mx1 = max(tree[2 * p].mx1 , tree[2 * p + 1].mx1) ;
    tree[p].mx2 = max( min(tree[2 * p].mx1 , tree[2 * p + 1].mx1) , max(tree[2 * p].mx2 , tree[2 * p + 1].mx2) ) ;
}

void build(int s = 0 , int e = n - 1 , int p = 1) {
    if(s == e)
        return (void) (tree[p] = node(ve[s] , 0)) ;
    build(s , (s + e) / 2 , 2 * p ) ;
    build((s + e)/2 + 1 , e , 2 * p + 1) ;
    merge(p) ;
}

void update(int idx , int val , int s = 0 , int e = n - 1,  int p = 1) {

    if(s == e)
        return (void) (tree[p] = node(val , 0)) ;

    if(idx <= (s + e)/2)
        update(idx , val , s , (s + e)/2 , 2 * p) ;
    else
        update(idx , val , (s + e)/2 + 1 , e , 2 * p + 1) ;

    merge(p) ;
}

node query(int l , int r , int s = 0 , int e = n - 1 , int p = 1) {

    if(s > r || e < l) return node() ;

    if(s >= l && e <= r) return tree[p] ;

    node left = query(l , r , s , (s + e)/2 , 2 * p) ;
    node right = query(l , r , (s + e)/2 + 1 , e ,  2 * p + 1)  ;

    return node( max(left.mx1 , right.mx1) , max( min(left.mx1 , right.mx1) , max(left.mx2 , right.mx2) ) ) ;
}


int main() {

    scanf("%d",&n) ;

    for(int i = 0 ; i < n ; i++) {
        int x ;
        scanf("%d",&x) ;
        ve.push_back(x) ;
    }

    build() ;

    int Q ;
    scanf("%d",&Q) ;

    while(Q--) {
        char c ;
        scanf(" %c",&c) ;
        if(c == 'Q') {
            int l , r ;
            scanf("%d%d",&l,&r) ;
            l-- , r-- ;
            node res = query(l , r) ;
            printf("%lld\n",(ll)(res.mx1 + res.mx2));
        } else {
            int idx , val  ;
            scanf("%d%d",&idx,&val) ;
            idx-- ;
            update(idx , val) ;
        }
    }

    return 0;
}

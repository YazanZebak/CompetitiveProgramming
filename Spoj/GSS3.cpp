#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 50005;
struct node {
    int pre , suf , sum , res ;
    node(int pre , int suf , int sum , int res) : pre(pre) , suf(suf) , sum(sum) , res(res) {}
    node() {
        pre = suf = sum = res = 0 ;
    }
} tree[N << 2];

int n ;
vector < int > ve ;

node merge(node left , node right) {
    node ret ;
    ret.pre = max(left.pre , left.sum + right.pre) ;
    ret.suf = max(right.suf , right.sum + left.suf) ;
    ret.sum = left.sum + right.sum ;
    ret.res = max( max(left.res , right.res) , left.suf + right.pre );
    return ret ;
}

void build(int s = 0 , int e = n - 1  , int p = 1) {
    if(s == e) {
        tree[p] = node(ve[s] , ve[s] , ve[s] , ve[s]) ;
        return ;
    }
    build(s , (s + e)/2 , 2 * p) ;
    build((s + e)/2 + 1 , e , 2 * p + 1) ;
    tree[p] = merge(tree[2 * p] , tree[2 * p + 1]) ;
}

const int inf = 1 << 30 ;
node query(int l , int r , int s = 0 , int e = n - 1 , int p = 1) {

    if(s >= l && e <= r) return tree[p] ;

    if(r <= (s + e)/2)
        return query(l , r , s , (s + e)/2 , 2 * p);
    else if(l >= (s + e)/2 + 1)
        return query(l , r , (s + e)/2 + 1 , e , 2 * p + 1) ;

    return merge(query(l , r , s , (s + e)/2 , 2 * p) , query(l , r , (s + e)/2 + 1 , e , 2 * p + 1));
}

void updata(int pos , int val , int s = 0 , int e = n - 1 , int p = 1) {

    if(s == e) return (void) (tree[p] = node(val , val , val , val)) ;

    if(pos <= (s + e)/2)
        updata(pos , val , s , (s + e)/2 , 2 * p) ;
    else
        updata(pos , val , (s + e)/2 + 1 , e , 2 * p + 1) ;

    tree[p] = merge(tree[2 * p] , tree[2 * p + 1]) ;
}

int main() {

    scanf("%d",&n) ;

    for(int i = 0 ; i < n ; i++) {
        int x ;
        scanf("%d",&x);
        ve.push_back(x) ;
    }

    build();

    int Q ;
    scanf("%d",&Q);
    while(Q--) {
        int t , l , r ;
        scanf("%d",&t) ;

        if(t == 0) {
            int pos , val;
            scanf("%d%d",&pos,&val) ;
            pos-- ;
            updata(pos , val) ;
        }

        if(t == 1) {
            scanf("%d%d",&l,&r);
            l-- , r-- ;
            int ans = query(l , r).res ;
            printf("%d\n",ans) ;
        }
    }
    return 0;
}

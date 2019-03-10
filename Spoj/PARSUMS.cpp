/*
    Editorial Link : https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/SPOJ/SPOJ_PARSUMS.txt
    Idea : 
        - build segment tree for the partial sum of the input
        - Implement the cyclic shift , double the size of the array n = 2 * n 
        - let the first n element equal to zero , and the remaining part equal to the input 
        - start from the right most element put it in (n - i) , i = {1 , 2 , ... , n}
        - increment the partial sum [n - i , 2 * n - i - 1] with the value of input[i] 
        - get the min element of the new partial sum and update the answer.    
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 2 * 1e6 + 1 ;

struct node{
    ll val , lazy ;
    node(ll val , ll lazy) : val(val) , lazy(lazy) {}
    node(){val = 0  , lazy = 0  ;}
}tree[N << 2];
int n ;

void pushLazy(int p , int s , int e){
     if(tree[p].lazy){
           tree[p].val += tree[p].lazy ;
           if(s != e){
               tree[2 * p].lazy += tree[p].lazy ;
               tree[2 * p + 1].lazy += tree[p].lazy ;
           }
           tree[p].lazy = 0 ;
     }
}

void update(int l , int r , int val , int s = 0 , int e = 2 * n - 1 , int p = 1){

     if(l > e || r < s) return ;

     pushLazy(p , s , e) ;

     if(l <= s && e <= r){
          tree[p].lazy += val ;
          pushLazy(p , s , e) ;
          return ;
     }

     update(l , r , val , s , (s + e)/2 , 2 * p) ;
     update(l , r , val , (s + e)/2 + 1 , e , 2 * p + 1) ;
     tree[p].val = min(tree[2 * p].val , tree[2 * p + 1].val) ;
}


ll query(int l  , int r , int s = 0 , int e = 2 * n - 1 , int p = 1){
    if(l > e || r < s ) return 1LL << 60 ;
    pushLazy(p , s , e);
    if(l <= s && e <= r) return tree[p].val ;
    return min(query(l , r , s , (s + e)/2 , 2 * p) , query(l , r , (s + e)/2 + 1 , e , 2 * p + 1)) ;
}

int main() {

    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0);

    while(cin >> n && n ) {

        vector < ll > pre ;

        memset(tree , 0 , sizeof tree);

        for(int i = 0 ; i < n ; i++) pre.push_back(0);

        for(int i = n ; i < 2 * n ; i++) {
            ll x ; cin >> x ;
            pre.push_back(pre.back() + x) ;
        }

        for(int i = 0 ; i < pre.size() ; i++) update(i , i , pre[i]);

        int res = 0 ;

        for(int i = 2 * n - 1 , j = 1 ; i >= n ; i-- , j++) {
            update(n - j , i - 1 , pre[i] - pre[i - 1]);
            ll ret = query(n - j , i - 1);
            if(ret < 0) continue ;
            res ++ ;
        }

        cout << res << endl ;
    }


    return 0;
}

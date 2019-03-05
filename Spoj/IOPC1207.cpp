/*
    Editorial Link : https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/SPOJ/SPOJ_IOPC1207.txt
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;
 
const int N = 100005 ;
ll tree[N << 2][3] ;
ll lazy[N << 2][3] ;
ll nx , ny , nz , n ;
 
void pushLazy(int s , int e , int p , int dim){
     if(lazy[p][dim]){
           tree[p][dim] ^= 1  ;
           if(s != e){
                 lazy[2 * p][dim] ^= 1;
                 lazy[2 * p + 1][dim] ^= 1 ;
           }
           lazy[p][dim] = 0 ;
     }
}
 
void update(int l , int r , int dim , int s = 0 , int e = n - 1 , int p = 1){
 
     if(s > r || e < l) return ;
 
     pushLazy(s , e , p , dim);
 
     if(s >= l && e <= r){
            tree[p][dim] ^= 1 ;
            if(s != e){
                   lazy[2 * p][dim] ^= 1 ;
                   lazy[2 * p + 1][dim] ^= 1 ;
            }
            return ;
     }
 
     update(l , r , dim , s , (s + e)/2 , 2 * p) ;
     update(l , r , dim , (s + e)/2 + 1 , e , 2 * p + 1);
     tree[p][dim] = tree[2 * p][dim] + tree[2 * p + 1][dim];
}
 
ll query(int l , int r , int dim , int s = 0 , int e = n - 1 , int p = 1){
    if(s > r || e < l) return 0 ;
    pushLazy(s , e , p , dim) ;
    if(s >= l && e <= r)
          return tree[p][dim] ;
    return query(l , r , dim , s , (s + e)/2 , 2 * p) + query(l , r , dim , (s + e)/2 + 1 , e , 2 * p + 1) ;
}
 
int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;
 
    int t ; cin >> t;
 
    while(t--){
          memset(tree , 0 , sizeof tree);
          memset(lazy , 0 , sizeof lazy);
 
          int q;
          cin >> nx >> ny >> nz >> q ;
 
          while(q--){
                 int type ; cin >> type ;
                 if(type == 3){
                    ll lx , ly , lz , rx , ry , rz ;
                    cin >> lx >> ly >> lz >> rx >> ry >> rz ;
                    n = nx ;
                    ll redx = query(lx , rx , 0) ;
                    n = ny ;
                    ll redy = query(ly , ry , 1) ;
                    n = nz ;
                    ll redz = query(lz , rz , 2) ;
 
                    ll grex = (rx - lx + 1) - redx ;
                    ll grey = (ry - ly + 1) - redy ;
                    ll grez = (rz - lz + 1) - redz  ;
 
                    ll res = (redx * redy * redz) + (redx * grey * grez) + (grex * redy * grez) + (grex * grey * redz) ;
                    cout << res << endl ;
                 }
                 else{
                      if(type == 0) n = nx ;
                      if(type == 1) n = ny ;
                      if(type == 2) n = nz ;
                      ll l , r ;
                      cin >> l >> r ;
                      update(l , r , type) ;
                 }
          }
 
 
    }
 
 
 
 
    return 0 ;
}
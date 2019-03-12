/*
    Editorial Link : https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/SPOJ/SPOJ_IOPC1207.txt
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 100005 ;
struct node{
     ll red , lazy , green ;
     node(ll red , ll lazy , ll green) : red(red) , lazy(lazy) , green(green) {}
     node() {red = lazy = green = 0 ;}
} tree[N << 2][3];


void build(int s , int e , int id ,  int p = 1){
     if(s == e){
          tree[p][id] = node(0 , 0 , 1);
          return ;
     }
     build(s , (s + e)/2 , id , 2 * p);
     build((s + e)/2 + 1 , e , id , 2 * p + 1);
     tree[p][id].green = tree[2 * p][id].green + tree[2 * p + 1][id].green ;
}

void pushLazy(int s , int e , int p , int dim){
     if(tree[p][dim].lazy){
           swap(tree[p][dim].green , tree[p][dim].red);
           if(s != e){
                 tree[2 * p][dim].lazy ^= 1;
                 tree[2 * p + 1][dim].lazy ^= 1 ;
           }
           tree[p][dim].lazy = 0 ;
     }
}

void update(int l , int r , int dim , int s , int e  , int p = 1){

     pushLazy(s , e , p , dim);

     if(s > r || e < l) return ;

     if(s >= l && e <= r){
            tree[p][dim].lazy ^= 1 ;
            pushLazy(s, e , p , dim);
            return ;
     }

     update(l , r , dim , s , (s + e)/2 , 2 * p) ;
     update(l , r , dim , (s + e)/2 + 1 , e , 2 * p + 1);
     tree[p][dim].red = tree[2 * p][dim].red + tree[2 * p + 1][dim].red;
     tree[p][dim].green = tree[2 * p][dim].green + tree[2 * p + 1][dim].green;
}

ll query(int l , int r , int dim , int s , int e , int p = 1){
    pushLazy(s , e , p , dim) ;
    if(s > r || e < l) return 0 ;
    if(s >= l && e <= r)
          return tree[p][dim].red ;
    return query(l , r , dim , s , (s + e)/2 , 2 * p) + query(l , r , dim , (s + e)/2 + 1 , e , 2 * p + 1) ;
}

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int t ; cin >> t;

    while(t--){
          memset(tree , 0 , sizeof tree);


          int q;
          int nx , ny , nz , n ;
          cin >> nx >> ny >> nz >> q ;

          build(0 , nx - 1 , 0);
          build(0 , ny - 1 , 1);
          build(0 , nz - 1 , 2);

          while(q--){
                 int type ; cin >> type ;
                 if(type == 3){
                    ll lx , ly , lz , rx , ry , rz ;
                    cin >> lx >> ly >> lz >> rx >> ry >> rz ;
                    ll redx = query(lx , rx , 0 , 0 , nx - 1) ;
                    ll redy = query(ly , ry , 1 , 0 , ny - 1) ;
                    ll redz = query(lz , rz , 2 , 0 , nz - 1) ;

                    ll grex = (rx - lx + 1) - redx ;
                    ll grey = (ry - ly + 1) - redy ;
                    ll grez = (rz - lz + 1) - redz ;

                    ll res = (redx * redy * redz) + (redx * grey * grez) + (grex * redy * grez) + (grex * grey * redz) ;
                    cout << res << endl ;
                 }
                 else{
                      if(type == 0) n = nx ;
                      if(type == 1) n = ny ;
                      if(type == 2) n = nz ;
                      ll l , r ;
                      cin >> l >> r ;
                      update(l , r , type , 0 , n - 1) ;
                 }
          }


    }

    return 0 ;
}

/*
    Idea :
        - build a segment tree (max-query) contain the values of |A[i] - A[i + 1]|
        - the first query is simple update operation
        - for the second one we need to do binary search on the number of steps starting from i
        - the maximum number in the range[i , i + mid - 1] should be <= D.
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 2e5 + 10 ;
int n ;
vector < int > ve ;

int tree[N << 2] ;
void build(int s = 0 , int e = n - 1 , int p = 1){
    if(s == e){
         tree[p] = abs(ve[s] - ve[s + 1]);
         return ;
    }
    build(s , (s + e)/2 , 2 * p);
    build((s + e)/2 + 1 , e , 2 * p + 1);
    tree[p] = max(tree[2 * p] , tree[2 * p + 1]);
}

int query(int l , int r , int s = 0 , int e = n - 1 , int p = 1){
    if(s > r || e < l) return (-1 << 30) ;
    if(s >= l && e <= r) return tree[p] ;
    return max(query(l , r , s , (s + e)/2 , 2 * p) , query(l , r , (s + e)/2 + 1 , e , 2 * p + 1));
}

void setVal(int pos , int s = 0 , int e = n - 1 , int p = 1) {
    if(s > pos || e < pos) return ;
    if(s == e)
        return (void) (tree[p] = abs(ve[pos] - ve[pos + 1]));

    setVal(pos , s , (s + e)/2 , 2 * p);
    setVal(pos , (s + e)/2 + 1 , e , 2 * p + 1);
    tree[p] = max(tree[2 * p] , tree[2 * p + 1]) ;
}


int main() {

    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    cin >> n ;

    for(int i = 0 ; i < n ; i++){
          int x ; cin >> x;
          ve.push_back(x);
    }
    ve.push_back((1e8));

    build();

    int q ; cin >> q ;

    while(q--){

         int t , i , x ;
         cin >> t >> i >> x ;
         i-- ;

         if(t == 1){
              ve[i] = x;
              int where = i - 1;
              if(i == 0) where = n - 1 ;

              setVal(i);
              setVal(where);
         }
         else{
             int low = 1 , high = n - 1 , res = i ;
             while(low <= high){
                 int mid = (low + high)/2 ;
                 if(mid == 0) break ;
                 if(query(i , i + mid - 1) <= x)
                      res = (i + mid)   , low = mid + 1;
                 else
                      high = mid - 1 ;
             }

             cout << res + 1  << endl ;
         }
    }

    return 0;
}

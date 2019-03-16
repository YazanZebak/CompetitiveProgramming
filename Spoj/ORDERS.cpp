#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;


struct BIT {

    vector < int > tree ;

    BIT(int n){
        tree = vector < int > (n) ;
    }

    void update(int i , int add) {
        for( ; i < tree.size() ; i += (i & (-i))) tree[i] += add ;
    }

    int sum(int i) {
        int ans = 0 ;
        for( ; i ; i -= (i & (-i))) ans += tree[i];
        return ans ;
    }

    int getKth(int k) {
        int low = 0 , high = tree.size() ;
        while(low < high) {
            int mid = (low + high)/2 ;
            if(k <= sum(mid))
                high = mid ;
            else
                low = mid + 1 ;
        }
        return low;
    }

    void insert(int x) {
        update(x , 1);
    }

    void erase(int x) {
        update(x , -1);
    }
};

int main() {
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int t ;
    cin >> t ;

    while(t--) {
        int n ;
        cin >> n ;

        BIT tree(n + 1);

        vector < int > ve;
        for(int i = 0 ; i < n ; i++) {
            int x ;
            cin >> x ;
            ve.push_back(x);
            tree.insert(i + 1);
        }

        vector < int > res(n);

        int m = n ;
        for(int i = n - 1 ; i >= 0 ; i--) {
            res[i] = tree.getKth(m - ve[i]);
            tree.erase(res[i]);
            m-- ;
        }

        for(int i = 0 ; i < n ; i++) cout << res[i]  << " " ;
        cout << endl ;

    }
    return 0;
}

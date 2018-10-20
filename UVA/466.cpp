#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

typedef vector < char  > row  ;
typedef vector < row >  matrix ;

matrix rotate(matrix &A) {

    for(int i = 0 ; i < A.size() ; i++)
        for(int j = 0 ; j < A[0].size() ; j++)
            ret[j][A.size() - 1 - i] = A[i][j] ;

    return A = ret ;
}

matrix reflect(matrix &A) {

    matrix ret = A;
    for(int i = 0 ; i < A.size() / 2 ; i++)
        swap(ret[i] , ret[A.size() - i - 1]) ;

    return A = ret ;
}


bool operator == (matrix &A , matrix &B) {

    for(int i = 0 ; i < A.size() ; i++)
        for(int j = 0 ; j < A[0].size() ; j++)
            if(A[i][j] != B[i][j])
                return false ;

    return true ;
}

int main() {
    ios::sync_with_stdio(false) ;

    int n , c = 0;

    while(cin >> n) {

        c++ ;

        matrix A , B;

        A.resize(n) , B.resize(n) ;

        for(int i = 0 ; i < n ; i++) {
            for(int j = 0 ; j < n ; j++) {
                char c;
                cin >> c ;
                A[i].push_back(c) ;
            }
            for(int j = 0 ; j < n ; j++) {
                char c ;
                cin >> c ;
                B[i].push_back(c) ;
            }
        }

        if(A == B) {
            cout << "Pattern " << c << " was preserved." << endl;
            continue;
        }

        bool ok = 0 ;

        for(int i = 0 ; i < 3 && !ok ; i++) {
            rotate(A) ;
            if(A == B) {
                ok = 1 ;
                if(i == 0) cout << "Pattern " << c << " was rotated 90 degrees." << endl ;
                if(i == 1) cout << "Pattern " << c << " was rotated 180 degrees." << endl ;
                if(i == 2) cout << "Pattern " << c << " was rotated 270 degrees." << endl ;
            }
        }


        if(ok) continue ;
        rotate(A) ;
        reflect(A) ;

        if(A == B) {
            cout << "Pattern " << c << " was reflected vertically." << endl ;
            continue ;
        }

        for(int i = 0 ; i < 3 && !ok ; i++) {
            rotate(A) ;
            if(A == B) {
                ok = 1 ;
                if(i == 0) cout << "Pattern " << c << " was reflected vertically and rotated 90 degrees." << endl;
                if(i == 1) cout << "Pattern " << c << " was reflected vertically and rotated 180 degrees." << endl;
                if(i == 2) cout << "Pattern " << c << " was reflected vertically and rotated 270 degrees." << endl;
            }
        }

        if(ok) continue ;

        cout << "Pattern " << c << " was improperly transformed." << endl;
    }


    return 0;
}

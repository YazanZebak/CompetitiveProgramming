/*
   Editorial Link : https://community.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm428
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;


const int MAX = 202;
ll C[MAX][MAX] ;
void build(){
	for(int i = 0 ; i < MAX; ++i)
		for(int j = 0 ; j < MAX; ++j)
			C[i][j] = min( (j == 0) ? 1 : ( (i == 0) ? 0 : C[i - 1][j - 1] + C[i - 1][j]) , 1LL << 30 ) ;
}

string solve(int n , int m , int k){
	   if(n == 0 && m == 0) return "" ;
	   if(n == 0) return "z" + solve(n , m - 1 , k) ;
	   if(m == 0) return "a" + solve(n - 1 , m , k) ;
	   return (C[n + m - 1][m] >= k ? "a" + solve(n - 1 , m , k) : "z" + solve(n , m - 1 , k - C[n + m - 1][m]));
}

class TheDictionary{

public :
    string find(int n , int m , int k){
        build();
    	if(C[n + m][m] < k) return "" ;
    	return solve(n , m , k);
    }
};

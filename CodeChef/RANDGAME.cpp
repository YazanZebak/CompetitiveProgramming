// Editorial : https://discuss.codechef.com/t/randgame-editorial/24524
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

unordered_map < ll, int > memo;

int solve(ll n) {

    if(n == 1)
        return true ;
    if(n == 0)
        return false ;

    if(memo.find(n) != memo.end())
        return memo[n];

    if(n % 2 == 0)
        return memo[n] = !solve(n / 2);
    else
        return memo[n] = !solve(n - 1) || !solve(n + 1);
}

int main() {

    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    int t ; cin >> t ;

    while(t--) {
        ll n ; cin >> n ;

        int temp = solve(n);

        if(temp) {
            cout << "Win" << endl ;
            while(n) {
                if(n % 2 == 0) {
                    cout << "/2" << endl ;
                    fflush(stdout);
                    n /= 2 ;
                }
                else {
                    if(!solve(n - 1))
                        cout << "-1" << endl, n-- ;
                    else
                        cout << "+1" << endl, n++ ;
                    fflush(stdout);
                }

                string s ; cin >> s ;

                if(s == "WA") exit(0);
                else if(s == "GG") break ;
                else {
                    if(s == "/2") n /= 2 ;
                    if(s == "-1") n--;
                    if(s == "+1") n++;
                }
            }
        }

        else {
            cout << "Lose" << endl ;
            fflush(stdout);
            string s ;
            cin >> s ;
            continue ;
        }


    }

    return 0;
}

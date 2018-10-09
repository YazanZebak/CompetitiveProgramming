#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;



map < set < int > , int > num;
map < int , set < int > > se;

int main() {

    ios::sync_with_stdio(false) ;


    int t ;
    scanf("%d",&t);

    int cnt = 2 ;

    while(t--) {

        int n ;
        scanf("%d",&n) ;

        stack < int > st ;

        num[set < int > ()] = 1;
        se[1] = set < int > ();

        while(n -- ) {

            char in[20] ;
            scanf("%s",in) ;

            int res = 0 ;

            if(in[0] == 'P') {
                st.push(1);
            }

            else if(in[0] == 'D') {
                st.push(st.top());
            }

            else if(in[0] == 'A') {

                auto A = st.top() ;
                st.pop() ;
                auto B = se[st.top()] ;
                st.pop() ;

                B.insert(A) ;
                if(!num[B]) {
                    num[B] = cnt ;
                    se[cnt] = B ;
                    cnt ++ ;
                }

                st.push(num[B]) ;
            }

            else if(in[0] == 'I') {

                auto A = se[st.top()] ;
                st.pop() ;
                auto B = se[st.top()] ;
                st.pop() ;

                set < int > sec ;
                set_intersection(A.begin() , A.end() , B.begin() , B.end() , inserter(sec , sec.begin()));

                if(!num[sec]) {
                    num[sec] = cnt;
                    se[cnt] = sec ;
                    cnt ++ ;
                }

                st.push(num[sec]) ;
            }

            else {


                auto A = se[st.top()] ;
                st.pop() ;
                auto B = se[st.top()] ;
                st.pop() ;

                set < int > sec ;
                set_union(A.begin() , A.end() , B.begin() , B.end() , inserter(sec , sec.begin()));


                if(!num[sec]) {
                    num[sec] = cnt;
                    se[cnt] = sec ;
                    cnt ++ ;
                }

                st.push(num[sec]) ;
            }

            res = (int)se[st.top()].size() ;
            printf("%d\n",res) ;
        }
        puts("***");
    }

    return 0;
}

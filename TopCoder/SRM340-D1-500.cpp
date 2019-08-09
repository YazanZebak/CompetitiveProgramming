// solution : https://community.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm340
#include<bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int inf = 1e4;

class CsCourses {
  public:
    vector <int> getOrder(vector <int>, vector <int>, vector <int>, int);
};

struct data{
    int tv , pv , month ;
    data(){}
    data(int tv , int pv , int month) : tv(tv) , pv(pv) , month(month) {}
};

vector < data > course ;
int sp , n , memo[52][52][52];

int solve(int i, int t, int p){

    if(t >= sp && p >= sp) return i ;
    if(i == 50) return inf ;

    int &ret = memo[i][t][p];
    if(ret != -1) return ret ;

    ret = inf ;

    for(int j = 0 ; j < n ; j++){

          if(course[j].month <= i) continue ;
          if(t < course[j].tv - 1 || p < course[j].pv - 1) continue ;
          int a = max(t , course[j].tv) , b = max(p , course[j].pv) ;

          if(a == t && b == p) continue ;

          ret = min(ret , solve(i + 1, a , b));
    }

    return ret ;
}

vector < int > res ;

void build(int i, int t, int p){

    if(t >= sp && p >= sp) return  ;
    if(i == 50) return  ;

    int ret = solve(i , t , p);

    for(int j = 0 ; j < n ; j++){

          if(course[j].month <= i) continue ;
          if(t < course[j].tv - 1 || p < course[j].pv - 1) continue ;
          int a = max(t , course[j].tv) , b = max(p , course[j].pv) ;

          if(a == t && b == p) continue ;

          int c = solve(i + 1 , a , b);
          if(c == ret){
                res.push_back(j);
                build(i + 1, a, b);
                break ;
          }
    }
}


vector <int> CsCourses::getOrder(vector <int> TV, vector <int> PV, vector <int> E, int skill){

        n = E.size() ;
        course.clear() ;
        for(int i = 0 ; i < n ; i++)
            course.push_back(data(TV[i] , PV[i] , E[i]));

        sp = skill ;
        memset(memo , -1 , sizeof memo);
        res.clear();

        int ret = solve(0 , 0 , 0);
        if(ret == inf) return vector < int > ();


        build(0 , 0 , 0);
        return res ;
}

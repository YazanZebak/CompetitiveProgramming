#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

struct state {
    vector < string > grid ;
    vector < int > path ;

    state(vector < string > grid , vector < int > path) : grid(grid) , path(path) {}

    bool check(vector < string > target) {
        for(int i = 0 ; i < grid.size() ; i++)
            if(grid[i] != target[i]) return false ;
        return true ;
    }
};

vector < int > bfs(vector < string > src , vector < string > trg) {

    queue < state > Q ;
    map < vector < string > , bool > vis ;

    vis[src] = 1 ;
    Q.push(state(src , vector < int > ())) ;

    while(!Q.empty()) {
        state u = Q.front() ;
        Q.pop() ;

        if(u.check(trg)) {
            return u.path ;
        }

        for(int i = 0 ; i < u.grid.size() ; i++) {
            for(int j = 0 ; j < u.grid[i].size() ; j++) {


                for(int k = j + 1 ; k < u.grid[i].size() ; k++) {

                    vector < string > st = u.grid ;
                    vector < int > path = u.path ;
                    st[i][min(k , j)] = '.' ;
                    st[i][max(k , j)] = (u.grid[i][j] == u.grid[i][k] ? '.' : '#') ;
                    path.push_back(i * 1000000 + j * 10000 + i * 100 + k);
                    if(!vis[st]) {
                        vis[st] = 1;
                        Q.push(state(st , path));
                    }
                }

                for(int k = i + 1 ; k < u.grid.size() ; k++) {

                    vector < string > st = u.grid ;
                    vector < int > path = u.path ;
                    st[i][j] = '.' ;
                    st[k][j] = (u.grid[k][j] == u.grid[i][j] ? '.' : '#') ;

                    path.push_back(i * 1000000 + j * 10000 + k * 100 + j);
                    if(!vis[st]) {
                        vis[st] = 1;
                        Q.push(state(st , path));
                    }
                }
            }
        }
    }

    vector < int > ret ;
    ret.push_back(-1);
    return ret;
}


class TransformBoardDiv2 {

public :
    vector < int > getOperations(vector < string > start , vector < string > target) {
        return bfs(start , target);
    }
};

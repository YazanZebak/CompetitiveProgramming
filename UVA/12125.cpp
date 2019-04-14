/*
	Idea: 
	    - we want to build a flow network and calc the max_flow for each sink. 
		- represent each ice piece as a node.
		- the source node is each node has penguin on it , we need to link it with super src.
		- we have to do vertex split so we can move capacitiy from the nodes to the edges.  
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

struct node{
    int x , y , p , j ;
    node(int x , int y , int p , int j) : x(x) , y(y) , p(p) , j(j) {}
    node(){ x = y = p = j = -1 ;}
};

int n;
double d;
vector < node > ve;

struct edge{
	int to , cap , rev;
	edge(){}
	edge(int to , int cap,  int rev) : to(to) , cap(cap) , rev(rev) {}
};

vector < vector < edge > > G;

void add_edge(int from , int to , int cap){
	G[from].push_back(edge(to , cap , G[to].size()));
	G[to].push_back(edge(from , 0 , G[from].size() - 1));
}

void get_network(){

    G.clear() ;
    G.resize(300);

    for(int i = 1 ; i <= n ; i++){
          add_edge(0 , i , ve[i].p);
          add_edge(i  , i + n , ve[i].j);
    }

    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= n ; j++){
              if(i == j) continue ;
              int x = (ve[i].x - ve[j].x) * (ve[i].x - ve[j].x);
              int y = (ve[i].y - ve[j].y) * (ve[i].y - ve[j].y);
              double dist = sqrt(x + y * 1.0) ;
              if(dist > d) continue ;
              add_edge(i + n , j , INT_MAX);
        }
    }

}

int level[300];

void bfs(int s){

	memset(level , -1 , sizeof(level));
	queue < int > Q;
	level[s] = 0;
	Q.push(s);
	while(Q.size()){
		int v = Q.front();
		Q.pop();
		for(auto &e : G[v]){
			if(e.cap > 0 && level[e.to] < 0){
				level[e.to] = level[v] + 1;
				Q.push(e.to);
			}
		}
	}

}

int dfs(int v , int sink , int flow){
	if(v == sink) return flow;
	for(auto &e : G[v]){
		if(e.cap > 0 && level[v] < level[e.to]){
			int d = dfs(e.to , sink  , min(flow , e.cap) );
			if(d > 0){
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}

int max_flow(int src , int sink){
	int flow = 0;
	while(true){
		bfs(src);
		if(level[sink] < 0)
			return flow;
		int f;
		while( (f = dfs(src , sink , INT_MAX)) > 0){
			flow += f;
		}
	}
	return flow;
}


int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int tc ; cin >> tc;

    while(tc--){

        cin >> n >> d ;

        ve.clear() ;
        ve.push_back(node());

        int tot = 0 ;
        for(int i = 1 ; i <= n ; i++){
                int x , y , p , j ;
                cin >> x >> y >> p >> j  ;
                ve.push_back(node(x , y , p , j));
                tot += p ;
        }

        vector < int > res ;
        for(int sink = 1 ; sink <= n ; sink++){
             get_network() ;
             if(max_flow(0 , sink) == tot)
                  res.push_back(sink - 1) ;
        }
        if(!res.size()) cout << -1  ;

        else{
              cout << res[0];
              for(int i = 1 ; i < res.size() ; i++)
                  cout << " " << res[i] ;
        }

        cout << endl ;
    }



    return 0;
}

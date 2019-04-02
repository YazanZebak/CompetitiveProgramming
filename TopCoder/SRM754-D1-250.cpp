/*
	Idea:
	    - define S as the set of points, and N = |S|.
		- We take every distinct pair of points, which is O(N^2) 
		- For each pair of points A, B, compute the two other points C, D that make a square ABCD
		- If C and D are both NOT in S, or both IN S, then move on. 
		- Otherwise the one which is NOT in S will be adding a new square, so add it to some other set T.
		- Final answer will be |T|.
		- Finding C and D can be done through this method 
		- Link : https://math.stackexchange.com/questions/964625/find-3rd-and-4th-co-ordinates-for-a-square-given-co-ordinates-of-two-points
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;
typedef pair < int , int > point ;

#define x first
#define y second


class MoreSquares{

public :

    int countLocations(int N, int SX, int SY, vector <int> Xprefix, vector <int> Yprefix){

        vector < int > X = Xprefix;
        vector < int > Y = Yprefix;
        int L = X.size();
        for(int i = L ; i < N ; i++){
               X.push_back(0) , Y.push_back(0);
               X[i] = (X[i - 1] * 47 + 42) % SX ;
               Y[i] = (Y[i - 1] * 47 + 42) % SY ;
        }

        set < pair < int , int > > se ;
        for(int i = 0 ; i < N ; i++) se.insert({X[i] , Y[i]});

        int res = 0 ;

        set < pair < int , int > > T ;

        for(auto A : se){
            for(auto B : se){

                   if(A == B) continue ;

                   int deltaX = B.x - A.x ;
                   int deltaY = B.y - A.y ;

                   point p1(0 , 0) , p2(0 , 0)  ;

                   p1.x = B.x - deltaY;
                   p1.y = B.y + deltaX;

                   p2.x = A.x - deltaY ;
                   p2.y = A.y + deltaX ;

                   if(se.find({p1.x , p1.y}) != se.end()) if(se.find({p2.x , p2.y}) == se.end()) T.insert({p2.x , p2.y});
            }
        }

        return T.size() ;
    }

};
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

struct trie {

    bool isleaf ;
    trie* child[30] ;

    trie() {
        isleaf = 0 ;
        memset(child , 0 , sizeof child);
    }

    void insert(char* str) {
        if(*str == '\0') isleaf = 1;
        else {
            int cur = *str - 'a' ;
            if(child[cur] == 0)
                child[cur] = new trie() ;
            child[cur]->insert(str + 1) ;
        }
    }

    int query(const char* str) {
        if(*str == '\0') return 0 ;

        int cnt = 0 ;
        int cur = *str - 'a' ;

        for(char c = 'a' ; c <= 'z' ; c++)
            if(child[cur]->child[c - 'a']) cnt ++ ;

        return ( (cnt > 1) || child[cur]->isleaf ) + child[cur]->query(str + 1) ;
    }

    void inti(trie* cur) {
        for(int i = 0 ; i < 26 ; i++)
            if(cur->child[i] != NULL)
                inti(cur->child[i]);

        delete cur ;
    }

};

int main() {
    int n ;

    while(scanf("%d",&n) != EOF) {

        trie tree ;

        vector < string > vs ;

        for(int i = 0 ; i < n ; i++) {
            char str[100];
            scanf("%s",str);
            tree.insert(str);
            string s = (string)str ;
            vs.push_back(s);
        }
        double res = 0 ;

        for(auto &s : vs) {
            res += tree.query(s.c_str()) ;
        }
        res /= n ;

        printf("%.2f\n",res);

        for(char c = 'a' ; c <= 'z' ; c++)
            if(tree.child[c - 'a'])
                tree.inti(tree.child[c - 'a']);
    }




    return 0;
}

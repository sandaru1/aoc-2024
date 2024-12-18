#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <regex>
#include <limits>

using namespace std;

#define pi pair<int,int>

struct node {
    int r,c,distance;
    node(int R,int C,int dist) {
        r = R; c = C; distance = dist;
    }

    bool operator>(const node& rhs) const
    {
        return distance > rhs.distance;
    }
};

vector<string> grid;
priority_queue<node,vector<node>,greater<node> > pq;

int dr[4] = {0,1,0,-1};
int dc[4] = {1,0,-1,0};

bool visited[200][200];

vector<pi> blocks;

#define R 71
#define C 71
#define COUNT 1024

int main() {
    while(!cin.eof()) {
        int x,y;
        cin >> x;
        cin.ignore();
        cin >> y;
        blocks.push_back(pi(x,y));
    }


    for(int i=0;i<R;i++) {
        string s = "";
        for(int k=0;k<C;k++) s+=".";
        grid.push_back(s);
    }

    for(int i=0;i<COUNT;i++) {
        grid[blocks[i].second][blocks[i].first]='#';
    }

    for(int i=0;i<grid.size();i++) {
        cout << grid[i] << endl;
    }

    pq.push(node(0,0,0));

    while(pq.size()>0) {
        node cur = pq.top();
        pq.pop();
        if (cur.r == R-1 && cur.c==C-1) {
            cout << cur.distance << endl;
            break;
        }
        if (visited[cur.r][cur.c]) continue;
        visited[cur.r][cur.c] = true;
        for(int i=0;i<4;i++) {
            int r = cur.r + dr[i];
            int c = cur.c + dc[i];
            if (r<0 || c<0 || r>=R || c>=C) continue;
            if (grid[r][c]=='#') continue;
            if (visited[r][c]) continue;
            pq.push(node(r,c,cur.distance+1));
        }
    }

    return 0;
}
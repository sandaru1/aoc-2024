#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <regex>
#include <limits>

using namespace std;

struct node {
    int r,c,d,distance;
    int pr,pc,pd;
    node(int R,int C,int D,int dist) {
        r = R; c = C; d = D; distance = dist;
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

bool visited[200][200][4];
vector<node> previous[200][200][4];

void mark(int r,int c, int d) {
    if (r==-1 || c==-1) return;
    if (visited[r][c][d]) return;
    visited[r][c][d] = true;
    //cout << r << " " << c << " " << d << " "<< endl;
    grid[r][c] = 'O';
    for(int i=0;i<previous[r][c][d].size();i++) {
        mark(previous[r][c][d][i].r,previous[r][c][d][i].c,previous[r][c][d][i].d);
    }
}

int main() {
    string s;
    while(cin >> s) grid.push_back(s);

    int r = 0;
    int c = 0;
    int er = 0;
    int ec = 0;

    for(int i=0;i<grid.size();i++) {
        for(int k=0;k<grid[0].size();k++) {
            if (grid[i][k]=='S') {
                r = i;
                c = k;
                grid[i][k] = '.';
            }
            if (grid[i][k]=='E') {
                er = i;
                ec = k;
            }
        }
    }

    node first_node = node(r,c,0,0);
    first_node.pr = -1;
    first_node.pc = -1;
    first_node.pd = -1;
    pq.push(first_node);

    int best = 10000000;

    while(pq.size()>0) {
        node cur = pq.top();
        pq.pop();
        if (!visited[cur.r][cur.c][cur.d]) {
            previous[cur.r][cur.c][cur.d].push_back(node(cur.pr,cur.pc,cur.pd,cur.distance));
        } else if (previous[cur.r][cur.c][cur.d][0].distance==cur.distance) {
            previous[cur.r][cur.c][cur.d].push_back(node(cur.pr,cur.pc,cur.pd,cur.distance));
        }
        visited[cur.r][cur.c][cur.d] = true;
        //cout << cur.r << " " << cur.c << " " << cur.d << " " << cur.distance  << endl;
        if (cur.distance>best) break;
        if (grid[cur.r][cur.c]=='E') {
            best = cur.distance;
            cout << cur.distance << endl;
            continue;
        }
        for(int d=0;d<4;d++) {
            int diff = abs(cur.d-d);
            if (diff>2) diff=1;

            int R = cur.r;
            int C = cur.c;
            int distance = cur.distance;
            if (diff == 0) {
                R += dr[d]; C+= dc[d];
                distance += 1;
            } else {
                distance += 1000*diff;
            }
            if (visited[R][C][d]) continue;
            if (grid[R][C]=='#') continue;

            node nd = node(R,C,d,distance);
            nd.pr = cur.r;
            nd.pc = cur.c;
            nd.pd = cur.d;
            pq.push(nd);
        }
    }

    memset(visited,0,sizeof(visited));
    for(int i=0;i<4;i++) {
        mark(er,ec,i);
    }

    int ans = 0;
    for(int i=0;i<grid.size();i++) {
        for(int k=0;k<grid.size();k++) {
            if (grid[i][k]=='O') ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
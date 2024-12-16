#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <regex>
#include <limits>

using namespace std;

struct node {
    int r,c,d,distance;
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

void check_and_add(int r,int c,int d,int distance) {
    if (d<0) d+=4;
    if (d>3) d=d%4;
    int R = r + dr[d];
    int C = c + dc[d];
    if (visited[R][C][d]) return;
    if (grid[R][C]=='#') return;
    pq.push(node(R,C,d,distance));
}

int main() {
    string s;
    while(cin >> s) grid.push_back(s);

    int r = 0;
    int c = 0;

    for(int i=0;i<grid.size();i++) {
        for(int k=0;k<grid[0].size();k++) {
            if (grid[i][k]=='S') {
                r = i;
                c = k;
                grid[i][k] = '.';
                break;
            }
        }
    }

    pq.push(node(r,c,0,0));

    while(pq.size()>0) {
        node cur = pq.top();
        pq.pop();
        visited[cur.r][cur.c][cur.d] = true;
        //cout << cur.r << " " << cur.c << " " << cur.d << " " << cur.distance  << endl;
        if (grid[cur.r][cur.c]=='E') {
            cout << cur.distance << endl;
            break;
        }
        int d = cur.d;
        check_and_add(cur.r,cur.c,d,cur.distance+1);
        check_and_add(cur.r,cur.c,d+1,cur.distance+1001);
        check_and_add(cur.r,cur.c,d-1,cur.distance+1001);
        check_and_add(cur.r,cur.c,d+2,cur.distance+2001);
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool looped(vector<string> grid,int R,int C) {
    bool visited[1000][1000][4];
    memset(visited,0,sizeof(visited));

    int direction = 0;
    int d[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};

    int r = R;
    int c = C;

    while(true) {
        if (visited[r][c][direction%4]) {
            return true;
        }
        visited[r][c][direction%4] = true;
        int nextR = r + d[direction%4][0];
        int nextC = c + d[direction%4][1];
        if (nextR < 0 || nextR >= grid.size() || nextC < 0 || nextC >= grid[0].size()) {
            return false;
        }
        if (grid[nextR][nextC]=='#') {
            direction++;
        } else {
            r = nextR;
            c = nextC;
        }
    }

    return false;
}

int main() {
    vector<string> grid;

    while(!cin.eof()) {
        string s;
        cin >> s;
        grid.push_back(s);
    }

    int r,c;

    for(int i=0;i<grid.size();i++) {
        for(int k=0;k<grid[i].size();k++) {
            if (grid[i][k]=='^') {
                grid[i][k] = '.';
                r = i;
                c = k;
                break;
            }
        }
    }

    int ans = 0;
    for(int i=0;i<grid.size();i++) {
        for(int k=0;k<grid[i].size();k++) {
            if (i==r && k==c) continue;
            if (grid[i][k]=='#') continue;
            grid[i][k] = '#';
            if (looped(grid,r,c)) {
                ans++;
            }
            grid[i][k] = '.';
        }
    }

    cout << ans << endl;

    return 0;
}
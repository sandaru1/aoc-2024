#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> grid;
bool visited[1000][1000];

int main() {
    while(!cin.eof()) {
        string s;
        cin >> s;
        grid.push_back(s);
    }

    int direction = 0;
    int d[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};

    int r = 0;
    int c = 0;

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

    while(true) {
        visited[r][c] = true;
        int nextR = r + d[direction%4][0];
        int nextC = c + d[direction%4][1];
        if (nextR < 0 || nextR >= grid.size() || nextC < 0 || nextC >= grid[0].size()) {
            break;
        }
        if (grid[nextR][nextC]=='#') {
            direction++;
        } else {
            r = nextR;
            c = nextC;
        }
    }

    int ans = 0;
    for(int i=0;i<grid.size();i++) {
        for(int k=0;k<grid[i].size();k++) {
            if (visited[i][k]) ans++;
        }
    }

    cout << ans << endl;

    return 0;
}
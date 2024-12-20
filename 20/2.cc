#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <regex>
#include <limits>

using namespace std;

vector<string> grid;
int dist[200][200];

int dr[4] = {0,1,0,-1};
int dc[4] = {1,0,-1,0};

int main() {
    string s;
    while(cin >> s) grid.push_back(s);

    int r,c,er,ec;

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
                grid[i][k] = '.';
            }
        }
    }

    memset(dist,-1,sizeof(dist));
    bool ok = true;
    int cur = 0;
    while(ok) {
        dist[r][c] = cur++;
        ok = false;
        for(int i=0;i<4;i++) {
            int R = r + dr[i];
            int C = c + dc[i];
            if (grid[R][C]=='.' && dist[R][C]==-1) {
                ok = true;
                r = R;
                c = C;
                break;
            }
        }
    }

    int total = 0;

    for(int r1=0;r1<grid.size();r1++) {
        for(int c1=0;c1<grid[0].size();c1++) {
            if (dist[r1][c1]==-1) continue;
            for(int r2=0;r2<grid.size();r2++) {
                for(int c2=0;c2<grid[0].size();c2++) {
                    if (dist[r2][c2]==-1) continue;
                    if ((abs(r1-r2) + abs(c1-c2))>20) continue;
                    if (dist[r1][c1]>dist[r2][c2]) {
                        int save = dist[r1][c1] - dist[r2][c2] - abs(r1-r2) - abs(c1-c2);
                        if (save>=100) total++;
                    }
                }
            }
        }
    }

    cout << "Total = " << total << endl;

    return 0;
}
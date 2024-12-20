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
//int saves[1000];

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

    /*cout.fill(' ');

    for(int i=0;i<grid.size();i++) {
        for(int k=0;k<grid[0].size();k++) {
            if (grid[i][k]=='#') cout << "###"; else
            cout << setw(3) << dist[i][k];
        }
        cout << endl;
    }*/

    int total = 0;

    for(int i=0;i<grid.size();i++) {
        for(int k=0;k<grid[0].size();k++) {
            if (grid[i][k]=='#') {
                if (i>0 && i<grid.size()-1 && dist[i-1][k]!=-1 && dist[i+1][k]!=-1) {
                    int save = max(dist[i-1][k],dist[i+1][k]) - min(dist[i-1][k],dist[i+1][k]) - 2;
                    if (save>=100) total++;
                    //saves[save]++;
                }
                if (k>0 && k<grid[0].size()-1 && dist[i][k-1]!=-1 && dist[i][k+1]!=-1) {
                    int save = max(dist[i][k-1],dist[i][k+1]) - min(dist[i][k-1],dist[i][k+1]) - 2;
                    if (save>=100) total++;
                    //saves[save]++;
                }
            }
        }
    }

    /*for(int i=0;i<1000;i++) {
        if (saves[i]!=0) cout << i << " " << saves[i] << endl;
    }*/

    cout << "Total = " << total << endl;

    return 0;
}
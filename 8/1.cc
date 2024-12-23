#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

vector<string> grid;
bool anti[200][200];
map< char,vector< pair<int,int> > > ants;

int main() {
    while(!cin.eof()) {
        string s;
        cin >> s;
        grid.push_back(s);
    }

    for(int i=0;i<grid.size();i++) {
        for(int k=0;k<grid.size();k++) {
            if (grid[i][k]!='.') {
                pair<int,int> pos(i,k);
                ants[grid[i][k]].push_back(pos);
            }
        }
    }

    for(char c='0';c<='z';c++) {
        for(int i=0;i<ants[c].size();i++) {
            for(int k=i+1;k<ants[c].size();k++) {
                int r1 = ants[c][i].first;
                int c1 = ants[c][i].second;
                int r2 = ants[c][k].first;
                int c2 = ants[c][k].second;

                int r3 = r1 - (r2 - r1);
                int c3 = c1 - (c2 - c1);

                int r4 = r2 - (r1 - r2);
                int c4 = c2 - (c1 - c2);

                if (r3 >= 0 && c3 >= 0) {
                    anti[r3][c3] = true;
                }

                if (r4 >= 0 && c4 >= 0) {
                    anti[r4][c4] = true;
                }

                //grid[r3][c3] = '#';
                //grid[r4][c4] = '#';

            }
        }
    }

    int ans = 0;

    for(int i=0;i<grid.size();i++) {
        for(int k=0;k<grid.size();k++) {
            if (anti[i][k]) {
                ans++;
            }
        }
    }

    cout << ans << endl;

    return 0;
}
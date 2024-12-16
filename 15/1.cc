#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <regex>
#include <limits>

using namespace std;

vector<string> grid;
string operations = "";

int main() {
    while(!cin.eof()) {
        string s;
        getline(cin,s);
        grid.push_back(s);

        if (s=="") break;
    }

    while(!cin.eof()) {
        string s;
        getline(cin,s);
        operations += s;
    }

    int roboR = 0;
    int roboC = 0;

    for(int i=0;i<grid.size();i++) {
        for(int k=0;k<grid[0].size();k++) {
            if (grid[i][k]=='@') {
                roboR = i;
                roboC = k;
                grid[i][k] = '.';
                break;
            }
        }
    }

    //            ^  >  v  <
    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = { 0, 1, 0,-1};
    
    map<char,int> dpos;
    dpos['^'] = 0;
    dpos['>'] = 1;
    dpos['v'] = 2;
    dpos['<'] = 3;

    for(int i=0;i<operations.size();i++) {
        int r = roboR;
        int c = roboC;
        int d = dpos[operations[i]];
        while(true) {
            r += dr[d];
            c += dc[d];
            if (grid[r][c]=='#') break;
            if (grid[r][c]=='.') {
                roboR += dr[d];
                roboC += dc[d];
                if (grid[roboR][roboC]=='O') {
                    grid[roboR][roboC] = '.';
                    grid[r][c] = 'O';
                }
                break;
            }
        }
    }

    int ans = 0;
    for(int i=0;i<grid.size();i++) {
        for(int k=0;k<grid[0].size();k++) {
            if (grid[i][k]=='O') {
                ans += i*100 + k;
            }
            cout << grid[i][k];
        }
        cout << endl;
    }

    cout << ans << endl;


    return 0;
}
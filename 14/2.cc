#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <regex>
#include <limits>

using namespace std;

#define XSIZE 101
#define YSIZE 103

int main() {
    
    vector<pair<int,int> > locations;
    vector<pair<int,int> > velocities;

    while(!cin.eof()) {
        string s;
        getline(cin,s);

        regex rgx("p=([\\-0-9]+),([\\-0-9]+) v=([\\-0-9]+),([\\-0-9]+)");
        smatch match;

        if (regex_search(s, match, rgx)) {
            long x = stol(match[1]);
            long y = stol(match[2]);
            long vx = stol(match[3]);
            long vy = stol(match[4]);
            locations.push_back(pair<int,int>(x,y));
            velocities.push_back(pair<int,int>(vx,vy));
        }
    }

    char grid[XSIZE][YSIZE];

    for(int i=1;i<10000;i++) {
        memset(grid,'.',sizeof(grid));
        for(int k=0;k<locations.size();k++) {
            locations[k].first = (locations[k].first + velocities[k].first) % XSIZE;
            locations[k].second = (locations[k].second + velocities[k].second) % YSIZE;
            if (locations[k].first<0) locations[k].first+=XSIZE;
            if (locations[k].second<0) locations[k].second+=YSIZE;
            grid[locations[k].first][locations[k].second] = '1';
        }

        // biggest cluster
        int best = 0;
        for(int x=0;x<XSIZE;x++) {
            for(int y=0;y<YSIZE;y++) {
                if (grid[x][y]=='.') continue;
                int cnt = 0;
                int y2 = 0;
                while(y2+y>=0) {
                    if (grid[x][y2+y]=='1') cnt++;
                    y2--;
                }
                y2 = 0;
                while(y2+y<YSIZE) {
                    if (grid[x][y2+y]=='1') cnt++;
                    y2++;
                }
                int x2 = 0;
                while(x2+x>=0) {
                    if (grid[x2+x][y]=='1') cnt++;
                    x2--;
                }
                x2 = 0;
                while(x2+x<XSIZE) {
                    if (grid[x2+x][y]=='1') cnt++;
                    x2++;
                }
                best = max(best,cnt);
            }
        }

        if (best>50) {
            for(int k=0;k<YSIZE;k++) {
                for(int i=0;i<XSIZE;i++) {
                    cout << grid[i][k];
                }
                cout << endl;
            }
            cout << i << endl << endl;
        }
    }

    return 0;
}
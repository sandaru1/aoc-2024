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
            //cout << x << " " << y << " " << vx << " " << vy << endl;
            locations.push_back(pair<int,int>((x + vx *100) % XSIZE,(y + vy * 100) % YSIZE));
        }
    }

    /*char grid[XSIZE][YSIZE];
    for(int i=0;i<XSIZE;i++) {
        for(int k=0;k<YSIZE;k++) {
            grid[i][k] = '.';
        }
    }*/

    int q[4] = {0,0,0,0};

    for(int i=0;i<locations.size();i++) {
        int x = locations[i].first;
        int y = locations[i].second;
        if (x<0) x += XSIZE;
        if (y<0) y += YSIZE;
        if (x<XSIZE/2) {
            if (y<YSIZE/2) {
                q[0]++;
            } else if (y>YSIZE/2) {
                q[1]++;
            }
        } else if (x>XSIZE/2) {
            if (y<YSIZE/2) {
                q[2]++;
            } else if (y>YSIZE/2) {
                q[3]++;
            }
        }
        //grid[x][y] = '1';
    }

    /*for(int k=0;k<YSIZE;k++) {
        for(int i=0;i<XSIZE;i++) {
            cout << grid[i][k];
        }
        cout << endl;
    }*/

    long ans = q[0] * q[1] * q[2] * q[3];
    //cout << q[0] << " " << q[1] << " " << q[2] << " " << q[3] << endl;
    cout << ans << endl;


    return 0;
}
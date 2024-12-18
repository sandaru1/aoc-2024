#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <regex>
#include <limits>

using namespace std;

vector<string> grid;
string operations = "";
int dr[4] = {-1, 0, 1, 0};
int dc[4] = { 0, 1, 0,-1};

bool can_move(int r,int c,int d) {
    if (grid[r][c]=='#') return false;
    if (grid[r][c]=='.') return true;

    int c1,c2;
    if (grid[r][c]=='[') {
        c1 = c; c2 = c+1;
    } else {
        c1 = c-1; c2 = c;
    }

    if (d==0 || d==2) {
        return can_move(r+dr[d],c1+dc[d],d) && can_move(r+dr[d],c2+dc[d],d);
    }
    if (d==1) {
        return can_move(r+dr[d],c2+dc[d],d);
    }
    if (d==3) {
        return can_move(r+dr[d],c1+dc[d],d);
    }
    cout << "INVALID" << endl;
    return false;
}

void move(int r,int c,int d) {
    if (grid[r][c]=='@') {
        move(r+dr[d],c+dc[d],d);
        grid[r+dr[d]][c+dc[d]] = '@';
        grid[r][c]='.';
        return;
    }
    if (grid[r][c]=='.') return;
    int c1,c2;
    if (grid[r][c]=='[') {
        c1 = c; c2 = c+1;
    } else {
        c1 = c-1; c2 = c;
    }
    if (d==0 || d==2) {
        move(r+dr[d],c1+dc[d],d);
        move(r+dr[d],c2+dc[d],d);
    }
    if (d==1) {
        move(r+dr[d],c2+dc[d],d);
    }
    if (d==3) {
        move(r+dr[d],c1+dc[d],d);
    }
    grid[r][c1] = '.';
    grid[r][c2] = '.';
    grid[r+dr[d]][c1+dc[d]] = '[';
    grid[r+dr[d]][c2+dc[d]] = ']';
}

int main() {
    while(!cin.eof()) {
        string s;
        getline(cin,s);
        string s2;
        for(int i=0;i<s.size();i++) {
            if (s[i]=='#') s2+="##";
            if (s[i]=='O') s2+="[]";
            if (s[i]=='.') s2+="..";
            if (s[i]=='@') s2+="@.";
        }
        grid.push_back(s2);

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
                break;
            }
        }
    }
    
    map<char,int> dpos;
    dpos['^'] = 0;
    dpos['>'] = 1;
    dpos['v'] = 2;
    dpos['<'] = 3;

    for(int i=0;i<operations.size();i++) {
        int r = roboR;
        int c = roboC;
        int d = dpos[operations[i]];
        if (can_move(roboR + dr[d],roboC + dc[d],d)) {
            move(roboR,roboC,d);
            roboR += dr[d];
            roboC += dc[d];
        }

    }

    int ans = 0;
    for(int i=0;i<grid.size();i++) {
        for(int k=0;k<grid[0].size();k++) {
            if (grid[i][k]=='[') {
                ans += i*100 + k;
            }
            cout << grid[i][k];
        }
        cout << endl;
    }

    cout << ans << endl;

    return 0;
}
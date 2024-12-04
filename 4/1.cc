#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> grid;

bool check(int R, int C, int rc, int cc) {
    string xmas = "XMAS";
    for(int i=0;i<4;i++) {
        int r = R + (rc * i);
        int c = C + (cc * i);
        if (r < 0 || r >= grid.size()) return false;
        if (c < 0 || c >= grid[0].size()) return false;
        if (grid[r][c]!=xmas[i]) return false;
    }
    return true;
}

int main() {
    while(!cin.eof()) {
        string s;
        cin >> s;
        grid.push_back(s);
    }

    int ans = 0;
    for(int i=0;i<grid.size();i++) {
        for(int k=0;k<grid[i].size();k++) {
            ans += check(i,k,0,1);
            ans += check(i,k,1,1);
            ans += check(i,k,1,0);
            ans += check(i,k,1,-1);
            ans += check(i,k,0,-1);
            ans += check(i,k,-1,-1);
            ans += check(i,k,-1,0);
            ans += check(i,k,-1,1);
        }
    }

    cout << ans << endl;

    return 0;
}
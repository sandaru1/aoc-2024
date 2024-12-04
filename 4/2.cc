#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> grid;

bool check_chars(char a,char b) {
    if (a=='M' && b=='S') return true;
    if (a=='S' && b=='M') return true;
    return false;
}

bool check(int r, int c) {
    if (grid[r+1][c+1]!='A') return false;
    if (
        check_chars(grid[r][c],grid[r+2][c+2]) &&
        check_chars(grid[r+2][c],grid[r][c+2])
    ) return true;
    return false;
}

int main() {
    while(!cin.eof()) {
        string s;
        cin >> s;
        grid.push_back(s);
    }

    int ans = 0;
    for(int i=0;i<grid.size()-2;i++) {
        for(int k=0;k<grid[i].size()-2;k++) {
            ans += check(i,k);
        }
    }

    cout << ans << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

vector<string> grid;
bool visited[100][100];

int visit(int r,int c, int d) {
    if (r<0 || r>=grid.size() || c < 0 || c >= grid[0].size()) return 0;
    if (visited[r][c]) return 0;
    if ((grid[r][c]-'0') != d) return 0;
    visited[r][c] = true;
    if (grid[r][c]=='9') return 1;
    int total = 0;
    total += visit(r+1,c,d+1);
    total += visit(r-1,c,d+1);
    total += visit(r,c+1,d+1);
    total += visit(r,c-1,d+1);
    return total;
}

int main() {
    while(!cin.eof()) {
        string s;
        cin >> s;
        grid.push_back(s);
    }

    int ans = 0;

    for(int i=0;i<grid.size();i++) {
        for(int k=0;k<grid.size();k++) {
            if (grid[i][k]=='0') {
                memset(visited,0,sizeof(visited));
                ans += visit(i,k,0);
            }
        }
    }

    cout << ans << endl;

    return 0;
}
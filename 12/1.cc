#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

vector<string> grid;
bool visited[200][200];

int check(int r,int c,int r2, int c2) {
    if (r2<0 || c2<0 || r2>=grid.size() || c2>=grid[0].size()) {
        return 0;
    }
    if (grid[r2][c2]==grid[r][c]) {
        if (visited[r2][c2]) return -1;
        return 1;
    }
    return 0;
}

int main() {
    while(!cin.eof()) {
        string s;
        cin >> s;
        grid.push_back(s);
    }

    long ans = 0;

    for(int i=0;i<grid.size();i++) {
        for(int k=0;k<grid.size();k++) {
            if (visited[i][k]) continue;
            int area = 0;
            int peri = 0;
            queue<pair<int,int> > q;
            q.push(pair<int,int>(i,k));
            while(!q.empty()) {
                pair<int,int> cur = q.front();
                q.pop();
                int r = cur.first;
                int c = cur.second;
                if (visited[r][c]) continue;
                visited[r][c] = true;
                area++;
                int a[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
                for(int x=0;x<4;x++) {
                    int ret = check(r,c,r+a[x][0],c+a[x][1]);
                    if (ret == 0) {
                        peri++;
                    } else if (ret == 1) {
                        q.push(pair<int,int>(r+a[x][0],c+a[x][1]));
                    }
                }
            }

            cout << grid[i][k] << " " << area << " " << peri << endl;

            ans += peri * area;
        }
    }


    cout << ans << endl;

    return 0;
}
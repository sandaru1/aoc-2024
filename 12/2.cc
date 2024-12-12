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
            queue<pair<int,int> > q;
            vector<pair<int,int> > edges[4];
            q.push(pair<int,int>(i,k));
            while(!q.empty()) {
                pair<int,int> cur = q.front();
                q.pop();
                int r = cur.first;
                int c = cur.second;
                if (visited[r][c]) continue;
                visited[r][c] = true;
                area++;
                int a[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
                for(int x=0;x<4;x++) {
                    int ret = check(r,c,r+a[x][0],c+a[x][1]);
                    if (ret == 0) {
                        edges[x].push_back(pair<int,int>(r,c));
                    } else if (ret == 1) {
                        q.push(pair<int,int>(r+a[x][0],c+a[x][1]));
                    }
                }
            }

            int sides = 0;

            for(int x=0;x<4;x++) {
                int groups[200];
                memset(groups,0,sizeof(groups));
                int n = 0;
                //cout << "x = " << x << endl;
                for(int a=0;a<edges[x].size();a++) {
                    //cout << edges[x][a].first << " " << edges[x][a].second << endl;
                    if (groups[a]==0) {
                        n++;
                        groups[a] = n;
                    }
                    for(int b=a+1;b<edges[x].size();b++) {
                        if (
                           ( (x==1 || x==3) && abs(edges[x][a].first-edges[x][b].first)==1 && edges[x][a].second==edges[x][b].second )
                            || ((x==0|| x==2) && abs(edges[x][a].second-edges[x][b].second)==1 && edges[x][a].first==edges[x][b].first)
                        ) {
                            if (groups[b]==0) {
                                groups[b] = groups[a];
                            } else {
                                int oldgroup = groups[b];
                                for(int c=0;c<edges[x].size();c++) {
                                    if (groups[c]==oldgroup) {
                                        groups[c] = groups[a];
                                    }
                                }
                            }
                        }
                    }
                }

                map<int,bool> used;
                for(int c=0;c<edges[x].size();c++) {
                    if (used.find(groups[c])==used.end()) {
                        sides++;
                        used[groups[c]] = true;
                    }
                }

            }

            cout << grid[i][k] << " " << area << " " << sides << endl;

            ans += sides * area;
        }
    }


    cout << ans << endl;

    return 0;
}
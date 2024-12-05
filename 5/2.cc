#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<int> before[100];
vector< vector<int> > upgrades;

bool is_valid(vector<int> u) {
    bool passed[100];
    memset(passed,0,sizeof(passed));
    for(int i=0;i<u.size();i++) {
        for(int k=0;k<before[u[i]].size();k++) {
            if (passed[before[u[i]][k]]) return false;
        }
        passed[u[i]] = true;
    }
    return true;
}

bool check_before(int a,int b) {
    for(int i=0;i<before[a].size();i++) {
        if (before[a][i]==b) return true;
    }
    return false;
}

int main() {
    while(!cin.eof()) {
        string s;
        getline(cin,s);
        if (s.empty()) break;
        stringstream ss(s);
        int x,y;
        ss >> x;
        ss.ignore();
        ss >> y;
        before[x].push_back(y);
    }

    while(!cin.eof()) {
        string s;
        cin >> s;
        stringstream ss(s);
        int x;
        vector<int> upgrade;
        while(ss >> x) {
            upgrade.push_back(x);
            if (ss.peek()==',') ss.ignore();
        }
        upgrades.push_back(upgrade);
    }

    int ans = 0;

    for(int i=0;i<upgrades.size();i++) {
        if (!is_valid(upgrades[i])) {
            
            for(int x=0;x<upgrades[i].size();x++) {
                for(int y=x+1;y<upgrades[i].size();y++) {
                    if (check_before(upgrades[i][y],upgrades[i][x])) {
                        int tmp = upgrades[i][x];
                        upgrades[i][x] = upgrades[i][y];
                        upgrades[i][y] = tmp;
                    }
                }
            }

            ans += upgrades[i][upgrades[i].size()/2];
        }
    }

    cout << ans << endl;

    return 0;
}
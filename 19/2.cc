#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <regex>
#include <limits>

using namespace std;

vector<string> patterns;
string design;

long dp[100];

long check(int pos) {
    if (pos==design.size()) {
        return 1;
    }
    if (dp[pos]==-1) {
        long cnt = 0;
        for(int i=0;i<patterns.size();i++) {
            if (design.substr(pos,patterns[i].size())==patterns[i]) {
                cnt += check(pos+patterns[i].size());
            }
        }
        dp[pos] = cnt;
    }
    return dp[pos];
}

int main() {
    string s;
    getline(cin,s);
    stringstream ss(s);
    while(ss >> s) {
        if (s[s.size()-1]==',') {
            s.erase(s.end()-1);
        }
        patterns.push_back(s);
    }

    long ans = 0;
    while(cin >> design) {
        memset(dp,-1,sizeof(dp));
        ans += check(0);
    }

    cout << ans << endl;

    return 0;
}
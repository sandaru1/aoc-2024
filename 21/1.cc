#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <regex>
#include <limits>

using namespace std;

#define pi pair<int,int>

//vector<string> keypad[11][11];
pi keypad_pos[2][11];
int keypad[2][4][3] = {
    {
        {7,8,9},
        {4,5,6},
        {1,2,3},
        {-1,0,10}
    },
    {
        {-1,0,10},
        {1,2,3},
        {-1,-1,-1},
        {-1,-1,-1}
    }
};
vector<string> dp[2][11][11];

vector<string> find_best(int keyboard,int s,int t) {
    vector<string> all;
    if (s==-1) return all;
    if (s==t) {
        all.push_back("");
        return all;
    } else {
        if (dp[keyboard][s][t].size()==0) {
            pi spos = keypad_pos[keyboard][s];
            pi tpos = keypad_pos[keyboard][t];
            vector<string> x;
            if (spos.first<tpos.first) {
                x = find_best(keyboard,keypad[keyboard][spos.first+1][spos.second],t);
                for(int i=0;i<x.size();i++) {
                    dp[keyboard][s][t].push_back("v"+ x[i]);
                }
            } else if (spos.first>tpos.first) {
                x = find_best(keyboard,keypad[keyboard][spos.first-1][spos.second],t);
                for(int i=0;i<x.size();i++) {
                    dp[keyboard][s][t].push_back("^"+ x[i]);
                }
            }
            if (spos.second<tpos.second) {
                x = find_best(keyboard,keypad[keyboard][spos.first][spos.second+1],t);
                for(int i=0;i<x.size();i++) {
                    dp[keyboard][s][t].push_back(">"+ x[i]);
                }
            } else if (spos.second>tpos.second) {
                x = find_best(keyboard,keypad[keyboard][spos.first][spos.second-1],t);
                for(int i=0;i<x.size();i++) {
                    dp[keyboard][s][t].push_back("<"+ x[i]);
                }
            }
        }
        return dp[keyboard][s][t];
    }
}

vector<string> find_all(string s,int keyboard) {
    int cur = 10;
    vector<string> ans;
    ans.push_back("");
    for(int i=0;i<s.size();i++) {
        int next = s[i]-'0';
        if (s[i]=='A') next = 10;
        if (s[i]=='^') next = 0;
        if (s[i]=='<') next = 1;
        if (s[i]=='v') next = 2;
        if (s[i]=='>') next = 3;
        vector<string> x = find_best(keyboard,cur,next);
        vector<string> y;
        for(int a=0;a<x.size();a++) {
            for(int b=0;b<ans.size();b++) {
                y.push_back(ans[b]+x[a]+"A");
            }
        }
        cur = next;
        ans = y;
    }
    return ans;
}

long find_best_2(vector<string> ans,int d) {
    vector<string> ans_best;
    for(int i=0;i<ans.size();i++) {
        //cout << ans[i] << endl;
        vector<string> ans2 = find_all(ans[i],1);
        if (ans_best.empty() || ans2[0].size()<ans_best[0].size()) {
            ans_best = ans2;
        } else if (ans2[0].size()==ans_best[0].size()) {
            ans_best.insert(ans_best.end(),ans2.begin(),ans2.end());
        }
    }

    if (d==0) {
        return ans_best[0].size();
    } else {
        return find_best_2(ans_best,d-1);
    }
}

int main() {
    for(int keyboard=0;keyboard<2;keyboard++){
        for(int i=0;i<4;i++) {
            for(int k=0;k<3;k++) {
                if (keypad[keyboard][i][k]==-1) continue;
                keypad_pos[keyboard][keypad[keyboard][i][k]] = pi(i,k);
            }
        }
    }

    string s;
    long total = 0;
    while(cin >> s) {
        cout << s << endl;
        vector<string> ans = find_all(s,0);
        long len = find_best_2(ans,1);
        long numeric = stol(s.substr(0,s.size()-1));
        total += len * numeric;
    }

    cout << total << endl;

    return 0;
}
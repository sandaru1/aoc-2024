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

map<string,long> dp2[2][11][30];

long find_all(string s,int last,int keyboard, int d) {
    if (dp2[keyboard][last][d].find(s)!=dp2[keyboard][last][d].end()) return dp2[keyboard][last][d][s];
    vector<string> ans;
    int i = 0;
    int next = s[i] - '0';
    if (s[i]=='A') next = 10;
    if (s[i]=='^') next = 0;
    if (s[i]=='<') next = 1;
    if (s[i]=='v') next = 2;
    if (s[i]=='>') next = 3;
    vector<string> x = find_best(keyboard,last,next);
    for(int i=0;i<x.size();i++) {
        x[i] = x[i] + "A";
    }

    long best = 100000000000000;
    if (d==0) {
        best = x[0].size();
    } else {
        for(int i=0;i<x.size();i++) {
            best = min(best,find_all(x[i],10,1,d-1));
        }
    }
    if (s.size()==1) return best;

    best += find_all(s.substr(1),next,keyboard,d);

    dp2[keyboard][last][d][s] = best;
    return best;
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
        long len = find_all(s,10,0,25);
        //cout << len << endl;
        long numeric = stol(s.substr(0,s.size()-1));
        total += len * numeric;
    }

    cout << total << endl;

    return 0;
}
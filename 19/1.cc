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

bool check(int pos) {
    if (pos==design.size()) {
        return true;
    }
    for(int i=0;i<patterns.size();i++) {
        if (design.substr(pos,patterns[i].size())==patterns[i]) {
            //cout << design.substr(pos,patterns[i].size()) << " " << patterns[i] << endl;
            if (check(pos+patterns[i].size())) {
                return true;
            }
        }
    }
    return false;
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

    int ans = 0;
    while(cin >> design) {
        if (check(0)) ans++;
    }

    cout << ans << endl;

    return 0;
}
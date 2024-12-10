#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

string s;

int main() {
    cin >> s;

    int id = 0;
    vector< pair<int,int> > x;
    bool free = false;
    for(int i=0;i<s.size();i++) {
        int cnt = s[i]-'0';
        if (free) {
            x.push_back(pair<int,int>(-1,cnt));
            free = false;
            id++;
        } else {
            x.push_back(pair<int,int>(id,cnt));
            free = true;
        }
    }

    for(int r=x.size()-1;r>0;r--) {
        if (x[r].first==-1) continue;
        for(int l=0;l<r;l++) {
            if (x[l].first==-1 && x[l].second>=x[r].second) {
                if (x[l].second==x[r].second) {
                    x[l].first = x[r].first;
                    x[r].first = -1;
                } else {
                    x[l].first = x[r].first;
                    int diff = x[l].second - x[r].second;
                    x[l].second = x[r].second;
                    x[r].first = -1;
                    x.insert(x.begin()+l+1,pair<int,int>(-1,diff));
                }
                break;
            }
        }
    }

    long ans = 0;
    int pos = 0;
    for(int i=0;i<x.size();i++) {
        if (x[i].first==-1) {
            pos += x[i].second;
        } else {
            for(int k=0;k<x[i].second;k++) {
                ans += (x[i].first*pos);
                pos++;
            }
        }
    }

    cout << ans << endl;
    return 0;
}
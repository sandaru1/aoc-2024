#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

string s;

int main() {
    cin >> s;

    int id = 0;
    vector<int> x;
    bool free = false;
    for(int i=0;i<s.size();i++) {
        int cnt = s[i]-'0';
        for(int k=0;k<cnt;k++) {
            if (free) {
                x.push_back(-1);
            } else {
                x.push_back(id);
            }
        }
        if (free) {
            free = false;
            id++;
        } else {
            free = true;
        }
    }

    int l = 0;
    int r = x.size()-1;
    while(l<=r) {
        while(x[l]!=-1) l++;
        while(x[r]==-1) r--;
        if (l<r) {
            x[l]=x[r];
            x[r]=-1;
        }
    }

    long ans = 0;
    for(int i=0;i<x.size();i++) {
        if (x[i]==-1) break;
        ans += i * x[i];
    }
    cout << ans << endl;
    return 0;
}
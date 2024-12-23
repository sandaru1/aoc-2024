#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <regex>
#include <limits>

using namespace std;

map<string,int> ids;
vector<string> names;
int id = 0;

int getID(string s) {
    if (ids.find(s)==ids.end()) {
        names.push_back(s);
        ids[s] = id++;
    }
    return ids[s];
}

bool connections[1000][1000];
int cnts[2000];

bool find_cluster(vector<int> ids,int size,int start) {
    if (ids.size()==size) {
        vector<string> ans;
        for(int i=0;i<ids.size();i++) {
            ans.push_back(names[ids[i]]);
        }
        sort(ans.begin(),ans.end());
        for(int i=0;i<ans.size();i++) {
            cout << ans[i];
            if (i!=ans.size()-1) cout << ",";
        }
        cout << endl;
        return true;
    }
    for(int i=start;i<id;i++) {
        if (cnts[i]<(size-1)) continue;
        bool ok = true;
        for (int k=0;k<ids.size();k++) {
            if (connections[i][ids[k]]==false) {
                ok = false;
                break;
            }
        }
        //cout << names[i] << ": " << ok << endl;
        if (ok) {
            vector<int> next = vector<int>(ids);
            next.push_back(i);
            if (find_cluster(next,size,i+1)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    string s;
    while(cin >> s) {
        string s1 = s.substr(0,2);
        string s2= s.substr(3);
        connections[getID(s1)][getID(s2)] = true;
        connections[getID(s2)][getID(s1)] = true;
    }

    int largest = 0;
    for(int i=0;i<id;i++) {
        for(int k=0;k<id;k++) {
            if (connections[i][k]) cnts[i]++;
            largest = max(largest,cnts[i]);
        }
    }

    for(int i=largest;i>0;i--) {
        cout << i << endl;
        if (find_cluster(vector<int>(),i,0)) {
            break;
        }
    }

    return 0;
}
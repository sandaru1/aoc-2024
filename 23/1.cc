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

int main() {
    string s;
    while(cin >> s) {
        string s1 = s.substr(0,2);
        string s2= s.substr(3);
        connections[getID(s1)][getID(s2)] = true;
        connections[getID(s2)][getID(s1)] = true;
    }

    for(int i=0;i<=id;i++) {
        for(int k=i+1;k<=id;k++) {
            for(int j=k+1;j<=id;j++) {
                if (connections[i][k] && connections[i][j] && connections[k][j]) {
                    if (names[i][0]=='t' || names[k][0]=='t' || names[j][0]=='t') {
                        cout << names[i] << " " << names[k] << " " << names[j] << endl;
                    }
                }
            }
        }
    }

    return 0;
}
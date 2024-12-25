#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <regex>
#include <limits>

using namespace std;

#define W 5

int locks[1000][5];
int keys[1000][5];
int ln, kn;

int main() {
    while(!cin.eof()) {
        string s;
        cin >> s;
        bool lock = false;
        if (s=="#####") {
            lock = true;
        }
        for(int i=0;i<6;i++) {
            cin >> s;
            for(int k=0;k<W;k++) {
                if (s[k]=='#') {
                    if (lock) locks[ln][k]++; else keys[kn][k]++;
                }
            }
        }
        if (!lock) {
            for(int k=0;k<W;k++) keys[kn][k]--;
        }
        if (lock) ln++; else kn++;
        cin.ignore();
    }

    int ans = 0;
    for(int i=0;i<ln;i++) {
        for(int k=0;k<kn;k++) {
            bool ok = true;
            for(int x=0;x<W;x++) {
                if (locks[i][x]+keys[k][x]>=6) {
                    ok = false;
                    break;
                }
            }
            if (ok) ans++;
        }
    }

    cout << ans << endl;
    return 0;
}
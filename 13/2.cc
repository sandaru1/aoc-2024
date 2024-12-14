#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <regex>
#include <limits>

using namespace std;

#define pl pair<long long,long long>
#define INF numeric_limits<long>::max()

pl extract(string s) {
    regex rgx(".*: X[\\+=]([0-9]*), Y[\\+=]([0-9]*)");
    smatch match;

    if (regex_search(s, match, rgx)) {
        return pl(stol(match[1]),stol(match[2]));
    }

    return pl(-1,-1);
}

int main() {
    long long ans = 0;
    while(!cin.eof()) {
        string s;
        pl data[3];
        for(int i=0;i<3;i++) {
            getline(cin,s);
            data[i] = extract(s);
        }

        data[2].first += 10000000000000;
        data[2].second += 10000000000000;

        long long b1 = data[1].first * data[0].second; // BX * AY
        long long b2 = data[1].second * data[0].first; // BY * AX
        long long c1 = data[2].first * data[0].second; // CX * AY
        long long c2 = data[2].second * data[0].first; // CY * AX

        long long b,c;
        if (c1>c2) {
            c = c1 - c2;
            b = b1 - b2;
        } else {
            c = c2 - c1;
            b = b2 - b1;
        }

        if (c%b==0) {
            b = c/b;
            if ((data[2].first - data[1].first * b)%data[0].first==0) {
                long long a = (data[2].first - data[1].first * b)/data[0].first;
                if (a>=0 && b>=0) {
                    ans += a * 3 + b;
                }
            }
        }        

        getline(cin,s);
    }

    cout << ans << endl;

    return 0;
}
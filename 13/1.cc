#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <regex>
#include <limits>

using namespace std;

#define pl pair<long,long>
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
    long ans = 0;
    while(!cin.eof()) {
        string s;
        pl data[3];
        for(int i=0;i<3;i++) {
            getline(cin,s);
            data[i] = extract(s);
        }

        long best = INF;
        
        for(int a=0;a<=100;a++) {
            for(int b=0;b<=100;b++) {
                long X = data[0].first*a + data[1].first*b;
                long Y = data[0].second*a + data[1].second*b;
                if (X==data[2].first && Y==data[2].second) {
                    best = min(best,long(a*3+b));
                }
            }
        }
        if (best != INF) {
            ans += best;
        }
        getline(cin,s);
    }

    cout << ans << endl;

    return 0;
}
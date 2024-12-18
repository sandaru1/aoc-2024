#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <regex>
#include <limits>

using namespace std;

#define pi pair<int,int>

long a,b,c;
vector<pi> program;
vector<int> p;
long ans = 10000000000000000;

long combo(long x) {
    if (x<=3) return x;
    if (x==4) return a;
    if (x==5) return b;
    if (x==6) return c;
    return -1;
}

bool check(long A,int pos) {
    a = A; b = 0; c = 0;
    vector<long> outputs;

    int i = 0;
    while(i<program.size()) {
        switch(program[i].first) {
            case 0:
                a = a/pow(2,combo(program[i].second));
                i++;
                break;
            case 1:
                b = b ^ program[i].second;
                i++;
                break;
            case 2:
                b = combo(program[i].second) % 8;
                i++;
                break;
            case 3:
                if (a==0) {
                    i++;
                } else {
                    i = program[i].second/2;
                }
                break;
            case 4:
                b = b ^ c;
                i++;
                break;
            case 5:
                outputs.push_back(combo(program[i].second)%8);
                i++;
                break;
            case 6:
                b = a/pow(2,combo(program[i].second));
                i++;
                break;
            case 7:
                c = a/pow(2,combo(program[i].second));
                i++;
                break;
        }
    }

    if (outputs[pos]==p[pos] && outputs.size() == p.size()) return true;
    return false;
}

void dfs(long A, long pos) {
    //cout << pos << " " << A << endl;
    if (pos==-1) {
        //cout << A << endl;
        ans = min(ans,A);
        return;
    }
    for(long i=0;i<8;i++) {
        long newA = A | (i << ((pos) * 3 ));
        if (check(newA,pos)) {
            dfs(newA,pos-1);
        }
    }
}

int main() {
    string s;
    cin >> s >> s >> a;
    cin >> s >> s >> b;
    cin >> s >> s >> c;
    cin >> s;

    while(!cin.eof()) {
        int op,val;
        cin >> op;
        cin.ignore();
        cin >> val;
        cin.ignore();
        p.push_back(op);
        p.push_back(val);
        program.push_back(pi(op,val));
    }

    dfs(0,15);

    cout << ans << endl;

    return 0;
}
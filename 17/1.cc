#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <regex>
#include <limits>

using namespace std;

#define pi pair<int,int>

long a,b,c;

long combo(int x) {
    if (x<=3) return x;
    if (x==4) return a;
    if (x==5) return b;
    if (x==6) return c;
    return -1;
}

int main() {
    string s;
    cin >> s >> s >> a;
    cin >> s >> s >> b;
    cin >> s >> s >> c;
    cin >> s;

    vector<pi> program;
    while(!cin.eof()) {
        int op,val;
        cin >> op;
        cin.ignore();
        cin >> val;
        cin.ignore();
        program.push_back(pi(op,val));
    }

    vector<int> outputs;

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

    //cout << a << " " << b << " " << c << endl;
    for(int k=0;k<outputs.size();k++) {
        cout << outputs[k];
        if (k==outputs.size()-1) cout << endl; else cout << ",";
    }
    return 0;
}
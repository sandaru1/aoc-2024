#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <regex>
#include <limits>

using namespace std;

struct Gate {
    string i1,i2,out,op;
};

map<string,int> wires;
vector<Gate> gates;
string max_wire;

void add_wire(string wire) {
    if (wires.find(wire)==wires.end()) {
        max_wire = max(max_wire,wire);
        wires[wire] = -1;
    }
}

int ans[2][2][2];

void calc_all() {
    while(true) {
        bool changed = false;
        for(int i=0;i<gates.size();i++) {
            Gate gate = gates[i];
            if (wires[gate.out] == -1 && wires[gate.i1] != -1 && wires[gate.i2] != -1) {
                //cout << i << " " << wires[gate.out];
                changed = true;
                if (gate.op=="AND") {
                    wires[gate.out] = wires[gate.i1] & wires[gate.i2];
                } else if (gate.op == "XOR") {
                    wires[gate.out] = wires[gate.i1] ^ wires[gate.i2];
                } else if (gate.op == "OR") {
                    wires[gate.out] = wires[gate.i1] | wires[gate.i2];
                }
                //cout << " = " << wires[gate.out] << endl;
            }
        }
        if (!changed) break;
    }
}

bool is_valid(int n) {
    for (map<string,int>::iterator it = wires.begin(); it != wires.end(); it++) {
        if (it->first[0]!='x' && it->first[0]!='y') {
            wires[it->first] = -1;
        }
    }

    calc_all();

    string xwire = string("x")+string(n<10?"0":"")+to_string(n);
    string ywire = string("y")+string(n<10?"0":"")+to_string(n);

    int xval = wires[xwire];
    int yval = wires[ywire];
    int xprev = 0;
    if (n>0) {
        xwire = string("x")+string((n-1)<10?"0":"")+to_string(n-1);
        ywire = string("y")+string((n-1)<10?"0":"")+to_string(n-1);
        if (wires[xwire] && wires[ywire]) {
            xprev = 1;
        }
    }
    
    string end_wire = string("z")+string(n<10?"0":"")+to_string(n);

    return ans[xprev][xval][yval] == wires[end_wire];
}

int main() {
    string s;
    while(true) {
        getline(cin,s);
        if (s=="") break;
        stringstream ss(s);
        string w;
        int val;
        ss >> w >> val;
        wires[w.substr(0,3)] = val;
    }

    while(!cin.eof()) {
        string i1,i2,out,op;
        cin >> i1 >> op >> i2 >> s >> out;
        Gate g;
        g.i1 = i1;
        g.i2 = i2;
        g.op = op;
        g.out = out;
        gates.push_back(g);

        add_wire(i1);
        add_wire(i2);
        add_wire(out);
    }

    ans[0][0][0] = 0;
    ans[0][0][1] = 1;
    ans[0][1][0] = 1;
    ans[0][1][1] = 0;
    ans[1][0][0] = 1;
    ans[1][0][1] = 0;
    ans[1][1][0] = 0;
    ans[1][1][1] = 1;

    for(int n=0;n<50;n++) {
        cout << n;
        if (is_valid(n)) {
            cout << " valid" << endl;
        } else {
            cout << " INVALID" << endl;
            bool changed = false;
            for(int i=0;i<gates.size();i++) {
                for(int k=i+1;k<gates.size();k++) {
                    //cout << i << " " << k << endl;
                    string out1 = gates[i].out;
                    string out2 = gates[k].out;
                    gates[i].out = out2;
                    gates[k].out = out1;
                    if (is_valid(n)) {
                        changed = true;
                        break;
                    }
                    gates[i].out = out1;
                    gates[k].out = out2;
                }
                if (changed) break;
            }
        }
    }


    return 0;
}
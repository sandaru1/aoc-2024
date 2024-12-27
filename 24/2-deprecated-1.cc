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
map<string,int> wires_original;
vector<Gate> gates;
string max_wire;
map<string,int> wire_gate;
vector<string> used_wires[100];
map<string,bool> swapped;
bool valid[100];

int ans[2][2][2];
map<string,bool> visited;

int next_invalid(int start) {
    for(int i=start;i<50;i++)
        if (valid[i]==false) return i;
    return -1;
}

int get_wire(string wire) {
    if (wires[wire]!=-1) return wires[wire];
    if (visited[wire]) return -1;
    visited[wire] = true;
    for(int i=0;i<gates.size();i++) {
        if (gates[i].out==wire) {
            int i1 = get_wire(gates[i].i1);
            int i2 = get_wire(gates[i].i2);
            if (i1 != -1 && i2 != -1) {
                if (gates[i].op=="AND") {
                    wires[gates[i].out] =i1 & i2;
                } else if (gates[i].op == "XOR") {
                    wires[gates[i].out] = i1 ^ i2;
                } else if (gates[i].op == "OR") {
                    wires[gates[i].out] = i1 | i2;
                }
            }
            break;
        }
    }
    visited[wire] = false;
    return wires[wire];
}

bool is_valid(int n) {
    string xwire = string("x")+string(n<10?"0":"")+to_string(n);
    string ywire = string("y")+string(n<10?"0":"")+to_string(n);
    string xprev_wire = string("x")+string((n-1)<10?"0":"")+to_string(n-1);
    string yprev_wire = string("y")+string((n-1)<10?"0":"")+to_string(n-1);

    wires = wires_original;
    for (map<string,int>::iterator it = wires.begin(); it != wires.end(); it++) {
        if (it->first[0]!='x' && it->first[0]!='y') {
            wires[it->first] = -1;
        }
    }

    int xval = wires[xwire];
    int yval = wires[ywire];
    int xprev = 0;
    if (n>0) {
        if (wires[xprev_wire] && wires[yprev_wire]) {
            xprev = 1;
        }
    }
    
    string end_wire = string("z")+string(n<10?"0":"")+to_string(n);

    //cout << "\t" << get_wire(end_wire) << endl;
    return ans[xprev][xval][yval] == get_wire(end_wire);
}

void dfs(int bit,int d) {
    if (d==4) {
        for(int i=0;i<50;i++) {
            if (is_valid(i)==false) {
                return;
            }
        }
        for (map<string,bool>::iterator it = swapped.begin(); it != swapped.end(); it++) {
            if (swapped[it->first]) {
                cout << it->first << " ";
            }
        }
        cout << endl;
        exit(0);
        return;
    }
    if (bit>=50) return;
    if (is_valid(bit)) {
        dfs(next_invalid(bit+1),d);
        return;
    }
    if (d<3) cout << d << endl;
    for(int i=0;i<used_wires[bit].size();i++) {
        int gate1 = wire_gate[used_wires[bit][i]];
        for(int k=0;k<gates.size();k++) {
            string out1 = gates[gate1].out;
            string out2 = gates[k].out;
            if (swapped[out1] || swapped[out2]) continue;
            if (out1 != out2) {
                gates[gate1].out = out2;
                gates[k].out = out1;
                swapped[out1] = true;
                swapped[out2] = true;
                bool ok = true;
                for(int x=0;x<=bit;x++)
                 if (is_valid(x)==false) {
                    ok = false;
                    break;
                 }
                if (ok) {
                    dfs(next_invalid(bit+1),d+1);
                }
                swapped[out1] = false;
                swapped[out2] = false;
                gates[gate1].out = out1;
                gates[k].out = out2;
            }
        }
    }
}

void add_wire(string wire) {
    if (wires.find(wire)==wires.end()) {
        max_wire = max(max_wire,wire);
        wires[wire] = -1;
    }
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

        wire_gate[out] = gates.size()-1;
    }

    wires_original = wires;

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
            valid[n] = true;
            cout << " valid" << endl;
        } else {
            cout << " INVALID" << endl;
            for(int i=0;i<gates.size();i++) {
                if (wires[gates[i].out]!=-1) {
                    used_wires[n].push_back(gates[i].out);
                }
            }
        }
    }

    dfs(next_invalid(0),0);

    return 0;
}
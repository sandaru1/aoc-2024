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

    while(true) {
        bool all_done = true;

        for(int i=0;i<gates.size();i++) {
            Gate gate = gates[i];
            if (wires[gate.out] == -1 && wires[gate.i1] != -1 && wires[gate.i2] != -1) {
                all_done = false;
                if (gate.op=="AND") {
                    wires[gate.out] = wires[gate.i1] & wires[gate.i2];
                } else if (gate.op == "XOR") {
                    wires[gate.out] = wires[gate.i1] ^ wires[gate.i2];
                } else if (gate.op == "OR") {
                    wires[gate.out] = wires[gate.i1] | wires[gate.i2];
                }
            }
        }

        if (all_done) {
            break;
        }
    }

    long X = 0;
    long Y = 0;
    long ans = 0;

    for(int i=0;i<45;i++) { 
        string wire = string("x")+string(i<10?"0":"")+to_string(i);
        cout << wire << " " << wires[wire] << endl;
        if (wires[wire]==1) {
            long x = (1L << i);
            X = X | x;
        }
        wire = string("y")+string(i<10?"0":"")+to_string(i);
        cout << wire << " " << wires[wire] << endl;
        if (wires[wire]==1) {
            long x = (1L << i);
            Y = Y | x;
        }

    }

    for(int i=0;i<100;i++) {
        string wire = string("z")+string(i<10?"0":"")+to_string(i);
        cout << wire << " " << wires[wire] << endl;
        if (wires[wire]==1) {
            long x = (1L << i);
            ans = ans | x;
        }
        if (wire==max_wire) break;
    }

    cout << X << endl << Y << endl;
    cout << ans << endl;

//    cout << wires["z00"] << wires["z01"] << wires["z02"] << endl;

    return 0;
}
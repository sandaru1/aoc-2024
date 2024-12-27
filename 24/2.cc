#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <regex>
#include <limits>

using namespace std;

/*
The invalid bits are calculated and a dot file is generated.
The dotfile can be viewed from https://edotor.net/.
The invalid gates are obvious from the graph.
*/

struct Gate {
    string i1,i2,out,op;
};

map<string,int> wires;
map<string,int> wires_original;
vector<Gate> gates;
long X,Y,TOTAL;

map<string,bool> visited;

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

void add_wire(string wire) {
    if (wires.find(wire)==wires.end()) {
        wires[wire] = -1;
    }
}

void swap_outputs(int g1,int g2) {
    string tmp = gates[g1].out;
    gates[g1].out = gates[g2].out;
    gates[g2].out = tmp;
}

bool is_valid(int n) {
    long x;
    string end_wire = string("z")+string(n<10?"0":"")+to_string(n);
    if (get_wire(end_wire)) {
        if (TOTAL & (1L << n)) return true;
        return false;
    }

    if (TOTAL & (1L << n)) return false;
    return true;
}


map<string,int> wire_gates;

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

        wire_gates[out] = gates.size()-1;
    }

   for(int i=0;i<45;i++) {
        string wire = string("x")+string(i<10?"0":"")+to_string(i);
        wire_gates[wire] = gates.size()+i;
        wire = string("y")+string(i<10?"0":"")+to_string(i);
        wire_gates[wire] = gates.size()+i;
        cout << "G" << (gates.size()+i) << "[label=" << i << ", shape=Mdiamond]" << endl;
    }

    for(int i=0;i<gates.size();i++) {
        cout << "G" << i << "[label=" << gates[i].op << ",shape=" << (gates[i].op=="XOR"?"diamond":(gates[i].op=="AND"?"square":"oval")) << "]" << endl;
        cout << "G" << wire_gates[gates[i].i1] << " -> " << "G" << i << "[label=" << gates[i].i1 << "]" << endl;
        cout << "G" << wire_gates[gates[i].i2] << " -> " << "G" << i << "[label=" << gates[i].i2 << "]" << endl;
        if (gates[i].out[0]=='z') {
            cout << "G" << i << " -> " << gates[i].out << endl;
        }
    }

    //return 0;

    
    for(int i=0;i<45;i++) { 
        string wire = string("x")+string(i<10?"0":"")+to_string(i);
        if (wires[wire]==1) {
            long x = (1L << i);
            X = X | x;
        }
        wire = string("y")+string(i<10?"0":"")+to_string(i);
        if (wires[wire]==1) {
            long x = (1L << i);
            Y = Y | x;
        }
    }
    TOTAL = X + Y;

    wires_original = wires;

    for(int i=0;i<50;i++) {
        cout << i << ": ";
        wires_original = wires;
        if (is_valid(i)==false) {
            string end_wire = string("z")+string(i<10?"0":"")+to_string(i);
            cout << get_wire(end_wire) << " ";
            cout << "INVALID";
        }
        cout << endl;
    }

    return 0;

}
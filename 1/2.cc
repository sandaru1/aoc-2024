#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> l1;
    int counts[100000];
    memset(counts,0,sizeof(counts));

    while(!cin.eof()) {
        int a,b;
        cin >> a >> b;
        l1.push_back(a);
        counts[b]++;
    }


    long similar = 0;
    for(int i=0;i<l1.size();i++) {
        similar += l1[i] * counts[l1[i]];
    }
    cout << similar << endl;

    return 0;
}
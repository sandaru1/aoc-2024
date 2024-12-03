#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> l1,l2;
    while(!cin.eof()) {
        int a,b;
        cin >> a >> b;
        l1.push_back(a);
        l2.push_back(b);
    }

    sort(l1.begin(),l1.end());
    sort(l2.begin(),l2.end());

    int diff = 0;
    for(int i=0;i<l1.size();i++) {
        diff += max(l1[i],l2[i]) - min(l1[i],l2[i]);
    }
    cout << diff << endl;

    return 0;
}
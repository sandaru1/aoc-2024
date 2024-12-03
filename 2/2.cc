#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

bool is_safe(vector<int> level) {
    bool increase = (level[1] - level[0])>0;
    for(int i=1;i<level.size();i++) {
        int diff = level[i] - level[i-1];
        if (increase && (diff < 1 || diff > 3)) {
            return false;
        } else if (!increase && (diff > -1 || diff < -3)) {
            return false;
        }
    }
    return true;
}

int main() {
    string str;
    int ans = 0;
    while(getline(cin, str)) 
    {
        istringstream ss(str);
        int num;
        vector<int> level;
        while (ss >> num) level.push_back(num);
        if (is_safe(level)) {
            ans++;
        } else {
            for(int i=0;i<level.size();i++) {
                vector<int> new_level(level);
                new_level.erase(new_level.begin()+i);
                if (is_safe(new_level)) {
                    ans++;
                    break;
                }
            }
        }
    }

    cout << ans << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

bool can_make(vector<long> nums,long target) {
    if (nums.size()==0) return (target==0);
    if (nums.size()==1) return (target==nums[0]);
    vector<long> new_nums(nums.begin()+1,nums.end());
    if (can_make(new_nums,target - nums[0])) {
        return true;
    }
    if (target%nums[0]==0) {
        if (can_make(new_nums,target/nums[0])) {
            return true;
        }
    }
    return false;
}

int main() {
    long ans = 0;
    while(!cin.eof()) {
        long target;
        vector<long> nums;
        string s;
        getline(cin,s);
        stringstream ss(s);
        ss >> target;
        ss.ignore();
        while(!ss.eof()) {
            long x;
            ss >> x;
            nums.push_back(x);
        }
        reverse(nums.begin(),nums.end());
        if (can_make(nums,target)) {
            ans += target;
        }
    }

    cout << ans << endl;

    return 0;
}
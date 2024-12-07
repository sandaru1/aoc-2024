#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

long concat(long a,long b) {
    stringstream ss;
    ss << a;
    ss << b;
    long ans;
    ss >> ans;
    return ans;
}

bool can_make(vector<long> nums,long target) {
    if (nums.size()==0) return (target==0);
    if (nums.size()==1) return (target==nums[0]);
    vector<long> new_nums(nums.begin()+1,nums.end());
    new_nums[0] = nums[0]+nums[1];
    if (can_make(new_nums,target)) {
        return true;
    }
    new_nums[0] = nums[0] * nums[1];
    if (can_make(new_nums,target)) {
        return true;
    }
    new_nums[0] = concat(nums[0],nums[1]);
    if (can_make(new_nums,target)) {
        return true;
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
        
        if (can_make(nums,target)) {
            //cout << target << endl;
            ans += target;
        }
    }

    cout << ans << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

using namespace std;


int main(){
    vector<long long> nums;
    while(!cin.eof()) {
        long long x;
        cin >> x;
        //cout << x << endl;
        nums.push_back(x);
    }
    //cout << endl;

    for(int i=0;i<25;i++) {
        cout << i << " " << nums.size() << endl;
        vector<long long> new_nums;
        for(int k=0;k<nums.size();k++) {
            //cout << nums[k] << " ";
            if (nums[k]==0) {
                new_nums.push_back(1);
            } else {
                stringstream ss;
                string s;
                ss << nums[k];
                ss >> s;
                if (s.size()%2==0) {
                    string s1 = s.substr(0,s.size()/2);
                    string s2 = s.substr(s.size()/2,s.size()/2);
                    stringstream ss2;
                    ss2 << s1 << " " << s2;
                    long long a,b;
                    ss2 >> a >> b;
                    new_nums.push_back(a);
                    new_nums.push_back(b);
                } else {
                    new_nums.push_back(nums[k]*2024);
                }
            }
        }
        //cout << endl;
        nums = new_nums;
    }

    cout << nums.size() << endl;
    return 0;
}

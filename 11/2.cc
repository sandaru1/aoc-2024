#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

using namespace std;

map<long,long> dp[80];

long calc(long num,int rounds) {
    if (rounds == 0) return 1;
    if (dp[rounds].find(num)==dp[rounds].end()){
        if (num==0) {
            dp[rounds][num] = calc(1,rounds-1);
        } else {
            string s = to_string(num);
            if (s.size()%2==0) {
                int mid = s.size()/2;
                dp[rounds][num] = calc(stol(s.substr(0,mid)),rounds-1) + calc(stol(s.substr(mid,mid)),rounds-1);
            } else {
                dp[rounds][num] = calc(num*2024,rounds-1);
            }
        }
    }

    return dp[rounds][num];
}


int main(){
    long ans = 0;
    while(!cin.eof()) {
        long x;
        cin >> x;
        ans += calc(x,75);
    }

    cout << ans << endl;
    return 0;
}

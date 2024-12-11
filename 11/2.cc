#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

using namespace std;

map<long long,long long> dp[80];

long long calc(long long num,int rounds) {
    if (rounds == 0) return 1;
    if (dp[rounds].find(num)==dp[rounds].end()){
        if (num==0) {
            dp[rounds][num] = calc(1,rounds-1);
        } else {
            stringstream ss;
            string s;
            ss << num;
            ss >> s;
            if (s.size()%2==0) {
                string s1 = s.substr(0,s.size()/2);
                string s2 = s.substr(s.size()/2,s.size()/2);
                stringstream ss2;
                ss2 << s1 << " " << s2;
                long long a,b;
                ss2 >> a >> b;
                long long ans = calc(a,rounds-1);
                ans += calc(b,rounds-1);
                dp[rounds][num] = ans;
            } else {
                dp[rounds][num] = calc(num*2024,rounds-1);
            }
        }
    }

    return dp[rounds][num];
}


int main(){
    long long ans = 0;
    while(!cin.eof()) {
        long long x;
        cin >> x;
        ans += calc(x,75);
    }

    cout << ans << endl;
    return 0;
}

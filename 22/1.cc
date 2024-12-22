#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <regex>
#include <limits>

using namespace std;

int main() {
    long n;
    long total = 0;
    while(cin >> n) {
        for(int i=0;i<2000;i++) {
            long x = n * 64;
            n = n ^ x;
            n = n % 16777216;

            x = n / 32;
            n = n ^ x;
            n = n % 16777216;

            x = n * 2048;
            n = n ^ x;
            n = n % 16777216;
        }
        total += n;
    }

    cout << total << endl;

    return 0;
}
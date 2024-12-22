#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <regex>
#include <limits>

using namespace std;

bool ans[20][20][20][20];
int total[20][20][20][20];

int main() {
    long n;
    int best = 0;

    int x = 0;
    while(cin >> n) {
        memset(ans,false,sizeof(ans));
        int list[2001];
        list[0] = n%10;
        for(int i=1;i<=2000;i++) {
            long x = n * 64;
            n = n ^ x;
            n = n % 16777216;

            x = n / 32;
            n = n ^ x;
            n = n % 16777216;

            x = n * 2048;
            n = n ^ x;
            n = n % 16777216;

            list[i] = n%10;

            if (i>3) {
                int a = list[i-3] - list[i-4] + 10;
                int b = list[i-2] - list[i-3] + 10;
                int c = list[i-1] - list[i-2] + 10;
                int d = list[i] - list[i-1] + 10;

                if (ans[a][b][c][d]==false) {
                    ans[a][b][c][d] = true;
                    total[a][b][c][d] += list[i];
                    best = max(best,total[a][b][c][d]);
                    //cout << a << " " << b << " " << c << " " << d << " = " << total[a][b][c][d] << endl;

                }
            }
        }
        x++;

    }

    cout << best << endl;

    return 0;
}
#ifdef JUDGE
#   include <fstream>
    std::ifstream cin("input.txt");
    std::ofstream cout("output.txt");
#else
#   include <iostream>
    using std::cin;
    using std::cout;
#endif
#include <vector>
#include <limits>
#include <cmath>
#include <iomanip>

using namespace std;
 
const int n = 3;

int main() {
    vector<double> a, b, c;
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        a.push_back(tmp * tmp * 1.);
    }
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        b.push_back(tmp * tmp * 1.);
    }
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        c.push_back(tmp * tmp * 1.);
    }

    double perf = numeric_limits<double>::min();;

    perf = max(perf, sqrt(a[0] + b[1] + c[2]));
    perf = max(perf, sqrt(a[0] + b[2] + c[1]));
    perf = max(perf, sqrt(a[1] + b[0] + c[2]));
    perf = max(perf, sqrt(a[1] + b[2] + c[0]));
    perf = max(perf, sqrt(a[2] + b[0] + c[1]));
    perf = max(perf, sqrt(a[2] + b[1] + c[0]));

    // Please note that std::endl flushes output after writing and works slower
    // than just "\n", so it's reasonable to use "\n" unless you don't need to
    // flush output (usually you don't need).
    cout << setprecision(12) << perf << endl;
    return 0;
}

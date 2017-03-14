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
#include <algorithm>
#include <limits>

using namespace std;
  
int main() {
    int n;
    cin >> n;

    //
    //  Read input data
    //

    vector<int> t, p;
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        t.push_back(tmp);
    }
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        p.push_back(tmp);
    }

    //
    // Compute min of abs difference.
    //

    int abs_min = std::numeric_limits<int>::max();;
    for (int i = 0; i < n; i++) {
        int tmp = std::abs(t[i] - p[i]);
        if (tmp < abs_min) {
            abs_min = tmp;
        }
    }

    //
    //
    //

    int sum = 0;
    bool has_t = false;
    bool has_p = false;

    for (int i = 0; i < n; i++) {
        if (t[i] >= p[i]) {
            sum += t[i];
            has_t = true;
        } else {
            sum += p[i];
            has_p = true;
        }
    }

    if (not (has_t and has_p)) {
        sum -= abs_min;
    }

    // Please note that std::endl flushes output after writing and works slower
    // than just "\n", so it's reasonable to use "\n" unless you don't need to
    // flush output (usually you don't need).
    cout << sum << std::endl;
    return 0;
}

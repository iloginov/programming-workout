#ifdef JUDGE
#   include <fstream>
    std::ifstream cin("input.txt");
    std::ofstream cout("output.txt");
#else
#   include <iostream>
    using std::cin;
    using std::cout;
#endif
#include <map>
#include <utility>
#include <string>
#include <limits>

using namespace std;
 
int main() {
    int w, h;

	cin >> w >> h;

    map<char, pair<int, int>> keymap;

    // Read keymap

    for (int i = 0; i < h; i++) {
        string t;
        cin >> t;
        for (int j = 0; j < w; j++) {
            keymap[t[j]] = pair<int, int>(i, j);
        }
    }

    string answ_lang;
    int answ_time = numeric_limits<int>::max();

    string lang;
    getline(cin, lang); // Read EOL

    while (getline(cin, lang)) {
        int time = 0;
        char prev = 0;

        string t;
        getline(cin, t); // Skip %TEMPLATE-START%
        while (getline(cin, t) && t != "%TEMPLATE-END%") {
            for (int i = 0; i < t.length(); i++) {
                if (t[i] == ' ') {
                    continue;
                }

                char cur = t[i];

                if (prev) {
                    int x1 = keymap[prev].first;
                    int y1 = keymap[prev].second;
                    int x2 = keymap[cur].first;
                    int y2 = keymap[cur].second;
                    int val = max(abs(x1 - x2), abs(y1 - y2));
                    time += val;
                }
                prev = cur;
            }
        }

        if (time < answ_time) {
            answ_time = time;
            answ_lang = lang;
        }
    }

    // Please note that std::endl flushes output after writing and works slower
    // than just "\n", so it's reasonable to use "\n" unless you don't need to
    // flush output (usually you don't need).
    cout << answ_lang << endl;
    cout << answ_time << endl;
    return 0;
}

#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;

    while (N--) {
        int a, b;
        cin >> a >> b;

        if (a > b) {
            cout << '>' << endl;
        } else if (a < b) {
            cout << '<' << endl;
        } else {
            cout << '=' << endl;
        }
    }

    return 0;
}
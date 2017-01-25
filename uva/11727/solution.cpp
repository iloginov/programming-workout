#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;

    for (int i = 1; i <= N; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        cout << "Case " << i << ": ";
        if (a >= b && a >= c) {
            if (b >= c) {
                cout << b << endl;
            } else {
                cout << c << endl;
            }
        } else if (b >= a && b >= c) {
            if (a >= c) {
                cout << a << endl;
            } else {
                cout << c << endl;
            }
        } else {
            if (a >= b) {
                cout << a << endl;
            } else {
                cout << b << endl;
            }
        }
    }

    return 0;
}
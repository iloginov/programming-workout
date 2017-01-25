#include <iostream>

using namespace std;

int main() {
    int K;
    while (cin >> K, K) {
        int M, N;
        cin >> M >> N;
        while (K--) {
            int X, Y;
            cin >> X >> Y;

            if ((X-M) > 0 && (Y - N) > 0) {
                cout << "NE" << endl;
            } else if ((X - M) > 0 && (Y - N) < 0) {
                cout << "SE" << endl;
            } else if ((X - M) < 0 && (Y - N) < 0) {
                cout << "SO" << endl;
            } else if ((X - M) < 0 && (Y - N) > 0) {
                cout << "NO" << endl;
            } else {
                cout << "divisa" << endl;
            }
        }
    }

    return 0;
}
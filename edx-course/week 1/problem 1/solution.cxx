#ifdef JUDGE
#include <fstream>
std::ifstream cin("input.txt");
std::ofstream cout("output.txt");
#else
#include <iostream>
using std::cin;
using std::cout;
#endif
  
int main() {
    int a, b;
    cin >> a >> b;
    // Please note that std::endl flushes output after writing and works slower
    // than just "\n", so it's reasonable to use "\n" unless you don't need to
    // flush output (usually you don't need).
    cout << a + b << std::endl;
    return 0;
}

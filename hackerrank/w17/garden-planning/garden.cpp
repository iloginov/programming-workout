#include<set>
#include<cassert>
#include<unordered_map>
#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstring>
using namespace std;

typedef long long LL;
typedef vector<int> VI;

#define REP(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)
#define EACH(i,c) for(__typeof((c).begin()) i=(c).begin(),i##_end=(c).end();i!=i##_end;++i)
#define eprintf(s...) fprintf(stderr, s)

template<class T> inline void amin(T &a, const T &b) { if (b<a) a=b; }
template<class T> inline void amax(T &a, const T &b) { if (a<b) a=b; }
template<int MOD>
struct ModInt {
    unsigned x;
    void undef() { x = -1; }
    bool isnan() const { return x == -1; }
    inline int getInt() const { return (int)x; }
    template<class T> T get() const { return (T)x; }
    inline int mod() const { return MOD; }
    ModInt(int y=0) { if (y<0 || MOD<=y) y %= MOD; if (y<0) y += MOD; x=y; }
    ModInt(long long y) { if (y<0 || MOD<=y) y %= MOD; if (y<0) y += MOD; x=y; }
    ModInt(unsigned long long y) { if (MOD<=y) x = y % MOD; else x = y; }
    ModInt &operator+=(const ModInt &y) { if ((x += y.x) >= MOD) x -= MOD; return *this; }
    ModInt &operator-=(const ModInt &y) { if ((x += MOD - y.x) >= MOD) x -= MOD; return *this; }
    ModInt &operator*=(const ModInt &y) { x = (unsigned long long)x * y.x % MOD; return *this; }
    ModInt &operator/=(const ModInt &y) { x = (unsigned long long)x * y.inv().x % MOD; return *this; }
    ModInt operator-() const { return (x ? MOD-x: 0); }
    ModInt inv() const {
	int a = MOD, b = x, u = 0, v = 1;
	while (b) {
	    int t = a / b;
	    a -= t * b; swap(a, b);
	    u -= t * v; swap(u, v);
	}
	if (u < 0) u += MOD;
	return ModInt(u);
    }
    ModInt pow(long long y) const {
	ModInt b = *this, r = 1;
	if (y < 0) { b = b.inv(); y = -y; }
	for (; y; y>>=1) {
	    if (y&1) r *= b;
	    b *= b;
	}
	return r;
    }
};
const LL MOD = 1000000007;
typedef ModInt<MOD> Mint;
Mint operator+(Mint x, const Mint &y) { if ((x.x += y.x) >= (unsigned)x.mod()) x.x -= x.mod(); return x; }
Mint operator-(Mint x, const Mint &y) { if ((x.x += x.mod() - y.x) >= (unsigned)x.mod()) x.x -= x.mod(); return x; }
Mint operator*(Mint x, const Mint &y) { x.x = (unsigned long long)x.x * y.x % x.mod(); return x; }
Mint operator/(Mint x, const Mint &y) { x.x = (unsigned long long)x.x * y.inv().x % x.mod(); return x; }
bool operator<(const Mint &x, const Mint &y) { return x.x < y.x; }
bool operator==(const Mint &x, const Mint &y) { return x.x == y.x; }
bool operator!=(const Mint &x, const Mint &y) { return x.x != y.x; }

int N, M;
char F[111][11];
unordered_map<int, Mint> dp[1011];

const int BASE = 6;
int encode(int t, VI v) {
    int cur = 1;
    int T[9] = {};
    REP (j, M) {
	if (v[j] && T[v[j]] == 0) T[v[j]] = cur++;
    }
    REP (j, M) v[j] = T[v[j]];
    assert(cur <= BASE);

    int S = 0;
    for (int i=M; i--;) S = S * BASE + v[i];
    S = S * 2 + t;
    return S;
}

unordered_map<int, int> mem[2][8];

int cnt;
void next_states(const int S, const int i, const int j) {
    assert(S % 2 == 0 || S == 1);
    const int p = j;
    if (mem[0][p].count(S) == 0) {
		cnt++;

		VI v;
		int m = S/2;
		REP (k, M) {
		    v.push_back(m % BASE);
		    m /= BASE;
		}
		mem[0][p][S] = mem[1][p][S] = -2;

		// .
		if ((j && v[j] && v[j] == v[j-1]) || S == 1) {
		    // nothing
		} else {
		    VI w = v;
		    if (v[j] == 0 && (j==0 || v[j-1] == 0)) {
			int T[9] = {};
			REP (k, M) T[v[k]]++;
			for (int k=1; k<9; k++) {
			    if (T[k] == 0) {
				w[j] = k;
				break;
		    	}
			}
	    	} else if (j == 0 || v[j-1] == 0) {
	    	} else if (v[j] == 0) {
				w[j] = w[j-1];
	    	} else {
				int mi = min(v[j], v[j-1]), ma = max(v[j], v[j-1]);
				REP (k, M) if (w[k] == ma) w[k] = mi;
	    	}
	    	mem[0][p][S] = encode(0, w);
		}

		// #
		if (v[j] && count(v.begin(), v.end(), v[j]) == 1) {
	    	if (count(v.begin(), v.end(), 0) == M-1) {
				VI w = v;
				w[j] = 0;
				mem[1][p][S] = encode(1, w);
				// if (w == VI(M, 0))
	    	}
		} else {
	    	VI w = v;
	    	w[j] = 0;
	    	mem[1][p][S] = encode(S&1, w);
		}
    }
}

int main() {
    scanf("%d%d", &N, &M);
    REP (i, N) scanf("%s", F[i]);

    // N = 100; M = 8;
    // memset(F, '?', sizeof F);

    REP (j, M) F[N][j] = '#';
    N++;


    dp[0][0] = 1;
    int cur = 0;
    REP (i, N) REP (j, M) {
		EACH (X, dp[cur]) {
		    next_states(X->first, i, j);
		    if ((F[i][j] == '.' || F[i][j] == '?') && mem[0][j][X->first] >= 0) {
				dp[cur+1][mem[0][j][X->first]] += X->second;
		    }
		    if ((F[i][j] == '#' || F[i][j] == '?') && mem[1][j][X->first] >= 0) {
				dp[cur+1][mem[1][j][X->first]] += X->second;
		    }

		}
		cur++;
    }

    Mint ans = 0;
    EACH (X, dp[cur]) {
	ans += X->second;
    }

    printf("%d\n", ans.get<int>());
    eprintf("%d\n", cnt);
    return 0;
}

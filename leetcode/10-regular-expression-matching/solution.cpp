#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

#include "gmock/gmock.h"

using namespace std;

class Solution {
public:
    //
    //  Assume that p is not empty;
    //
    string getPart(string p) {
        if (p.length() > 1 && p[1] == '*') {
            return p.substr(0, 2);
        } else {
            return p.substr(0, 1);
        }
    }

    //
    //  Assume that s is not empty.
    //
    std::vector<size_t> matchPrefix(string s, string p) {
        std::vector<size_t> res;

        if (p.length() == 1) {  // x
            if (p == ".") {
                res.push_back(1);
            } else if (p[0] == s[0]) {
                res.push_back(1);
            }
        }

        if (p.length() == 2) {  // x*
            res.push_back(0);
            if (p[0] == '.') {
                for (auto i = 1; i <= s.length(); ++i) {
                    res.push_back(i);
                }
            } else {
                auto i = 0;
                while (i < s.length() && s[i] == p[0]) {
                    res.push_back(++i);
                }
            }
        }

        return res;
    }

private:
    bool isMatchC(const char *s, const char *p) {
      if (*p == '\0') return *s == '\0';
     
      // next char is not '*': must match current character
      if (*(p+1) != '*') {
        return ((*p == *s) || (*p == '.' && *s != '\0')) && isMatch(s+1, p+1);
      }
      // next char is '*'
      while ((*p == *s) || (*p == '.' && *s != '\0')) {
        if (isMatch(s, p+2)) return true;
        s++;
      }
      return isMatch(s, p+2);
    }

public:
    bool isMatch1(string s, string p) {
        if (p.length() == 0) {
            if (s.length() == 0) {
                return true;
            } else {
                return false;
            }
        }

        if (s.length() == 0) {
            return false;
        }

        auto p1 = getPart(p);                                       // First part of regexp.
        auto p2 = p.substr(p1.length(), p.length() - p1.length());  // Rest.

        auto matches = matchPrefix(s, p1);

        for (auto m : matches) {
            auto s2 = (m == 0 ? s : s.substr(m, s.length() - m));
            if (isMatch(s2, p2)) {
                return true;
            }
        }

        return false;
    }

    bool isMatch(string s, string p) {
        return isMatchC(s.c_str(), p.c_str());
    }
};

TEST(LongestSubstring, matchPrefix1) {
    Solution sol;
    std::vector<size_t> res = { 1 };
    ASSERT_THAT(sol.matchPrefix("aa", "a"), testing::Eq(res));
}

TEST(LongestSubstring, matchPrefix2) {
    Solution sol;
    std::vector<size_t> res = { };
    ASSERT_THAT(sol.matchPrefix("aa", "b"), testing::Eq(res));
}

TEST(LongestSubstring, matchPrefix3) {
    Solution sol;
    std::vector<size_t> res = { 0, 1, 2 };
    ASSERT_THAT(sol.matchPrefix("aa", "a*"), testing::Eq(res));
}

TEST(LongestSubstring, matchPrefix4) {
    Solution sol;
    std::vector<size_t> res = { 0, 1, 2 };
    ASSERT_THAT(sol.matchPrefix("ab", ".*"), testing::Eq(res));
}

TEST(LongestSubstring, getPart1) {
    Solution sol;
    ASSERT_THAT(sol.getPart("a"), testing::Eq("a"));
}

TEST(LongestSubstring, getPart2) {
    Solution sol;
    ASSERT_THAT(sol.getPart("aa"), testing::Eq("a"));
}

TEST(LongestSubstring, getPart3) {
    Solution sol;
    ASSERT_THAT(sol.getPart("abc"), testing::Eq("a"));
}

TEST(LongestSubstring, getPart4) {
    Solution sol;
    ASSERT_THAT(sol.getPart(".bc"), testing::Eq("."));
}

TEST(LongestSubstring, getPart5) {
    Solution sol;
    ASSERT_THAT(sol.getPart("a*bc"), testing::Eq("a*"));
}

TEST(LongestSubstring, getPart6) {
    Solution sol;
    ASSERT_THAT(sol.getPart(".*bc"), testing::Eq(".*"));
}

TEST(LongestSubstring, getPart7) {
    Solution sol;
    ASSERT_THAT(sol.getPart(".*"), testing::Eq(".*"));
}

TEST(LongestSubstring, isMatch1) {
    Solution sol;
    ASSERT_THAT(sol.isMatch("aa", "a"), testing::Eq(false));
}

TEST(LongestSubstring, isMatch2) {
    Solution sol;
    ASSERT_THAT(sol.isMatch("aa", "aa"), testing::Eq(true));
}

TEST(LongestSubstring, isMatch3) {
    Solution sol;
    ASSERT_THAT(sol.isMatch("aaa", "aa"), testing::Eq(false));
}

TEST(LongestSubstring, isMatch4) {
    Solution sol;
    ASSERT_THAT(sol.isMatch("aa", "a*"), testing::Eq(true));
}

TEST(LongestSubstring, isMatch5) {
    Solution sol;
    ASSERT_THAT(sol.isMatch("aa", ".*"), testing::Eq(true));
}

TEST(LongestSubstring, isMatch6) {
    Solution sol;
    ASSERT_THAT(sol.isMatch("ab", ".*"), testing::Eq(true));
}

TEST(LongestSubstring, isMatch7) {
    Solution sol;
    ASSERT_THAT(sol.isMatch("aab", "c*a*b"), testing::Eq(true));
}

TEST(LongestSubstring, isMatch8) {
    Solution sol;
    ASSERT_THAT(sol.isMatch("aab", ""), testing::Eq(false));
}

TEST(LongestSubstring, isMatch9) {
    Solution sol;
    ASSERT_THAT(sol.isMatch("", ""), testing::Eq(true));
}

TEST(LongestSubstring, isMatch10) {
    Solution sol;
    ASSERT_THAT(sol.isMatch("aab", "a*ab"), testing::Eq(true));
}

TEST(LongestSubstring, isMatch11) {
    Solution sol;
    ASSERT_THAT(sol.isMatch("aab", ".*ab"), testing::Eq(true));
}

TEST(LongestSubstring, isMatch12) {
    Solution sol;
    ASSERT_THAT(sol.isMatch("aab", ".*aab"), testing::Eq(true));
}

TEST(LongestSubstring, isMatch13) {
    Solution sol;
    ASSERT_THAT(sol.isMatch("aab", "a.*b"), testing::Eq(true));
}

TEST(LongestSubstring, isMatchTLE1) {
    Solution sol;
    ASSERT_THAT(sol.isMatch("aaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*c"), testing::Eq(false));
}

TEST(LongestSubstring, isMatchRE1) {
    Solution sol;
    ASSERT_THAT(sol.isMatch("a", ".*..a*"), testing::Eq(false));
}

int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}

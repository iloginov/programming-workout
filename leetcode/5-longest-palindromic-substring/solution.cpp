#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

#include "gmock/gmock.h"

using namespace std;

class Solution {
public:
    string transformString(string s) {
        // Как я бы написал это на чём-нибудь динамическом.
        // return "#" + "#".join(s.split("")) + "#";
        // Как приходится писать на C++. Нифига это не понятнее.
        stringstream out;
        out << "#";
        copy(begin(s), end(s), ostream_iterator<char>(out, "#"));
        return out.str();
    }

    int computeRadius(const string &s, int len, int pos) {
        int res = 0;
        for (int i = 1; i <= len / 2; ++i) {
            if (pos - i >=0 && pos + i < len && s[pos - i] == s[pos + i]) {
                res++;
            } else {
                break;
            }
        }
        return res;
    }

    std::vector<int> fillP(string s)
    {
        auto len = s.length();
        std::vector<int> p(len, 0);

        int R = -1;
        int C = -1;
        for (int i = 0; i < len; ++i) {
            int symIdx = 2 * C - i;
            if (i < R && symIdx >= 0 && i + p[symIdx] < R) {
                p[i] = p[symIdx];
            } else {
                p[i] = computeRadius(s, len, i);
                C = i;
                R = C + p[C];
            }
        }

        return p;
    }

    // Как бы я это сделал на другом языке?
    int maxIdx(const std::vector<int> v)
    {
        if (v.size() == 0)
            return -1;
        int idx = 0;
        int m = v[0];

        for (int i = 0; i < v.size(); ++i) {
            if (v[i] > m) {
                m = v[i];
                idx = i;
            }
        }

        return idx;
    }

    string longestPalindrome(string s) {
        auto n = s.length();
        auto str = transformString(s);
        auto p = fillP(str);
        auto idx = maxIdx(p);
        auto len = p[idx];

    	return s.substr((idx - len) / 2, len);
    }
};

TEST(LongestSubstring, transformString0) {
    Solution sol;
    ASSERT_THAT(sol.transformString(""), testing::Eq("#"));
}

TEST(LongestSubstring, transformString1) {
    Solution sol;
    ASSERT_THAT(sol.transformString("a"), testing::Eq("#a#"));
}

TEST(LongestSubstring, transformString2) {
    Solution sol;
    ASSERT_THAT(sol.transformString("abcdef"), testing::Eq("#a#b#c#d#e#f#"));
}

TEST(LongestSubstring, computeRadius1) {
    Solution sol;
    ASSERT_THAT(sol.computeRadius("#a#", 3, 1), testing::Eq(1));
}

TEST(LongestSubstring, fillP1) {
    Solution sol;
    std::vector<int> res = {0, 1, 0};
    ASSERT_THAT(sol.fillP("#a#"), testing::Eq(res));
}

TEST(LongestSubstring, fillP2) {
    Solution sol;
    std::vector<int> res = {0, 1, 0, 3, 0, 1, 0};
    ASSERT_THAT(sol.fillP("#a#b#a#"), testing::Eq(res));
}

TEST(LongestSubstring, Test1) {
	Solution sol;
   	ASSERT_THAT(sol.longestPalindrome("a"), testing::Eq("a"));
}

TEST(LongestSubstring, Test2) {
    Solution sol;
	ASSERT_THAT(sol.longestPalindrome("abcbf"), testing::Eq("bcb"));
}

TEST(LongestSubstring, Test3) {
    Solution sol;
    ASSERT_THAT(sol.longestPalindrome("abba"), testing::Eq("abba"));
}

TEST(LongestSubstring, Test4) {
    Solution sol;
    ASSERT_THAT(sol.longestPalindrome("fabbad"), testing::Eq("abba"));
}

TEST(LongestSubstring, Test5) {
    Solution sol;
    ASSERT_THAT(sol.longestPalindrome("ccc"), testing::Eq("ccc"));
}

TEST(LongestSubstring, Test6) {
    Solution sol;
    ASSERT_THAT(sol.longestPalindrome("bananas"), testing::Eq("anana"));
}

TEST(LongestSubstring, Test7) {
    Solution sol;
    ASSERT_THAT(sol.longestPalindrome("ababababa"), testing::Eq("ababababa"));
}

TEST(LongestSubstring, Test8) {
    Solution sol;
    ASSERT_THAT(sol.longestPalindrome("321012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210123210012321001232100123210123"), testing::Eq("321012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210012321001232100123210123"));
}

TEST(LongestSubstring, Long) {
    Solution sol;
    ASSERT_THAT(sol.longestPalindrome("lcnvoknqgejxbfhijmxglisfzjwbtvhodwummdqeggzfczmetrdnoetmcydwddmtubcqmdjwnpzdqcdhplxtezctvgnpobnnscrmeqkwgiedhzsvskrxwfyklynkplbgefjbyhlgmkkfpwngdkvwmbdskvagkcfsidrdgwgmnqjtdbtltzwxaokrvbxqqqhljszmefsyewwggylpugmdmemvcnlugipqdjnriythsanfdxpvbatsnatmlusspqizgknabhnqayeuzflkuysqyhfxojhfponsndytvjpbzlbfzjhmwoxcbwvhnvnzwmkhjxvuszgtqhctbqsxnasnhrusodeqmzrlcsrafghbqjpyklaaqximcjmpsxpzbyxqvpexytrhwhmrkuybtvqhwxdqhsnbecpfiudaqpzsvfaywvkhargputojdxonvlprzwvrjlmvqmrlftzbytqdusgeupuofhgonqoyffhmartpcbgybshllnjaapaixdbbljvjomdrrgfeqhwffcknmcqbhvulwiwmsxntropqzefwboozphjectnudtvzzlcmeruszqxvjgikcpfclnrayokxsqxpicfkvaerljmxchwcmxhtbwitsexfqowsflgzzeynuzhtzdaixhjtnielbablmckqzcccalpuyahwowqpcskjencokprybrpmpdnswslpunohafvminfolekdleusuaeiatdqsoatputmymqvxjqpikumgmxaxidlrlfmrhpkzmnxjtvdnopcgsiedvtfkltvplfcfflmwyqffktsmpezbxlnjegdlrcubwqvhxdammpkwkycrqtegepyxtohspeasrdtinjhbesilsvffnzznltsspjwuogdyzvanalohmzrywdwqqcukjceothydlgtocukc"), testing::Eq("lbabl"));
}

int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}

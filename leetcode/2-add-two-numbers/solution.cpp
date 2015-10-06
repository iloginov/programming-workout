#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "gmock/gmock.h"

using namespace std;

struct ListNode {
 	int val;
 	ListNode *next;
 	ListNode(int x) : val(x), next(NULL) {}
 };

ListNode *conj(ListNode *l, int x)
{
	ListNode *res = new ListNode(x);
	res->next = l;
	return res;
}
 
ListNode *vector2list(std::vector<int> v)
{
	ListNode *res = nullptr;
	reverse(begin(v), end(v));
	for (auto n : v) {
		res = conj(res, n);
	}

	return res;
}

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    	ListNode *n1 = l1;
    	ListNode *n2 = l2;

    	ListNode *res = nullptr;
    	ListNode *last = nullptr;

  		int curry = 0;
  		while (n1 != nullptr || n2 != nullptr) {
  			int d1 = 0;
  			int d2 = 0;

  			if (n1 != nullptr) {
  				d1 = n1->val;
  				n1 = n1->next;
  			}

  			if (n2 != nullptr) {
  				d2 = n2->val;
  				n2 = n2->next;
  			}

  			int sum = d1 + d2 + curry;
  			curry = sum / 10;

  			if (last == nullptr) {
  				res = new ListNode(sum % 10);
  				last = res;
  			} else {
  				last->next = new ListNode(sum % 10);
  				last = last->next;
  			}
  		}

  		if (curry)
  			last->next = new ListNode(curry);

  		return res;
    }
};

TEST(addTwoNumbers, Helpers) {
	Solution sol;
	std::vector<int> v = { 2, 4, 3 };
	ListNode *num = vector2list(v);
	ASSERT_THAT(num->val, testing::Eq(v[0]));
	ASSERT_THAT(num->next->val, testing::Eq(v[1]));
	ASSERT_THAT(num->next->next->val, testing::Eq(v[2]));
}

TEST(addTwoNumbers, StatementExample) {
	Solution sol;
	ListNode *num1 = vector2list(std::vector<int> {2, 4, 3});
	ListNode *num2 = vector2list(std::vector<int> {5, 6, 4});
	ListNode *etalon = vector2list(std::vector<int> {7, 0, 8});
	ListNode *res = sol.addTwoNumbers(num1, num2);
	ASSERT_THAT(res->val, testing::Eq(etalon->val));
	ASSERT_THAT(res->next->val, testing::Eq(etalon->next->val));
	ASSERT_THAT(res->next->next->val, testing::Eq(etalon->next->next->val));
	ASSERT_THAT(res->next->next->next, testing::Eq(nullptr));
}

TEST(addTwoNumbers, DifferentLength) {
	Solution sol;
	ListNode *num1 = vector2list(std::vector<int> {9, 9, 9});
	ListNode *num2 = vector2list(std::vector<int> {2});
	ListNode *etalon = vector2list(std::vector<int> {1, 0, 0, 1});
	ListNode *res = sol.addTwoNumbers(num1, num2);
	ASSERT_THAT(res->val, testing::Eq(etalon->val));
	ASSERT_THAT(res->next->val, testing::Eq(etalon->next->val));
	ASSERT_THAT(res->next->next->val, testing::Eq(etalon->next->next->val));
	ASSERT_THAT(res->next->next->next->val, testing::Eq(etalon->next->next->next->val));
	ASSERT_THAT(res->next->next->next->next, testing::Eq(nullptr));
}

TEST(addTwoNumbers, Test1) {
	Solution sol;
	ListNode *num1 = vector2list(std::vector<int> {1, 2, 3});
	ListNode *num2 = vector2list(std::vector<int> {1, 2, 3});
	ListNode *etalon = vector2list(std::vector<int> {2, 4, 6});
	ListNode *res = sol.addTwoNumbers(num1, num2);
	ASSERT_THAT(res->val, testing::Eq(etalon->val));
	ASSERT_THAT(res->next->val, testing::Eq(etalon->next->val));
	ASSERT_THAT(res->next->next->val, testing::Eq(etalon->next->next->val));
	ASSERT_THAT(res->next->next->next, testing::Eq(nullptr));
}


int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}

#include <iostream>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *dummy = new ListNode();
        ListNode *res = dummy;
        int total = 0, carry = 0;

        while (l1 || l2 || carry)
        {
            total = carry;

            if (l1)
            {
                total += l1->val;
                l1 = l1->next;
            }
            if (l2)
            {
                total += l2->val;
                l2 = l2->next;
            }

            int num = total % 10;
            carry = total / 10;
            dummy->next = new ListNode(num);
            dummy = dummy->next;
        }

        ListNode *result = res->next;
        delete res;
        return result;
    }
};

void printList(ListNode *node)
{
    while (node)
    {
        std::cout << node->val;
        if (node->next)
            std::cout << " -> ";
        node = node->next;
    }
    std::cout << std::endl;
}

ListNode *createList(std::initializer_list<int> vals)
{
    ListNode dummy;
    ListNode *tail = &dummy;
    for (int val : vals)
    {
        tail->next = new ListNode(val);
        tail = tail->next;
    }
    return dummy.next;
}

int main()
{
    ListNode *l1 = createList({2, 4, 3});
    ListNode *l2 = createList({5, 6, 4});

    Solution sol;
    ListNode *result = sol.addTwoNumbers(l1, l2);

    std::cout << "Result: ";
    printList(result);

    return 0;
}
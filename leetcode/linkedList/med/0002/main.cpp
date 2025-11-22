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
        ListNode *head = new ListNode(); // ダミーヘッド
        ListNode *tail = head;
        int carry = 0;

        while (l1 || l2 || carry)
        {
            int val1 = l1 ? l1->val : 0;
            int val2 = l2 ? l2->val : 0;
            int sum = val1 + val2 + carry;

            carry = sum / 10;
            tail->next = new ListNode(sum % 10);
            tail = tail->next;

            if (l1)
                l1 = l1->next;
            if (l2)
                l2 = l2->next;
        }

        ListNode *result = head->next;
        delete head; // ダミーヘッドを解放
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
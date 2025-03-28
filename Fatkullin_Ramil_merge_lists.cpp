#include <iostream>
#include <vector>
#include <queue>

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(nullptr) {
    }
};

struct Comp {
    bool operator()(const ListNode *a, const ListNode *b) {
        return a->val > b->val;
    }
};

ListNode *merge(std::vector<ListNode *> &v) {
    std::priority_queue<ListNode *, std::vector<ListNode *>, Comp> Heap;

    for (ListNode *list: v) {
        Heap.push(list);
    }

    ListNode prev_head(0);
    ListNode *tail = &prev_head;

    while (!Heap.empty()) {
        ListNode *Node = Heap.top();
        Heap.pop();

        tail->next = Node;
        tail = tail->next;
        if (Node->next) {
            Heap.push(Node->next);
        }
    }

    return prev_head.next;
}

int main() {
    ListNode *head1 = new ListNode(1);
    head1->next = new ListNode(2);
    head1->next->next = new ListNode(3);

    ListNode *head2 = new ListNode(4);
    head2->next = new ListNode(5);
    head2->next->next = new ListNode(6);

    ListNode *head3 = new ListNode(7);
    head3->next = new ListNode(8);
    head3->next->next = new ListNode(11);
    std::vector<ListNode *> lists{head1, head2, head3};

    ListNode *result = merge(lists);
    while (result) {
        std::cout << result->val << '\n';
        result = result->next;
    }
    return 0;
}


struct ListNode {
       int val;
       struct ListNode *next;
};
#include <stddef.h>
size_t sizeOfList(const struct ListNode* head)
{
    const struct ListNode* node = head;
    size_t size = 0;
    do{
        size++;
    }while (node = (node -> next));
    return size;
}

struct ListNode* accessElement(const struct ListNode *head, int nth_from_last)
{
    size_t size = sizeOfList(head);
    const struct ListNode *element = head;
    for (int i = 0;i < (int)size - nth_from_last;i++){
        element = element -> next;
    }
    return element;
}
struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    size_t size = sizeOfList(head);
    if (size == 0 || size == 1)
        return NULL;
    if (size == n)
        return head -> next;
    struct ListNode *nth_element = accessElement(head, n);
    struct ListNode *nplusoneth_element = accessElement(head, n + 1);
    nplusoneth_element -> next = nth_element -> next;
    return head;
}
struct ListNode {
    int val;
    struct ListNode *next;
};
 

size_t sizeOfList(const struct ListNode *head)
{
    const struct ListNode* nextNode = head;
    size_t size = 1;
    while (nextNode = nextNode -> next)
        size++;
    return size;
}

struct ListNode* middleNode(const struct ListNode* head){
    size_t size = sizeOfList(head);
    const struct ListNode* middle = head;
    
    for (int i = 0;i < (int)(size) / 2;i++)
        middle = middle -> next;
    return middle;
}
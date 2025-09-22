#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void append(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head_ref;
    new_node->data = new_data;
    new_node->next = NULL;
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
}

struct Node* reverse(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}


int isPalindrome(struct Node* head) {
    if (head == NULL || head->next == NULL)
        return 1;

    struct Node *slow = head, *fast = head;
    struct Node *prev_of_slow = NULL;
    struct Node *second_half, *midnode = NULL;
    int result = 1;


    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        prev_of_slow = slow;
        slow = slow->next;
    }

    if (fast != NULL) {
        midnode = slow;
        slow = slow->next;
    }

    second_half = slow;
    prev_of_slow->next = NULL;

    second_half = reverse(second_half);

    struct Node *first_half = head;
    struct Node *second_half_copy = second_half;
    while (first_half && second_half) {
        if (first_half->data != second_half->data) {
            result = 0;
            break;
        }
        first_half = first_half->next;
        second_half = second_half->next;
    }

    second_half_copy = reverse(second_half_copy);
    if (midnode != NULL) {
        prev_of_slow->next = midnode;
        midnode->next = second_half_copy;
    } else {
        prev_of_slow->next = second_half_copy;
    }
    return result;
}

void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int n, val;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        append(&head, val);
    }
    printList(head);
    if (isPalindrome(head))
        printf("The linked list is a palindrome.\n");
    else
        printf("The linked list is NOT a palindrome.\n");
    return 0;
}

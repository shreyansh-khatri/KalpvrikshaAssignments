#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node *insertAtBeginning(Node *head, int data)
{
    Node *newNode = createNode(data);
    newNode->next = head;
    return newNode;
}

Node *insertAtEnd(Node *head, int data)
{
    Node *newNode = createNode(data);
    if (head == NULL)
    {
        return newNode;
    }
    Node *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

Node *insertAtPosition(Node *head, int data, int position)
{
    if (position < 1)
    {
        printf("Invalid position\n");
        return head;
    }

    Node *newNode = createNode(data);
    if (position == 1)
    {
        newNode->next = head;
        return newNode;
    }

    Node *current = head;
    int count = 1;
    while (count < position - 1 && current != NULL)
    {
        current = current->next;
        count++;
    }

    if (current == NULL)
    {
        printf("Invalid position\n");
        return head;
    }

    newNode->next = current->next;
    current->next = newNode;
    return head;
}

Node *deleteNode(Node *head, int data)
{
    Node *current = head;
    Node *prev = NULL;

    while (current != NULL && current->data != data)
    {
        prev = current;
        current = current->next;
    }

    if (current != NULL)
    {
        if (prev == NULL)
        {
            head = head->next;
        }
        else
        {
            prev->next = current->next;
        }
        free(current);
    }

    return head;
}

void displayList(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void freeList(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main()
{
    Node *head = NULL;
    int choice, data, position;

    do
    {
        printf("\nLinked List Operations:\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Delete Element\n");
        printf("5. Display List\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter data to insert at beginning: ");
            scanf("%d", &data);
            head = insertAtBeginning(head, data);
            break;
        case 2:
            printf("Enter data to insert at end: ");
            scanf("%d", &data);
            head = insertAtEnd(head, data);
            break;
        case 3:
            printf("Enter data to insert: ");
            scanf("%d", &data);
            printf("Enter position: ");
            scanf("%d", &position);
            head = insertAtPosition(head, data, position);
            break;
        case 4:
            printf("Enter data to delete: ");
            scanf("%d", &data);
            head = deleteNode(head, data);
            break;
        case 5:
            printf("Linked List: ");
            displayList(head);
            break;
        case 6:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 6);

    freeList(head);
    return 0;
}
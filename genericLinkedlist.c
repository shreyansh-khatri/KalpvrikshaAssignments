#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    void *data;
    enum
    {
        INT,
        CHAR,
        FLOAT
    } type;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
    int size;
} LinkedList;

Node *createNode(void *data, size_t dataSize, int type)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = malloc(dataSize);
    memcpy(newNode->data, data, dataSize);
    newNode->type = type;
    newNode->next = NULL;
    return newNode;
}

void initializeList(LinkedList *list)
{
    list->head = NULL;
    list->size = 0;
}

void insertAtStart(LinkedList *list, void *data, size_t dataSize, int type)
{
    Node *newNode = createNode(data, dataSize, type);
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

void insertAtEnd(LinkedList *list, void *data, size_t dataSize, int type)
{
    Node *newNode = createNode(data, dataSize, type);
    if (list->head == NULL)
    {
        list->head = newNode;
    }
    else
    {
        Node *current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

void printList(LinkedList *list)
{
    Node *current = list->head;
    while (current != NULL)
    {
        switch (current->type)
        {
        case INT:
            printf("%d", *((int *)current->data));
            break;
        case CHAR:
            printf("%c", *((char *)current->data));
            break;
        case FLOAT:
            printf("%.2f", *((float *)current->data));
            break;
        }
        printf(" -> ");
        current = current->next;
    }
    printf("NULL\n");
}

void insertAtPosition(LinkedList *list, int position, void *data, size_t dataSize, int type)
{
    if (position < 0 || position > list->size)
    {
        printf("Invalid position.\n");
        return;
    }
    if (position == 0)
    {
        insertAtStart(list, data, dataSize, type);
    }
    else if (position == list->size)
    {
        insertAtEnd(list, data, dataSize, type);
    }
    else
    {
        Node *newNode = createNode(data, dataSize, type);
        Node *current = list->head;
        for (int i = 0; i < position - 1; i++)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        list->size++;
    }
}

void deleteAtPosition(LinkedList *list, int position)
{
    if (position < 0 || position >= list->size)
    {
        printf("Invalid position.\n");
        return;
    }
    Node *temp = list->head;
    if (position == 0)
    {
        list->head = temp->next;
        free(temp->data);
        free(temp);
    }
    else
    {
        for (int i = 0; i < position - 1; i++)
        {
            temp = temp->next;
        }
        Node *nodeToDelete = temp->next;
        temp->next = nodeToDelete->next;
        free(nodeToDelete->data);
        free(nodeToDelete);
    }
    list->size--;
}

void printInt(void *data)
{
    printf("%d", *(int *)data);
}

void printChar(void *data)
{
    printf("%c", *((char *)data));
}

void printFloat(void *data)
{
    printf("%.2f", *((float *)data));
}

int main()
{
    LinkedList list;
    initializeList(&list);

    int choice;
    int intData;
    char charData;
    float floatData;
    int position;

    while (1)
    {
        printf("\n1. Insert at start\n2. Insert at end\n3. Insert at position\n4. Delete at position\n5. Print list\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter data type: 1. Int 2. Char 3. Float: ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                printf("Enter integer data: ");
                scanf("%d", &intData);
                insertAtStart(&list, &intData, sizeof(int), INT);
                break;
            case 2:
                printf("Enter character data: ");
                scanf(" %c", &charData);
                insertAtStart(&list, &charData, sizeof(char), CHAR);
                break;
            case 3:
                printf("Enter float data: ");
                scanf("%f", &floatData);
                insertAtStart(&list, &floatData, sizeof(float), FLOAT);
                break;
            default:
                printf("Invalid choice.\n");
            }
            break;
        case 2:
            printf("Enter data type: 1. Int 2. Char 3. Float: ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                printf("Enter integer data: ");
                scanf("%d", &intData);
                insertAtEnd(&list, &intData, sizeof(int), INT);
                break;
            case 2:
                printf("Enter character data: ");
                scanf(" %c", &charData);
                insertAtEnd(&list, &charData, sizeof(char), CHAR);
                break;
            case 3:
                printf("Enter float data: ");
                scanf("%f", &floatData);
                insertAtEnd(&list, &floatData, sizeof(float), FLOAT);
                break;
            default:
                printf("Invalid choice.\n");
            }
            break;
        case 3:
            printf("Enter position: ");
            scanf("%d", &position);
            printf("Enter data type: 1. Int 2. Char 3. Float: ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                printf("Enter integer data: ");
                scanf("%d", &intData);
                insertAtPosition(&list, position, &intData, sizeof(int), INT);
                break;
            case 2:
                printf("Enter character data: ");
                scanf(" %c", &charData);
                insertAtPosition(&list, position, &charData, sizeof(char), CHAR);
                break;
            case 3:
                printf("Enter float data: ");
                scanf("%f", &floatData);
                insertAtPosition(&list, position, &floatData, sizeof(float), FLOAT);
                break;
            default:
                printf("Invalid choice.\n");
            }
            break;
        case 4:
            printf("Enter position to delete: ");
            scanf("%d", &position);
            deleteAtPosition(&list, position);
            break;
        case 5:
            printf("Linked List: ");
            printList(&list);
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
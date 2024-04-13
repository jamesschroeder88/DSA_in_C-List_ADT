#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
} Node_t;

typedef struct LinkedList {
    Node_t *head;
    Node_t *tail;
} LinkedList_t;



// 1
Node_t* CreateAndInitNode(int value) {
    //Allocate memory on the heap for the node.
    //Initalize the date field of the node to the value passed to the function.
    //Return the address of the node.
    Node_t *newNode = (Node_t*)malloc(sizeof(Node_t)); // Allocate memory for the node
    if (newNode != NULL) { 
        newNode->data = value; 
        newNode->next = NULL; 
    }
    return newNode; 
}

// 2
Node_t* FindValue(LinkedList_t *list, int value){
    Node_t* current = list->head; // Start at head
    while (current != NULL) {
        if (current->data == value) { // check if data matches in this node
            // if it finds it return it
            return current; 
        }
        current = current->next; // keep moving the nodes
    }
    printf("Value not found.\n"); // incase we don't find it
    return NULL; // Return NULL if not found
}

//3
Node_t* FindIndex(LinkedList_t *list, int index) {
    // If the index is invalid (i.e. less than 0)
    if (index < 0) {  
        printf("Invalid index.\n");
        return NULL;
    }
    Node_t* current = list->head; 
    int currentIndex = 0; 
    while (current != NULL) {
        if (currentIndex == index) { 
            return current; 
        }
        current = current->next;
        currentIndex++; 
    }
    printf("Index not found.\n"); 
    return NULL; 
}


//4
void InsertAfter(LinkedList_t *list, Node_t *newNode, Node_t *currNode) {
    //Insert the new node into the list after the current node.
    //If the current node is NULL, insert the new node at the beginning of the list
    if (newNode == NULL) return; 
    if (list->head == NULL || currNode == NULL) { 
        newNode->next = list->head; // insert this new node at beginning
        list->head = newNode; //  head update that thing to the new node
        if (list->tail == NULL) { // Note to self I need this because empty lists mess it up, so I update the tail
            list->tail = newNode;
        }
    } else {
        newNode->next = currNode->next; // link new node with next node of currNode
        currNode->next = newNode; // link currNode with new node
        if (currNode == list->tail) { // Note to self, I added this case because during test case of currNode being tail, update tail to new node
            list->tail = newNode;
        }
    }
}


//5
int InsertAfterValue(LinkedList_t *list, Node_t *newNode, int value) {
    Node_t* current = list->head;
    while (current != NULL) {
        if (current->data == value) {
            newNode->next = current->next; 
            current->next = newNode; 
            if (current == list->tail) { 
                list->tail = newNode;
            }
            return 0; 
        }
        current = current->next;
    }
    printf("Value not found.\nNode not inserted.\n");
    return -1;
}


//6 
int InsertAfterIndex(LinkedList_t *list, Node_t *newNode, int index) {
    if (index < 0) {
        printf("Invalid index.\n");
        printf("Node not inserted.\n");
        return -1; // Invalid index
    }
    // Note to self, the list can be empty so remember to insert at beginning of empty list
    if (index == 0 && list->head == NULL) { 
        list->head = list->tail = newNode;
        return 0;
    }
    Node_t* current = list->head;
    int currentIndex = 0;
    while (current != NULL) {
        if (currentIndex == index) {
            newNode->next = current->next;
            current->next = newNode;
            if (current == list->tail) {
                list->tail = newNode;
            }
            return 0; 
        }
        current = current->next;
        currentIndex++;
    }
    printf("Index not found.\n");
    printf("Node not inserted.\n");
    return -1; 
}


//7 
void Remove(LinkedList_t *list, Node_t *remNode) {
    if (list->head == NULL || remNode == NULL) return; // empty list don't nothing to remove
    if (list->head == remNode) { // remove only head given 1 thing in list
        list->head = list->head->next;
        if (list->tail == remNode) { // Note to self: updating the tail because it is first and last
            list->tail = NULL;
        }
        free(remNode); 
        return;
    }
    Node_t* current = list->head;
    while (current->next != NULL && current->next != remNode) {
        current = current->next;
    }
    if (current->next == remNode) {
        current->next = remNode->next; // I need to bypass for this case, so bypass the removed node
        if (list->tail == remNode) { // If it was the tail then update the tail
            list->tail = current;
        }
        free(remNode); 
    }
}


//8 
int RemoveByValue(LinkedList_t *list, int value) {
    
    if (list->head == NULL){ // empty list
        printf("List is already empty\n");
        return -1;
    } 

    Node_t *current = list->head;
    Node_t *prev = NULL;

    while (current != NULL) {
        if (current->data == value) { // If I find the node with matching value
            if (prev == NULL) { // Note to self: Pretty much you always have these edge cases where it is head or tail. Node is at the head
                list->head = current->next;
            } else {
                prev->next = current->next;
            }

            if (current == list->tail) { // Same thing as always: node is at the tail
                list->tail = prev;
            }

            free(current);
            return 0; 
        }
        prev = current;
        current = current->next;
    }
    printf("Value not found.\n");
    printf("Node not removed.\n");
    return -1; 
}


//9
int RemoveByIndex(LinkedList_t *list, int index) {
    
    if (list->head == NULL || index < 0) { // empty or invalid index
        printf("Invalid index\n");
        printf("Node not removed.\n");
        return -1; 
    }
    
    Node_t *current = list->head;
    Node_t *prev = NULL;
    int currentIndex = 0;

    while (current != NULL) {
        if (currentIndex == index) { // found matching index
            if (prev == NULL) { // node at head
                list->head = current->next;
            } else {
                prev->next = current->next;
            }

            if (current == list->tail) { // node at tail
                list->tail = prev;
            }

            free(current);
            return 0; 
        }
        prev = current;
        current = current->next;
        currentIndex++;
    }
    printf("Index not found.\n");
    printf("Node not removed.\n");
    return -1;
}


//10 
// Function to reverse the list and create a copy of it in reverse order
LinkedList_t* ReverseList(LinkedList_t *list) {
    // Create a new list to hold the reversed copy
    LinkedList_t* reversedList = (LinkedList_t*)malloc(sizeof(LinkedList_t));
    if (reversedList == NULL) { // If the memory allocation is failed alert
        printf("Memory allocation failed for reversed list.\n");
        return NULL;
    }
    reversedList->head = NULL;
    reversedList->tail = NULL;

    Node_t *current = list->head;
    while (current != NULL) { // Create a new node with the current data
        Node_t *newNode = CreateAndInitNode(current->data);
        if (newNode == NULL) {
            // I tested without this and it seems to work, but while reading 
            // documentation it seems that best practice is to handle memory allocation failure for edge cases
            printf("Memory allocation failed for new node.\n");
            
            return NULL;
        }
        // insert new node at the beginning of the reversed list
        if (reversedList->head == NULL) {
            reversedList->head = reversedList->tail = newNode;
        } else {
            newNode->next = reversedList->head;
            reversedList->head = newNode;
        }
        current = current->next;
    }

    return reversedList;
}



//11
// I was having issue with the IsPalindrome() returning the correct answer but dropping the second half of the palindrome (or just list if it wasn't a palindrome)
// To fix that I am making a copy function to copy the list that IsPalindrome checks
LinkedList_t* CopyList(LinkedList_t *list) {
    LinkedList_t* newList = (LinkedList_t*)malloc(sizeof(LinkedList_t));
    if (newList == NULL) {
        printf("Memory allocation failed for new list.\n");
        return NULL;
    }
    newList->head = newList->tail = NULL;
    Node_t *current = list->head;
    while (current != NULL) {
        Node_t *newNode = CreateAndInitNode(current->data);
        if (newNode == NULL) {
            printf("Memory allocation failed for new node.\n");
            return NULL;
        }
        if (newList->head == NULL) {
            newList->head = newList->tail = newNode;
        } else {
            newList->tail->next = newNode;
            newList->tail = newNode;
        }
        current = current->next;
    }
    return newList;
}

// It works without this but, seems best practice is too handle edge cases like this 
// Utility function to free a list, preventing memory leaks
void FreeList(LinkedList_t *list) {
    Node_t *current = list->head;
    Node_t *next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    free(list); // Note to future self: I need to free the list structure itself
}

// Here is the IsPalindrome function
int IsPalindrome(LinkedList_t *list) {
    // getting the copy from my above CopyList function as noted above the CopyList function
    LinkedList_t* copy = CopyList(list);
    if (copy == NULL) {
        printf("Failed to create a copy for palindrome check.\n");
        return -1; 
    }
    
    // Easy case: empty list or single element is always palindrome
    if (copy->head == NULL || copy->head->next == NULL) {
        FreeList(copy); 
        return 1; 
    }

    Node_t *slow = copy->head, *fast = copy->head;
    Node_t *prev_slow = NULL, *midnode = NULL, *second_half;
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        prev_slow = slow;
        slow = slow->next;
    }

    // odd-sized list
    if (fast != NULL) {
        midnode = slow;
        slow = slow->next;
    }

    second_half = slow;
    prev_slow->next = NULL; 
    Node_t *prev = NULL, *current = second_half, *next;

    while (current != NULL) { // reverse the second half for comparison
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    second_half = prev;

    // Compare the first half and the reversed second half
    int result = 1;
    Node_t *first_half = copy->head;
    while (second_half != NULL && first_half != NULL) {
        if (first_half->data != second_half->data) {
            result = 0;
            break;
        }
        first_half = first_half->next;
        second_half = second_half->next;
    }

    // The copy function I made above makes it so I can discard the copy and 
    // I don't need to reverse the second half back because I'm discarding it

    FreeList(copy); // prevent memory leaks so, free the copy

    return result; // Return result of palindrome check function
}


//12
void PrintList(LinkedList_t *list) {
    //Print the data value of each node in the list, starting with the head node
    Node_t *current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}



int main() {
    printf("==========================\nTest 1:\n"); 
    Node_t *myNode = CreateAndInitNode(11);
    if ((myNode->data == 11) && (myNode->next == NULL)) {
     printf("CreateNode: Success. \n");
    } else {
     printf("CreateNode: Failure. \n");
    } // Should print: CreateNode: Success

    printf("==========================\nTest 2:\n");    
    LinkedList_t *myList = (LinkedList_t*)malloc(sizeof(LinkedList_t));
    myList->head = NULL;
    myList->tail = NULL;
    InsertAfter(myList, myNode, NULL);
    PrintList(myList); // Should print: 11
    
    printf("==========================\nTest 3:\n"); 
    myNode = CreateAndInitNode(22);
    InsertAfterValue(myList, myNode, 11);
    myNode = CreateAndInitNode(33);
    InsertAfterValue(myList, myNode, 22);
    myNode = CreateAndInitNode(44);
    InsertAfterIndex(myList, myNode, 2);
    myNode = CreateAndInitNode(55);
    InsertAfterIndex(myList, myNode, 3);
    PrintList(myList); // Should print: 11, 22, 33, 44, 55
    
    printf("==========================\nTest 4:\n"); 
    myNode = CreateAndInitNode(77);
    InsertAfterValue(myList, myNode, 66); // Should print: Value not found.
     // Should print: Node not inserted.
    InsertAfterIndex(myList, myNode, 5); // Should print: Index not found.
     // Should print: Node not inserted.
    InsertAfterIndex(myList, myNode, -1); // Should print: Invalid index.
     // Should print: Node not inserted.
    PrintList(myList); // Should print: 11, 22, 33, 44, 55
    
    printf("==========================\nTest 5:\n"); 
    int rval = RemoveByValue(myList, 44);
    rval = RemoveByIndex(myList, 0);
    PrintList(myList); // Should print: 22, 33, 55
    
    printf("==========================\nTest 6:\n"); 
    rval = RemoveByValue(myList, 11); // Should print: Value not found.
     // Should print: Node not removed.
    rval = RemoveByIndex(myList, 999); // Should print: Index not found.
     // Should print: Node not removed.
    rval = RemoveByIndex(myList, -5); // Should print: Invalid index.
     // Should print: Node not removed.
    
    PrintList(myList);// I added this for extra testing
    
    printf("==========================\nTest 7:\n"); 
    LinkedList_t *revList = ReverseList(myList);
    PrintList(revList); // Should print: 55, 33, 22
    
    
    
    printf("==========================\nTest 8:\n"); 
    myNode = CreateAndInitNode(22);
    InsertAfterValue(myList, myNode, 55);
    myNode = CreateAndInitNode(33);
    InsertAfterValue(myList, myNode, 55);
    PrintList(myList); //prints 22, 33, 55, 33, 22
    int pal = IsPalindrome(myList);
    if (pal == 1) {
        printf("Palindrome: Yes! \n");
    } else {
        printf("Palindrome: No. \n");
    } // Should print: Palindrome: Yes!
    PrintList(myList); // FIXME: Should print: 22, 33, 55, 33, 22 but incorrectly prints 22 33 55
    
    printf("==========================\nTest 9:\n"); 
    myNode = CreateAndInitNode(88);
    InsertAfterValue(myList, myNode, 33);
    RemoveByValue(myList, 22);
    PrintList(myList); // Should print: 33, 88, 55, 33, 22
    
    printf("==========================\nTest 10:\n"); 
    pal = IsPalindrome(myList);
    if (pal == 1) {
     printf("Palindrome: Yes! \n");
    } else {
     printf("Palindrome: No. \n");
    } // Should print: Palindrome: No.
    
    printf("==========================\nTest 11:\n"); 
    rval = RemoveByIndex(myList, 1);
    rval = RemoveByIndex(myList, 1);
    rval = RemoveByIndex(myList, 1);
    rval = RemoveByIndex(myList, 1);
    rval = RemoveByIndex(myList, 1); // Should print: Index not found.
     // Should print: Node not removed.
    PrintList(myList); // Should print: 33

    printf("==========================\nTest 12:\n"); 
    rval = RemoveByIndex(myList, 0);
    PrintList(myList);
    
    return 0;
}
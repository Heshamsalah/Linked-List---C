#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
}node;

void insertNode(node** headRef, int newData); /* insert a new node and make it the head of the list (moving the head) */
void append(node** headRef, int newData); /* add a new node to the last of the list without moving the head */
void addAfter(node* prevNode, int newData); /* add a new node after a given node */
void deleteNodeWithValue(node** headRef, int searchKey);
void deleteNodeWithPosition(node** headRef, int searchKey);
void printList(node* temp);
int scanUserInput(node** listHead);
int getLength(node* listHead);
int getLengthRecursive(node* listHead);


int main(){
	node *head = NULL; /* don't allocate this node in the memory */
	system("cls");
	while(1){
		printf("%s\n", "Enter:\n1 for insert.\n2 for append.\n3 for delete.\n4 to delete position.\n5 to print list.\n6 to exit.");
		if(!scanUserInput(&head)){
			break;
		}
	}
	return 0;
}

int scanUserInput(node** listHead){
	int userInput, val;
	scanf("%d", &userInput);
	switch(userInput){
		case 1: system("cls"); printf("%s\n", "insert node:\nnode data:\t"); scanf("%d", &val); insertNode(listHead, val); printf("\n\n"); break;
		case 2: system("cls"); printf("%s\n", "append node:\nnode data:\t"); scanf("%d", &val); append(listHead, val); printf("\n\n"); break;
		case 3: system("cls"); printf("%s\n", "delete node:\nnode data:\t"); scanf("%d", &val); deleteNodeWithValue(listHead, val); printf("\n\n"); break;
		case 4: system("cls"); printf("%s\n", "delete node:\nposition number:\t"); scanf("%d", &val); deleteNodeWithPosition(listHead, val); printf("\n\n"); break;
		case 5: system("cls"); printList(*listHead); printf("\n\n"); break;
		case 6: system("cls"); return 0;
		default: system("cls"); printf("%s\n", "Incorrect input!\n");
	}
	return 1;
}

void insertNode(node** headRef, int newData){
	node* newNode = (node*) malloc(sizeof(node));
	newNode->data = newData; /*put the new data into the new node */
	newNode->next = (*headRef); /*make the next of newNode as the head*/
	(*headRef) = newNode; /*make the head point to the new node (now the newNode is the head)*/
}

void append(node** headRef, int newData){
	node* newNode = (node*) malloc(sizeof(node));
	node* lastNode = (*headRef); /* This will point to the head of the list*/

	newNode->data = newData;
	newNode->next = NULL; /* This will make the new node always point to NULL (as it is the last node always)*/

	/* This will check if the list is empty or not (head = null??) */
	if(*headRef == NULL){
		*headRef = newNode;
		return;
	}
	else{
		/* This will traverse the list till it get the last inserted node*/
		while(lastNode->next != NULL){ 
			lastNode = lastNode->next;
		}
		lastNode->next = newNode; /* Make the last node in the list point to the new node instead of NULL (we have a new node now) */
		return;
	}
}

void addAfter(node* prevNode, int newData){
	if(prevNode == NULL){
		printf("%s\n", "Can\'t be Null");
		return;
	}
	node* newNode = (node*) malloc(sizeof(node));
	newNode->data = newData;
	newNode->next = prevNode->next; /* make the new node point to the node right after previous node*/ 
	prevNode->next = newNode; /* make the previous node point to the new node*/
}

void deleteNodeWithPosition(node** headRef, int searchKey){
	node *tempNode = *headRef;
	node *prevNode;

	/* if the head itself is the desired node to be deleted */
	if(tempNode != NULL && searchKey == 0){
		*headRef = tempNode->next;
		free(tempNode); /*free this node location from the memory*/
		return;
	}
	else{
		/* search the list for the desired node*/
		int position = 0;
		while(tempNode != NULL && position != searchKey){
			prevNode = tempNode;
			tempNode = tempNode->next;
			position++;
		}
		if(tempNode == NULL) return; /* the node not found */
		prevNode->next = tempNode->next;
		free(tempNode);
	}
}

void deleteNodeWithValue(node** headRef, int searchKey){
	node *tempNode = *headRef;
	node *prevNode;

	/* if the head itself is the desired node to be deleted */
	if(tempNode != NULL && tempNode->data == searchKey){
		*headRef = tempNode->next;
		free(tempNode); /*free this node location from the memory*/
		return;
	}
	else{
		/* search the list for the desired node*/
		while(tempNode != NULL && tempNode->data != searchKey){
			prevNode = tempNode;
			tempNode = tempNode->next;
		}
		if(tempNode == NULL) return; /* the node not found */
		prevNode->next = tempNode->next;
		free(tempNode);
	}
	
}

int getLength(node* listHead){
	int length = 0;
	node *currentNode = listHead;
	while(currentNode != NULL){
		currentNode = currentNode->next;
		length++;
	}
	return length;
}

int getLengthRecursive(node* listHead){
	if(listHead == NULL) return 0;
	return 1 + getLengthRecursive(listHead->next);
}

void printList(node* temp){
	node *holdHead = temp;
	while(temp != NULL) /*the received node doesn't point to a NULL.*/
	{
		printf("%d\n", temp->data);
		temp = temp->next; /*this makes the current temp node point to the next node to it.*/
	}
	printf("%s %d\n", "\nList length:\t", getLengthRecursive(holdHead));
}
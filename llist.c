/*

 * Author: Hesham Salah
 * Email: heshamsalahuldeen@gmail.com
 * Linkedin: https://eg.linkedin.com/in/heshamsalahuldeen
 * Github: https://github.com/Heshamsalah

*/

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
void deleteNodeWithValue(node** headRef, int searchKey); /* delete using the value of the node */
void deleteNodeWithPosition(node** headRef, int searchKey); /* delete using the position of the node */
void printList(node* tempNode);
int scanUserInput(node** listHead);
int getLength(node* listHead); /* calculate the length of the list */
int getLengthRecursive(node* listHead); /* calculate the length of the list using recursion method */
void swapNodes(node** headRef, int nodeValX, int nodeValY); /* swapping two nodes positions without swapping their values*/
void reverseList(node** headRef);

int main(){
	node *head = NULL; /* don't allocate this node in the memory */
	system("cls");
	while(1){
		printf("%s\n", "Enter:\n1 for insert.\n2 for append.\n3 for delete.\n4 to delete position.\n5 to swap two nodes.\n6 to reverse the list\n7 to print list.\n8 to exit.");
		if(!scanUserInput(&head)){
			break;
		}
	}
	return 0;
}

int scanUserInput(node** listHead){
	int userInput, valX, valY;
	scanf("%d", &userInput);
	switch(userInput){
		case 1: system("cls"); printf("%s\n", "insert node:\nnode data:\t"); scanf("%d", &valX); insertNode(listHead, valX); printf("\n\n"); break;
		case 2: system("cls"); printf("%s\n", "append node:\nnode data:\t"); scanf("%d", &valX); append(listHead, valX); printf("\n\n"); break;
		case 3: system("cls"); printf("%s\n", "delete node:\nnode data:\t"); scanf("%d", &valX); deleteNodeWithValue(listHead, valX); printf("\n\n"); break;
		case 4: system("cls"); printf("%s\n", "delete node:\nposition number:\t"); scanf("%d", &valX); deleteNodeWithPosition(listHead, valX); printf("\n\n"); break;
		case 5: system("cls"); printf("%s\n", "swap nodes:\nFirstNode SecondNode:\t"); scanf("%d %d", &valX, &valY); swapNodes(listHead, valX, valY); printf("\n\n"); break;
		case 6: system("cls"); reverseList(listHead); printf("Done Reversing\n\n"); break;
		case 7: system("cls"); printList(*listHead); printf("\n\n"); break; /*here we are passing the pointer itself we don't need the reference because this method doesn't accpt pointer to pointer */
		case 8: system("cls"); return 0;
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

void swapNodes(node** headRef, int nodeValX, int nodeValY){
	node *prevNodeX = NULL, *currentNodeX = *headRef; /* to help traverse the list till finding X value and hold the previuos node */
	node *prevNodeY = NULL, *currentNodeY = *headRef; /* to help traverse the list till finding Y value and hold the previuos node */
	node *tempNode = NULL; /* Used for swapping the values */
	if(*headRef == NULL || nodeValX == nodeValY) return; /* If the list is empty or the values are equal end */
	/* Loop the list till find the desired X node */
	while(currentNodeX != NULL && currentNodeX->data != nodeValX){
		prevNodeX = currentNodeX; /* Hold the Previous value to current node */
		currentNodeX = currentNodeX->next; /* move on to the next node */
	}
	/* Loop the list till find the desired Y node */
	while(currentNodeY != NULL && currentNodeY->data != nodeValY){
		prevNodeY = currentNodeY; /* Hold the Previous value to current node */
		currentNodeY = currentNodeY->next; /* move on to the next node */
	}
	if(currentNodeX == NULL || currentNodeY == NULL) return; /* couldn't find either X or Y */

	/* if the prevNodeX = NUll this means that the currentNodeX = *headRef (list head) */
	if(prevNodeX == NULL){ 
		*headRef = currentNodeY; /* *headRef here acts as if it is prevNodeX */
	}
	else{
		prevNodeX->next = currentNodeY;
	}

	/* if the prevNodeY = NUll this means that the currentNodeY = *headRef (list head) */
	if(prevNodeY == NULL){ 
		*headRef = currentNodeX; /* *headRef here acts as if it is prevNodeY */
	}
	else{
		prevNodeY->next = currentNodeX;
	}

	/* Swapping the Nodes */
	tempNode = currentNodeY->next;
	currentNodeY->next = currentNodeX->next;
	currentNodeX->next = tempNode;
}

void reverseList(node** headRef){
	node *prevNode = NULL, *currentNode = *headRef, *nextNode;
	while(currentNode != NULL){
		nextNode = currentNode->next;
		currentNode->next = prevNode;
		prevNode = currentNode;
		currentNode = nextNode;
	}
	*headRef = prevNode; /* prevNode here is pointing to what currentNode was pointing to befor moving to the next 
							which in this case is the node before NULL (last node of the old list) */
	/* *headRef = currentNode; this one will make the head point to null as currentNode at the end of the 
		loop will point to what nextNode points to which is NULL (old end of the list while going forward) */
}

void printList(node* tempNode){
	node *holdHead = tempNode;
	while(tempNode != NULL) /*the received node doesn't point to a NULL.*/
	{
		printf("%d\n", tempNode->data);
		tempNode = tempNode->next; /*this makes the current temp node point to the next node to it.*/
	}
	printf("%s %d\n", "\nList length:\t", getLengthRecursive(holdHead));
}
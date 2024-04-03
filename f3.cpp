/*
* FILE : f3.cpp
* PROJECT : focused 3
* PROGRAMMER : Minchul Hwang
* FIRST VERSION : 2023-02-06
* Description : This project is understand about hash table.
				Make 11 table and save the word as list which head of it is a key in hash table.
				and if I want to find, it can search it. it prints appropriate message of it.
* The functions in this file are used to struct - insertNode, clearLine, deleteAllNode, djb2, myHashFunction, searchWord
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#define kStructWordString		21
#define kWordString				20
#define kContinue				1
#define kHashArray				11
#define kZeroValue				0

typedef struct WordNode {
	char words[kStructWordString];
	struct WordNode* next;
	struct WordNode* prev;
} node;

void insertNode(char* wordString, node** head, node **tail);
void clearLine(char* string);
void deleteAllNode(node* head);
unsigned long djb2(const char* str);
int myHashFunction(char* wordString);
void searchWord(char* wordString, node** head);

int main() {
	char getString[kWordString] = {};
	node* head = NULL;
	
	node* listArr[kHashArray] = { };
	node* listArrTail[kHashArray] = {};
	int retHashV = 0;				//index of array
	printf("Please enter a word no more than 20 characters long.\n");
	while (kContinue) {

		printf("Enter Words : ");
		fgets(getString, sizeof(getString), stdin);
		clearLine(getString);
		
		// Make a loop until user enter '.'
		if (strcmp(getString, ".") == 0) {
			break;
		}

		// Make a key and insert that word into the list
		retHashV = myHashFunction(getString);
		insertNode(getString, &listArr[retHashV], &listArrTail[retHashV]);
	}
	printf("\n");
	while (kContinue) {
		printf("Enter Words which you want to find : ");
		fgets(getString, sizeof(getString), stdin);
		clearLine(getString);

		// Make a loop until user enter '.'
		if (strcmp(getString, ".") == 0) {
			break;
		}

		// Make that word which is input from user into key, and search it.
		retHashV = myHashFunction(getString);
		searchWord(getString, &listArr[retHashV]);
	}

	// Delete all list
	for (int i = kZeroValue; i < kHashArray; i++) {
		deleteAllNode(listArr[i]);
	}
	return 0;
}

/*
* Function : searchWord()
* Description : This function find the word which user want to find in hash table.
				If there is an word which user want to find, print "Success!", if not, print "Not there!".
* Parameters :	*wordString		char		which has the word string user want to find.
				**head			node		the head pointer of the list which has user want to find an word.
* Returns : NULL
*/
void searchWord(char* wordString, node** head) {
	node* currNode = *head;
	printf("Search word : '%s'...\n", wordString);
	while (currNode != NULL) {
		// If input word is in the list.
		if (strcmp(currNode->words, wordString) == 0) {
			printf("Success!\n");
			printf("\n");
			return;
		}
		currNode = currNode->next;
	}

	if (currNode == NULL) {
		printf("Not there!\n");
		printf("\n");
		return;
	}
}

/*
* Function : myHashFunction
* Description : This function get the string which user want to save, send that word into hash function.
				and calculate appropriate number to return.
* Parameters :	*wordString		char		which has the word string user want to store.
* Returns : retCode			int			mod of 11 from hash function
*/
int myHashFunction(char* wordString) {
	int retCode = djb2(wordString) % kHashArray;
	return retCode;
}

/*
* Function : djb2
* Description : This function is hash function calculates from string into appropriate number.
* Parameters : *str		const char			the word string from myHashFunction.
* Returns : hash		unsigned long		a calculated number
*/
unsigned long djb2(const char*str){
	unsigned long hash = 5381;
	int	c = 0;
	while ((c = *str++) !=  '\0') {
		hash = ((hash << 5) + hash) + c;
	}
	return hash;
}

/*
* Function : deleteAllNode
* Description : This function delete all node in the list.
* Parameters : *head		node		the head pointer of the list
* Returns : NONE
*/
void deleteAllNode(node* head) {
	node* currentNode = head;
	node* ptr = NULL;
	while (currentNode != NULL) {
		ptr = currentNode;
		currentNode = currentNode->next;
		free(ptr);
	}
}

/*
* Function : insertNode
* Description : This function get word string and head pointer of list and save string in it.
*				and the words are saved as acsending order.
* Parameters : **head			node		the head pointer of the list
*			   *wordString		char		the string which is getting from user.
* Returns : NONE
*/
void insertNode(char* wordString, node** head, node **tail) {
	node* newBlock = NULL;
	newBlock = (node*)malloc(sizeof(node));
	
	if (newBlock == NULL) {
		printf("There is no memory");
		return;
	}
	strncpy(newBlock->words, wordString, strlen(wordString) + 1);
	newBlock->next = NULL;
	
	if (*head == NULL) {
		// If there is nothing in head
		*head = *tail = newBlock;
		return;
	}
	// From here, make it ascending order
	else if (strcmp((*head)->words, newBlock->words) >= 0) {
		newBlock->next = *head;
		(*head)->prev = newBlock;
		*head = newBlock;
	}
	else {
		node* currBlock = *head;
		node* nextBlock = ( * head)->next;
		while (nextBlock != NULL) {
	
			if (strcmp(nextBlock->words, newBlock->words) >= 0) {
				break;
			}
			currBlock = currBlock->next; //첫 대가리부터 비교하기 위해
			nextBlock = nextBlock->next;
		}
		newBlock->prev = currBlock;
		newBlock->next = nextBlock;
		currBlock->next = newBlock;
		
		if (nextBlock == NULL) {
			*tail = newBlock;
		}
		else
			nextBlock->prev = newBlock;
	}
}

/*
* Function : clearNewLine()
* Description : If the received data is blank or contains \n, it is removed.
* Parameters : *str		char		the pointer has string from user
* Returns : None
*/
void clearLine(char* string) {
	char* searchNewLine = strchr(string, '\n');
	if (searchNewLine != NULL){
		*searchNewLine = '\0';
	}
}
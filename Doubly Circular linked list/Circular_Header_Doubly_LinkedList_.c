#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//nodes for list
typedef struct node {
	int data;
	struct node* next;
	struct node* prev;
}node;
//header that can store different information as needed
typedef struct header {
	int num_of_elem;
	struct node* first;//head (first node)
	struct node* last;//tail (last node)
}header;
header* head = NULL;//i used pointer to a list header as global variable in this example as it simplifies it

//create header
void CreateHeader() {
	if (head != NULL) {
		printf("Header already initialized\n");
		return;
	}
	head = (header*)malloc(sizeof(header));
	//initialize empty list
	head->num_of_elem = 0;
	head->first = head;
	head->last = head;
	printf("Header created\n");
}
//insert node at the end
void insert_at_tail(int data) {
	if (head == NULL) {
		printf("Header not created\n");
		return;
	}
	else if (head->last == head) {
		node* newnode = (node*)malloc(sizeof(node));
		newnode->data = data;
		head->first = newnode;
		head->last = newnode;
		newnode->prev = head;
		newnode->next = head;
		head->num_of_elem = 1;
	}
	else {//assuming header is already created
		node* newnode = (node*)malloc(sizeof(node));
		newnode->data = data;
		newnode->next = head;
		newnode->prev = head->last;
		head->last->next = newnode;//direct access to last node
		head->last = newnode;
		head->num_of_elem++;
	}

}
//insert node at beginning
void insert_at_head(int data) {
	if (head == NULL) {
		printf("Header not created\n");
		return;
	}
	else if (head->first == head) {
		node* newnode = (node*)malloc(sizeof(node));
		newnode->data = data;
		head->first = newnode;
		head->last = newnode;
		newnode->prev = head;
		newnode->next = head;
		head->num_of_elem = 1;
	}
	else {
		node* newnode = (node*)malloc(sizeof(node));
		newnode->data = data;
		newnode->prev = head;
		newnode->next = head->first;
		head->first->prev = newnode;
		head->first = newnode;
		head->num_of_elem++;
		
	}
}
//insert ndoe at given position
void insert_at_pos(int pos, int data) {
	if (head == NULL) {
		printf("Header not created\n");
		return;
	}
	else if (head->first == head) {
		//regardless of given position, if list is empty, insert as first element
		printf("(inserted as first node)\n");
		node* newnode = (node*)malloc(sizeof(node));
		newnode->data = data;
		head->first = newnode;
		head->last = newnode;
		newnode->prev = head;
		newnode->next = head;
		head->num_of_elem = 1;
	}
	else {
		if (pos > head->num_of_elem+1 || pos < 1) {
			printf("Invalid input...\n");
			return;
		}
		else if (pos == 1) {
			insert_at_head(data);
			return;
		}
		else if (pos == head->num_of_elem +1) {
			insert_at_tail(data);
			return;
		}
		node* temp = head->first;
		while (pos != 2) {
			temp = temp->next;
			pos--;
		}
		node* newnode = (node*)malloc(sizeof(node));
		newnode->data = data;
		newnode->prev = temp;
		newnode->next = temp->next;
		temp->next->prev = newnode;
		temp->next = newnode;
		head->num_of_elem++;
	}
}
//delete first node after header
void DeleteFirst() {
	if (head == NULL) {
		printf("Header not created\n");
		return;
	}
	else if (head->first == head) {
		printf("list is empty\n");
		return;
	}
	else{
		node* temp = head->first;
		head->first = head->first->next;
		free(temp);
		head->first->prev = head;
		head->num_of_elem--;
	}
}
//delete last node
void DeleteLast() {
	if (head == NULL) {
		printf("Header not created\n");
		return;
	}
	else if (head->last == head) {
		printf("list is empty\n");
		return;
	}
	else {
		node* temp = head->last;
		head->last = head->last->prev;
		free(temp);
		head->last->next = head;
		head->num_of_elem--;
	}
}
//delete node at given position
void DeleteAtPos(int pos) {
	if (head == NULL) {
		printf("Header not created\n");
		return;
	}
	else if (head->first == head) {
		printf("list is empty\n");
		return;
	}
	else {
		if (pos > head->num_of_elem || pos < 1) {
			printf("Invalid input...\n");
			return;
		}
		else if (pos == 1) {
			DeleteFirst();
			return;
		}
		else if (pos == head->num_of_elem) {
			DeleteLast();
			return;
		}
		node* temp = head->first;
		while (pos != 1) {
			temp = temp->next;
			pos--;
		}
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		free(temp);
		head->num_of_elem--;
	}
}
//This function frees linked list but doesnt delete header file
void FreeLinkedList() {
	node* current = head->first;
	node* next;
	while (current != head) {
		next = current->next; //save the next pointer before freeing the current node
		free(current); //free the current node
		current = next; //move to the next node
	}
	head->num_of_elem = 0;
	head->first = head;
	head->last = head;
}
//print elements of list
void PrintList() {
	if (head == NULL) {
		printf("Header not created\n");
		return;
	}
	printf("---------------------------\n");
	node* ptr = head->first;
	printf("Number of elements: %d\n", head->num_of_elem);
	while (ptr != head) {
		printf("%d ", ptr->data);
		ptr = ptr->next;
		
	}
	printf("\n---------------------------\n");
}
int main() {
	int choice;
	int data;
	int pos;
	CreateHeader();
	insert_at_head(4);
	insert_at_head(6);
	insert_at_tail(7);
	insert_at_tail(9);
	insert_at_pos(5, 10);
	insert_at_pos(5, 14);
	
	printf("Current list:\n");
	PrintList();

	do {
		printf("\n");
		printf("Choose an option:\n");
		printf("1)Add at end\n");
		printf("2)Add at beginning\n");
		printf("3)Add at given position\n");
		printf("4)Delete last\n");
		printf("5)Delete first\n");
		printf("6)Delete at given position\n");
		printf("7)Free list\n");
		printf("8)Print list\n");
		printf("9)Exit\n");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			printf("Number:\n");
			scanf("%d", &data);
			insert_at_tail(data);
			break;
		case 2:
			printf("Number:\n");
			scanf("%d", &data);
			insert_at_head(data);
			break;
		case 3:
			printf("Number:\n");
			scanf("%d", &data);
			printf("Position:\n");
			scanf("%d", &pos);
			insert_at_pos(pos,data);
			break;
		case 4:
			DeleteLast();
			break;
		case 5:
			DeleteFirst();
			break;
		case 6:
			printf("Position:\n");
			scanf("%d", &pos);
			DeleteAtPos(pos);
			break;
		case 7:
			FreeLinkedList();
			break;
		case 8:
			PrintList();
			break;
		}
	} while (choice != 9);

	return 0;
}

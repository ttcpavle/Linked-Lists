/*
=============================================================================================
PROJECT: Polynomials as linked list and operations
FILE: Polynomials.c
NOTE: more information in README.md
DATE:   4.5.2024
AUTHOR: Pavle Totic
=============================================================================================
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int c;
	int exp;
	struct node* next;
}node;

node* CreateHeaderP() {
	node* header = (node*)malloc(sizeof(node));
	header->c = 0;
	header->exp = -1;//used to distinct header of polynomial
	header->next = header;//points to itself by default
	return header;
}
//insert at end of polynomial. SortedInsert recommended!
void Insert(node* p, int c, int exp) {
	node* newnode = (node*)malloc(sizeof(node));
	newnode->c = c;
	newnode->exp = exp;
	if (p->next == p) {
		newnode->next = p;
		p->next = newnode;
	}
	else {		
		node* current = p->next;
		node* prev = p;
		while (current->exp != -1) {
			prev = current;
			current = current->next;
		}
		prev->next = newnode;
		newnode->next = p;
	}
}
//inserts new element into polynomial. Polynomial always stays sorted.
void SortedInsert(node* p, int c, int exp) {
	if (p->next == p) {
		//if empty
		node* newnode = (node*)malloc(sizeof(node));
		newnode->c = c;
		newnode->exp = exp;
		newnode->next = p;
		p->next = newnode;
	}
	else if (exp > p->next->exp) {
		//if given exp is the largest > insert at beginning
		node* newnode = (node*)malloc(sizeof(node));
		newnode->c = c;
		newnode->exp = exp;
		newnode->next = p->next;
		p->next = newnode;

	}
	else {
		//insert at right location
		node* current = p->next;
		node* prev = p;
		while (current->exp >= exp && current->exp != -1) {
			prev = current;
			current = current->next;
			if (prev->exp == exp) {
				//merge with existing element if exp is the same
				prev->c += c;
				return;
			}
		}
		node* newnode = (node*)malloc(sizeof(node));
		newnode->c = c;
		newnode->exp = exp;
		prev->next = newnode;
		newnode->next = current;
	}
}

//add 2 polynomials (new = p1+p2)
node* PolyAdd(node* p1, node* p2) {
	node* r = CreateHeaderP();
	node* p = p1->next;
	node* q = p2->next;
	while (p != p1 || q != p2) {
		if (p->exp == q->exp) {
			if(p->c + q->c != 0)
			    SortedInsert(r, p->c + q->c, p->exp);
			p = p->next;
			q = q->next;
		}
		else if (p->exp < q->exp) {
			SortedInsert(r, q->c, q->exp);
			q = q->next;
		}
		else {
			SortedInsert(r, p->c, p->exp);
			p = p->next;
		}
		
	}
	return r;
}
//substract p2 from p1 (new = p1-p2)
node* PolySubstract(node* p1, node* p2) {
	node* r = CreateHeaderP();
	node* p = p1->next;
	node* q = p2->next;
	while (p != p1 || q != p2) {
		if (p->exp == q->exp) {
			if (p->c - q->c != 0)
				SortedInsert(r, p->c - q->c, p->exp);
			p = p->next;
			q = q->next;
		}
		else if (p->exp < q->exp) {
			SortedInsert(r, -q->c, q->exp);
			q = q->next;
		}
		else {
			SortedInsert(r, p->c, p->exp);
			p = p->next;
		}

	}
	return r;
}
//multiply 2 polynomials (new = p1*p2)
node* PolyMultiply(node* p1, node* p2) {
	node* r = CreateHeaderP();
	node* p = p1->next;//first element that is not header
	node* q = p2->next;
	while (q != p2) {
		while (p != p1) {
			//traverse through all p
			SortedInsert(r, (p->c)*(q->c), p->exp + q->exp);
			p = p->next;
		}
		p = p1->next;//reset first
		q = q->next;//move to next
	}
	return r;
}
void PrintPolynomial(node* p) {	
	if (p->next == p) {
		printf("empty\n");
		return;
	}
	node* temp = p->next;
	while (temp->exp != -1) {
		if (temp->exp == 0) {
			printf("%d", temp->c);
		}
		else {
			printf("%d(x^%d)", temp->c, temp->exp);
		}
		temp = temp->next;
		if (temp->exp != -1) {
			if (temp->c > 0){
				printf("+");
			}
		}
	}
	printf("\n");
}

int main() {
	node* p1 = CreateHeaderP();//first polynomial p1
	node* p2 = CreateHeaderP();//second polynomial p2
	
	SortedInsert(p1, 3, 7);
	SortedInsert(p1, -2, 2);
	SortedInsert(p1, 7, 5);

	SortedInsert(p2, -1, 0);
	SortedInsert(p2, 2, 8);
	SortedInsert(p2, 3, 2);

	node* n = PolyAdd(p1, p2);
	node* r = PolySubstract(p1, p2);
	node* k = PolyMultiply(p1, p2);

	printf("Polynomial    p1: ");
	PrintPolynomial(p1);
	printf("Polynomial    p2: ");
	PrintPolynomial(p2);
	printf("Polynomial p1+p2: ");
	PrintPolynomial(n);
	printf("Polynomial p1-p2: ");
	PrintPolynomial(r);
	printf("Polynomial p1*p2: ");
	PrintPolynomial(k);
	return 0;
}

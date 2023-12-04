#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *next;
};

typedef struct node node;
node *head;
void insert_end(){
	int data;
	node *temp,*pre;

	printf("\n Enteer the value : ");
	scanf("%d",&data);

	temp=(node*)malloc(sizeof(node));
	temp->data=data;

	if (head == NULL){
		head=temp;
		head->next=NULL;
	}
	  else { 
		pre =head;
		while (pre->next != NULL) {
			pre=pre->next;
		}

		pre->next=temp;
		temp->next=NULL;
		}
	
	}
void insert_first(){
	int data;
	node *temp;

	printf("\n Enter the value to inserted :");
	scanf("%d",&data);

	temp=(node*)malloc(sizeof(node));
	temp->data=data;

	if (head == NULL) {
		head=temp;
		head->next=NULL;
	}
	  else {
			temp->next=head;
			head=temp;
		}
  }

 void insert_pos(){
	int data;
	int pos;
	int count=2;
	node *temp,*pre;
	printf("/n Enter the value to be inserted :");
	scanf("%d",&data);
	printf("/n enter the position to be inserted : ");
	scanf("%d",&pos);
	temp=head;
	pre=(node*)malloc(sizeof(node));
	pre->data=data;

	if ( head ==NULL) {
		pirntf("\n List is empty \n");
	}
	else if (pos == 1) {
		pre->next=head;
		head=pre;
	}
	else {
		temp=head;
		while(temp->next != NULL){
		if (pos==count){
			pre->next=temp->next;
			temp->next=pre;
			break;
		}
		else { 
			temp=temp->next;
			count++;
		}
	}
	}
}

	void display(){
		node  *temp;
		int data;
		int flag=0;
		int count=1;
		temp=head;
		printf("Enter the element to seaerch :");
		scanf("%d",&data);
		
		if (head== NULL) {
			printf("\n List is empty\n");
		}
		else{
			while(temp->next!=NULL){
				printf("List [%d] : %d \n",count,temp->data);
	}
	}

	
	void search(){
	int data;
	node *temp;
	int count = 1;
	temp=head;
	int flag=0;
	printf("/n Enter the element  to search  :");
	scanf("%d",&data);

	if (head == NULL ) {
		printf(" \n LIST IS  EMPTY \n");
		
	}
	else {
	while(temp->next !=NULL){
		if (data == temp->data){
			flag=1;
			break;
		}
		temp=temp->next;
		count++;
	}
	if(temp->data == data) {
		flag=1;
	 
	     if ( flag==1) {
	printf("\n FOUUND ");
	}
	else {
		printf("\n not found \n:");
	}
}
}

/*	void delete();
		node *temp;
		if (head == NULL) {
		printf("List is empty");
		}
}*/
int main() {
	int option;
	do {
		printf("\n1) insert the first ");
		printf("\n 2)insert the end \n");
		printf("\n 3)inset @ a position ");
		printf("\n 4)display");
		printf("\n 5)search ");
		printf("\n 6)delete ");
		printf("\n qiet ");
		printf("\n choose ption :");
		scanf("%d",&option){


		switch(opt) {
			case 1:
				insert_first();
				break;
			case2:
				insert_end();
				break;
			case 3:
				insert_pos();
				break;
			case 4:
				display()
				break;
			case 5: 		
				search();
				break;
			case 6:
				delete();
				break;
			default:
				printf("\n invalid option try again ...");
	}while (opt!=0);
	return 0;
}

	






	


































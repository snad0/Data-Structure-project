#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define size 2

struct node{
    int reg_no;
    int age;
    int seates;
    char name[25];
    struct node * next;
};
struct node *front;
struct node *rear;

// Declaring variables globally
int seates_num=100;
struct node* deq();
int create();
int reserve(struct node*);
int cancel(int);
void enq(struct node*);
void display();
struct node *start;
int count=0;
int num=0;

int create(){
    struct node* new;
    new= (struct node *)malloc(sizeof(struct node));
    new->reg_no=1;
    printf("Enter name: ");
    scanf("\n");
    gets(new->name);
    // puts(new->name);mmm
    printf("Age: ");
    scanf("%d",&new->age);
    if(new->age>=90 || new->age<=10) {
        free(new);
        return -1;
    }
    printf("Number of seates required:");
    scanf("%d",&new->seates);
    if(new->seates >seates_num) {
        return -2;
    }
    else{
        seates_num=seates_num-new->seates;

    }

    start=new;
    new->next=NULL;
    num++;
    return 1;
    // printf("%s", new->name);
    // printf("%d", new->age);
};


int reserve(struct node *start)
{
	int temp;
	if(start==NULL)
	{   
   		temp = create(start);
		return temp;
	}
	else 
	{
	
	struct node *temp, *new_node;
	temp=start;
	while(temp->next!=NULL)
	{ 
	  temp=temp->next;
	}
	
	new_node=(struct node *)malloc(sizeof(struct node));
	
	printf("Enter Name: ");
	scanf("\n");
    gets(new_node->name);
	printf("Age : ");
	scanf("%d", &new_node->age);
    if(new_node->age >=90 || new_node->age<=10) {
        return -1;
    }
    printf("Number of seates required:");
    scanf("%d",&new_node->seates);
    if(new_node->seates >seates_num) {
        return -2;
    }
    else{
        seates_num=seates_num-new_node->seates;

    }
	new_node->next=NULL;
	if(num<=size)
	{
		num++;
		new_node->reg_no=num;
		temp->next=new_node;
		
		return 1;
	}
	else
	{
		enq(new_node);
		return 0;
	}
}
}
int cancel(int reg)
{
	struct node *ptr, *preptr, *new;
	ptr=start;
	preptr=NULL;
	if(start==NULL)
	return -1;
	if(ptr->next==NULL && ptr->reg_no==reg)
		{
		start=NULL;
		num--;
		free(ptr);
		return 1;
		
		}
		
	else{	
	while(ptr->reg_no!=reg && ptr->next!=NULL)
		{
			preptr=ptr;
			ptr=ptr->next;
		}
		if(ptr==NULL && ptr->reg_no!=reg)
			return -1;
		else
			preptr->next=ptr->next;
		free(ptr);
		new=deq();
		while(preptr->next!=NULL)
			preptr=preptr->next;
		preptr->next=new;
		num--;
		return 1;
	
	}
}

void enq(struct node *new_node)
{
	if(rear==NULL)
	{
		rear=new_node;
		rear->next=NULL;
		front=rear;
	}
	else
	{
		struct node *temp;
		temp=new_node;
		rear->next=temp;
		temp->next=NULL;
		rear=temp;
	}
	count++;
}

struct node* deq()
{
	struct node *front1;
	front1=front;
	if(front==NULL)
		return NULL;
	else
	{
	    count-- ;
		if(front->next!=NULL)
		{
			front=front->next;
			front1->next=NULL;
			return front1;
		}
		else
		{
			front=NULL;
			rear=NULL;
			
			return front1;
		}
	}	
}


void display()
{
	struct node *temp;
	temp=start;
	while(temp!=NULL)
	{
		printf("\nRegistration Number: %d\n", temp->reg_no);
		printf("Name : %s\nAge: %d\nSeates booked: %d\n", temp->name,temp->age,temp->seates);
		temp=temp->next;
    }
    printf("Seates left=%d\n",seates_num);

    
}

int main(){
int choice, status=0,canc=0, reg=0;
	start=NULL;
	rear=NULL;
	front=NULL;
	
	
	
	printf("\n\t\t\t**RAILWAY RESERVATION**\t\t\t\t\n");
	int ch =0;
	while(ch!=4)
	{
	printf("\nDo you want to - \n 1. Book a ticket \n 2. Cancel Booking \n 3. Display passenger details \n 4. exit\n\n");
	scanf("%d", &choice); 
	switch(choice)
	{	
		case 1 :  status=reserve(start);
	              if(status==0)
	                printf("\nBooking Full!! \nYou are added to waiting list. Waiting list number %d", count);
	              else if(status == -1) {
                      printf("\n age not eligible");
                  }
	              else if(status == -2) {
                      printf("\nSorry we dont have this much seates\nremaining seates are: %d\n\n",seates_num);
                  }
                  else
	                printf(" \nBooking Successful!!! Enjoy your journey! Your Reg No is %d\n\n", num);
	                
	              break;
	        
	    case 2:   printf(" \n Give the Registration number to be cancelled\n");
	              scanf(" %d", &reg);
	              if(reg>num)
	              printf("Invalid!!");
	              else
	              {
	              canc=cancel(reg);
	              if(canc==-1)
	              	printf("\nRegistration number invalid!!\n");
	              else
	              	printf("\nRegistration cancelled successfully\n");
	              	}
	              break;
	              
	    case 3: display();
	    break;
	    case 4: exit(0);   
	    break;
	    default: printf("\nWrong choice!\n");       
	              
	                 
		          
	
	}
	
}
};
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct list{
	int data;
	struct list *addr;
}number;

number* cNode()
{
	return (number *)malloc(sizeof(number));
}

number* int2num(long x)
{

	number *head = cNode(),*temp = NULL,*t_head = NULL;
	t_head=head;
	head->data = x%10;
	head->addr = NULL;
	x/=10;
	while(x!=0)
	{
		temp = cNode();
		temp->data = x%10;
		temp->addr = NULL;
		t_head->addr = temp;
		t_head = temp;
		x/=10;
	}
	return head;

}

void fact_number(number *stnum,long num)
{
	int carry,product;
	number *temp,*dtemp;
	carry = 0;
	while(num!=1)
	{
		temp = stnum;
		num-=1;
		while(temp!=NULL)
		{
			product = (temp->data)*num + carry;
			temp->data = product%10;
			carry = product/10;

			if(temp->addr==NULL && carry!=0)
			{
				dtemp = temp;
				while(carry!=0)
				{
					dtemp = cNode();
					dtemp->data = carry%10;
					dtemp->addr = NULL;
					carry/=10;
					temp->addr = dtemp;
					temp = dtemp;
				}
				temp = temp->addr;
			}
			else
				temp = temp->addr;
		}
	}
}

void shownum(number *head)
{
	while(head!=NULL){
		printf("%d",head->data);
		head=head->addr;
	}
	printf("\n");
	return;
}

void revlist(number **num)
{
	number *temp = *num,*dtemp = NULL,*ctemp = NULL;
	int x=1;
	dtemp = temp->addr;
	while(dtemp!=NULL)
	{
		ctemp = dtemp->addr;
		dtemp->addr = temp;
		temp = dtemp;
		dtemp = ctemp;
	}
	(*num)->addr = NULL;
	(*num) = temp;
}

int main()
{
	long num;
	clock_t start;
	float time_taken;
	printf("Enter a number: ");
	scanf("%ld",&num);

	printf("Entered Number: %ld\n",num);

	start = clock();
	
	number *onum = int2num(num);
	fact_number(onum,num);

	time_taken = (float)(clock() - start)/(float)CLOCKS_PER_SEC;	
	revlist(&onum);
	printf("%ld! = ",num);
	shownum(onum);
	printf("\nTime Taken: %lfs\n",(float)time_taken);

	return 0;
}

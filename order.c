/* this is a profgram to store numbers in bitwise numbers	
   by adithya.s.k*/
#include<stdio.h>
#include<stdlib.h>
struct NODE
{
	int offset;
	int a[4];
	struct NODE *link;
};
typedef struct NODE *node;
node insert(node,int,int);
node getnode(int );
void set(int,node);
node clone(node,node);
node search(node,node);
node Union(node,node,node);
node intersection(node,node,node);
node subtract(node,node,node);
void display(node);
void main()
{
	int n,i,m,ch;
	scanf("%d",&n);
	node cust[10],un=NULL,temp,inter=NULL,dif=NULL;
	for(i=0;i<n;i++)
		cust[i]=NULL;
	for(i=0;i<n;i++)
	{
		while(1)
		{
			scanf("%d",&m);
			if(m>=1280)
				break;//terminating condition
			ch=m/128;
			switch(ch)
			{
				 case 0: 
				 case 1:
				 case 2:
				 case 3:
				 case 4:
				 case 5:
				 case 6:
				 case 7:
				 case 8:
				 case 9:cust[i]=insert(cust[i],m,127+ch*128);//gives the position to insert
					break;
				default:exit(0);
			}
		}
	}
	un=Union(cust[0],cust[1],un);
	display(un);
	inter=intersection(cust[0],cust[1],inter);
	display(inter);
	dif=subtract(cust[0],cust[1],dif);
	display(dif);
}
node getnode(int offset)
{
	int i;				
	node x=(node)malloc(sizeof(struct NODE));
	x->offset=offset;
	x->link=NULL;
	for(i=0;i<4;i++)
		x->a[i]=0;
	return x;
}
node insert(node root,int m,int offset)
{
	node temp,prev;
	if(root==NULL)
	{
		root=getnode(offset);
		set(m%128,root);//each node has 4 integers
		return root;
	}
	temp=root;
	while(temp!=NULL)
	{
		prev=temp;
		if(temp->offset==offset)
		{
			set(m%128,temp);
			return root;
		}
		temp=temp->link;
	}
	node x=getnode(offset);
	set(m%128,x);
	prev->link=x;
	return root;
}
void set(int m,node root)
{
	int x=m/32;
	int y=m%32;
	if(y==0||y==1)
		y++;//else gives erroneous results
	root->a[x]=(root->a[x])|(1<<(y-1));//to set the required position to 1

}
node clone( node root,node temp1)//creates a clone of the node and assigns it to the end of the list.works like insert rear.
{
	int i;
	node x=getnode(temp1->offset);
	node temp=root,prev;//does not represent the original nodes
	for(i=0;i<4;i++)
		x->a[i]=temp1->a[i];
	if(root==NULL)
		return x;
	while(temp!=NULL)
	{
		prev=temp;
		temp=temp->link;
	}
	prev->link=x;
	return root;
}
node search(node root,node temp)
{
	while(root!=NULL)
	{
		if(root->offset==temp->offset)
			return root;
		root=root->link;
	}
	return NULL;
}
node Union(node root1,node root2,node root)
{
	node temp=root1;
	int i;
	while(temp!=NULL)
	{
		root=clone(root,temp);
		temp=temp->link;
	}
	temp=root2;
	while(temp!=NULL)	
	{
		node x=search(root,temp);
		if(x==NULL)
			root=clone(root,temp);//copy elements of A
		else
			for(i=0;i<4;i++)
				x->a[i]=(x->a[i])|(temp->a[i]);
		temp=temp->link;
	}
	return root;
}
node intersection(node root1,node root2,node root)
{
	node x,temp=root1,nod;
	int i,test;
	while(temp!=NULL)
	{
		x=search(root2,temp);
		if(x!=NULL)
		{
			test=0;	
			nod=getnode(temp->offset);
			for(i=0;i<4;i++)
			{
				nod->a[i]=(x->a[i])&(temp->a[i]);
				if(nod->a[i]>0)
					test=1;
			}
			if(test==1)
				root=clone(root,nod);
			free(nod);
		}
		temp=temp->link;
	}
	return root;
}
node subtract(node root1,node root2,node root)
{
	node inter=intersection(root1,root2,root);
	node temp=root1,x;
	int i;
	while(temp!=NULL)
	{
		root=clone(root,temp);
		temp=temp->link;
	}
	temp=inter;
	while(temp!=NULL)
	{
		x=search(root,temp);
		if(x!=NULL)
		{
			for(i=0;i<4;i++)
				x->a[i]=(x->a[i])^(temp->a[i]);
		}
		temp=temp->link;
	}
	return root;
}
void display(node root)
{
	int i,j,count,test=0,num;
	while(root!=NULL)
	{
		for(i=0;i<4;i++)
		{
			if(root->a[i]>0)
			{
				num=root->a[i];
				count=0;
				for(j=0;j<32;j++)
				{
					if(num%2==0)
					{
						count++;`
						num=num>>1;
					}
					else
					{
						num=num>>1;
						printf("%d ",count+32*i+((root->offset)/128)*128);
						count++;
						if(num==0)
							break;
					}
				}
			}
		}
		root=root->link;
	}
	printf("\n");
}	

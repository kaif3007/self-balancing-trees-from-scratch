#include<bits/stdc++.h>
using namespace std;

struct node
{
	int data;
	node* left;
	node* right;
	node* parent;
	bool colour;
};

node* createnode(int dat)
{
node* temp=new node;
temp->data=dat;
temp->left=NULL;
temp->right=NULL;
temp->parent=NULL;	
temp->colour=0;
return temp;
}

node* insert(node* root,node* &p)
{
	if(root==NULL)
	return p;
	
	else if(root->data>p->data)
	{root->left=insert(root->left,p);
	root->left->parent=root;
    }
    
    else if(root->data<=p->data)
    {root->right=insert(root->right,p);
	root->right->parent=root;
    }
    
    return root;
}

void rightrot(node* &root,node* &pt)
{
	node* temp=pt->left;
	pt->left=temp->right;
	
	if(pt->left!=NULL)
	pt->left->parent=pt;
	
	temp->parent=pt->parent;
	
	if(pt->parent==NULL)
	root=temp;
	
	else if(pt==pt->parent->left)
	pt->parent->left=temp;
	
	else
	pt->parent->right=temp;
	
	temp->right=pt;
	pt->parent=temp;
}


void leftrot(node* &root,node* &pt)
{
	node* temp=pt->right;
	pt->right=temp->left;
	
	if(pt->right!=NULL)
	pt->right->parent=pt;
	
	temp->parent=pt->parent;
	if(pt->parent==NULL)
	root=temp;
	
	else if(pt==pt->parent->right)
	pt->parent->right=temp;
	
	else
	pt->parent->left=temp;
	
	temp->left=pt;
	pt->parent=temp;
}

void fixviolation(node* &root,node* &p)
{
	node* papa=NULL;
	node* dada=NULL;
	while((p!=root)&&(p->colour!=1)&&(p->parent->colour==0))
	{
		papa=p->parent;
		dada=p->parent->parent;
		if(papa==dada->left)
		{
			node* uncle=dada->right;
			if(uncle!=NULL && uncle->colour==0)
			{
				dada->colour=0;
				papa->colour=1;
				uncle->colour=1;
				p=dada;
			}
			else if(p==papa->right)
			{
				leftrot(root,papa);
				p=papa;
				papa=p->parent;
			}
			else if(p==papa->left)
			{
				rightrot(root,dada);
				if(dada->colour==0)
				dada->colour=1;
				else
				dada->colour=0;
				
				if(papa->colour==0)
				papa->colour=1;
				else
				papa->colour=0;
				p=papa;
			}
		}
		
		else
		{
			node* uncle=dada->left;
			if(uncle!=NULL && uncle->colour==0)
			{
				dada->colour=0;
				papa->colour=1;
				uncle->colour=1;
				p=dada;
			}
			else if(p==papa->left)
			{
				rightrot(root,papa);
				p=papa;
				papa=p->parent;
			}
			else if(p==papa->right)
			{
				leftrot(root,dada);
				if(dada->colour==0)
				dada->colour=1;
				else
				dada->colour=0;
				
				if(papa->colour==0)
				papa->colour=1;
				else
				papa->colour=0;
				p=papa;
			}
		}
	}
	root->colour=1;
}

void insertrb(node* &root,int dat)
{
	node* temp=createnode(dat);
	root=insert(root,temp);
	
	fixviolation(root,temp);
}

void inorder(node* root)
{
	if(root==NULL)
	return;
	inorder(root->left);
	cout<<root->data<<"_"<<root->colour<<" ";
	inorder(root->right);
}


int main()
{node* root=NULL;
insertrb(root,9);
insertrb(root,5);
insertrb(root,10);
insertrb(root,0);
insertrb(root,6);
insertrb(root,11);
insertrb(root,11);
insertrb(root,-1);
insertrb(root,1);
insertrb(root,2);


inorder(root);
	
	return 0;
}

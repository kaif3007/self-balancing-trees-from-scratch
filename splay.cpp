#include<bits/stdc++.h>


using namespace std;

struct node
{
int data;
node* left;
node* right;	
};

node* create(int dat)
{
	node* temp=new node;
	temp->data=dat;
	temp->left=NULL;
	temp->right=NULL;
}

node* rightrot(node* p)
{
	node* y=p->left;
	p->left=y->right;
	y->right=p;
	
	return y;
}

node* leftrot(node* p)
{
	node* y=p->right;
	p->right=y->left;
	y->left=p;
	
	return y;
}

node* splay(node* root,int data)
{
	if(root==NULL || root->data==data)
	return root;
	
	if(root->data>data)
	{
		if(root->left==NULL)
		return root;
		
		if(root->left->data>data)
		{
			root->left->left=splay(root->left->left,data);
			root=rightrot(root);
			
		}
		else if(root->left->data<data)
		{
			root->left->right=splay(root->left->right,data);
			
			if(root->left->right!=NULL)
			root->left=leftrot(root->left);
     	}
     	
     	if(root->left==NULL)
     	return root;         //takes care if no value is found return last nnode prior to null
     	
     	else
     	return rightrot(root);       //handles case of no grandparent .
	}
	else
	if(root->right==NULL)
		return root;
		
		if(root->right->data<data)
		{
			root->right->right=splay(root->right->right,data);
			root=leftrot(root);
		}
		else if(root->right->data>data)
		{
			root->right->left=splay(root->right->left,data);
			
			if(root->right->left!=NULL)
			root->right=rightrot(root->right);
     	}
     	
     	if(root->right==NULL)
     	return root;
     	
     	else
     	return leftrot(root);
	
}

node* insert(node* root,int k)
{
	if(root==NULL)
	return create(k);
	
	root=splay(root,k);
	
	if(root->data==k)
	return root;
	
	node* temp=create(k);
	
	if(root->data>k)
	{
		temp->right=root;
		temp->left=root->left;
		root->left=NULL;
		
	}
	else
	{
		temp->left=root;
		temp->right=root->right;
		root->right=NULL;
   }
	return temp;
}

node* deletee(node* root,int key)
{
	if(root==NULL)
	return root;
	
	root=splay(root,key);
	
	if(root->data!=key)
	return root;
	
	if(root->left==NULL)
	{
		node* temp=root->right;
		free(root);
		return temp;
	}
	
	else
	{
		node* temp=root;
		root=splay(root->left,key);
		
		root->right=temp->right;
		
		free(temp);
		return root;
		
	}
}

void pre(node* root)
{ if(root==NULL)
return;
	cout<<root->data<<" ";
	pre(root->left);
	pre(root->right);
}


int main()
{ node *root = NULL;
root=insert(root,90);
root=insert(root,290);
root=insert(root,40);
root=insert(root,20);
root=insert(root,10);
    
    pre(root);
    cout<<endl;
    root=deletee(root,40);
    pre(root);
	return 0;
}




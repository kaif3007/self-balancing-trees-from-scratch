#include <bits/stdc++.h>

using namespace std;
 struct node
 {  
 	int data;
 	int height;
 	node* left; 
 	node* right;
 };

node* makenode(int data)
{
	node*temp=new node;
	temp->data=data;
	temp->left=NULL;
	temp->right=NULL;
	temp->height=1; 
	return temp;
}


int height(node*n)
{
	if(n==NULL)
	return 0;
	
	return n->height;
}

int balance(node*n)
{
	return (height(n->left)-height(n->right));
}

node* rightrotate(node* root)
{
	node*x=root->left;
	node*y=x->right;
	
	x->right=root;                                                    //rightrotation algo;
	root->left=y;
	
	
	root->height=1+max(height(root->left),height(root->right));
	x->height=1+max(height(x->left),height(x->right));
	
	return x;
}

node* leftrotate(node* root)
{
	node*x=root->right;
	node*y=x->left;
	
	x->left=root;
	root->right=y;
	
	                                                                                    //leftrotation algo
	root->height=1+max(height(root->left),height(root->right));
	x->height=1+max(height(x->left),height(x->right));
	
	return x;
}

node *avl(node*root,int data)
{
	if(root==NULL)
	return makenode(data);
	
	if(root->data>data)
	root->left=avl(root->left,data);
	
	if(root->data<data)
	root->right=avl(root->right,data);
	
	if(root->data==data)
	return root;
	
	root->height=1+max(height(root->left),height(root->right));
	
	int b=balance(root);
	
	if(b>1 && data<root->left->data)
	return rightrotate(root);
	if(b<-1 && data>root->right->data)
	return leftrotate(root);
	if(b>1 && data>root->left->data)
	{
		root->left=leftrotate(root->left);
		return rightrotate(root);                                  //four different cases ll rr lr rl;
	}
	if(b<-1 && data<root->right->data)
	{
		root->right=rightrotate(root->right);
		return leftrotate(root);
	}
	return root;
}


node* deleteavl(node* head,int data)
{if(head==NULL)
return head;

if	(head->data>data)
head->left=deleteavl(head->left,data);

if(head->data<data)
head->right=deleteavl(head->right,data);

if(head->data==data)
{
  if(head->right==NULL)
  { node*temp=head->left;
  free(head);
  return temp;
	}
	
	else if(head->left==NULL)
  { node*temp=head->right;
  free(head);
  return temp;
	 }
	 
	 else
	 {node*temp=head->right;
	 	while(temp->left!=NULL)
	 	temp=temp->left;
	 	
	 	head->data=temp->data;
	 	head->right=deleteavl(head->right,temp->data);
	 }
	 
	 if(head==NULL)
       return head;	 
       

	 	head->height=1+max(height(head->left),height(head->right));
}
	int b=balance(head);
	
	if(b>1 && balance(head->left)>=0)
	return rightrotate(head);
	if(b<-1 && balance(head->right)<=0)
	return leftrotate(head);
	if(b>1 && balance(head->left)<0)
	{
		head->left=leftrotate(head->left);
		return rightrotate(head);                                  //four different cases ll rr lr rl;
	}
	if(b<-1 && balance(head->right)>0)
	{
		head->right=rightrotate(head->right);
		return leftrotate(head);
	}
	
	
	return head;
}


void inorder(node*head)
{
	if(head==NULL)
	return;
	else
	{
		inorder(head->left);
		cout<<head->data<<" ";                                                       
		inorder(head->right);
	}
}


int main() 
{ node *root = NULL;
 
    root = avl(root, 9);
    root = avl(root, 5);
    root = avl(root, 10);
    root = avl(root, 0);
    root = avl(root, 6);
    root = avl(root, 11);
    root = avl(root, -1);
    root = avl(root, 1);
    root = avl(root, 2);
    
    
    //root=deleteavl(root,1);
     inorder(root);
 
 
	return 0;
}

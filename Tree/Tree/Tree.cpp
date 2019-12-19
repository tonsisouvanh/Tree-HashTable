#include <iostream>
#include<windows.h>
using namespace std;
#define COUNT 10
struct Node {
	int		data;
	Node* left;
	Node* right;
};


Node* createNode(int data)
{
	Node* node = new Node();
	node->left = NULL;
	node->right = NULL;
	node->data = data;
	return node;
}
// insert
void insertNode(Node*& root, int data)
{
	if (root == NULL)
		root = createNode(data);
	else if (data <= root->data)
	{
		insertNode(root->left, data);
	}
	else
	{
		insertNode(root->right, data);
	}
}
//LRN - postorder
void LRN(Node* root)
{
	if (root == NULL)
		return;

	LRN(root->left);
	LRN(root->right);
	cout << root->data << " ";
}

//NLR - preorder
void NLR(Node* root)
{
	if (root != NULL)
	{
		cout << root->data << "\n";
		NLR(root->left);
		NLR(root->right);
	}
}
//LNR - inorder
void LNR(Node* root)
{
	if (root != NULL)
	{
		LNR(root->left);
		cout << root->data << "\n";
		LNR(root->right);
	}
}
//search node
Node* searchNode(Node* root, int x)
{
	if (root == NULL)
		return NULL;
	else if (root->data == x)
		return root;
	else if (x < root->data)
		searchNode(root->left, x);
	else
		searchNode(root->right, x);
}

int maxDepth(Node* node)
{
	if (node == NULL)
		return 0;
	else
	{
		/* compute the depth of each subtree */
		int lDepth = maxDepth(node->left);
		int rDepth = maxDepth(node->right);

		/* use the larger one */
		if (lDepth > rDepth)
			return(lDepth + 1);
		else return(rDepth + 1);
	}
}
//find min
Node* findMin(Node* root)
{
	while (root->left != NULL)
	{
		root = root->left;
	}
	return root;
}
// delete bst
void deleteBST(Node*& root, int x)
{
	if (root == NULL)	//case not find del node
		root = NULL;
	else if (x < root->data)	//del node data < 
		deleteBST(root->left, x);
	else if (x > root->data)
		deleteBST(root->right, x);
	else
	{
		if (root->left == NULL && root->right == NULL)
		{
			delete root;
			root = NULL;
		}
		else if (root->left == NULL)
		{
			Node* tmp = root;
			root = root->right;
			delete tmp;
		}
		else if (root->right == NULL)
		{
			Node* tmp = root;
			root = root->left;
			delete tmp;
		}
		else
		{
			Node* min = findMin(root->right);
			root->data = min->data;
			deleteBST(root->right, min->data);
		}
	}
}
// find height
int FindHeight(Node* root)
{
	if (root == NULL) return -1;
	else
	{
		int lb = FindHeight(root->left);
		int rb = FindHeight(root->right);

		return max(lb, rb) + 1;

	}
}
// Is tree bst
bool isLesserSubTree(Node* root, int data)
{
	if (root == NULL)
		return true;
	else
	{
		if (root->data <= data
			&& isLesserSubTree(root->left, data)
			&& isLesserSubTree(root->right, data))
			return true;
		else
			return false;
	}
}

bool isGreatersubTree(Node* root,int data)
{
	if (root == NULL)
		return true;
	else
	{
		if (root->data > data
			&& isGreatersubTree(root->left, data)
			&& isGreatersubTree(root->right, data))
			return true;
		else
			return false;
	}
}

bool IsBST(Node* root)
{
	if (root == NULL) return true;
	else
	{
		if (isLesserSubTree(root->left, root->data)
			&& isGreatersubTree(root->right, root->data)
			&& IsBST(root->left)
			&& IsBST(root->right))
			return true;
		else
			return false;
	}
}
//count Node
int CountNode(Node* root)
{
	int c = 0;
	if (root != NULL)
	{
		c++;
		c = c + CountNode(root->left);
		c += CountNode(root->right);
	}
	return c;
}

int main()
{
	Node* root = NULL;

	insertNode(root, 10);
	insertNode(root, 5);
	insertNode(root, 20);
	insertNode(root, -10);
	insertNode(root, -20);

	//deleteBST(root, 10);

	//root->left->left->data = 6;

	//find Node
	//Node* find = searchNode(root, 10);
	//if (find != NULL)
	//	cout << find->data << endl;
	//else if (find == NULL)
	//	cout << "Not found" << endl;
	//cout << maxDepth(root) << endl;
	//root->left->left = 

	LNR(root);
	cout << "Height: " << FindHeight(root) << endl;
	if (IsBST(root))
		cout << "This tree is BST" << endl;
	else
		cout << "This tree is not BST" << endl;

	cout << "Nodes of bst: " << CountNode(root) << endl;
}



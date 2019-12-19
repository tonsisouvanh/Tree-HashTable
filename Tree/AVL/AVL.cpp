#include <iostream>
using namespace std;
struct Node {
	int data;
	int height;
	Node* left;
	Node* right;
};
Node* CreateNode(int data)
{
	Node* node = new Node();
	node->data = data;
	node->left = node->right = NULL;
	node->height = 1;
	return node;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

int Height(Node* root) {
	if (root == NULL) return 0;
	else
	{
		int lh = Height(root->left);
		int rh = Height(root->right);

		return max(lh, rh) + 1;
	}
}

Node* rightRotate(Node* root)
{
	Node* newRoot = root->left;
	root->left = newRoot->right;
	newRoot->right = root;
	root->height = max(Height(root->left), Height(root->right)) + 1;
	newRoot->height = max(Height(newRoot->left), Height(newRoot->right)) + 1;
	return newRoot;
}

Node* leftRotate(Node* root)
{
	Node* newRoot = root->right;
	root->right = newRoot->left;
	newRoot->left = root;
	root->height = max(Height(root->left), Height(root->right)) + 1;
	newRoot->height = max(Height(newRoot->left), Height(newRoot->right)) + 1;
	return newRoot;

}

Node* Insert(Node* root, int x)
{
	if (root == NULL)
		return (CreateNode(x));
	else
	{
		if (x < root->data)
			root->left = Insert(root->left, x);
		else if (x > root->data)
			root->right = Insert(root->right, x);
		else
			return root;

		root->height = max(Height(root->left), Height(root->right)) + 1;
		int balance = Height(root->left) - Height(root->right);

		if (balance > 1) {
			if (x < root->left->data) {
				return rightRotate(root);	//LL
			}
			else if (x > root->left->data) { //LR
				root->left = leftRotate(root->left);
				return rightRotate(root);
			}
		}
		else if (balance < -1) {
			if (x > root->right->data) {
				return leftRotate(root);		//RR
			}
			else if (x < root->right->data) {
				root->right = rightRotate(root->right);	//RL
				return leftRotate(root);			//..
			}
		}
	}
	return root;

}
void inorder(Node* root)
{
	if (root != NULL)
	{
		inorder(root->left);
		cout << root->data << " ";
		inorder(root->right);
	}
}

Node* removeUtil(Node* p_root, int data) {
	if (p_root == NULL) return NULL;
	if (data < p_root->data) {
		p_root->left = removeUtil(p_root->left, data);
	}
	else if (data > p_root->data) {
		p_root->right = removeUtil(p_root->right, data);
	}
	else {
		Node* r = p_root->right;
		if (p_root->right== NULL) {
			Node* l = p_root->left;
			delete(p_root);
			p_root = l;
		}
		else if (p_root->left == NULL) {
			delete(p_root);
			p_root = r;
		}
		else {
			while (r->left != NULL) r = r->left;
			p_root->data = r->data;
			p_root->right = removeUtil(p_root->right, r->data);
		}
	}
	if (p_root == NULL) return p_root;
	p_root->height = 1 + max(Height(p_root->p_left), height(p_root->p_right));
	int bal = height(p_root->p_left) - height(p_root->p_right);
	if (bal > 1) {
		if (data > p_root->p_left->key) {
			return rightRotation(p_root);
		}
		else {
			p_root->p_left = leftRotation(p_root->p_left);
			return rightRotation(p_root);
		}
	}
	else if (bal < -1) {
		if (data < p_root->p_right->key) {
			return leftRotation(p_root);
		}
		else {
			p_root->p_right = rightRotation(p_root->p_right);
			return leftRotation(p_root);
		}
	}
	return p_root;
}

void LevelOrder(Node* p_root)
{
	if (p_root == NULL) return;
	LevelOrder(p_root->left);
	cout << p_root->data << " ";
	LevelOrder(p_root->right);
}
bool IsAVL(Node* p_root)
{
	int lh;
	int rh;
	if (p_root == NULL)
		return 1;
	lh = Height(p_root->left);
	rh = Height(p_root->right);
	if (abs(lh - rh) <= 1 && IsAVL(p_root->left) && IsAVL(p_root->right))
		return 1;

	return 0;
}
void main()
{
	Node* root = NULL;
	root = Insert(root, 10);
	root = Insert(root, 5);
	root = Insert(root, 20);
	root = Insert(root, -10);
	root = Insert(root, -20);
	//cout << Height(root->left) << endl;
	inorder(root);
}


//how to read file
//vector<Company> ReadListCompany(string file_name)
//{
//	Company compObject;
//
//	int i = 0;
//
//	file_name = file_name + ".txt";
//
//	vector<Company> comp;
//
//	string token;
//
//	ifstream fi;
//
//	fi.open(file_name);
//
//	if (fi.is_open())
//	{
//		getline(fi, token);
//		while (!fi.eof())
//		{
//			getline(fi, token, '|');
//			if (token == "")
//				break;
//
//			comp.push_back(compObject);
//
//			comp[i].name = token;
//
//			getline(fi, token, '|');
//			comp[i].profit_tax = token;
//
//			getline(fi, token, '\n');
//			comp[i].address = token;
//
//			i++;
//		}
//
//		fi.close();
//	}
//	else
//		cout << "File not found" << endl;
//
//	return comp;
//
//}
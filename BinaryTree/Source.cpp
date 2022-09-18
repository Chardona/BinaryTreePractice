#include <cstddef>
#include <iostream>
#include <queue>
struct Node {
	int data;
	Node* right;
	Node* left;
	Node* parent;
};

void levelOrder(Node* root) {
	if (root == NULL) return;
	std::queue <Node*> Q;
	Q.push(root);
	while (!Q.empty()) {
		Node* current = Q.front();
		std::cout << current->data << " ";
		if (current->left != NULL) Q.push(current->left);
		if (current->right != NULL) Q.push(current->right);
		Q.pop();
	}
}
//DLR
void preOrder(Node* root) {	
	if (root == NULL) return;
	std::cout << root->data << " ";
	preOrder(root->left);
	preOrder(root->right);
}
//LDR
void inOrder(Node* root) {
	if (root == NULL) return;
	inOrder(root->left);
	std::cout << root->data << " ";
	inOrder(root->right);
}
//LRD
void postOrder(Node* root) {
	if (root == NULL) return;
	inOrder(root->left);
	inOrder(root->right);
	std::cout << root->data << " ";
}

int findMin(Node* root) {
	if (root == NULL)
	{
		std::cout << "No numbers\n";
		return -1;
	}
	while (root->left != NULL) {
		root = root->left;
	}
	return root->data;
}
Node* findMinRoot(Node* root) {
	if (root == NULL)
	{
		std::cout << "No numbers\n";
		return root;
	}
	while (root->left != NULL) {
		root = root->left;
	}
	return root;
}
int findMinRec(Node* root) {
	if (root == NULL)
	{
		std::cout << "No numbers\n";
		return -1;
	}
	else if (root->left == NULL) {
		return root->data;
	}
	return findMinRec(root->left);
}
int findMax(Node* root) {
	if (root == NULL) {
		std::cout << "No numberss\n";
		return -1;
	}
	while (root->right != NULL) {
		root = root->right;
	}
	return root->data;
}
int findMaxRec(Node* root) {
	if (root == NULL) {
		std::cout << "wrong numbers\n";
		return -1;
	}
	else if (root->right == NULL) {
		return root->data;
	}
	return findMaxRec(root->right);
}
int findHeight(Node* root) {
	if (root == NULL)
		return -1;
	return std::max(findHeight(root->left), findHeight(root->right)) + 1;
}
bool search(Node* root, int data) {
	if (root == NULL) { return false; }
	else if (root->data == data) { return true; }
	else if (data <= root->data) return search(root->left, data);
	else  return search(root->right, data); 
}
Node* Find(Node* root, int data) {
	if (root == NULL) return NULL;
	if (root->data == data) return root;
	else if (root->data >= data) return Find(root->left, data);
	else return Find(root->right, data);
	
}
Node* getNewNode(int data) {
	Node* newNode = new Node();
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}
Node* insert(Node* rootPtr, int data) {
	if (rootPtr == NULL) {
		rootPtr = getNewNode(data);
	}
	else if (data <= rootPtr->data) {
		rootPtr->left = insert(rootPtr->left, data);
	}
	else {
		rootPtr->right = insert(rootPtr->right, data);
	}
	return rootPtr;
}
Node* del(Node* root, int value) {
	if (root == NULL) return root;
	else if (value < root->data) root->left = del(root->left, value);
	else if (value > root->data) root->right = del(root->right, value);
	else {
		//Case 1: No children
		if (root->left == root->right == NULL) {
			delete root;
			root = NULL;
		}
		//Case 2:: One child
		if (root->left == NULL) {
			Node* temp = root;
			root = root->right;
			delete temp;
		}
		else if (root->right == NULL) {
			Node* temp = root;
			root = root->left;
			delete temp;
		}
		//Case 3: 2 Children
		else {
			Node* min = findMinRoot(root->right);
			root->data = min->data;
			root->right = del(root->right, min->data);
		}
	}
	return root;
}
bool isSubTreeLesser(Node* root, int data) {
	if (root == NULL) return true;
	if (root->data <= data &&
		isSubTreeLesser(root->left, data) &&
		isSubTreeLesser(root->right, data))
		return true;
	else
		return false;
}
Node* getSuccessor(Node* root, int data) {
	Node* current = Find(root, data);
	if (current == NULL) return NULL;
	//Case 1: Node has right subtree
	if (current->right != NULL) {
		Node* temp = current->right;
		while (temp != NULL) temp = temp->left;
		return temp;
	}
	//Case 2: No right sub tree
	else {
		Node* successor = NULL;
		Node* ancestor = root;
		while (ancestor != current) {
			if (current->data < ancestor->data) {
				successor = ancestor;
				ancestor = ancestor->left;
			}
			else {
				ancestor = ancestor->right;
			}
		}
		return successor;
	}
}
bool isSubTreeGreater(Node* root, int data) {
	if (root == NULL) return true;
	if (root->data > data &&
		isSubTreeGreater(root->left, data) &&
		isSubTreeGreater(root->right, data))
		return true;
	else
		return false;
}
bool isBST(Node* root) {
	if (root == NULL) return true;
	if (isSubTreeLesser(root->left, root->data) && isSubTreeGreater(root->right, root->data)
		&& isBST(root->left) && isBST(root->right))
		return true;
	else
		return false;
}
bool isBST2(Node* root, float minV, float maxV) {
	if (root == NULL) return true;
	if (root->data > minV && root->data < maxV
		&& isBST2(root->left, minV, root->data) && isBST2(root->right, root->data, maxV))
	{
		return true;
	}
	else
		return false;
}
bool isBST3(Node* root) {
	return (findMin(root) < findMax(root));
}
int main() {
	Node* root = NULL;
	root = insert(root, 15);
	root = insert(root, 20);
	root = insert(root, 45);
	root = insert(root, 77);
	root = insert(root, 29);
	root = insert(root, 91);
	root = insert(root, 250);
	root = insert(root, 400);
	root = insert(root, 14);
	/*if (search(root, 400)) { std::cout << "Found\n"; }
	std::cout << "Min is: " << findMin(root) <<"\n";
	std::cout << "Max is: " << findMax(root) << "\n";
	std::cout<<"Now max rec: "<<findMaxRec(root)<<"\n";
	std::cout << "And min rec: " << findMinRec(root) << "\n";
	std::cout << "Height is: " << findHeight(root) << '\n';*/
	/*std::cout << "Lever order: ";
	levelOrder(root);
	std::cout << "\nPreorder: ";
	preOrder(root);*/
	std::cout << "\nIn Order: ";
	inOrder(root);
	/*std::cout << "\nPost Order: ";
	postOrder(root);
	std::cout << "\nCheck if BST: "<<isBST(root);
	std::cout << "\nCheck if BST2: " << isBST2(root, -INFINITY, INFINITY);
	std::cout << "\nCheck if BST3: " << isBST3(root);*/
	root = del(root, 400);
	root = del(root, 29);
	std::cout << "\nIn order after deletion: ";
	inOrder(root);
	std::cout << "\nSuccessor: " << getSuccessor(root, 15);
	/*int count = log10(1010) + 1;
	std::cout << count;*/
}
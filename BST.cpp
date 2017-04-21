/*
 * BST.cpp
 *
 *  Created on: Apr 16, 2017
 *  Author: McKay Madsen
 *
 *
 */


#include <iostream>
using namespace std;

struct node {
    node *left;
    node *right;
    int data;
};

class BST {

private:

	node* root;

    void set_data(node* ptr, int num) {
        ptr->left = NULL;
        ptr->right = NULL;
        ptr->data = num;
    }

    node *minVal(node* node){
    	struct node* curr = node;
    	while (curr->left != NULL) {
    		curr = curr->left;
    	}
    	return curr;
	}

	node *maxVal(node* node){
    	struct node* curr = node;
    	while (curr->right != NULL) {
    		curr = curr->right;
    	}
    	return curr;
	}

    node* arrayToBST(int arr[], int length) {
		if (length == 0) {
			return NULL;
		}
		struct node *node = new(struct node);
		int mid = length/2;
		node->data = arr[mid];
		node->left = arrayToBST(arr, mid);
		node->right = arrayToBST(arr + mid + 1, length - (mid + 1));
		return node;
	}

	/*
	 * Search_helper: a helper function. Allows the search function to be based
	 * on the algorithm in the book
	 */
	node *search_helper(node *ptr, int key) {
        if(ptr == NULL) {
            return NULL;
        }
        else if(key < ptr->data) {
            return search_helper(ptr->left, key);
        }
        else if(key > ptr->data) {
            return search_helper(ptr->right, key);
        }
        else {
        	return ptr;
        }
	}

	/*
	 * Search_helper: a helper function. Allows the search function to be based
	 * on the algorithm in the book
	 */
	node *remove_helper(node* root, int key, char det){
	    if (root == NULL) {
	    	return root;
	    }
	    if (key < root->data) {
        	root->left = remove_helper(root->left, key, det);
	    }
	    else if (key > root->data) {
        	root->right = remove_helper(root->right, key, det);
	    }
	    else {
        	if (root->left == NULL) {
            	node *temp = root->right;
            	free(root);
            	return temp;
        	}
        	else if (root->right == NULL) {
            	node *temp = root->left;
            	free(root);
            	return temp;
            }
        	if (det == 's') {
        		node* temp = minVal(root->right);
        		root->data = temp->data;
        		root->right = remove_helper(root->right, temp->data, det);
    		}
        	else {
        		node* temp = maxVal(root->left);
        		root->data = temp->data;
        		root->left = remove_helper(root->left, temp->data, det);
        	}
    	}
    	return root;
	}

	node *preorder_helper(node *ptr) {
		if (ptr != NULL) {
	    	cout << ptr->data << " ";
	    	preorder_helper(ptr->left);
	    	preorder_helper(ptr->right);
		}
	    return ptr;
	}

	node *inorder_helper(node *ptr) {
		if (ptr != NULL) {
	    	inorder_helper(ptr->left);
	    	cout << ptr->data << " ";
	    	inorder_helper(ptr->right);
		}
	    return ptr;
	}

	node *postorder_helper(node *ptr) {
		if (ptr != NULL) {
	    	postorder_helper(ptr->left);
	    	postorder_helper(ptr->right);
	    	cout<<ptr->data<<" ";
		}
	    return ptr;
	}



public:

	/*
	 * basic bool function to check if BST is empty
	 */
	bool isEmpty() const {
		return root==NULL;
	}

	/*
	 * Default Constructor: creates an empty tree
	 */
	BST() {
		root = NULL;
	}

	/*
	 * Constructor: Constructor, first parameter is an ordered
	 * array of elements and the second parameter is the number of elements in the array.
	 * The tree should be built in a balanced fashion, with odd elements
	 * going to the left when
	 */
	BST(int arr[], int length) {
		if (length == 0) {
			return;
		}

		struct node *node = new(struct node);
		int mid = length/2;
		node->data = arr[mid];
		node->left = arrayToBST(arr, mid);
		node->right = arrayToBST(arr + mid + 1, length - (mid + 1));
		root = node;
	}

	/*
	 * Insert function: insert the integer parameter into the BST
	 */
	void insert(int key) {
		struct node* ptr = new node;
		struct node* parent;

		parent = NULL;

		ptr->right = NULL;
		ptr->left = NULL;
		ptr->data = key;

		if(isEmpty()) {
			root = ptr;
		}
		else {
			struct node* current;
			current = root;

		    while(current) {
		        parent = current;
		        if(ptr->data > current->data) {
		        	current = current->right;
		        }
		        else {
		        	current = current->left;
		        }
		    }
		    if(ptr->data < parent->data) {
		       parent->left = ptr;
		    }
		    else {
		       parent->right = ptr;
		    }
		}
	}

	/*
	 * Removes the integer parameter from the BST.  The
	 * character parameter will determine which node is used to replace
	 * the deleted value.  The second parameter will either be a ‘p’ for
	 * predecessor or an ‘s’ for successor; the default value will be ‘p’.
	 * delete returns true if the value is in the BST and can be deleted
	 * and false if the value is not in the tree
	 */
	bool remove(int key, char det = 'p') {
		if (search(key) != NULL) {
			remove_helper(root, key, det);
			return true;
		}
		return false;
	}

	/*
	 * Search: Returns a pointer to the tree node containing the parameter.
	 * Returns Null if the value is not in the BST
	 */
	node * search(int key) {
		struct node *ptr = root;
		struct node *found = search_helper(ptr,key);
		return found;
	}

	/*
	 * Prints the pre-order, in-order, or post-order traversal of the tree
	 * The default value for the parameter is the root of the BST
	 */
	void preorder() {
		//preorder(root);
		preorder_helper(root);
		cout << endl;
	}

	void inorder() {
		inorder_helper(root);
		cout << endl;
	}

	void postorder() {
		postorder_helper(root);
		cout << endl;
	}

	void preorder(node *ptr) {
		preorder_helper(ptr);
		cout << endl;
	}

	void inorder(node *ptr) {
		inorder_helper(ptr);
		cout << endl;
	}

	void postorder(node *ptr) {
		postorder_helper(ptr);
		cout << endl;
	}

};

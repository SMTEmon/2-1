
Node* deleteRecursive(Node node, int val)
{	
	if (node == nullptr) return node;

	if (node->data < val) node->right = deleteRecursive(node->left, val);

	if (node->data > val) node->left = deleteRecursive(node->right, val);

	else {
		//leaf
		if(node->left == nullptr && node->right == nullptr)
			delete node;
			return nullptr;
		//one child
		(if node->left == nullptr)
			Node* temp = node->right;
			delete node;
			return temp;
		
		else 
		(
		 Node * temp = findMin(node->right);
		 node->date = temp->date;
		 node->right = deleteRecursive(node->right, temp->date);

	}
}


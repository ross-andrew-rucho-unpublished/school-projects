package BST_A2;

public class BST implements BST_Interface {
	// Fields
	public BST_Node root;
	int size;

	// Constructor for a BST
	public BST() {
		size = 0;
		root = null;
	}

	// used for testing, please leave as is
	@Override
	public BST_Node getRoot() {
		return root;
	}

	// Public methods

	// Determines if a new element can be inserted in BST
	// and performs the insert
	public boolean insert(String s) {
		if (root == null) {
			// Element is stored in root
			root = new BST_Node(s);
			size++;
			return true;
		} else {
			// BST is checked to either insert the element
			// or determine that an insert can't occur
			if (root.insertNode(s)) {
				size++;
				return true;
			} else {
				return false;
			}
		}
	}

	// Determines if an element can be removed from a BST
	// and performs the removal
	public boolean remove(String s) {
		if (root == null) {
			return false;
		} else if (root.data.compareTo(s) == 0) {
			// Root node must be removed
			if (root.left == null && root.right == null) {
				// Root is a leaf
				root = null;
			} else if (root.right == null) {
				// Root has only a left child
				root = root.left;
			} else if (root.left == null) {
				// Root has only a right child
				root = root.right;
			} else {
				// Root has two children
				BST_Node tempNode = root.right.findMin();
				root.removeNode(tempNode.data);
				root.data = tempNode.data;
			}
			size--;
			return true;
		} else {
			if (root.removeNode(s)) {
				size--;
				return true;
			} else {
				return false;
			}
		}
	}

	// Finds the smallest string in the BST
	public String findMin() {
		if (root == null) {
			return null;
		} else {
			return root.findMin().data;
		}
	}

	// Finds the largest string in the BST
	public String findMax() {
		if (root == null) {
			return null;
		} else {
			return root.findMax().data;
		}
	}

	// Determines if the BST is empty
	public boolean empty() {
		if (size == 0) {
			return true;
		} else {
			return false;
		}
	}

	// Determines if a element is in the BST
	public boolean contains(String s) {
		if (root == null) {
			return false;
		} else {
			return root.containsNode(s);
		}
	}

	// Returns the number of elements in the BST
	public int size() {
		return size;
	}

	// Returns the height of the BST
	public int height() {
		if (root == null) {
			return -1;
		} else {
			return root.getHeight(0);
		}
	}
}

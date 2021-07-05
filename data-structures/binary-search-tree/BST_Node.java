package BST_A2;

public class BST_Node {
	String data;
	BST_Node left;
	BST_Node right;

	// BST node constructor
	BST_Node(String data) {
		this.data = data;
		this.left = null;
		this.right = null;
	}

	// leave these 3 methods in, as is

	public String getData() {
		return data;
	}

	public BST_Node getLeft() {
		return left;
	}

	public BST_Node getRight() {
		return right;
	}

	// Public methods

	// Node logic to recursively check the tree for an element
	public boolean containsNode(String s) {
		if (data.compareTo(s) == 0) {
			// element is at current node
			return true;
		} else if (data.compareTo(s) > 0) {
			// element must be in left subtree
			if (left == null) {
				return false;
			} else {
				return left.containsNode(s);
			}
		} else {
			// element must be in right subtree
			if (right == null) {
				return false;
			} else {
				return right.containsNode(s);
			}
		}
	}

	// Node logic to recursively determine the location
	// to insert a new node
	public boolean insertNode(String s) {
		if (data.compareTo(s) == 0) {
			// Element is already in the BST
			return false;
		} else if (data.compareTo(s) > 0) {
			// Element must be inserted in the left tree
			if (left == null) {
				// Insert element
				left = new BST_Node(s);
				return true;
			} else {
				return left.insertNode(s);
			}
		} else {
			// Element must be inserted in the right tree
			if (right == null) {
				// Insert element
				right = new BST_Node(s);
				return true;
			} else {
				return right.insertNode(s);
			}
		}
	}

	// Node logic to recursively determine the location
	// to remove a node
	public boolean removeNode(String s) {
		// Initialize local variables
		BST_Node prev_node = this;
		BST_Node cur_node = this;
		boolean flag = false;
		boolean done = false;

		while (!done) {
			// Initialize local variables
			int cmp = cur_node.data.compareTo(s);

			if (cmp > 0) {
				// Element to remove is in the left child
				if (cur_node.left == null) {
					flag = false;
					done = true;
				} else {
					prev_node = cur_node;
					cur_node = cur_node.left;
				}
			} else if (cmp < 0) {
				// Element to remove is in the right child
				if (cur_node.right == null) {
					flag = false;
					done = true;
				} else {
					prev_node = cur_node;
					cur_node = cur_node.right;
				}
			} else {
				// Remove this element
				if (cur_node == prev_node.left) {
					if (cur_node.left == null && cur_node.right == null) {
						// Node has no children
						prev_node.left = null;
					} else if (cur_node.right == null) {
						// Node has only a left child
						prev_node.left = cur_node.left;
					} else if (cur_node.left == null) {
						// Node has only a right child
						prev_node.left = cur_node.right;
					} else {
						// Node has two children
						BST_Node tempNode = cur_node.right.findMin();
						cur_node.removeNode(tempNode.data);
						cur_node.data = tempNode.data;
					}
				} else {
					if (cur_node.left == null && cur_node.right == null) {
						// Node has no children
						prev_node.right = null;
					} else if (cur_node.right == null) {
						// Node has only a left child
						prev_node.right = cur_node.left;
					} else if (cur_node.left == null) {
						// Node has only a right child
						prev_node.right = cur_node.right;
					} else {
						// Node has two children
						BST_Node tempNode = cur_node.right.findMin();
						cur_node.removeNode(tempNode.data);
						cur_node.data = tempNode.data;
					}
				}
				flag = true;
				done = true;
			}
		}
		return flag;
	}

	// Node logic to recursively find the smallest node
	public BST_Node findMin() {
		if (left == null) {
			// At smallest node
			return this;
		} else {
			// There is a smaller node
			return left.findMin();
		}
	}

	// Node logic to recursively find the largest node
	public BST_Node findMax() {
		if (right == null) {
			// At largest node
			return this;
		} else {
			// There is a larger node
			return right.findMax();		// This said return right.findMin(); that's why you missed points
		}
	}

	// Node logic to recursively find the node with the
	// greatest depth
	public int getHeight(int depth) {
		if (left == null && right == null) {
			// Lowest node in the path
			return depth;
		} else if (right == null) {
			// Lower node in the left tree
			return left.getHeight(depth + 1);
		} else if (left == null) {
			// Lower node in the right tree
			return right.getHeight(depth + 1);
		} else {
			// Declare local variables
			int l = left.getHeight(depth + 1);
			int r = right.getHeight(depth + 1);

			// Lower node in both trees
			if (l > r) {
				return l;
			} else {
				return r;
			}
		}
	}

	public String toString() {
		return "Data: " + this.data + ", Left: " + ((this.left != null) ? left.data : "null") + ",Right: "
				+ ((this.right != null) ? right.data : "null");
	}
}

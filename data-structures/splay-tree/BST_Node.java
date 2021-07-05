package SPLT_A4;

public class BST_Node {
	// Fields
	String data;
	BST_Node left;
	BST_Node right;
	BST_Node par;
	boolean just_made;

	BST_Node(String data) {
		this.data = data;
		this.left = null;
		this.right = null;
		this.par = null;
		just_made = true;
	}

	BST_Node(String data, BST_Node left, BST_Node right, BST_Node par) {
		this.data = data;
		this.left = left;
		this.right = right;
		this.par = par;
		just_made = true;
	}

	// leave these 3 methods in, as is (meaning also make sure they do in fact
	// return data,left,right respectively)
	public String getData() {
		return data;
	}

	public BST_Node getLeft() {
		return left;
	}

	public BST_Node getRight() {
		return right;
	}

	// BST_Node methods

	// Determines if the SPLT contains a node
	public BST_Node containsNode(String s) {
		if (data.equals(s)) {
			splay(this);
			return this;
		} else if (data.compareTo(s) > 0) {
			if (left == null) {
				splay(this);
				return this;
			}
			return left.containsNode(s);
		} else {
			if (right == null) {
				splay(this);
				return this;
			}
			return right.containsNode(s);
		}
	}

	// Method to insert Node in SPLT
	public BST_Node insertNode(String s) {
		if (data.compareTo(s) == 0) {
			// Element is already in the SPLT
			splay(this);
			just_made = false;
			return this;
		} else if (data.compareTo(s) > 0) {
			// Element must be inserted in the left subtree
			if (left == null) {
				left = new BST_Node(s, null, null, this);
				BST_Node tempLeft = left;
				splay(tempLeft);
				return tempLeft;
			}
			return left.insertNode(s);
		} else {
			// Element must be inserted in the right subtree
			if (right == null) {
				right = new BST_Node(s, null, null, this);
				BST_Node tempRight = right;
				splay(tempRight);
				return tempRight;
			}
			return right.insertNode(s);
		}
	}

	// Method to remove Node in SPLT
	public BST_Node removeNode() {
		if (this.left != null && this.right != null) {
			// Initialize temporary pointers
			BST_Node left_child = this.left;
			BST_Node right_child = this.right;

			// Un-hook root
			left_child.par = null;
			right_child.par = null;

			// Find maximum on left child and connect right child
			BST_Node tempRoot = left_child.findMax();
			tempRoot.right = right_child;
			right_child.par = tempRoot;
			return tempRoot;

		} else if (this.left != null) {
			// Initialize temporary pointers
			BST_Node left_child = this.left;

			// Un-hook root
			left_child.par = null;

			// Find maximum on left child
			return left_child;

		} else if (this.right != null) {
			// Initialize temporary pointers
			BST_Node right_child = this.right;

			// Un-hook root
			right_child.par = null;

			// Find minimum on right child
			return right_child;

		} else {
			return null;
		}
	}

	// Method to find minimum in SPLT
	public BST_Node findMin() {
		if (left != null)
			return left.findMin();
		splay(this);
		return this;
	}

	// Method to find maximum in SPLT
	public BST_Node findMax() {
		if (right != null)
			return right.findMax();
		splay(this);
		return this;
	}

	// Method to determine the height of a node in SPLT
	public int getHeight() {
		int l = 0;
		int r = 0;
		if (left != null)
			l += left.getHeight() + 1;
		if (right != null)
			r += right.getHeight() + 1;
		return Integer.max(l, r);
	}

	// Internal Splay method
	private void splay(BST_Node toSplay) {
		while (toSplay.par != null) {
			// Initialize a temporary node
			BST_Node tempNode = toSplay;
			int parents = 0;

			// Find how deep toSplay is in tree
			while (tempNode.par != null) {
				parents++;
				tempNode = tempNode.par;
			}

			// Cases
			if (parents == 1) {
				if (toSplay.par.left != null && toSplay.par.left == toSplay) {
					// Link is L
					rotateRight(toSplay);
				} else { // toSplay is right child
					// Link is R
					rotateLeft(toSplay);
				}
			} else {
				if (toSplay.par.par.left != null && toSplay.par.par.left == toSplay.par) {
					// Top link is L
					if (toSplay.par.left != null && toSplay.par.left == toSplay) {
						// Bottom link is L
						rotateRight(toSplay.par);
						rotateRight(toSplay);
					} else { // toSplay is right child
						// Bottom link is R
						rotateLeft(toSplay);
						rotateRight(toSplay);
					}
				} else { // toSplay.par is right child
					// Top link is R
					if (toSplay.par.left != null && toSplay.par.left == toSplay) {
						// Bottom link is L
						rotateRight(toSplay);
						rotateLeft(toSplay);
					} else { // toSplay is right child
						// Bottom link is R
						rotateLeft(toSplay.par);
						rotateLeft(toSplay);
					}
				}
			}
		}
	}

	// Helper methods

	// Helper method that does a single left rotation
	private void rotateLeft(BST_Node toSplay) {
		// Handle grandparent child link
		if (toSplay.par.par != null) {
			if (toSplay.par.par.left == toSplay.par) {
				toSplay.par.par.left = toSplay;
			} else {
				toSplay.par.par.right = toSplay;
			}
		}

		// Handle toSplay left child
		if(toSplay.left != null)
			toSplay.left.par = toSplay.par;
		toSplay.par.right = toSplay.left;
		toSplay.left = toSplay.par;

		// Handle toSplay parent
		toSplay.par = toSplay.par.par;
		toSplay.left.par = toSplay;
		
	}

	// Helper method that does a single right rotation
	private void rotateRight(BST_Node toSplay) {
		// Handle grandparent child link
		if (toSplay.par.par != null) {
			if (toSplay.par.par.left == toSplay.par) {
				toSplay.par.par.left = toSplay;
			} else {
				toSplay.par.par.right = toSplay;
			}
		}

		// Handle toSplay right child
		if(toSplay.right != null)
			toSplay.right.par = toSplay.par;
		toSplay.par.left = toSplay.right;
		toSplay.right = toSplay.par;
		
		
		// Handle toSplay parent
		toSplay.par = toSplay.par.par;
		toSplay.right.par = toSplay;

	}

	//
	public String toString() {
		return "Data: " + this.data + ", Left: " + ((this.left != null) ? left.data : "null") + ",Right: "
				+ ((this.right != null) ? right.data : "null");
	}
}

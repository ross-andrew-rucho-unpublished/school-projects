package SPLT_A4;

public class SPLT implements SPLT_Interface {
	private BST_Node root;
	private int size;

	public SPLT() {
		this.size = 0;
		root = null;
	}

	// used for testing, please leave as is
	public BST_Node getRoot() {
		return root;
	}

	// Method to insert a node in SPLT
	public void insert(String s) {
		if (empty()) {
			root = new BST_Node(s);
			size++;
		} else {
			root = root.insertNode(s);
			if (root.just_made)
				size++;
		}
	}

	// Method to remove a node in SPLT
	public void remove(String s) {
		if (!contains(s)) {
			// Do Nothing
		} else {
			root = root.removeNode();
			size--;
		}
	}

	// Finds the minimum in SPLT
	public String findMin() {
		if (empty()) {
			return null;
		} else {
			root = root.findMin();
			return root.data;
		}
	}

	// Finds the maximum in SPLT
	public String findMax() {
		if (empty()) {
			return null;
		} else {
			root = root.findMax();
			return root.data;
		}
	}

	// Method to determine if SPLT is empty
	public boolean empty() {
		if (size == 0) {
			return true;
		} else {
			return false;
		}
	}

	// Determines if SPLT contains a node
	public boolean contains(String s) {
		if (empty()) {
			return false;
		}

		root = root.containsNode(s);
		if (root.data.equals(s))
			return true;

		return false;

	}

	// Method to determine number of elements in SPLT
	public int size() {
		return size;
	}

	// Method to determine height of SPLT
	public int height() {
		if (empty()) {
			return -1;
		} else {
			return root.getHeight();
		}
	}
}

package LinkedList_A1;

public class LinkedListImpl implements LIST_Interface {
	Node sentinel; // this will be the entry point to your linked list (the head)

	public LinkedListImpl() {// this constructor is needed for testing purposes. Please don't modify!
		sentinel = new Node(Double.NaN); // Note that the root's data is not a true part of your data set!
		sentinel.next = sentinel;
		sentinel.prev = sentinel;
		numElts = 0;
	}

	public Node getRoot() { // leave this method as is, used by the grader to grab your linkedList easily.
		return sentinel;
	}

	// Fields
	private int numElts;

	// LIST_Interface methods

	// The list state will be altered so that the element is located at the
	// specified index; the list has size bigger by one; all elements that were
	// at the specified index or after have been moved down one slot
	public boolean insert(double elt, int index) {
		// Checks the insert parameters
		if (index < 0 || index > size()) {
			return false;
		} else {
			// Declare local variables
			Node cur_node = sentinel;
			Node new_node = new Node(elt);

			// Finds node previous to index
			for (int i = -1; i < index - 1; i++) {
				cur_node = cur_node.next;
			}

			// Sets node links
			new_node.next = cur_node.next;
			new_node.prev = cur_node;
			cur_node.next.prev = new_node;
			cur_node.next = new_node;

			// Update length and return
			numElts++;
			return true;
		}
	}

	// effect: list state is altered in that the Node at the specified index is
	// decoupled. list size decreases by one
	public boolean remove(int index) {
		// Checks the remove parameters
		if (index < 0 || index >= size()) {
			return false;
		} else {
			// Declare local variables
			Node cur_node = sentinel;

			// Finds node at index
			for (int i = -1; i < index; i++) {
				cur_node = cur_node.next;
			}

			// Sets node links
			cur_node.prev.next = cur_node.next;
			cur_node.next.prev = cur_node.prev;

			// Update length and return
			numElts--;
			return true;
		}
	}

	// Return: double, the element stored at index, or Double.NaN
	public double get(int index) {
		// Checks the get parameters
		if (index < 0 || index >= size()) {
			return Double.NaN;
		} else {
			// Declare local variables
			Node cur_node = sentinel;

			// Finds node at index
			for (int i = -1; i < index; i++) {
				cur_node = cur_node.next;
			}
			
			// Update length and return
			return cur_node.data;
		}
	}

	// Return: number of elements stored in the list
	public int size() {
		return numElts;
	}

	// Return: boolean, true if the list has no elements in it, true is size is 0
	public boolean isEmpty() {
		if (size() == 0) {
			return true;
		} else {
			return false;
		}
	}

	// List is left with size 0, no elements in it,
	// consists of just the original root Node
	public void clear() {
		numElts = 0;
		sentinel.next = sentinel;
		sentinel.prev = sentinel;
	}

}

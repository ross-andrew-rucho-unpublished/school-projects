package MinBinHeap_A3;

public class MinBinHeap implements Heap_Interface {
	// Fields
	private EntryPair[] array; // load this array
	private int size;
	private static final int arraySize = 10000; // Everything in the array will initially be null.

	// Constructor
	public MinBinHeap() {
		this.array = new EntryPair[arraySize];
		array[0] = new EntryPair(null, -100000); // 0th will be unused
		size = 0;
	}

	// Please do not remove or modify this method! Used to test your entire Heap.
	@Override
	public EntryPair[] getHeap() {
		return this.array;
	}

	// Heap_Interface Methods

	// Inserts a new element into the minimum binary heap
	public void insert(EntryPair entry) {
		if (size == 0) {
			array[1] = entry;
		} else {
			// Initialize local variables
			int i = size + 1;

			// Bubble hole up until it is in the right spot
			// or until it reaches the root
			while (i > 1) {
				if (bubbleUP(entry, array[i / 2])) {
					array[i] = array[i / 2];
					i = i / 2;
				} else {
					array[i] = entry;
					i = 0;
				}
			}

			// Handle the root case
			if (i != 0) {
				array[1] = entry;
			}
		}
		size++;
	}

	// Removes the root element and establishes a new minimum binary heap
	public void delMin() {
		if (size == 0) {
			// Do Nothing
		} else if (size == 1) {
			array[1] = null;
			size--;
		} else {
			// Remove the last element from the array
			EntryPair temp = array[size];
			array[size] = null;
			size--;

			// Handle cases with less than 3 nodes after remove
			if (size == 1) {
				array[1] = temp;
			}
			if (size == 2) {
				if (temp.getPriority() < array[2].getPriority()) {
					array[1] = temp;
				} else {
					array[1] = array[2];
					array[2] = temp;
				}
			}

			// Initialize/declare variables
			int i = 1;
			int val;

			// Loop through minimum binary heap to restore heap order
			while (size >= 3 && i <= size) {
				if (i * 2 + 1 <= size) {
					val = compareNode(temp, array[i * 2], array[i * 2 + 1]);

					if (val == 0) {
						array[i] = temp;
						i = size + 1;
					} else if (val == 1) {
						array[i] = array[i * 2];
						i = i * 2;
					} else if (val == 2) {
						array[i] = array[i * 2 + 1];
						i = i * 2 + 1;
					}
				} else if (i * 2 <= size) {
					if (temp.getPriority() < array[i * 2].getPriority()) {
						array[i] = temp;
						i = size + 1;
					} else {
						array[i] = array[i * 2];
						array[i*2] = temp;
						i = size + 1;
					}
				} else {
					array[i] = temp;
					i = size + 1;
				}
			}
		}
	}

	// Returns the minimum element in the binary heap
	public EntryPair getMin() {
		if (size == 0) {
			return null;
		} else {
			return array[1];
		}
	}

	// Returns the size of the minimum binary heap
	public int size() {
		return size;
	}

	// Magic build operation: builds a minimum binary heap in O(n)
	public void build(EntryPair[] entries) {
		// Insert all of the entries into the heap array
		for (int i = 0; i < entries.length; i++) {
			array[i + 1] = entries[i];
			size++;
		}

		// For every parent node from last to root
		for (int k = size / 2; k >= 1; k--) {
			if (k * 2 + 1 <= size) {
				bubbleDOWN(k, array[k], array[k * 2], array[k * 2 + 1]);
			} else if (k * 2 <= size) {
				EntryPair temp = array[k];
				if (array[k * 2].getPriority() < array[k].getPriority()) {
					array[k] = array[k * 2];
					array[k * 2] = temp;
				}
			}
		}
	}

	// Private helper methods

	// Determine if a hole needs to be bubbled up
	private boolean bubbleUP(EntryPair child, EntryPair parent) {
		if (child.getPriority() < parent.getPriority()) {
			return true;
		} else {
			return false;
		}
	}

	// Performs the bubbling down of a hole
	private void bubbleDOWN(int index, EntryPair temporary, EntryPair left, EntryPair right) {
		// Check which node is lowest priority
		if (temporary.getPriority() < left.getPriority() && temporary.getPriority() < right.getPriority()) {
			array[index] = temporary;
			return;
		} else if (left.getPriority() < right.getPriority()) {
			array[index] = left;
			index = index * 2;
		} else {
			array[index] = right;
			index = index * 2 + 1;
		}

		// Go one level deeper
		if (index * 2 + 1 <= size) {
			bubbleDOWN(index, temporary, array[index * 2], array[index * 2 + 1]);
		} else if (index * 2 <= size) {
			if (temporary.getPriority() < array[index * 2].getPriority()) {
				array[index] = temporary;
			} else {
				array[index] = array[index * 2];
				array[index * 2] = temporary;
			}
		} else {
			array[index] = temporary;
		}
	}

	// Method to compare three nodes
	private int compareNode(EntryPair temporary, EntryPair left, EntryPair right) {
		if (temporary.getPriority() < left.getPriority() && temporary.getPriority() < right.getPriority()) {
			return 0;
		} else if (left.getPriority() < right.getPriority()) {
			return 1;
		} else {
			return 2;
		}

	}
}

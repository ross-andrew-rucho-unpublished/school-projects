package MinBinHeap_A3;

public interface Heap_Interface {
	// ADT operations
	
	// Inserts a new element into the minimum binary heap
	void insert(EntryPair entry);

	// Removes the root element and establishes a new minimum binary heap
	void delMin();
	
	// Returns the minimum element in the binary heap
	EntryPair getMin();

	// Returns the size of the minimum binary heap
	int size();

	// Magic build operation: builds a minimum binary heap in O(n)
	void build(EntryPair[] entries);

	EntryPair[] getHeap();
}

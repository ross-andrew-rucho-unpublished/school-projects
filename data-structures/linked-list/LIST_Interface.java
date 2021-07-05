package LinkedList_A1;

// Interface: The LIST will provide this collection of ADT operations:

public interface LIST_Interface {
	// The list state will be altered so that the element is located at the
	// specified index; the list has size bigger by one; all elements that were
	// at the specified index or after have been moved down one slot
	public boolean insert(double elt, int index);

	// effect: list state is altered in that the Node at the specified index is
	// decoupled. list size decreases by one
	public boolean remove(int index);

	// Return: double, the element stored at index, or Double.NaN
	public double get(int index);

	// Return: number of elements stored in the list
	public int size();

	// Return: boolean, true if the list has no elements in it, true is size is 0
	public boolean isEmpty();

	// List is left with size 0, no elements in it,
	// consists of just the original root Node
	public void clear();
}

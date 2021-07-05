package BST_A2;

public interface BST_Interface {
	// ADT operations

	// Determines if a new element can be inserted in BST
	// and performs the insert
	public boolean insert(String s);

	// Determines if an element can be removed from a BST
	// and performs the removal
	public boolean remove(String s);

	// Finds the smallest string in the BST
	public String findMin();

	// Finds the largest string in the BST
	public String findMax();

	// Determines if the BST is empty
	public boolean empty();

	// Determines if a element is in the BST
	public boolean contains(String s);

	// Returns the number of elements in the BST
	public int size();

	// Returns the height of the BST
	public int height();

	// Returns the root of the BST
	public BST_Node getRoot();
}

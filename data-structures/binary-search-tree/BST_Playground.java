package BST_A2;

public class BST_Playground {
	public static void main(String[] args) {
		BST tree = new BST();

		tree.insert("delta");
		tree.insert("beta");
		//tree.insert("charlie");
		tree.insert("gamma");
		//tree.insert("frank");
		//tree.insert("alpha");
		//tree.insert("zeta");
		printLevelOrder(tree);
		tree.remove("delta");
		System.out.println(" ");
		printLevelOrder(tree);
	}

	static void printLevelOrder(BST tree) {
		// will print your current tree in Level-Order...
		// https://en.wikipedia.org/wiki/Tree_traversal
		int h = tree.getRoot().getHeight(0);
		for (int i = 0; i <= h; i++) {
			printGivenLevel(tree.getRoot(), i);
			System.out.println(" ");
		}

	}

	static void printGivenLevel(BST_Node root, int level) {
		if (root == null)
			return;
		if (level == 0)
			System.out.print(root.data + " ");
		else if (level > 0) {
			printGivenLevel(root.left, level - 1);
			printGivenLevel(root.right, level - 1);
		}
	}

	static void printInOrder(BST_Node root) {
		// will print your current tree In-Order
		if (root != null) {
			printInOrder(root.getLeft());
			System.out.print(root.getData() + " ");
			printInOrder(root.getRight());
		}
	}
}

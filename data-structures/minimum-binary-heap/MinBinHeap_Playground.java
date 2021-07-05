package MinBinHeap_A3;

public class MinBinHeap_Playground {
	public static void main(String[] args) {
		// Add more tests as methods and call them here!!
		TestBuild();
	}

	public static void TestBuild() {
		// constructs a new minbinheap, constructs an array of EntryPair,
		// passes it into build function. Then print collection and heap.
		MinBinHeap mbh = new MinBinHeap();
		EntryPair[] collection = new EntryPair[8];
		collection[0] = new EntryPair("i", 3);
		collection[1] = new EntryPair("b", 5);
		collection[2] = new EntryPair("c", 1);
		collection[3] = new EntryPair("d", 0);
		collection[4] = new EntryPair("e", 46);
		collection[5] = new EntryPair("f", 7);
		collection[6] = new EntryPair("g", 6);
		collection[7] = new EntryPair("h", 17);
		mbh.build(collection);	
		printHeapCollection(collection);
		printHeap(mbh.getHeap(), mbh.size());
	}

	public static void TestBuild2() {
		MinBinHeap mbh = new MinBinHeap();
		EntryPair[] collection = {new EntryPair("b", 1), 
								  new EntryPair("c", 4),
								  new EntryPair("t", 2),
								  new EntryPair("e", 8),
								  new EntryPair("a", 5),
								  new EntryPair("z", 7)};
		mbh.build(collection);
		printHeapCollection(collection);
		printHeap(mbh.getHeap(), mbh.size());
	}
	public static void printHeapCollection(EntryPair[] e) {
		// this will print the entirety of an array of entry pairs you will pass
		// to your build function.
		System.out.println("Printing Collection to pass in to build function:");
		for (int i = 0; i < e.length; i++) {
			System.out.print("(" + e[i].value + "," + e[i].priority + ")\t");
		}
		System.out.print("\n");
	}

	public static void printHeap(EntryPair[] e, int len) {
		// pass in mbh.getHeap(),mbh.size()... this method skips over unused 0th
		// index....
		System.out.println("Printing Heap");
		int level = 0;
		for (int i = 1; i < len + 1; i++) {
			if(Math.floor(Math.log((double) i)/Math.log((double) 2)) == Math.log((double) i)/Math.log((double) 2) ) {
				System.out.print("\n");
				level++;
				for(int k = 30 - 3*level; k > 0; k = k - 1) {
					System.out.print("  ");
				}
			}
			System.out.print("(" + e[i].value + "," + e[i].priority + ")");
			for(int k = 2; k < 20 - 5*level; k = k + 1) {
				System.out.print(" ");
			}
		}
		System.out.print("\n");
	}
}

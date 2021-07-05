package A5_Dijkstra;

public interface DiGraph_Interface {
	// Attempts to add a new Vertex to the DiGraph and return true.
	// returns false if the add fails
	boolean addNode(long idNum, String label);
	
	// Attempts to add a new Edge between two Vertices in the DiGraph
	// returns true if successful, false otherwise
	boolean addEdge(long idNum, String sLabel, String dLabel, long weight, String eLabel);
	
	// Attempts to remove a Vertex from the DiGraph and return true.
	// returns false if the delete fails
	boolean delNode(String label);
	
	// Attempts to remove an Edge from the DiGraph and return true.
	// returns false if the delete fails
	boolean delEdge(String sLabel, String dLabel);
	
	// Returns the number of Nodes in the DiGraph
	long numNodes();
	
	// Returns the number of Edges in the DiGraph
	long numEdges();
	
	// Returns an array of the shortest paths from a start Vertex
	ShortestPathInfo[] shortestPath(String label);
}
package DiGraph_A5;

import java.util.ArrayList;

public interface Vertex_Interface {
	// Returns the idNum of the Vertex
	long getIdNum();
	
	// Returns the label of the Vertex
	String getLabel();
	
	// Returns the Edge associated with a destination Vertex
	Edge getEdge(String destination);
	
	// Returns the ArrayList of adjacent Vertexes
	ArrayList<String> getAdjacents();
	
	// Returns true if the Vertex has an edge, false otherwise
	boolean containsEdge(long idNum);
	
	// Returns true if the Vertex has an adjacent Vertex, false otherwise
	boolean hasAdjacent(String destination);
	
	// Adds an edge to the Vertex
	void addEdge(Edge edge, String destinatino);
	
	// Remove an Edge from the Vertex
	void removeEdge(String destination, boolean flag);
	
	// Returns the ArrayList of in Edges
	ArrayList<Edge> getEdgeIn();
}

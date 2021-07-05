package DiGraph_A5;

import java.util.HashMap;
import java.util.ArrayList;

public class Vertex implements Vertex_Interface {
	// Private Fields
	private long idNum;
	private String label;
	private HashMap<Long, Edge> edgeOut;
	private HashMap<String, Edge> adjacency;
	private ArrayList<Edge> edgeIn;
	private ArrayList<String> adjacents;

	// Public Constructors
	public Vertex(long idNum, String label) {
		this.idNum = idNum;
		this.label = label;
		this.edgeOut = new HashMap<Long, Edge>();
		this.adjacency = new HashMap<String, Edge>();
		this.edgeIn = new ArrayList<Edge>();
		this.adjacents = new ArrayList<String>();
	}

	// Vertex_Interface Methods

	// Returns the idNum of the Vertex
	public long getIdNum() {
		return idNum;
	}

	// Returns the label of the Vertex
	public String getLabel() {
		return label;
	}

	// Returns the ArrayList of in Edges
	public ArrayList<Edge> getEdgeIn() {
		return edgeIn;
	}
	
	// Returns the ArrayList of adjacent Vertexes
	public ArrayList<String> getAdjacents() {
		return adjacents;
	}
	
	// Returns the Edge associated with a destination Vertex
	public Edge getEdge(String destination) {
		return adjacency.get(destination);
	}

	// Returns true if the Vertex has an edge, false otherwise
	public boolean containsEdge(long idNum) {
		return edgeOut.containsKey(idNum);
	}

	// Returns true if the Vertex has an adjacent Vertex, false otherwise
	public boolean hasAdjacent(String destination) {
		return adjacency.containsKey(destination);
	}

	// Adds an Edge to the Vertex
	public void addEdge(Edge edge, String destination) {
		edgeOut.put(edge.getIdNum(), edge);
		adjacency.put(destination, edge);
		adjacents.add(destination);
	}

	// Removes an Edge from the Vertex
	public void removeEdge(String destination, boolean flag) {
		edgeOut.remove(adjacency.get(destination).getIdNum());
		adjacency.remove(destination);
		if (flag) {
			adjacents.remove(destination);
		}
	}
	
	// RemoveEdge with optional Parameters
	public void removeEdge(String destination) {
		removeEdge(destination, true);
	}
	
}

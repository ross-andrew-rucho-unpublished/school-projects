package DiGraph_A5;

import java.util.HashMap;
import java.util.ArrayList;

public class DiGraph implements DiGraph_Interface {
	// Private Fields
	private HashMap<Long, String> IDgraph;
	private HashMap<String, Vertex> lgraph;
	private ArrayList<String> nodes;
	private long numNodes;
	private long numEdges;

	// Public Constructor
	public DiGraph() {
		this.IDgraph = new HashMap<Long, String>();
		this.lgraph = new HashMap<String, Vertex>();
		this.nodes = new ArrayList<String>();
		this.numNodes = 0;
		this.numEdges = 0;
	}

	// DiGraph_Interface Methods

	// Attempts to add a new Vertex to the DiGraph and return true.
	// returns false if the add fails
	public boolean addNode(long idNum, String label) {
		// Checks to make sure that the add is valid
		if (idNum < 0 || IDgraph.containsKey(idNum) || label == null || lgraph.containsKey(label)) {
			return false;
		}

		// Add the mapping to both HashMaps
		Vertex newNode = new Vertex(idNum, label);
		IDgraph.put(idNum, label);
		lgraph.put(label, newNode);
		nodes.add(label);
		numNodes++;
		return true;
	}

	// Attempts to add a new Edge between two Vertices in the DiGraph
	// returns true if successful, false otherwise
	public boolean addEdge(long idNum, String sLabel, String dLabel, long weight, String eLabel) {
		// Checks to make sure that the add is valid
		if (idNum < 0 || !lgraph.containsKey(sLabel) || !lgraph.containsKey(dLabel)
				|| lgraph.get(sLabel).containsEdge(idNum) || lgraph.get(sLabel).hasAdjacent(dLabel)) {
			return false;
		}

		// Add the Edge to the Vertex
		Edge newEdge = new Edge(idNum, eLabel, weight, sLabel, dLabel);
		lgraph.get(sLabel).addEdge(newEdge, dLabel);
		lgraph.get(dLabel).getEdgeIn().add(newEdge);
		numEdges++;
		return true;
	}

	// Optional addEdge with different Signature
	public boolean addEdge(long idNum, String sLabel, String dLabel, long weight) {
		return addEdge(idNum, sLabel, dLabel, weight, null);
	}

	// Optional addEdge with different Signature
	public boolean addEdge(long idNum, String sLabel, String dLabel, String eLabel) {
		return addEdge(idNum, sLabel, dLabel, 1, eLabel);
	}

	// Optional addEdge with different Signature
	public boolean addEdge(long idNum, String sLabel, String dLabel) {
		return addEdge(idNum, sLabel, dLabel, 1, null);
	}

	// Attempts to remove a Vertex from the DiGraph and return true.
	// returns false if the delete fails
	public boolean delNode(String label) {
		// Checks to make sure that the delete is valid
		if (!lgraph.containsKey(label)) {
			return false;
		}

		// Removes all of the incoming Edges
		ArrayList<Edge> tempE = lgraph.get(label).getEdgeIn();
		for (int i = 0; i < tempE.size(); i++) {
			lgraph.get(tempE.get(i).getDestination()).removeEdge(label);
			numEdges--;
		}
		tempE.clear();

		// Removes all of the outgoing Edges
		ArrayList<String> tempV = lgraph.get(label).getAdjacents();
		for (int i = 0; i < tempV.size(); i++) {
			lgraph.get(label).removeEdge(tempV.get(i), false);
			lgraph.get(tempV.get(i)).getEdgeIn().remove(lgraph.get(label).getEdge(tempV.get(i)));
			numEdges--;
		}
		tempV.clear();

		// Delete the Vertex
		IDgraph.remove(lgraph.get(label).getIdNum());
		nodes.remove(label);
		lgraph.remove(label);
		numNodes--;
		return true;
	}

	// Attempts to remove an Edge from the DiGraph and return true.
	// returns false if the delete fails
	public boolean delEdge(String sLabel, String dLabel) {
		// Checks to make sure that the delete is valid
		if (!lgraph.containsKey(sLabel) || !lgraph.containsKey(dLabel) || !lgraph.get(sLabel).hasAdjacent(dLabel)) {
			return false;
		}

		// Removes the Edge from the Vertex
		lgraph.get(sLabel).removeEdge(dLabel);
		lgraph.get(dLabel).getEdgeIn().remove(lgraph.get(sLabel).getEdge(dLabel));
		numEdges--;
		return true;
	}

	// Returns the number of Nodes in the DiGraph
	public long numNodes() {
		return numNodes;
	}

	// Returns the number of Edges in the DiGraph
	public long numEdges() {
		return numEdges;
	}

}

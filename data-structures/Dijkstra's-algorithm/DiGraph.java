package A5_Dijkstra;

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

	// Returns an array of the shortest paths from a start Vertex
	public ShortestPathInfo[] shortestPath(String label) {
		// Declare the ShortestPathInfo Array, known Hash Map, and dv Hash Map
		ShortestPathInfo[] info = new ShortestPathInfo[(int) numNodes];
		HashMap<String, Boolean> known = new HashMap<String, Boolean>();
		HashMap<String, Integer> dv = new HashMap<String, Integer>();

		// Initialize the Minimum Binary Heap
		MinBinHeap DijkstraBin = new MinBinHeap();
		DijkstraBin.insert(new EntryPair(label, 0));
		dv.put(label, 0);
		int count = 0;

		// Loop through all of the priority queue
		while (DijkstraBin.size() > 0) {
			// Grab the next Vertex on the Priority Queue and remove it
			EntryPair cur = DijkstraBin.getMin();
			DijkstraBin.delMin();

			// Check to make sure that this node hasn't been processed before
			if (!known.containsKey(cur.getValue())) {
				// Mark the node as known and store it's information
				known.put(cur.getValue(), true);
				info[count] = new ShortestPathInfo(cur.getValue(), dv.get(cur.getValue()));
				count++;

				// Loop through all adjacent nodes
				for (String node : lgraph.get(cur.getValue()).getAdjacents()) {
					// Determine if the adjacent node is known
					if (!known.containsKey(node)) {
						// Determine if distance is shorter than previous distances
						if (!dv.containsKey(node) || dv.get(node) > dv.get(cur.getValue())
								+ lgraph.get(cur.getValue()).getEdge(node).getWeight()) {
							dv.put(node, (int) (dv.get(cur.getValue())
									+ lgraph.get(cur.getValue()).getEdge(node).getWeight()));
							DijkstraBin.insert(new EntryPair(node, (int) (dv.get(cur.getValue())
									+ lgraph.get(cur.getValue()).getEdge(node).getWeight())));
						}

					}
				}
			}
		}

		// Handle unconnected graphs
		int i = 0;
		while (count < numNodes) {
			if(!dv.containsKey(nodes.get(i))) {
				info[count] = new ShortestPathInfo(nodes.get(i), -1);
				count++;
			}
			i++;
		}

		// Return the shortest path info
		return info;
	}
}

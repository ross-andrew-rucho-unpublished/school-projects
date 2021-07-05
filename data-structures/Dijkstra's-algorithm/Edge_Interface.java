package A5_Dijkstra;

public interface Edge_Interface {
	// Returns the idNum of an Edge
	long getIdNum();
	
	// Returns the label of an Edge
	String getLabel();
	
	// Returns the weight of an Edge
	long getWeight();
	
	// Returns the source Vertex of an Edge
	String getSource();
	
	// Returns the destination Vertex of an Edge
	String getDestination();
}

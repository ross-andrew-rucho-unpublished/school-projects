package DiGraph_A5;

public class Edge implements Edge_Interface {
	// Private Fields
	private long idNum;
	private String label;
	private long weight;
	private String source;
	private String destination;
	
	// Public Constructor
	public Edge(long idNum, String label, long weight, String source, String destination) {
		this.idNum = idNum;
		this.label = label;
		this.weight = weight;
		this.source = source;
		this.destination = destination;
	}
	
	// Edge_Interface Methods
	
	// Returns the idNum of the Edge
	public long getIdNum() {
		return idNum;
	}
	
	// Returns the label of the Edge
	public String getLabel() {
		return label;
	}
	
	// Returns the weight of the Edge
	public long getWeight() {
		return weight;
	}
	
	// Returns the start Vertex of the Edge
	public String getSource() {
		return source;
	}
	
	// Returns the end Vertex of the Edge
	public String getDestination() {
		return destination;
	}
}

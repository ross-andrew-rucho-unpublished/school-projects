package A5_Dijkstra;

public class DiGraphPlayground {

  public static void main (String[] args) {
  
      // thorough testing is your responsibility
      //
      // you may wish to create methods like 
      //    -- print
      //    -- sort
      //    -- random fill
      //    -- etc.
      // in order to convince yourself your code is producing
      // the correct behavior
      exTest();
    }
  
    public static void exTest(){
    		DiGraph d = new DiGraph();
    		
    		d.addNode(0, "A");
    		d.addNode(1, "B");
    		d.addNode(2, "C");
    		d.addNode(3, "D");
    		d.addNode(4, "E");
    		d.addNode(5, "F");
    		d.addNode(6, "G");
    		
    		d.addEdge(0, "A", "B", 4);
    		d.addEdge(1, "A", "C", 2);
    		d.addEdge(2, "A", "G", 3);
    		d.addEdge(3, "B", "D", 3);
    		d.addEdge(4, "B", "F", 4);
    		d.addEdge(5, "B", "G", 2);
    		d.addEdge(6, "C", "B", 1);
    		d.addEdge(7, "C", "G", 1);
    		d.addEdge(8, "D", "E", 2);
    		d.addEdge(9, "D", "F", 1);
    		d.addEdge(10, "F", "E", 2);
    		d.addEdge(11, "G", "D", 1);
    		d.addEdge(12, "G", "F", 2);
    		
    		ShortestPathInfo[] info = d.shortestPath("A");
    		for (int i = 0; i < info.length; i++) {
    			System.out.println(info[i].toString());
    		}
    		
    		

    }
}
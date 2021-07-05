package DiGraph_A5;

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
        d.addNode(0, "0");
        for(int i = 1; i < 1000000; i++) {
      	  	d.addNode(i, "" + i);
      	  	d.addEdge(i, "" + i, "" + (i - 1));
        }
        System.out.println("numEdges: "+d.numEdges());
        System.out.println("numNodes: "+d.numNodes());
    }
}
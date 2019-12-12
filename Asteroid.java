package asteroidfield;
import blobzx.BlobUtils;
import blobzx.PolyBlob;
import blobzx.*;
import java.util.*;
import java.util.Random;
import java.lang.Math;


public class Asteroid extends PolyBlob {
    
    private static Random random = new Random();
    
    double angle[] = new double[9];
    private int [] ix = new int[9];
    private int []iy = new int[9];
    private double dx[] = new double[9];
    private double dy[] = new double[9];
    private int numberSides;
    private int[] distance = new int[9];
    
    public Asteroid(int idx, int jdx, double rot) {
        super(-100, -100, rot);
        setDelta(idx, jdx);
        
        // The number of sides the polygon will have
        int numberSides = random.nextInt(10-5) + 5;
        
        double region = (Math.PI * 2)/numberSides;
        
        for (int i = 0; i<numberSides; i++) 
        {
            angle[i] = (i *region) + (Math.random()*region);
            distance[i] = random.nextInt(11) +5;
        }
       for (int j = 0; j<numberSides; j++)
       {
          dx[j] = BlobUtils.rotatePoint(distance[j], angle[j]).getX();
          dy[j] = BlobUtils.rotatePoint(distance[j], angle[j]).getY();
       }
       for (int k =0; k<dx.length; k++)
       {
           ix[k] = (int) dx[k];
       }
       for (int k =0; k<dy.length; k++)
       {
           iy[k] = (int) dy[k];
       }
       setPolygon(ix,iy);
       setRate(rot);
    }
}
}

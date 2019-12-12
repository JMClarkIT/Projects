package asteroidgame;

import blobzx.BlobUtils;
import blobzx.PolyBlob;
import blobzx.*;
import java.awt.Point;
import java.util.*;
import java.util.Random;
import java.lang.Math;


public class AsteroidGame implements BlobGUI {

    private SandBox sb;
    private double rotation;
    private static Random random = new Random();
    
    public AsteroidGame()
    {
        sb = new SandBox();
        sb.setSandBoxMode(SandBoxMode.FLOW);
        sb.setFrameRate((long)15.0);
        sb.init(this);
        SandBox.simulate(sb);
    }
    public static void main(String[] args) {
        new AsteroidGame();
    }
    
    /*
       The generate method overrides the previous method in the superclass.
       It simply instantiates a new rocket and asteroid, then adds them to the
       SandBox.
    */
    @Override
    public void generate()
    {
        sb.addBlob(new Rocket(300,300,sb));
        
        int idx, idy;
        rotation = 0.1;
        for (int i = 0; i  < 10; i++)
        {
            idx = random.nextInt(7)-3;
            idy = random.nextInt(7)-3;
            
            while(idx == 0 || idy == 0)
            {
                idx = random.nextInt(7)-3;
                idy = random.nextInt(7)-3;
            }
            if(random.nextInt(100)%2 == 0)
            {
                rotation = -0.1;
            }
            sb.addBlob(new Asteroid(idx, idy, rotation));
        }
        sb.showBlobs();
    }
}
}

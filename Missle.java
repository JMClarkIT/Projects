package asteroidgame;

import blobzx.BlobUtils;
import blobzx.PolyBlob;
import blobzx.*;
import java.awt.Point;
import java.util.*;
import java.util.Random;
import java.lang.Math;


public class Missle extends Blob implements BlobProximity {
    private static final int speed = 5;
    private static final int size = 5;
    
    public Missle(int idx, int idy, double angle)
    {
        super(idx, idy, size);
        
        int dx = (int) Math.round(speed * Math.cos(angle));
        int dy = (int) Math.round(speed * Math.sin(angle));
        
        setDelta(dx, dy);
    }
}
}

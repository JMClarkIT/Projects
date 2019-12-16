package synchro;

public class SynchronizedBuffer {
    public String d = "NIL";
    private boolean occupied = false;
  
  
    public synchronized void setString(String str) throws InterruptedException{
        int w = 1;
        while (occupied) {
            System.out.printf("%1$-30s %2$-9s %3$-10s\\n\\n",
                    "Producer wait # " + w, d, occupied);
            wait();
            w += 1;
        }
        d = str;
        occupied = true;
        System.out.printf("Producer writes: %s\\n", str);
        notifyAll();
    }
  
     public synchronized String getString() throws InterruptedException{
         int w = 1;
         while(!occupied) {
            System.out.printf("%1$-30s %2$-9s %3$-10s\\n\\n",
                    "Consumer wait # " + w, d, occupied);
            wait();
            w += 1;
         }
         String rBuff = d;
         occupied = false;
         notifyAll();
       
         System.out.printf("Consumer reads: %s\\n\\n", rBuff);
         return rBuff;
    }
}
}

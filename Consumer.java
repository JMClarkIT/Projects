package synchro;

import java.security.SecureRandom;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Consumer implements Runnable {
    private final static SecureRandom ran = new SecureRandom();
    private final SynchronizedBuffer sb;
  
    public Consumer(SynchronizedBuffer sb) {
        this.sb = sb;
    }
  
    @Override
    public void run() {
        int dTotal = 0;
        String word = "";
        StringBuilder sent = new StringBuilder();
        while(!"@@@".equals(word)) {
            try {
                int delay = ran.nextInt(1000);
                dTotal += delay;
                Thread.sleep(delay);
                word = sb.getString();
                sent.append(word);
                if (!"@@@".equals(word))
                    sent.append(" ");
            } catch (InterruptedException ex) {
                Logger.getLogger(Consumer.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
      
        System.out.printf("Consumer Summary: %s\\nTotal sleep time: %d milliseconds\\n\\n",
                sent, dTotal);
    }
}
}

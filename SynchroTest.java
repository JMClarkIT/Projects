package synchro;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class SynchroTest {

    
    public static void main(String[] args) {
        SynchronizedBuffer sb = new SynchronizedBuffer();
      
        Consumer con = new Consumer(sb);
        Producer pro = new Producer(sb);
        
        System.out.println("University of Central Florida");
        System.out.println("COP 3330 (Spring 2016) Program 8: Synchronized Buffer");
        System.out.println("Author: Jamal Clark\\n");
        
        System.out.printf("%1$-30s %2$-9s %3$-10s\\n", "Operation", "Buffer", "Occupied");
        System.out.printf("%1$-30s %2$-9s %3$-10s\\n", "---------", "------", "--------");
      
        ExecutorService executorService = Executors.newCachedThreadPool();
      
        executorService.execute(con);
        executorService.execute(pro);
      
        executorService.shutdown();
    }
  
}}

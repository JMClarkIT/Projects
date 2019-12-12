package sentenceutils;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.io.BufferedReader;
import java.util.StringTokenizer;


public class SentenceUtilsTest 
{
    
    private static ArrayList<String> slist = new ArrayList<String>();
    
    public static void main(String[] args) throws FileNotFoundException{
        
            File file = new File( args[ 0 ]);
            
            Scanner scanner = new Scanner( new FileInputStream(file));
            
            int count1 = 0;
            while (scanner.hasNextLine() ) {
                String sent = scanner.nextLine();
                count1++;
                if (sent.trim().length() > 0) {
                    slist.add(sent);
                }
            }
            
            System.out.printf("\\n\\nSentence Utility Tester by Jamal Clark\\n\\n");
            System.out.printf("File that was read: %s\\n", args);
            System.out.printf("The file contains %d sentences", count1);
            System.out.printf("\\n\\nSentence reports: \\n\\n");
            SentenceUtils printSentence = new SentenceUtils(slist); 
        }
           
            
}
}

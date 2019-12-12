package sentenceutils;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.io.BufferedReader;
import java.util.Scanner;
import java.util.StringTokenizer;


public class SentenceUtils {
    
    private ArrayList<String> sentences;
    private String[] tokens;
    private String[] shingles;
    
    public SentenceUtils(ArrayList<String> slist) {
        
        sentences = slist;
        report(sentences);
        
    }
    
    void generateTokens(String s) {
        tokens = s.split(" ");
        int count = 0;
        for (String token : tokens)
        {
            System.out.println(count + ":" + token);
            count++;
        }
    }
    
    private void generateShingles(String s) {
        
        shingles = new String[s.length() - 1];
        for (int i = 0; i < s.length() - 1; i++) {
            shingles[i] = s.substring(i, i + 2);
            System.out.print(s.substring(i, i + 2) + " ");
        }
        System.out.println();
    }
    
    
    public void report(ArrayList<String> slist) {
        int sentenceNum = 0;
        for (String s: slist) {
            System.out.println("Sentence " +  sentenceNum + ";");
            sentenceNum++;
            System.out.println(s);
            generateTokens(s);
            generateShingles(s);
            System.out.println();
        }
        
        
    }
    
}
}

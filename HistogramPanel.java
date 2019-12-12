package histogram;

import java.awt.Color;
import java.awt.Graphics;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

public class HistogramPanel extends JPanel {
   
   private List<String> sents;
   private int snum;
   
   
   public String readFile( File file ) {
      sents = new ArrayList();
      snum = -1;
      clearDisplay( this.getGraphics() );
      StringBuilder sb = new StringBuilder();
      try {
          
         Scanner scanner = new Scanner( new FileInputStream(file));
         while( scanner.hasNextLine() ) {
            sents.add( scanner.nextLine() );
         }
         
         for( int i = 0; i < sents.size(); i++ ) {
            sb.append(i + " : " + sents.get( i ) + "\\n\\n");
         }
      } catch (FileNotFoundException ex) {
         Logger.getLogger(HistogramPanel.class.getName()).log(Level.SEVERE, null, ex);
      }
      return sb.toString().trim();
      
   }
   
   
   @Override
   public void paintComponent( Graphics gc ) {
      super.paintComponent( gc );
      if( sents != null && snum >= 0 && snum < sents.size() ) {
         showHisto( snum, true );
      }
   }
   
   public void showHisto() {
      this.setBackground( Color.white );
      showHisto( snum, false );
   }
   
   public void showHisto( int n, boolean b ) {            
      if( sents != null && n >= 0 && n < sents.size() ) {
         snum = n;
         Graphics gc = this.getGraphics();
         clearDisplay( gc );
         drawLines( gc );
         drawHisto( gc );
      }
      else if( b && sents != null ) {
         JOptionPane.showMessageDialog(this, "Sentence index out of range");
      }
   }
   
   private void clearDisplay( Graphics gc ) {      
      gc.setColor( Color.WHITE );
      gc.fillRect(0,0,this.getWidth(),this.getHeight());
   }
   
  
  
   private void drawLines( Graphics gc ) {
       int x = this.getWidth()/10; 
       int y = this.getHeight()/10;
       gc.setColor(Color.RED);
       gc.drawLine(x, y, x, y*9);
       gc.drawLine(x, y*9, x*9, y*9);
   
   }
   
   private void drawHisto( Graphics gc ) {
        int x = this.getWidth()/10; 
        int y = this.getHeight()/10;
        int max = 0, c;
       int counts[] = new int[26];
     
       String line = sents.get(snum).toLowerCase();
    
       for (int i = 0; i < line.length(); i++) {
            c = line.charAt(i) - 'a';
          
            if (c >= 0 && c < 26) {
                counts[c]++;
                max = Math.max(max,counts[c]);
            }
       }
     
       gc.setColor(Color.BLUE);
     
       int width = x*8/26;
       for (int i = 0; i < counts.length; i++) {
           int height = y*8*counts[i]/max;
           gc.drawRect(x + i*width, y*9 - height, width, height);
       }
   
   }

}
}

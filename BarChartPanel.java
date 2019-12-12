package histogram;

import java.awt.Color;
import java.awt.Graphics;
import javax.swing.JPanel;


public class BarChartPanel extends JPanel {
    
    private int[] histo = new int[ 26 ];
    private int maxHeight = 260;
    
    public void setHisto( int[] inputHisto) {
        scale( inputHisto );
    }
    
    @Override
    public void paintComponent( Graphics gc ) {
        super.paintComponent(gc);
        clearDisplay( gc );
        drawLines( gc );
        drawHisto( gc );
    }
    
    private void clearDisplay( Graphics gc) {
        gc.setColor( Color.WHITE);
        gc.fillRect(0, 0, this.getWidth(), this.getHeight()); 
    }
    
    private void drawLines( Graphics gc) {
        gc.setColor(Color.BLACK);
        gc.drawLine(50, 30, 50, 300);
        gc.drawLine(50, 300, 360, 300);
    }
    
    private void drawHisto( Graphics gc) {
        for (int i = 0; i < histo.length; i++)
        {
            int x = 50 + 10 * i;
            int y = 40 + (260-histo[i]);
            gc.drawRect(x, y, 10, histo[i]);
        }
    }
    
    private void scale( int [] inp )
    {
        int max = findMax(inp);
        for (int i = 0; i < histo.length; i++)
        {
            double scaled = maxHeight*((double) inp[i]/max);
            histo[i] = (int) Math.floor(scaled);
        }
    }
    
    private int findMax(int[] inp)
    {
        int max = inp[0];
        for (int i = 0; i < inp.length; i++)
        {
            if (inp[i] > max) {
                max = inp[i];
            }
        }
        return max;
    }
}
}

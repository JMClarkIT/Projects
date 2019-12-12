package histogram;

import javax.swing.JFrame;
import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JPanel;


public class BarChart {
   
    public static void main( String[] args) {
        
        JFrame frame = new JFrame();
        frame.setLayout(new BorderLayout() );
        
        BarChartPanel panel = new BarChartPanel();
        frame.add(panel, BorderLayout.CENTER);
        
        JPanel topPanel = new JPanel();
        JButton button = new JButton("Enter Text");
        
        button.addActionListener(
            new java.awt.event.ActionListener() {
                @Override
                public void actionPerformed( ActionEvent evt ) {
                    String s = JOptionPane.showInputDialog( "Enter text to analyze");
                    if ( s != null && s.trim().length() > 0) {
                        int [] ltrs = histo( s );
                        panel.setHisto(ltrs);
                    }
                    panel.repaint();
                }
            }    
        );
        
        topPanel.add(button);
        frame.add(topPanel, BorderLayout.NORTH);
        
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize( 400, 400 );
        frame.setVisible(true);
    }
    
    public static int[] histo( String s ) {
        s = s.toLowerCase();
        int[] letter = new int [26];
        for ( int i = 0; i < s.length(); i++)
        {
            char ch = s.charAt(i);
            if ( Character.isLetter(ch) ) {
                int num = ch - 'a';
                letter[ num ]++;
            }
        }
        return letter;
    }
}
}

package histogram;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.JTextArea;
import javax.swing.text.Document;

public class Histogram extends javax.swing.JFrame {

   private javax.swing.JScrollPane jScrollPane1;
   private javax.swing.JSplitPane jSplitPane1;
   private javax.swing.JButton loadButton;
   private javax.swing.JPanel mainPanel;
   private javax.swing.JTextField numField;
   private javax.swing.JButton showButton;
   private javax.swing.JTextArea sourceArea;
   private javax.swing.JPanel topPanel;

   private histogram.HistogramPanel outPanel;

   
   /**
    * Creates new HistoFrame
    */
   public Histogram() {
      initComponents();
      this.setTitle("Sentence Histograms by Jamal Clark");
   }

   
   private void initComponents() {

      topPanel = new javax.swing.JPanel();
      loadButton = new javax.swing.JButton();
      showButton = new javax.swing.JButton();
      numField = new javax.swing.JTextField();
      mainPanel = new javax.swing.JPanel();
      jSplitPane1 = new javax.swing.JSplitPane();
      jScrollPane1 = new javax.swing.JScrollPane();
      sourceArea = new javax.swing.JTextArea();
      outPanel = new histogram.HistogramPanel();

      setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

      topPanel.setBackground(new java.awt.Color(230, 240, 255));
      topPanel.setPreferredSize(new java.awt.Dimension(686, 40));

      loadButton.setText("Load File");
      loadButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            loadButtonActionPerformed(evt);
         }
      });
      topPanel.add(loadButton);

      showButton.setText("Show Histo for Sentence");
      showButton.setEnabled(false);
      showButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            showButtonActionPerformed(evt);
         }
      });
      topPanel.add(showButton);

      numField.setColumns(3);
      numField.setEnabled(false);
      numField.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(java.awt.event.ActionEvent evt) {
            numFieldActionPerformed(evt);
         }
      });
      topPanel.add(numField);

      getContentPane().add(topPanel, java.awt.BorderLayout.PAGE_START);

      mainPanel.setLayout(new javax.swing.BoxLayout(mainPanel, javax.swing.BoxLayout.X_AXIS));

      jScrollPane1.setVerticalScrollBarPolicy(javax.swing.ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);

      sourceArea.setColumns(20);
      sourceArea.setLineWrap(true);
      sourceArea.setRows(5);
      jScrollPane1.setViewportView(sourceArea);

      jSplitPane1.setLeftComponent(jScrollPane1);

      outPanel.setBackground(new java.awt.Color(230, 230, 230));
      outPanel.addComponentListener(new java.awt.event.ComponentAdapter() {
         public void componentResized(java.awt.event.ComponentEvent evt) {
            outPanelComponentResized(evt);
         }
      });

      javax.swing.GroupLayout outPanelLayout = new javax.swing.GroupLayout(outPanel);
      outPanel.setLayout(outPanelLayout);
      outPanelLayout.setHorizontalGroup(
         outPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
         .addGap(0, 128, Short.MAX_VALUE)
      );
      outPanelLayout.setVerticalGroup(
         outPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
         .addGap(0, 256, Short.MAX_VALUE)
      );

      jSplitPane1.setRightComponent(outPanel);

      mainPanel.add(jSplitPane1);

      getContentPane().add(mainPanel, java.awt.BorderLayout.CENTER);

      pack();
   }

   private void loadButtonActionPerformed(java.awt.event.ActionEvent evt) {
       JFileChooser fileChooser = new JFileChooser();
       fileChooser.setCurrentDirectory(new File(System.getProperty("user.home")));
       int result = fileChooser.showOpenDialog(this);
       if (result == JFileChooser.APPROVE_OPTION) {
           File selectedFile = fileChooser.getSelectedFile();
           String str = outPanel.readFile(selectedFile);
           sourceArea.append(str);
           showButton.setEnabled(true);
           numField.setEnabled(true);
           numField.setText("");
       }
       
   }

   private void showButtonActionPerformed(java.awt.event.ActionEvent evt) {
       try {
           int idx = Integer.parseInt(numField.getText());
           outPanel.showHisto(idx, true);

       } catch(NumberFormatException e) {
              JOptionPane.showMessageDialog(this, "Text Field is not an integer");
            }
   }

   private void numFieldActionPerformed(java.awt.event.ActionEvent evt) {
      showButtonActionPerformed( evt );
   }

   private void outPanelComponentResized(java.awt.event.ComponentEvent evt) {
      outPanel.showHisto();
   }

   
   public static void main(String args[]) {
      try {
         for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
            if ("Nimbus".equals(info.getName())) {
               javax.swing.UIManager.setLookAndFeel(info.getClassName());
               break;
            }
         }
      } catch (ClassNotFoundException | InstantiationException | 
		IllegalAccessException | javax.swing.UnsupportedLookAndFeelException ex) {
         java.util.logging.Logger.getLogger(Histogram.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
      }

      java.awt.EventQueue.invokeLater(new Runnable() {
         public void run() {
            new Histogram().setVisible(true);
         }
      });
   }

}
}

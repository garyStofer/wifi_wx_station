/*********************************************************************
*
*  TCPIP Microchip devices discoverer GUI
*
**********************************************************************
* FileName:        TCPIPDiscovererTool.java
* Complier:        JAVA version "1.6.0_20 and onwards"
* IDE :            Netbean
* Software License Agreement
*
* Copyright (C) 2012 Microchip Technology Inc.  All rights reserved.
*
* Microchip licenses to you the right to use, modify, copy, and
* distribute the Software when used with a Microchip microcontroller or
* digital signal controller product which is integrated into Licensee's product.
*
* You should refer to the license agreement accompanying this
* Software for additional information regarding your rights and
* obligations.
*
* THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
* WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
* LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
* MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
* CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
* PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
* BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
* THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
* SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
* (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE
**********************************************************************/

package TCPIP_Discoverer;
import java.awt.*;
import java.net.*;
import java.io.*;
import javax.swing.*;
import java.awt.Desktop;
import javax.swing.table.*;
import java.util.concurrent.locks.*;

public class TCPIPDiscovererTool extends javax.swing.JFrame 
{
    private  DatagramSocket socket ;
    private  Thread recvThread=null;
    private static final int   Discoveryport =30303;    
    private static final String DiscoveryMessage = new String("Discovery: Who is out there?\0\n");

    private ReentrantLock lock = new ReentrantLock();
    private ImageIcon icon;
    
    
    
    /** Creates new form TCPIPDiscovererTool */
    public TCPIPDiscovererTool() 
    {
        initComponents();
        icon = new ImageIcon(getClass().getResource("/Resource/RoosterArrow.png"));
        setIconImage(icon.getImage());
        changeTableColumnWidth();
        UIManager.put("Button.defaultButtonFollowsFocus", Boolean.TRUE);
        setLocation(200, 150);
        
    }

            
 /* Table updation Thread */
    private void addDiscoveryEntry(String receivePacket)
    {
        String[] s = receivePacket.split("\n");
        if(s[3].contains("                                                                ")== true)
            s[3] = "";
       
        DefaultTableModel model  = (DefaultTableModel)jTable1.getModel();
        int rowCnt = model.getRowCount();
        // to avoid the same mac
        for(int index=0;index<rowCnt;index++)
        {
            String macAddrs = (String)model.getValueAt(index,2);
            if(macAddrs.isEmpty() == false)
            {
                if(s[2].contentEquals(macAddrs))
                {
                    model.removeRow(index);
                    model.insertRow(index,s);
                    return;
                }
            }
        }
        model.insertRow(0,s);

    }

    /* Receive thread function*/
    private  void receiveUDPPacket()
    {
        String s_buff;
        byte[] buf = new byte[100];
         
        try
        {
            while(true)
            {
                for(int i=0;i<buf.length;i++)
                    buf[i]=' ';
                
                DatagramPacket packet = new DatagramPacket(buf, buf.length);

                try
                {
                    socket.receive(packet);
                }
                catch(SocketTimeoutException  e)  // this should never happen sice the timeout is set to infinity
                {
                    continue;
                }
           
                if(packet.getLength() < 36)     // not enough data to be a valid response
                    continue;

                s_buff = new String(packet.getData());
               
                if(s_buff.trim().length() == 0)
                    continue;

                lock.lock();
                s_buff = packet.getAddress().getHostAddress()+"\n"+s_buff.replace("\r\n", "\n");
                addDiscoveryEntry(s_buff);
                lock.unlock();
            }
        }
        catch (IOException e)
        {
           
            JOptionPane.showMessageDialog(null,"Exception trying to read device response\n"+e.getMessage(),"Error", JOptionPane.ERROR_MESSAGE); 
            udp_Close();
        }
    }
    
    // create datagram socket and start the thread listening for replies from devices
    // re-throws exception to be handled by caller 
    private void  
    udp_Connect() throws IOException
    {
        if( socket == null) 
        {
            socket = new DatagramSocket(Discoveryport);
            socket.setBroadcast(true);
            socket.setSoTimeout(0); // set indefinite timeout 
        }

        if (recvThread == null)
        {
            recvThread = new Thread()
            {
                @Override 
                public void run()
                {
                    receiveUDPPacket();
                }
            };
            recvThread.start();
       }

    }
    
    // close the socket and terminatethe receiving thread 
    private void udp_Close()
    {
        if(socket != null)
        {
            if(socket.isConnected() == true)
            {
                socket.close();
            }
            socket = null;
        }
        
        if(recvThread != null)
        {
            if(recvThread.isAlive() == true)
            {
                recvThread = null;
            }
            recvThread = null;
        }

    }
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        btnExit = new javax.swing.JButton();
        btnDiscover = new javax.swing.JButton();
        jScrollPane1 = new javax.swing.JScrollPane();
        jTable1 = new javax.swing.JTable();
        jTextField1 = new javax.swing.JTextField();
        jMenuBar1 = new javax.swing.JMenuBar();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("WWS Discoverer");
        setResizable(false);

        btnExit.setText("Exit");
        btnExit.setMaximumSize(new java.awt.Dimension(115, 23));
        btnExit.setMinimumSize(new java.awt.Dimension(115, 23));
        btnExit.setPreferredSize(new java.awt.Dimension(115, 23));
        btnExit.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnExitActionPerformed(evt);
            }
        });

        btnDiscover.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        btnDiscover.setLabel("Rescan");
        btnDiscover.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnRescanActionPerformed(evt);
            }
        });

        jTable1.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {

            },
            new String [] {
                "IP Address", "Host Name", "MAC Address", "Other Info"
            }
        ) {
            Class[] types = new Class [] {
                java.lang.String.class, java.lang.String.class, java.lang.String.class, java.lang.String.class
            };
            boolean[] canEdit = new boolean [] {
                false, false, false, false
            };

            public Class getColumnClass(int columnIndex) {
                return types [columnIndex];
            }

            public boolean isCellEditable(int rowIndex, int columnIndex) {
                return canEdit [columnIndex];
            }
        });
        jTable1.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        jTable1.getTableHeader().setReorderingAllowed(false);
        jTable1.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTable1MouseClicked(evt);
            }
        });
        jScrollPane1.setViewportView(jTable1);

        jTextField1.setText("Click on IP address to open browser");
        setJMenuBar(jMenuBar1);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addGap(30, 30, 30)
                .addComponent(jTextField1, javax.swing.GroupLayout.PREFERRED_SIZE, 227, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 187, Short.MAX_VALUE)
                .addComponent(btnDiscover)
                .addGap(36, 36, 36)
                .addComponent(btnExit, javax.swing.GroupLayout.PREFERRED_SIZE, 56, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(47, 47, 47))
            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(layout.createSequentialGroup()
                    .addContainerGap()
                    .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 630, Short.MAX_VALUE)
                    .addContainerGap()))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap(359, Short.MAX_VALUE)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(btnExit, javax.swing.GroupLayout.PREFERRED_SIZE, 32, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jTextField1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btnDiscover, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(layout.createSequentialGroup()
                    .addGap(26, 26, 26)
                    .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 300, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addContainerGap(76, Short.MAX_VALUE)))
        );

        btnDiscover.getAccessibleContext().setAccessibleDescription("");

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void btnExitActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnExitActionPerformed
        udp_Close();
        System.exit(0);
}//GEN-LAST:event_btnExitActionPerformed

    private void btnRescanActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnRescanActionPerformed
    
      
        DefaultTableModel model  = (DefaultTableModel)jTable1.getModel();
        
        // clear off the table to start from 
        for(int i=0; i < model.getRowCount();i++) 
            model.removeRow(0);
         
        try 
        {
            udp_Connect();
        
            InetAddress address = InetAddress.getByName("255.255.255.255");
            DatagramPacket packet = new DatagramPacket(DiscoveryMessage.getBytes(),DiscoveryMessage.length(), address, Discoveryport);
            socket.send(packet);
        }
        catch(IOException ex) 
        {
            udp_Close();
            String optionStr = "<html>Unable to transmit discovery message. <br> Check network " +
                    "connectivity and ensure that no other instance of this program is running.";

            JOptionPane.showMessageDialog(null,optionStr,
                    "Error", JOptionPane.ERROR_MESSAGE);
             
        }
}//GEN-LAST:event_btnRescanActionPerformed

    private void jTable1MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTable1MouseClicked
         
        Point pt = evt.getPoint();
        String url = "http://";
                
        url += (String)jTable1.getValueAt(jTable1.rowAtPoint(pt),0);
    
        try
        {
            URL myUrl = new URL(url);
            Desktop.getDesktop().browse(myUrl.toURI());
        }
        catch (Exception ex) 
        {
// TODO : say something went wrong        
        
        }
}//GEN-LAST:event_jTable1MouseClicked

    void changeTableColumnWidth()
    {
        TableColumn column;
        final TableCellRenderer tcr = jTable1.getTableHeader().getDefaultRenderer();
        
        jTable1.getTableHeader().setDefaultRenderer(new TableCellRenderer() {
            @Override
            public Component getTableCellRendererComponent(JTable table,
                    Object value, boolean isSelected, boolean hasFocus, int row, int column) {
                JLabel lbl = (JLabel) tcr.getTableCellRendererComponent
                        (table, value, isSelected, hasFocus, row, column);
                lbl.setBorder(BorderFactory.createCompoundBorder
                        (lbl.getBorder(), BorderFactory.createEmptyBorder(0,5, 0, 0)));
                lbl.setHorizontalAlignment(SwingConstants.LEFT);
                return lbl;
            }
        });
        /*
         * ((DefaultTableCellRenderer) jTable1.getTableHeader().getDefaultRenderer()).
                setHorizontalAlignment(SwingConstants.LEFT);
         */
        jTable1.setAutoResizeMode(JTable.AUTO_RESIZE_ALL_COLUMNS);
        jTable1.setDragEnabled(false);
        jTable1.setColumnSelectionAllowed(false);
        
        int colNumber = jTable1.getColumnCount();
        
        for (int i = 0; i < colNumber; i++) 
        {
            column = jTable1.getColumnModel().getColumn(i);

            switch(i)
            {
                case 0:
                    column.setPreferredWidth(100);
                    column.setMaxWidth(120);
                    break;
                case 1:
                    column.setPreferredWidth(100);
                    column.setMaxWidth(120);
                    break;
                case 2:
                    column.setPreferredWidth(130);
                    column.setMaxWidth(180);
                    break;
                case 3:
                    column.setPreferredWidth(100);//.setPreferedWidth(100);
                    //column.setMaxWidth(1000);
                    break;
            }
            column.setResizable(true);
        }
    }

    /**
    * Program Entry point. Sets the GUI look and feel and starts new GUI thread 
    */
    public static void main(String args[]) {
    try
    {
        javax.swing.UIManager.LookAndFeelInfo[] installedLookAndFeels=javax.swing.UIManager.getInstalledLookAndFeels();
        for (int idx=0; idx<installedLookAndFeels.length; idx++)
        if ("Nimbus".equals(installedLookAndFeels[idx].getName())) {
            javax.swing.UIManager.setLookAndFeel(installedLookAndFeels[idx].getClassName());
            break;
        }
    }catch (Exception e) 
    {
           // silently ignore any exceptions and just use what is provided
    }
    java.awt.EventQueue.invokeLater(new Runnable() 
    {
        public void run() {

            TCPIPDiscovererTool mainFrame = new TCPIPDiscovererTool();
            mainFrame.setVisible(true);
            mainFrame.btnRescanActionPerformed(null);
        }
    });
}

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btnDiscover;
    private javax.swing.JButton btnExit;
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JTable jTable1;
    private javax.swing.JTextField jTextField1;
    // End of variables declaration//GEN-END:variables

}

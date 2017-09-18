/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package SoilMoistSave;

import java.net.*;
import javax.swing.JOptionPane;
import javax.xml.parsers.*;
import org.w3c.dom.*;
import static java.nio.file.StandardOpenOption.*;
import java.nio.file.*;
import java.io.*;
import java.time.*;
import java.time.format.DateTimeFormatter;
/**
 *
 * @author Gary@Stofer.name
 */
public class WXSoilSave {

    private String Ip_addr;
    private File outputfile;
    
    //Constants 

    private static final String ADC_XML_file = "/status_adc.xml";
   // static final String Main_XML_file = "/sensors.xml";
    private static final float  ADC_scale[ ] = {3.3f/1023,
                                        3.3f/1023,
                                        3.3f/1023,
                                        330f/1023,
                                        15.95f/1023,
                                        6.6f/1023};
    
    
    public WXSoilSave( String Ip )
    {
        Ip_addr = Ip;
        String s = Ip_addr.replace('.', '_');
        s = s+".csv";
        outputfile = new File(s);
        
    }

    public  void Save_Record( )  
    {       
        String out_buff ="";

        LocalDateTime dateTime = LocalDateTime.now();
        String locDate = dateTime.format(DateTimeFormatter.ISO_LOCAL_DATE);
        String locTime = dateTime.withNano(0).format(DateTimeFormatter.ISO_LOCAL_TIME);
        
        //Try with resource for autoclose
        try (BufferedWriter out = Files.newBufferedWriter(outputfile.toPath(), CREATE,APPEND))
        {

            // Put in CSV header on beginning of file only 
            long len = outputfile.length();
            if (len == 0 )
            {
                out.write("Date,Time,SM1,SM2,SM3,STempF,VBatV,VSysV\n");
            }

            DocumentBuilderFactory fact = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = fact.newDocumentBuilder();
            
            out.write(locDate+","+ locTime) ; // == date, time
            
            URL myUrl = new URL("http://" + Ip_addr + ADC_XML_file); 
            URLConnection con = myUrl.openConnection();
            con.setConnectTimeout(5000);            // set faster timeouts
            con.setReadTimeout(5000);
            
            try (InputStream is = con.getInputStream())  //Try with resource for autoclose
            { 
                Document doc = builder.parse(is);
                NodeList nodelist = doc.getDocumentElement().getChildNodes();

                // go through the ADC readings and pull out the raw adc_count values
                // then scale up to voltage readings according to the scale table
                for (int i =0; i< nodelist.getLength();i++)
                {
                    Node node = nodelist.item(i);
                    if (node.getNodeType() == Node.ELEMENT_NODE)
                    {
                       String s = node.getNodeName();
                       if (s.matches("adc1."))
                       {
                           String sub = s.substring(4);         // get the ADC number after "adc1"
                           int adc_ndx = Integer.parseInt(sub);     // get the index from the ADC number

                           s = node.getTextContent();           // get the ADC value string
                           int adc_cnt = Integer.parseInt(s);   // get the integer value from string
                           float adc_V = adc_cnt * ADC_scale[adc_ndx];  // Scale the raw adcbits
                           out_buff += "," + String.format("%.2f", adc_V); // print reading with 2 decimals
                       }

                    }
                }
                out_buff += "\n";       // end of this line
                out.write(out_buff);
            } 
         } 
        
        catch (Exception e)
        {
            System.out.println(e);
            JOptionPane.showMessageDialog(null,e);
            System.exit(0);
        }
    

     System.out.println(Ip_addr + ": Sample stored at "+locTime);
   
    }
    
    
    public static void main(String[] args)  
    { 
        int sample_period = 15;
        
        // This is all to get at the program name becasue Java doesn't supply it in argv[0] like any other language
        StackTraceElement[] stack = Thread.currentThread().getStackTrace();
        StackTraceElement main = stack[ stack.length-1];
        String fn = main.getFileName();
        fn =  fn.substring(0, fn.indexOf('.'));
        
        final String usage = "Usage: " + fn + " -ip xxx.xxx.xxx.xxx [-i min]";
       
        if (args.length < 2) 
        {
            JOptionPane.showMessageDialog(null,usage);
            System.exit(0);
        }

        if (! args[0].contentEquals("-ip"))
        {
            JOptionPane.showMessageDialog(null,usage);
            System.exit(0);
        }
        // This is to check the general IP address format 
        if ( !args[1].matches("^\\d+(\\.\\d+){3}$"))
        {
            JOptionPane.showMessageDialog(null,usage);
            System.exit(0);
        }
        // This validates the IP addrees further with range checking
        try
        {   
            Inet4Address.getByName(args[1]); // just calling this to validate the address
        } 
        catch (UnknownHostException e) 
        {
            System.out.println(e);
            JOptionPane.showMessageDialog(null,e);
            System.exit(0);
        }

      
        if (args.length >= 4)
        {
            if (args[2].contentEquals("-i") && args[3].matches("^\\d+$"))
            {
                sample_period = Integer.parseInt(args[3]);
            }
        }
      
        System.out.println(fn +":Sampling ip address " +args[1]+ " at interval of " + sample_period + " Minutes.");
             
        WXSoilSave soilsampleSave = new WXSoilSave(args[1] );

        while (true)
        {
            soilsampleSave.Save_Record();
            try 
            {
                Thread.sleep(60 * 1000 * sample_period);
            }
            catch (InterruptedException e)
            {
                return ;
            }
         
        }

    }
    
}

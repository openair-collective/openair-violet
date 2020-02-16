
import processing.serial.*;
import java.util.*; 

Serial myPort;  // Create object from Serial class
String val;      // Data received from the serial port

List<Integer> vals;

int barSize = 100;

PImage img;

void setup()
{
  size(1024, 768);
  
  img = loadImage("OA_logo_wide_white.png");
  img.resize(img.width/10, img.height/10);
  
  // I know that the first port in the serial list on my mac
  // is Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  String portName = Serial.list()[1]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
  
  vals = new ArrayList<Integer>();
  
  imageMode(CENTER);
  textMode(LEFT);
}

void draw()
{
  
  if ( myPort.available() > 0) 
  {  // If data is available,
    val = myPort.readStringUntil('\n');         // read it and store it in val
  } 
  
  if(val != null){
    
    //print(val); //print it out in the console
    
    int co2 = int(val.trim());
    
    if(vals.size() == 0 || co2 != vals.get(vals.size() - 1).intValue()){
      vals.add(new Integer(co2));
      println(co2);
    }
    //vals.add(new Integer(frameCount));
    
    pushMatrix();
    background(0, 0, 0, 100);
    
    image(img, width/2, height/5);
    
    translate(barSize * -vals.size() + width, 0);
    
    for(int i = 0; i < vals.size(); i++){  
      float barH = vals.get(i).intValue()/10f;
      fill(255);
      rect(i * barSize, 
          height - barH, 
          barSize, 
          barH);
      fill(0);
      text("" + vals.get(i).intValue(), 
          i * barSize + barSize * .4f, height - barH + barSize * .2f);
    }
    
    popMatrix();
  }
}

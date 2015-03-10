/*
 * EEPROM Write
 *
 * Stores values read from analog input 0 into the EEPROM.
 * These values will stay in the EEPROM when the board is
 * turned off and may be retrieved later by another sketch.
 */

#include <EEPROM.h>

// the current address in the EEPROM (i.e. which byte
// we're going to write to next)
#define IO_START_PIN 4
#define IO_NUMBER 10
#define IO_BitLength 1

#define IO_MODE_BeginEEPromAddress 0
#define IO_MODE_SET "#IOMODESET"

#define IO_SET_BeginEEPromAddress 10
#define IO_SET "#IOSET"

void setup()
{
    Serial.begin(9600);
    //writeEEP("meme$",'$');
    
    getUserCommand("#IOMODESET,1111111111$");
    getUserCommand("#IOSET,0000000000$");
    String n=readEEP(512);
    Serial.println(n);
    
    Serial.println(readEEPByPart(IO_MODE_BeginEEPromAddress,IO_NUMBER));
    Serial.println(readEEPByPart(IO_SET_BeginEEPromAddress,IO_NUMBER));
    initIoMode(readEEPByPart(IO_MODE_BeginEEPromAddress,IO_NUMBER));
    initSetIO(readEEPByPart(IO_SET_BeginEEPromAddress,IO_NUMBER));
    
}

void loop()
{

}

void initIoMode(String iomodes)
{
   int iomodes_pointer=0;
   for(int ioPin=IO_START_PIN;ioPin<IO_START_PIN+IO_NUMBER;ioPin++)
   {     
       pinMode(ioPin,String(iomodes.charAt(iomodes_pointer)).toInt());
       iomodes_pointer+=1;
   }
}
void initSetIO(String ioset)
{
   int ioset_pointer=0;
   for(int ioPin=IO_START_PIN;ioPin<IO_START_PIN+IO_NUMBER;ioPin++)
   {
       Serial.println(ioset.charAt(ioset_pointer));
       digitalWrite(ioPin,String(ioset.charAt(ioset_pointer)).toInt());
       ioset_pointer+=1;
   }
}

//info fromat "#COMMANDparameter$";
void getUserCommand(String info)
{

  String command=info.substring(0,info.indexOf(","));
   int commandLen=String(command).length()+1;
  if (command ==IO_MODE_SET) {
     writeEEP(info.substring(info.indexOf(IO_MODE_SET)+commandLen,info.indexOf("$")),IO_MODE_BeginEEPromAddress,IO_NUMBER);
  }
  if (command ==IO_SET){
     writeEEP(info.substring(info.indexOf(IO_SET)+commandLen,info.indexOf("$")),IO_SET_BeginEEPromAddress,IO_NUMBER);
  }
 
  
}

void writeEEP(String info,int startAddress,int writeLen)
{

   
   for(int i=0;i<writeLen;i++)
   {
       EEPROM.write(startAddress,info.charAt(i));
       startAddress++;
   }
}
void writeEEP(String info,byte sign)
{
   int startIndex=512;
   int infoLength=info.length();
   int bytePointer=0;
   for(;startIndex>0;startIndex--)
   {
       if(EEPROM.read(startIndex)==sign)
          break;       
   }

   if(startIndex!=0)
       startIndex+=1;
      
   
   for(int addr=startIndex;addr<startIndex+infoLength;addr++)
   {
       EEPROM.write(addr,info.charAt(bytePointer));
       bytePointer++;
          
   }   
  
}

String readEEP(int num)
{

  String result;
  int addr=0;
  for(;addr<num;addr++)
  {
    result+=String(char(EEPROM.read(addr)));
  }  
  return result;
    
}
String readEEPByPart(int addr_begin,int length)
{
   String result;
   int len=addr_begin+length;
   for(;addr_begin<len;addr_begin++){
       result+=String(char(EEPROM.read(addr_begin)));
   }
   return result;
}

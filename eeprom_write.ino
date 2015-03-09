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
#define IO_Number 10
#define IO_BitLength 1

#define IO_MODE_BeginEEPromAddress 0
#define IO_MODE_SET "#IOMODESET"

#define IO_SET_BeginEEPromAddress 10
#define IO_SET "#IOSET"

void setup()
{
    Serial.begin(9600);
    //writeEEP("meme$",'$');
    
    getUserCommand("#IOMODESET,B21122000000011$");
    getUserCommand("#IOSET,P21122000000011$");
    String n=readEEP(512);
    Serial.println(n);
    
    
    
}

void loop()
{

}


//info fromat "#COMMANDparameter$";
void getUserCommand(String info)
{

  String command=info.substring(0,info.indexOf(","));
   int commandLen=String(command).length()+1;
  if (command ==IO_MODE_SET) {
     writeEEP(info.substring(info.indexOf(IO_MODE_SET)+commandLen,info.indexOf("$")),IO_MODE_BeginEEPromAddress);
  }
  if (command ==IO_SET){
     writeEEP(info.substring(info.indexOf(IO_SET)+commandLen,info.indexOf("$")),IO_SET_BeginEEPromAddress);
  }
 
  
}

void writeEEP(String info,int startAddress)
{
   int len=info.length();
   
   for(int i=0;i<len;i++)
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

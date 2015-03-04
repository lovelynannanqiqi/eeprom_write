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


void setup()
{
    Serial.begin(9600);
    writeEEP("meme$",'$');
    String n=readEEP(512);
    Serial.println(n);
}

void loop()
{

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

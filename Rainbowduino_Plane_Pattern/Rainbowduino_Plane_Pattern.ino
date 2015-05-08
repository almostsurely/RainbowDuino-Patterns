#include <Rainbowduino.h>

void setup(){
  Rb.init();
}

unsigned int z, x, y, a, e, f, g;

void loop(){
  for(z=0;z<4;z++)
  {
    for(x=0;x<4;x++)
    {
      for(y=0;y<4;y++)
      {
        if(a >= 4)
        {
          a=0;
        }
        
        if(x==a){
          e=0xFF;
        }
        else {
          e=0;
        }
        
        if(y==a){
          f=0xFF;
        }
        else {
          f=0;
        }
        
        if(z==a){
          g=0xFF;
        }
        else {
          g=0;
        }
        if(x == a || y == a || z == a){
          Rb.setPixelZXY(z, x, y, g, e, f);
        }
      }
    }
  }
  delay(500);
  Rb.blankDisplay();
  a++;
}

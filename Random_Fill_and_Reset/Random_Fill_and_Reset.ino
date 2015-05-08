#include <Rainbowduino.h>

void setup(){
  Rb.init();
}

unsigned char x, y, z, a, b, c;
unsigned int cube[4][4][4][3];
boolean full;

void loop(){
  full = true;
  
  a = random(4);
  b = random(4);
  c = random(4);
  cube[a][b][c][0]=random(0xFF);
  cube[a][b][c][1]=random(0xFF);
  cube[a][b][c][2]=random(0xFF);
  
  for(x=0;x<4;x++){
    for(y=0;y<4;y++){
      for(z=0;z<4;z++){
        if(cube[x][y][z][0] == 0 && cube[x][y][z][1] == 0 && cube[x][y][z][2] == 0){
          full = false;
        }
        Rb.setPixelZXY(z, x, y, cube[x][y][z][0], cube[x][y][z][1], cube[x][y][z][2]);
      }
    }
  }
  
  delay(100);
  if(full){
    Rb.blankDisplay();
    for(x=0;x<4;x++){
      for(y=0;y<4;y++){
        for(z=0;z<4;z++){
          cube[x][y][z][0] = 0;
          cube[x][y][z][1] = 0;
          cube[x][y][z][2] = 0;
        }
      }
    }
  }
}

#include <Rainbowduino.h>

char red[3] = {0, 0, 0}; // Red X, Y, Z
char blue[3] = {3, 3, 3}; // Blue X, Y, Z
char r_bullet[3] = {0, 0, -1}; // Red Bullet X, Y, Z
char b_bullet[3] = {0, 0, -1}; // Blue Bullet X, Y, Z

void setup(){
  Rb.init();
}


void loop(){
  Rb.blankDisplay();
  
  move_fighter(red); // Move red fighter.
  move_fighter(blue); // Move blue fighter.
  
  bullet_logic(r_bullet, red, blue, 1); // Perform bullet logic
  bullet_logic(b_bullet, blue, red, -1); // Perform bullet logic
  
  draw_bullet(r_bullet, 0xFF6600);
  draw_bullet(b_bullet, 0x00FF66);
  
  Rb.setPixelZXY(red[2], red[0], red[1], 0xFF0000); // Draw Red fighter.
  Rb.setPixelZXY(blue[2], blue[0], blue[1], 0x0000FF); // Draw Blue fighter.
  
  delay(750);
}

void move_fighter(char *fighter){
    
  char d = random(4); // Select Direction to move
  
  if(d == 0){ // Move positive X
    fighter[0] += 1;
  }
  if(d == 1){ // Move negative X
    fighter[0] -= 1;
  }
  if(d == 2){ // Move positive Y
    fighter[1] += 1;
  }
  if(d == 3){ // Move negative Y
    fighter[1] -= 1;
  }
  
  // Ensure the moves are valid.
  fighter[0] = check_value(fighter[0]);
  fighter[1] = check_value(fighter[1]);
}

char check_value(char a){
  // Ensure that fighter does not go off screen.
  if(a > 3){
    return 2;
  }
  if(a < 0){
    return 1;
  }
  return a;
}

void bullet_logic(char *bullet, char *fighter, char *opp, char dir){
  if(bullet[2] == -1){ // Check if there is no bullet.
    char a = random(3); // 1 in 3 chance to shoot.
    if(a == 0){ // Decide to shoot.
      bullet[0] = fighter[0];
      bullet[1] = fighter[1];
      if(dir == 1){ // If bullet is moving up.
        bullet[2] = 1;
      }
      else{ // If bullet is moving down.
        bullet[2] = 2;
      }
    }
  }
  else{ // If there is already a bullet
    move_bullet(bullet, dir);
    check_collision(bullet, opp);
  }
}

void move_bullet(char *bullet, char dir){
  bullet[2] += dir; // Move bullet in direction
  
  if(bullet[2] > 3 || bullet[2] < 0){ // If bullet is off screen.
    bullet[2] = -1; // Don't draw it.
  }
}

void check_collision(char *bullet, char *opp){
  // Check if a collision happened.
  if(bullet[0] == opp[0] && bullet[1] == opp[1] && bullet[2] == opp[2]){
    collision(bullet);
  }
}

void collision(char *bullet){
  
  // Reset fighter position.
  red[0] = 0;
  red[1] = 0;
  blue[0] = 3;
  blue[1] = 3;
  
  // Cause explosion.
  Rb.blankDisplay();
  explosion(bullet);
  
  // Remove bullets.
  Rb.blankDisplay();
  r_bullet[2] = -1;
  b_bullet[2] = -1;
}

void draw_bullet(char *bullet, long color){
  if(bullet[2] != -1){ // If bullet exists.
    Rb.setPixelZXY(bullet[2], bullet[0], bullet[1], color);
  }
}

void explosion(char *loc){
  
  for(char cycle = 0; cycle < 25; cycle++){
    Rb.blankDisplay();
    long colors[2];
    if(loc[2] == 0){
      colors[0] = 0xFF6600;
      colors[1] = 0xFF0000;
    }
    else{
      colors[0] = 0x00FF66;
      colors[1] = 0x0000FF;
    }
    Rb.setPixelZXY(loc[2], loc[0], loc[1], colors[cycle % 2]);
    if(loc[0] < 3 && cycle % 2 == 0){ // Positive X arm of explosion.
      Rb.setPixelZXY(loc[2], loc[0] + 1, loc[1], colors[cycle % 2]);
    }
    if(loc[0] > 0 && cycle % 2 == 0){ // Negative X arm of explosion.
      Rb.setPixelZXY(loc[2], loc[0] - 1, loc[1], colors[cycle % 2]);
    }
    if(loc[1] < 3 && cycle % 2 == 0){ // Positive Y arm of explosion.
      Rb.setPixelZXY(loc[2], loc[0], loc[1] + 1, colors[cycle % 2]);
    }
    if(loc[1] > 0 && cycle % 2 == 0){ // Negative Y arm of explosion.
      Rb.setPixelZXY(loc[2], loc[0], loc[1] - 1, colors[cycle % 2]);
    }
    if(loc[2] > 0 && cycle % 2 == 0){ // Negative Z arm of explosion.
      Rb.setPixelZXY(loc[2] - 1, loc[0], loc[1], colors[cycle % 2]);
    }
    if(loc[2] < 3 && cycle % 2 == 0){ // Positive Z arm of explosion.
      Rb.setPixelZXY(loc[2] + 1, loc[0], loc[1], colors[cycle % 2]);
    }
    delay(200);
  }
}

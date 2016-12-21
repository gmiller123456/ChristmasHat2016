#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 6
#define NUMPIXELS 150

Adafruit_NeoPixel strip = Adafruit_NeoPixel(89, PIN, NEO_GRB + NEO_KHZ800);

void setup() {

  strip.begin();
  strip.show();
}


void setPixel(int pixel,uint32_t c){
  int temp=pixel;
  if(temp==8) return;
  if(temp>8) temp--;
  strip.setPixelColor(temp,c);
}


void setPixel(int x, int y, uint32_t c){
  setPixel(y*18+x%18,c);
}

uint32_t getPixel(int x, int y){
  int p=y*18+x%18;
  if(p==8) return 0;
  if(p>8) p--;
  return strip.getPixelColor(p);
}


void loop() {
  snow();
  fillUp();
  randomRedGreen();
  rings();  
  wheel();
}

void snow(){
  long startTime=millis();
  uint32_t c=strip.Color(5,5,10);

  for(int i=0;i<strip.numPixels();i++){
    strip.setPixelColor(i,0);
  }
  strip.show();

  while(millis()-startTime<15000){
    for(int j=0;j<4;j++){
      for(int i=0;i<18;i++){
        setPixel(i,4-j,getPixel(i,3-j));
      }
    }

    for(int i=0;i<18;i++){
      if(random(10)<3){
        int brightness=random(2)*10;
        setPixel(i,0,strip.Color(10-brightness,10-brightness,20-brightness));
      } else {
        setPixel(i,0,0);
      }
    }
  
    strip.show();
    delay(100);
  }
}

void wheel(){
  uint32_t red=strip.Color(10,0,0);
  uint32_t green=strip.Color(0,10,0);
  uint32_t c=red;
  long startTime=millis();

  int offset=0;
  while(millis()-startTime<5000){
    for(int j=0;j<3;j++){
      for(int k=0;k<5;k++){
        setPixel(j*6+offset,k,c);  
        setPixel(j*6+1+offset,k,c);  
        //setPixel(j*6+2+offset,k,c);  
        //setPixel(j*6+3+offset,k,c);  
        //setPixel(j*6+4+offset,k,c);  
        //setPixel(j*6+5+offset,k,c);  
      }
      if(c==red){
        c=green;
      } else {
        c=red;
      }
    }
    strip.show();
    delay(100);
    offset++;
    if(offset==18) offset=0;
  }
}

void rings(){
  uint32_t red=strip.Color(10,0,0);
  uint32_t green=strip.Color(0,10,0);
  uint32_t c=red;
  long startTime=millis();
  
  while(millis()-startTime<5000){
    for(int i=0;i<5;i++){
      for(int j=0;j<19;j++){
        for(int x=0;x<5;x++){
          c=green;
          if(x==i) c=red;
          setPixel(j,4-x,c);
        }
      }
      strip.show();
      delay(100);
    }
  }
}

void fillUp(){
  uint32_t red=strip.Color(10,0,0);
  uint32_t green=strip.Color(0,10,0);
  uint32_t c=red;
  long startTime=millis();
  
  while(millis()-startTime<5000){
    for(int i=0;i<5;i++){
      for(int j=0;j<19;j++){
        setPixel(j,4-i,c);
      }
      strip.show();
      delay(100);
    }
    if(c==red){
      c=green;
    } else {
      c=red;
    }
  }
}

void randomRedGreen(){
  uint32_t red=strip.Color(10,0,0);
  uint32_t green=strip.Color(0,10,0);
  long startTime=millis();
  
  for(int i=0;i<strip.numPixels();i++){
    if(random(2)==1){
      setPixel(i,green);
    } else {
      setPixel(i,red);
    }
  }
  strip.show();
  while(millis()-startTime<5000){
    int r=random(strip.numPixels());
    if(random(2)==1){
      setPixel(r,green);
    } else {
      setPixel(r,red);
    }
    strip.show();
    //delay(1);
    
  }
}

void setAll(int r, int g, int b){
  for(int i=0;i<strip.numPixels();i++){
    setPixel(i,strip.Color(r,g,b));
  }
  strip.show();
}

void alternate(){
  uint32_t red=strip.Color(10,0,0);
  uint32_t green=strip.Color(0,10,0);
  int i=0;
  while(i<strip.numPixels()){
    setPixel(i,red);
    i++;
    setPixel(i,green);
    i++;
  }
  strip.show();
}

void alternate2(){
  int i=0;
  while(i<strip.numPixels()){
    strip.setPixelColor(i,strip.Color(0,10,0));
    i++;
    strip.setPixelColor(i,strip.Color(10,0,0));
    i++;
  }
  strip.show();
}



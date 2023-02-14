// used for turning on program
int IR_readings[32];

int getBits(int IR) {
    int val = 0;
    if(pulseIn(IR, HIGH) < 4000) {
        return 0; 
    }
    else {
      for(int i = 0; i < 32; ++i) {
          IR_readings[i] = pulseIn(IR, HIGH); // read in raw values
      }
      
      for(int j = 0; j < 32; ++j) { 
          if(IR_readings[j] > abs(1200)) {
              IR_readings[j] = 1;
          }
          else {
              IR_readings[j] = 0;
          }
  
      }
  
      for(int j = 0; j < 15; ++j) {
          if(j < 8) {
              if(IR_readings[j] == 1) {
                 return 0;
              }
          }
          else if(j < 15) {
              if(IR_readings[j] == 0) {
                  return 0;
              }
          }
         
      }

      int i = 0;
      for(int j = 31; j > 17; --j) {
          if(IR_readings[j] == 1) {
              val += pow(2, i);
          }
          else {
              val += 0;
          }
          ++i; 
      }

      return val;
  
     }

     
}

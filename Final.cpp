int x = A0;
int button = 0;
int reciever = 2;
bool active = false;
bool reset = false;
volatile bool fire = false;
bool fail = false;
byte column = 128; // B10000000
byte row = 69;
unsigned int ColumnSeed;
int highScore = 0;

int EnemyCount;
int wave = 0;
int grid[84][6];

bool left;
bool right;

int CE = 12;
int RST = 13;
int DC = 11;
int DIN = 10;
int CLK = 9;

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int(*TickFct)(int);
} task; 

const unsigned short taskNum = 4;
task tasks[taskNum];

void command(byte dc, byte data) {
      int bitPlacement = 7;
  
      digitalWrite(DC, dc);
      digitalWrite(CE, LOW);
      for(int i = 0; i < 8; ++i) {
           digitalWrite(DIN, bitRead(data, bitPlacement));
           digitalWrite(CLK, HIGH);
           digitalWrite(CLK, LOW);
           --bitPlacement;
      }
      digitalWrite(CE, HIGH);
}

void GridClear() {
    for(int i = 0; i < 84; ++i) { // sets all array values to zero
        for(int j = 0; j < 6; ++j) {
            grid[i][j] = 0;
        }
    }
}

unsigned int Rand(unsigned int m, unsigned int seed) { // used for random enemy spawns each wave. based on lehmer rng algorithm
      unsigned int val = seed;
      unsigned int a = 10;
      unsigned int b = 4;
      val = ((a * val) + b) % m;
      return val;
}


void initial() {
    digitalWrite(RST, LOW);
    digitalWrite(RST, HIGH);
    command(0, 0x21);
    command(0, 0xC0);
    command(0, 0x07);
    command(0, 0x13);
    command(0, 0x20);
    command(0, 0x0C); 
}

void Clean() {
    for(byte i = 128; i < 212; ++i) {
        for(byte j = 64; j < 70; ++j) {
              command(0, i);
              command(0, j);
              command(1, B00000000);
        } 
    }
}

void PrintPlayer() {
    command(0, row);
    command(0, column);
    command(1, B11111111);
    command(1, B00000001);
    command(1, B11111111);
}

void PrintStart() {
    command(0, 66);
    command(0, 160);
    command(1, B11111111);
    command(1, B00011000);
    command(1, B00011000);
    command(1, B00011000);
    command(1, B11111111);
    command(1, B00000000);
    command(1, B10000001);
    command(1, B11111111);
    command(1, B10000001);
    
}

void PrintEnemy() {
   unsigned int EnemyRow;
   unsigned int EnemyColumn;

   for(int i = 0; i < 4; ++i) {
      for(int j = 0; j < 2; ++j) {         
        ColumnSeed = Rand(83, ColumnSeed); // rand fuction used here
        EnemyColumn = ColumnSeed;
        if(grid[EnemyColumn][i] == 0 && EnemyColumn < 82) {
                 grid[EnemyColumn][i] = 1;
                 ++EnemyCount;
                 command(0, i + 64);
                 command(0, EnemyColumn + 128);
                 command(1, B00011111);
                 command(1, B00010001);
                 command(1, B00011111);
         }
      }
   }
   
    command(0, row);
    command(0, column);

    Serial.println(EnemyCount);
}

void PrintFail() {
    command(0, 66);
    command(0, 150);
    command(1, B00000001);
    command(1, B00000001);
    command(1, B11111111);
    command(1, B00000001);
    command(1, B00000001);

    command(1, B00000000);
    command(1, B00000000);
    command(1, B00000000);
    
    command(1, B10000001);
    command(1, B11111111);
    command(1, B10000001);

    command(1, B00000000);
    command(1, B00000000);
    command(1, B00000000);
    
    command(1, B11111111);
    command(1, B00000010);
    command(1, B00000100);
    command(1, B00001000);
    command(1, B00000100);
    command(1, B00000010);
    command(1, B11111111);
    
    command(1, B00000000);
    command(1, B00000000);
    command(1, B00000000);

    command(1, B11111111);
    command(1, B10001001);
    command(1, B10001001);
    command(1, B10001001);
    command(1, B10001001);

    command(1, B00000000);
    command(1, B00000000);
    command(1, B00000000);
    
    command(1, B10001111);  
    
}


void RightShift() {
    command(0, column);
    command(1, B00000000);
    command(1, B00000000);
    command(1, B00000000);
    command(1, B00000000);
    command(1, B00000000);
    command(1, B00000000);
    command(1, B00000000);

    column += 0x01;
    
    command(0, column);
    PrintPlayer();
}

void LeftShift() {
    command(0, column);
    command(1, B00000000);
    command(1, B00000000);
    command(1, B00000000);
    command(1, B00000000);
    command(1, B00000000);
    command(1, B00000000);
    command(1, B00000000);

    column -= 0x01;
    
    command(0, column);
    PrintPlayer();
    
}

void Bullet() {
    for(byte BulletRow = row - 1; BulletRow > 63; --BulletRow) {
          command(0, column);
          command(0, BulletRow);
          command(1, B00111111);
         // command(1, B00001111);
         // command(1, B00001111);
          delay(50);
          
          if(grid[column - 128][BulletRow - 64] == 1) {
              Serial.println("HIT");
              grid[column - 128][BulletRow - 64] = 0;
              command(0, column);
              command(0, BulletRow);
              command(1, B00000000);
              command(1, B00000000);
              command(1, B00000000);
              --EnemyCount;
              return;
          }
          else if(grid[(column - 128) - 1][BulletRow - 64] == 1) {
              Serial.println("HIT");
              grid[(column - 128) - 1][BulletRow - 64] = 0;
              command(0, column - 1);
              command(0, BulletRow);
              command(1, B00000000);
              command(1, B00000000);
              command(1, B00000000);
              --EnemyCount; 
              return;
          }
          else if(grid[(column - 128) - 2][BulletRow - 64] == 1) { 
              Serial.println("HIT");
              grid[(column - 128) - 2][BulletRow - 64] = 0; 
              command(0, column - 2);
              command(0, BulletRow);
              command(1, B00000000);
              command(1, B00000000);
              command(1, B00000000);
              --EnemyCount;
              return;
          }
          else {
              command(0, column);
              command(0, BulletRow);
              command(1, B00000000);
          }
         
    }
}
void ShootISR() {
   fire = true;
}

enum Joystick{Start, off, control};
int Joystick_SM(int state) {
   switch(state) {
        case Start:
              state = off;
              break;
        case off:
              if(active) {
                  state = control;                 
              }

              else {
                  state = off;
              }
              break;
        case control:
              if(!active || fail) {
                  state = off;
              }
              else {
                  state = control;
              }
              break;
   } 

   switch(state) {
        case control:
            //Serial.println(analogRead(x));
             if(analogRead(x) >= 700 && column < 209) {                
                  RightShift();
             }
            else if(analogRead(x) <= 130 && column > 128) {
                  LeftShift();
             }
             else if(digitalRead(button) == LOW) {
                  reset = true;
             }
            
             break;
   }
   return state;
}

enum lcd_states{lcd_start, lcd_off, lcd_on, lcd_restart, lcd_fail};
int lcd_SM(int state) {
  unsigned static char c = 0;
    switch(state) {
        case lcd_start:
            state = lcd_off;
            break;
        case lcd_off:
            if(active) {
                Clean();
                GridClear();
                PrintEnemy();
                PrintPlayer();
                state = lcd_on;               
            }
            else {
                state = lcd_off;
            }
            break;
        case lcd_on:
            if(!active) {
                state = lcd_off;
            }
            else if(reset) {
                state = lcd_restart;
            }
            else if(fail) {
               Clean();
               state = lcd_fail;
            }
            else {
                state = lcd_on;
            }
            break;
         case lcd_restart:
            reset = false;
            wave = 0;
            highScore = 0;
            EnemyCount = 0;
            Clean();
            GridClear();
            PrintEnemy();
            column = 128;
            row = 69;
            PrintPlayer();
            state = lcd_on;  
            break; 
         case lcd_fail:
            if(c > 10) {
                c = 0;
                Clean();
                GridClear();
                highScore = wave;
                state = lcd_off;
             }
             else if(c <= 10) {
                state = lcd_fail;
             }
            break;
    }

    switch(state) {
        case lcd_off:
            EnemyCount = 0;
            ColumnSeed = millis();
            PrintStart();
            break;
        case lcd_on:
            Serial.println(EnemyCount);
            if(EnemyCount == 0) {
                Clean();
                ++wave;
                GridClear();
                PrintEnemy();
                PrintPlayer();
            }
            break;
       case lcd_fail:
            PrintFail();
            ++c;
            break;
    }

    return state;
}

enum remote{remote_start, remote_idle, remote_on};
int remote_SM(int state) {
      switch(state) {
          case remote_start:
              state = remote_idle;
              break;
          case remote_idle:
              if(getBits(reciever) == 8792) { // for power button
                  //pulseIn(reciever, HIGH) > 128
                  // getBits(reciever) == 8792
                  active = true;
                  state = remote_on;
              }
              else {
                  state = remote_idle;
              }
              break;
          case remote_on:
             if(!active) {
                state = remote_idle;
             }
             else if(fail) {
                active = false;
                state = remote_idle;
             }
             else {
                state = remote_on; 
             }
             break;            
      }

      switch(state) {
          case remote_on:
            //  if(!left && !right) {
                  attachInterrupt(digitalPinToInterrupt(reciever), ShootISR, CHANGE);
                  if(fire) {                
                    Bullet();
                    command(0, row);
                    fire = false;
                }
            //  }
              break;
      }

      return state;
}

enum Timer{Timer_idle, Timer_HIGH, Timer_LOW, Timer_end};
int Timer_SM(int state) {
    static int val = 9;
    unsigned static char s = 0;
    switch(state) {
          case Timer_idle:
              if(active) {
                  state = Timer_HIGH;
              }
              else {
                  state = Timer_idle;
              }
              break;
          case Timer_HIGH:
              if(s > 60) {
                  s = 0;
                  --val;
                  state = Timer_LOW;
              }
              else if(reset) {
                  val = 9;
                  state = Timer_HIGH;
              }  
              else if(EnemyCount == 0 && val > 0) {
                  s = 0;
                  val = 9;
                  state = Timer_HIGH;
              }
              else if(s <= 60){
                  state = Timer_HIGH;
              }
              break;
         case Timer_LOW:
              if(s > 60) {
                  s = 0;
                  --val;
                  state = Timer_HIGH;
              }
               else if(reset) {
                  val = 9;
                  state = Timer_HIGH;
              } 
              else if(val == 0) {              
                  s = 0;
                  fail = true;
                  state = Timer_end;
              }
               else if(EnemyCount == 0 && val > 0) {
                  s = 0;
                  val = 9;
                  state = Timer_HIGH;
              }
              else if(s <= 60) {
                  state = Timer_LOW;
              }
              break;
        case Timer_end:
              if(s > 5) {
                 fail = false;
                 state = Timer_idle;
              }
              else if(s <= 5){
                 state = Timer_end;
              }
              break;
    }

    switch(state) {
          case Timer_idle:
              timer(highScore);  
              s = 0;
              val = 9;
              break;
          case Timer_HIGH:
              timer(val);
              ++s;
              break;
          case Timer_LOW:
              timer(val);
              ++s;
              break;
          case Timer_end:
              ++s;
              break;
    }

    return state;    
} 
     

void setup() {
  // put your setup code here, to run once:
  pinMode(CE, OUTPUT);
  pinMode(RST, OUTPUT);
  pinMode(DC, OUTPUT);
  pinMode(DIN, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(reciever, INPUT);
  pinMode(button, INPUT_PULLUP);

  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(1, OUTPUT);

  initial();
  Clean();
  GridClear();
   
  unsigned char j = 0;
  tasks[j].state = Start;
  tasks[j].period = 50;
  tasks[j].elapsedTime = 0;
  tasks[j].TickFct = &Joystick_SM;
  j++;
  tasks[j].state = lcd_start;
  tasks[j].period = 50;
  tasks[j].elapsedTime = 0;
  tasks[j].TickFct = &lcd_SM;
  j++;
  tasks[j].state = remote_start;
  tasks[j].period = 50;
  tasks[j].elapsedTime = 0;
  tasks[j].TickFct = &remote_SM;
  j++;
  tasks[j].state = Timer_idle;
  tasks[j].period = 50;
  tasks[j].elapsedTime = 200;
  tasks[j].TickFct = &Timer_SM; 
   

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 //  Serial.println(pulseIn(reciever, HIGH));
 // Serial.println(" ");
  unsigned char i;
  for (i = 0; i < taskNum; ++i) {
    if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
      tasks[i].state = tasks[i].TickFct(tasks[i].state);
      tasks[i].elapsedTime = millis(); // Last time this task was ran
    } 
  } 

}

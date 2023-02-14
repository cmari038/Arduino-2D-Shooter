void Nine() {
    digitalWrite(8, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(1, HIGH);
}

void Eight() {
    digitalWrite(8, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(1, HIGH);
}

void Seven() {
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    digitalWrite(1, HIGH);
}

void Six() {
    digitalWrite(8, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(1, HIGH);
}

void Five() {
    digitalWrite(8, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(1, HIGH);
}

void Four() {
   digitalWrite(8, HIGH);
   digitalWrite(7, HIGH);
   digitalWrite(6, LOW);
   digitalWrite(5, HIGH);
   digitalWrite(4, LOW);
   digitalWrite(3, LOW);
   digitalWrite(1, HIGH);
}

void Three() {
    digitalWrite(8, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(1, HIGH);
}

void Two() {
    digitalWrite(8, HIGH);
   digitalWrite(7, LOW);
   digitalWrite(6, HIGH);
   digitalWrite(5, HIGH);
   digitalWrite(4, HIGH);
   digitalWrite(3, HIGH);
   digitalWrite(1, LOW);
}

void One() {
   digitalWrite(8, LOW);
   digitalWrite(7, LOW);
   digitalWrite(6, LOW);
   digitalWrite(5, HIGH);
   digitalWrite(4, LOW);
   digitalWrite(3, LOW);
   digitalWrite(1, HIGH);
}

void Zero() {
    digitalWrite(8, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(1, HIGH);
}

void Off() {
     digitalWrite(8, LOW);
     digitalWrite(7, LOW);
     digitalWrite(6, LOW);
     digitalWrite(5, LOW);
     digitalWrite(4, LOW);
     digitalWrite(3, LOW);
     digitalWrite(1, LOW);
}
void timer(int val) {
   if(val == 9) {
      Nine();
   }
   else if(val == 8) {
      Eight();
   }
   else if(val == 7) {
      Seven();
   }
   else if(val == 6) {
      Six();
   }
   else if(val == 5) {
      Five();
   }
   else if(val == 4) {
      Four();
   }
   else if(val == 3) {
      Three();
   }
   else if(val == 2) {
      Two();
   }
   else if(val == 1) {
      One();
   }
   else {
      Zero();
   }
}

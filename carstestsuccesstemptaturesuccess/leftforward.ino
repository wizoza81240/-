void leftforward() {
  int speed1 = 100;
  int speed2 = 255;
  analogWrite(m1,speed1);
  analogWrite(m2,speed2);
  forward();
}

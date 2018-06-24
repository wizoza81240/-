void ultrasoundstop() {
  long cm = ping();
  if (cm <= 15) {
    backward();
    delay(300);
    motorstop();
    delay(100);
  }
}

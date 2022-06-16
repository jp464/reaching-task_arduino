//========================================================================
// PINs
//========================================================================
const int cue_pin = 13;
const int beamBreak_pin = 6;  
const int beamReport_pin = 5;
const int reward_pin = 7;
const int laser_pin = 4;


void setup() {
  pinMode(cue_pin, OUTPUT);
  pinMode(beamBreak_pin, INPUT);
  pinMode(beamReport_pin, OUTPUT);
  pinMode(reward_pin, OUTPUT);
}

//========================================================================
// Helper Functions
//========================================================================
void pin_time(int pin, float time) {
  digitalWrite(pin, HIGH);
  delay(time);
  digitalWrite(pin, LOW);
}

boolean beamBreak_check(int break_pin, int report_pin) {
  int state = digitalRead(break_pin);
  
  while (state != 0) {
    state = digitalRead(break_pin);
  }

  pin_time(report_pin, 250);
  return true;
}

//========================================================================
// Main
//========================================================================
void loop() {
  digitalWrite(cue_pin, HIGH);

  int cnt = 0;
  while (cnt < 10) {
    if (beamBreak_check(beamBreak_pin, beamReport_pin)) {
      cnt++;
      Serial.println(cnt);
      delay(250); // count beam breaks here?
      pin_time(reward_pin, 5);
    }
  }
  
  digitalWrite(cue_pin, LOW);
  float wait_time = random(10000, 20000);
  Serial.println(wait_time);

  float start_time = millis();
  float end_time = start_time + wait_time;

  while(millis() < end_time) {
    beamBreak_check(beamBreak_pin, beamReport_pin);
  }
}

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

boolean beamBreak_check() {
  int state = digitalRead(beamBreak_pin);
  
  while (state != 0) {
    state = digitalRead(beamBreak_pin);
  }

  pin_time(beamReport_pin, 250);
  return true;
}

//========================================================================
// Main
//========================================================================
void loop() {
  digitalWrite(cue_pin, HIGH);
  pin_time(reward_pin, 5); // check with Konstantin

  int cnt = 0;
  while (cnt < 10) {
    if (beamBreak_check()) {
      cnt++;
      Serial.println(cnt);
      delay(250); // count beam breaks here?
      pin_time(reward_pin, 5);
    }
  }
  
  digitalWrite(cue_pin, LOW);
  
  float wait_time = random(10000, 20000);
  float start_time = millis();
  float end_time = start_time + wait_time;

  float cur_time = millis();
  while(cur_time < end_time) {
    beamBreak_check();
    cur_time = millis();
  }
}

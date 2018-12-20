//
// rock-paper-scissors Arduino code
//

//
// parameters copied from TensorFlow code
//

float weights[2][3] = {
  {3.007032,-9.370312,6.363242},
  {10.726093,-0.494137,-10.231989},
};

float biases[3] = {-5.709740,6.722741,-1.013021};

float scaling[2] = {0.000978,0.001600};

//
// main
//

// setup
void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);  
  pinMode(A1, INPUT);  
  pinMode(5, OUTPUT);
}

// the main loop
void loop() {

  // wait for 0.01s
  delay(10);

  // read sensor data
  float d[2];
  d[0] = float(analogRead(A0));
  d[1] = float(analogRead(A1));

  // print sensor data
//  Serial.println(String(d[0]) + "," + String(d[1]); 
//  return;

  // standardize data
  d[0] *= scaling[0];
  d[1] *= scaling[1];

  // calc logits
  float lg[3];
  lg[0] = (d[0] * weights[0][0]) + (d[1] * weights[1][0]) + biases[0];
  lg[1] = (d[0] * weights[0][1]) + (d[1] * weights[1][1]) + biases[1];
  lg[2] = (d[0] * weights[0][2]) + (d[1] * weights[1][2]) + biases[2];

  // control servo
  if (lg[0] > lg[1] && lg[0] > lg[2]) {
    analogWrite(5, 190); // rock -> paper
  } else if (lg[1] > lg[0] && lg[1] > lg[2]) {
    analogWrite(5, 127); // paper -> scissors
  } else {
    analogWrite(5, 50);  // scissors -> rock
  }
}



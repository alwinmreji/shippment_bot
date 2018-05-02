int right_en = 3, right_in1 = 2, right_in2 = 4;
int left_en = 9, left_in1 = 5, left_in2 = 6;
int vel = 0, p = 0, a = 0;
int grp_en = 7, grp_in1 = 8, grp_in2 = 10;
char data;
void setup()
{
  pinMode(right_en, OUTPUT);
  pinMode(right_in1, OUTPUT);
  pinMode(right_in2, OUTPUT);
  pinMode(left_en, OUTPUT);
  pinMode(left_in1, OUTPUT);
  pinMode(left_in2, OUTPUT);
  //  pinMode(5, OUTPUT);
  //  pinMode(4, OUTPUT);
  pinMode(10, OUTPUT);
  //  digitalWrite(5, HIGH);
  digitalWrite(10, HIGH);
  Serial.begin(9600);
}

void grip_open()
{
  digitalWrite(grp_in1, LOW);
  digitalWrite(grp_in2, HIGH);
  digitalWrite(grp_en, HIGH);
  Serial.println("Grip_close");
}

void grip_close()
{
  digitalWrite(grp_in2, LOW);
  digitalWrite(grp_in1, HIGH);
  digitalWrite(grp_en, HIGH);
  Serial.println("Grip_close");
}

void grip_stop()
{
  digitalWrite(grp_en, LOW);
  Serial.println("Grip_stop");
}

void forward()
{
  digitalWrite(right_in1, HIGH);
  digitalWrite(right_in2, LOW);
  digitalWrite(left_in1, HIGH);
  digitalWrite(left_in2, LOW);
  //    digitalWrite(left_en, HIGH);
  //    digitalWrite(right_en, HIGH);
  analogWrite(right_en, vel);
  analogWrite(left_en, vel);
  Serial.println("Forward");
}

void backward()
{
  digitalWrite(right_in1, LOW);
  digitalWrite(right_in2, HIGH);
  digitalWrite(left_in1, LOW);
  digitalWrite(left_in2, HIGH);
  analogWrite(right_en, vel);
  analogWrite(left_en, vel);
  Serial.println("Backward");
}

void point ()
{
  if (p == 0)
  {
    p = 1;
    Serial.println("Turn Modified");
  }
  else
  {
    p = 0;
    Serial.println("Turn Modified");
  }
}

void left()
{
  digitalWrite(right_in1, HIGH);
  digitalWrite(right_in2, LOW);
  digitalWrite(left_in1, LOW);
  digitalWrite(left_in2, HIGH);
  analogWrite(right_en, vel);
  if (p == 1)
    analogWrite(left_en, vel);
  Serial.println("Left");
}

void right()
{
  digitalWrite(right_in1, LOW);
  digitalWrite(right_in2, HIGH);
  digitalWrite(left_in1, HIGH);
  digitalWrite(left_in2, LOW);
  analogWrite(left_en, vel);
  if (p == 1)
    analogWrite(right_en, vel);
  Serial.println("Right");
}

void no_mv()
{
  //  digitalWrite(left_en, LOW);
  //  digitalWrite(right_en, LOW);

  analogWrite(left_en, 0);
  analogWrite(right_en, 0);
  Serial.println("Stop");
}

//Speed value 1.275 = 1rmp. max rpm 100 = 127.

void gear_up()
{
  if (vel < 200)
  {
    vel += 40;
    a += 1;
    Serial.print(a);
    Serial.println(" Gear");
  }
}

void gear_down()
{
  if (vel > 40)
  {
    vel -= 40;
    a -= 1;
    Serial.print(a);
    Serial.println(" Gear");
  }
}


void loop()
{
  if (Serial.available() > 0)
  {
    data = Serial.read();
  }
  switch (data)
  {
    case 'F': forward();
      break;
    case 'B': backward();
      break;
    case 'R': right();
      break;
    case 'L': left();
      break;
    case 'U':  gear_up();
      break;
    case 'D':  gear_down();
      break;
    case 'p':  point();
      break;
    case 'n':  gear_up();
      break;
    case 'S': no_mv();
      break;
    case 'O' : grip_open();
      break;
    case 'C' : grip_close();
      break;
    case 'N' : grip_stop();
      break;


  }
  data = 0;
}

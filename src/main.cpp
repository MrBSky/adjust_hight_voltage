#include <Arduino.h>
#include <IRremote.h>
#include "Nextion.h"

int IRRecv_Pin = 8;
int nex_recv;
byte buff[2];
int loop_buff = 0;

#define stop_up 3
#define stop_down 4
bool reset_tigger = true;

char num_buff[2];
uint8_t count_ir = 0;

float ir_val;

const int stepM = 10;
const int dirM = 11;
const int enM = 12;
long int X = 200 * 2 * 5; // แก้ค่าตามที่ต้องการ

float Distance;
float old_Distance;
float new_Distance;

float value = 0;

#define ignor 4294967295

IRrecv ir_recv(IRRecv_Pin);
decode_results results;

enum c_ase
{
  up = 0xA0,
  down = 0xA1,
  reset = 0xA2
};

enum number
{
  one = 16738455,
  two = 16750695,
  three = 16756815,
  four = 16724175,
  five = 16718055,
  six = 16743045,
  seven = 16716015,
  eight = 16726215,
  nine = 16734885,
  zero = 16730805,

  ir_up = 16736925,
  ir_down = 16754775,

  right = 16761405,
  left = 16720605,

  ok = 16712445,

  star = 16728765,
  sharp = 16732845
};

uint8_t trig_up = false;
uint8_t trig_down = false;
uint8_t trig_reset = false;

void setup()
{
  Serial.begin(9600);
  ir_recv.enableIRIn();
  Serial1.begin(9600);

  pinMode(stepM, OUTPUT);
  pinMode(dirM, OUTPUT);
  pinMode(enM, OUTPUT);

  nexInit();
  dbSerialPrintln("setup done");
  pinMode(stop_up, INPUT);
  pinMode(stop_down, INPUT);
}

void motor_down()
{
  Serial.println("Now...Drive Down: ");
  digitalWrite(dirM, LOW);
  for (int a = 0; a < Distance; a++)
  {
    digitalWrite(stepM, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepM, LOW);
    delayMicroseconds(1000);
  }
  Serial.println("Finish...Drive Down: ");
}

void motor_up()
{
  Serial.println("Now...Drive Up");

  digitalWrite(dirM, HIGH);
  for (int i = 0; i < Distance; i++)
  {
    digitalWrite(stepM, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepM, LOW);
    delayMicroseconds(1000);
  }
  Serial.println("Finish...Drive Up");
}

void mortor_reset()
{
  Serial.println("Now...Reset");

  digitalWrite(dirM, HIGH);
  for (int i = 0; i < Distance; i++)
  {
    if (digitalRead(stop_up) == reset_tigger)
    {
      Serial.println("Run...Reset");
    }
    else
    {
      digitalWrite(stepM, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepM, LOW);
      delayMicroseconds(1000);
      Serial.println("Stop...Reset");
    }
  }
  Serial.println("Finish...Reset");
}

void serialEvent1()
{
  // form nextion
  // if (Serial1.available() > 0)
  while (Serial1.available())
  {
    if (loop_buff == 0)
    {
      buff[loop_buff] = Serial1.read();
      loop_buff = 1;
    }
    else
    {
      buff[loop_buff] = Serial1.read();
      loop_buff = 0;

      Serial.print("step: ");
      Distance = X * ((float)buff[1] / 10);
      Serial.println(Distance);

      switch (buff[0])
      {
      case up:
        Serial.print("Drive Up: ");
        Serial.print((float)buff[1] / 10);
        Serial.println(" CM.");
        trig_up = true;
        trig_down = false;
        trig_reset = false;
        break;

      case down:
        Serial.print("Drive Down: ");
        Serial.print((float)buff[1] / 10);
        Serial.println(" CM.");
        trig_up = false;
        trig_down = true;
        trig_reset = false;
        break;

      case reset:
        Serial.println("Reset");
        trig_up = false;
        trig_down = false;
        trig_reset = true;
        break;
      }

      // Serial.print("NexRecv: ");
      // Serial.print(buff[0]);
      // Serial.print("-");
      // Serial.println(buff[1]);
      // Serial.println("------------------");
    }
  }
}

void loop()
{

  //  Distance = X * 1.5;
  //   for (int a = 0; a < Distance; a++)
  //   {
  //     digitalWrite(stepM, HIGH);
  //     delayMicroseconds(1000);
  //     digitalWrite(stepM, LOW);
  //     delayMicroseconds(1000);
  //   }

  // form IR
  if (ir_recv.decode(&results))
  {
    if (results.value == ignor)
    {
      ir_recv.resume();
      free(&results);
    }
    else
    {
      // Serial.print("IRRecv: ");
      // Serial.println(results.value);
      ir_recv.resume();

      switch (results.value)
      {
      case one:
        Serial.println("key: 1");
        num_buff[count_ir] = '1';
        count_ir++;
        if (count_ir > sizeof(num_buff))
        {
          count_ir = 0;
        }
        break;

      case two:
        Serial.println("key: 2");
        num_buff[count_ir] = '2';
        count_ir++;
        if (count_ir > sizeof(num_buff))
        {
          count_ir = 0;
        }
        break;

      case three:
        Serial.println("key: 3");
        num_buff[count_ir] = '3';
        count_ir++;
        if (count_ir > sizeof(num_buff))
        {
          count_ir = 0;
        }
        break;

      case four:
        Serial.println("key: 4");
        num_buff[count_ir] = '4';
        count_ir++;
        if (count_ir > sizeof(num_buff))
        {
          count_ir = 0;
        }
        break;

      case five:
        Serial.println("key: 5");
        num_buff[count_ir] = '5';
        count_ir++;
        if (count_ir > sizeof(num_buff))
        {
          count_ir = 0;
        }
        break;

      case six:
        Serial.println("key: 6");
        num_buff[count_ir] = '6';
        count_ir++;
        if (count_ir > sizeof(num_buff))
        {
          count_ir = 0;
        }
        break;

      case seven:
        Serial.println("key: 7");
        num_buff[count_ir] = '7';
        count_ir++;
        if (count_ir > sizeof(num_buff))
        {
          count_ir = 0;
        }
        break;

      case eight:
        Serial.println("key: 8");
        num_buff[count_ir] = '8';
        count_ir++;
        if (count_ir > sizeof(num_buff))
        {
          count_ir = 0;
        }
        break;

      case nine:
        Serial.println("key: 9");
        num_buff[count_ir] = '9';
        count_ir++;
        if (count_ir > sizeof(num_buff))
        {
          count_ir = 0;
        }
        break;

      case zero:
        Serial.println("key: 0");
        num_buff[count_ir] = '0';
        count_ir++;
        if (count_ir > sizeof(num_buff))
        {
          count_ir = 0;
        }
        break;

      case ok:
        // Serial.println("key: ok");
        // Serial.print("num_buff=");
        // Serial.print((int)num_buff[0] - 48);
        // Serial.println((int)num_buff[1] - 48);
        break;

      case ir_up:
        Serial.println("key: up");
        count_ir = 0;
        ir_val = ((((int)num_buff[0] - 48) * 10) + ((int)num_buff[1] - 48)) / 10.0;
        Serial.print("ir_val: ");
        Serial.println(ir_val);

        Distance = X * ir_val;
        trig_up = true;
        trig_down = false;
        trig_reset = false;
        break;

      case ir_down:
        Serial.println("key: down");

        count_ir = 0;

        ir_val = ((((int)num_buff[0] - 48) * 10) + ((int)num_buff[1] - 48)) / 10.0;
        Serial.print("ir_val: ");
        Serial.println(ir_val);

        Distance = X * ir_val;
        trig_up = false;
        trig_down = true;
        trig_reset = false;
        break;

      case star:
        Serial.println("key: *");
        // count_ir++;
        break;

      case sharp:
        Serial.println("key: #");
        count_ir = 0;
        break;
      }
      free(&results);
    }
  }

  if (trig_up == true)
  {
    trig_up = false;
    trig_down = false;
    trig_reset = false;
    motor_up();
  }
  else if (trig_down == true)
  {
    trig_up = false;
    trig_down = false;
    trig_reset = false;
    motor_down();
  }
  else if (trig_reset == true)
  {
    trig_up = false;
    trig_down = false;
    trig_reset = false;
    mortor_reset();
  }
}
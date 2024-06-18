#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <LiquidCrystal_I2C.h>

#define MIN_PULSE_WIDTH 650
#define MAX_PULSE_WIDTH 2350
#define FREQUENCY 50
#define PCA9685_ADDRESS 0x40

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(PCA9685_ADDRESS);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Chan cac chiet ap
int control1 = 34;
int control2 = 35;
int control3 = 32;
int control4 = 27;
int control5 = 26;
int control6 = 25;

// Cong ra cua cac Servo tren PCA9685
int servo1 = 0;
int servo2 = 1;
int servo3 = 2;
int servo4 = 3;
int servo5 = 4;
int servo6 = 5;

//
long time_lcd = 0;

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(50000); // Set I2C clock to 50kHz
  lcd.init();
  lcd.backlight();
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
}

int moveServo(int controlIn, int servoOut)
{
  int pulseWide, pulseWidth, potVal, edge;

  // chuyen doi du lieu dau vao gui cho servo
  potVal = analogRead(controlIn);
  pulseWide = map(potVal, 0, 4095, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  pulseWidth = int(float(pulseWide) / 1000000 * FREQUENCY * 4096); // chuyen tu micro second sang do rung xung PWM
  edge = map(pulseWidth, 133, 481, 0, 180);

  Serial.println(potVal);
  // dieu khien servo
  pwm.setPWM(servoOut, 0, pulseWidth);
  return edge;
}

void loop()
{
  int lcd1 = moveServo(control1, servo1);
  int lcd2 = moveServo(control2, servo2);
  int lcd3 = moveServo(control3, servo3);
  int lcd4 = moveServo(control4, servo4);
  int lcd5 = moveServo(control5, servo5);
  int lcd6 = moveServo(control6, servo6);
  if (millis() - time_lcd >= 500)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("1->3:");

    lcd.setCursor(5, 0);
    lcd.print(lcd1);

    lcd.setCursor(9, 0);
    lcd.print(lcd2);

    lcd.setCursor(13, 0);
    lcd.print(lcd3);

    lcd.setCursor(0, 1);
    lcd.print("4->6:");

    lcd.setCursor(5, 1);
    lcd.print(lcd4);

    lcd.setCursor(9, 1);
    lcd.print(lcd5);

    lcd.setCursor(13, 1);
    lcd.print(lcd6);

    time_lcd = millis();
  }
}

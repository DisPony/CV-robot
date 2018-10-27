#include <Servo.h> //используем библиотеку для работы с сервоприводом

Servo servo; //объявляем переменную servo типа Servo

void setup() //процедура setup

{

servo.attach(10); //привязываем привод к порту 10

}

void loop() //процедура loop

{

for(int i = 0; i != 180; i++){
    servo.write(i);
    delay(200);
  }
  delay(3000);
}


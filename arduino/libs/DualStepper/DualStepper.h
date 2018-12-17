/*
  Stepper_28BYJ.h - - Stepper_28BYJ library for Wiring/Arduino
  Модифицированная библиотека для управления шаговым двигателем 28BYJ
  
  Original library     (0.1) by Tom Igoe.
  //Two-wire modifications   (0.2) by Sebastian Gassner
  Combination version   (0.3) by Tom Igoe and David Mellis
  Bug fix for four-wire   (0.4) by Tom Igoe, bug fix from Noah Shibley
  Модифицирована для 28BYJ - alex48 (www.alex48.110kpd.ru
  

  Управленине униполярным шаговым двигателем подключенным по 4-х проводной схеме.

  Если подключать несколько шаговых двигателей к одному микроконтроллеру,
  вывод микроконтролера быстро заканчиваются, так как для подключения каждого
  двигателя используется 4 вывода.

  Последовательность управляющих сигналов для 28BYJ следующая:
  
  C0 - BLUE
  C1 - PINK
  C2 - YELLOW
  C3 - ORANGE
  Шаг	C0	C1	C2	C3
    1	0	0	0	1
    2	0	0	1	1
    3	0	0	1	0
    4	0	1	1	0
    5	0	1	0	0
    6	1	1	0	0
    7	1	0	0	0
    8	1	0	0	1

  The circuits can be found at 
  http://www.arduino.cc/en/Tutorial/Stepper
*/

// убедимся, что описание библиотеки подключается 1 раз
#ifndef LIBS_DUALSTEPPER_H
#define LIBS_DUALSTEPPER_H

//#include <../arduino/binary.h>
#include "../arduino/Arduino.h"
#include "Interaction.h"

#define CLOCKWISE 1
#define COUNTERCLOCKWISE (-1)
#define FORWARD 1
#define BACKWARD (-1)

// Задержка между шагами двигателя
// Можно использовать для ускорения-замедления, 
// если перенести внутрь класса. 
// При указании задержки меньше порогового значения
// двигатели перестают успевать обработать сигнал.
// УКАЗЫВАЕТСЯ В МИКРОСЕКУНДАХ
#define LEAST_DELAY 900

// описание интерфейса библиотеки
class DualStepper {
public:
    DualStepper(byte maskPortD, byte maskPortB);

    virtual void move(long stepsToMove);

    virtual void turn(long stepsToTurn);

private:

    void moveForward(uint32_t stepsToMove);

    void moveBackward(uint32_t stepsToMove);

    void turnClockwise(uint32_t stepsToTurn);

    void turnCounterclockwise(uint32_t stepsToTurn);

    // Вспомогательные функции для шагания двигателя:

    // Езда влево-вправо
    void stepMotors(byte thisStep);

    // Езда взад-вперед
    void stepMotorsOpposite(byte thisStep);

    // количество шагов на 1 оборот
    int stepsPerTurn;       
    
    // Битовые маски портов B и D (См. https://www.arduino.cc/en/Reference/PortManipulation) 
    // 1 - порт используется выводом двигателя, 0 - не используется.
    // Для дальнейшего развития библиотеки.
    byte maskPortB;
    byte maskPortD;

};

#endif

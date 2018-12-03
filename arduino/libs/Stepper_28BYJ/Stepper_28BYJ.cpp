/*
  Stepper_28BYJ.cpp - - Stepper_28BYJ library for Wiring/Arduino - Version 0.4
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
 
http://www.arduino.cc/en/Tutorial/Stepper_28BYJ
 
 
 */


#include "Arduino.h"
#include "Stepper_28BYJ.h"

/*
 конструктор для 4-проводной схемы подключения двигателя
 указываем какие выводы используются для управления двигателем
 */

Stepper_28BYJ::Stepper_28BYJ(byte maskPortD, byte maskPortB) {
    this->stepsPerTurn = 4076;    // Количество шагов на один оборот внешнего вала на 360".
    this->maskPortB = maskPortB;
    this->maskPortD = maskPortD;
    // устанавливаем режим работы выводов на ВЫВОД
    pinMode(9, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(2, OUTPUT);
}


/*
 * Для всех функций движения направление определяется относительно
 * такого расположения колес: *-|___|-*
 * где * это колесо
 * а - это вал
 */


/*                      |    _____   ^
 * При движении налево  \/ *-|___|-* | <--- вот эта тележка
 * должна вращать оба колеса по часовой стрелке
 */
void Stepper_28BYJ::turnCounterclockwise(int stepsToTurn) {
    int stepsLeft = stepsToTurn;
    while (stepsLeft > 0){
        delayMicroseconds(LEAST_DELAY);
        stepMotors(stepsLeft % 8);
        stepsLeft--;
    }
}


/*                      ^   _____   |
 * При движении направо | *-|___|-* \/ <--- вот эта тележка
 * должна вращать оба колеса против часовой стрелки
 */
void Stepper_28BYJ::turnClockwise(int stepsToTurn) {
    int stepsPassed = 0;
    while(stepsPassed < stepsToMove){
        delayMicroseconds(LEAST_DELAY);
        stepMotors(stepsPassed % 8);
        stepsPassed++;
    }
}
/*
 * Направление поворота определяется знаком аргумента
 * Положительное - по часовой стрелке
 */
void Stepper_28BYJ::turn(int stepsToTurn) {
    int direction = stepsToTurn > 0? CLOCKWISE : COUNTERCLOCKWISE;

    if(direction == CLOCKWISE){
        turnClockwise(stepsToTurn);
    } else if (direction == COUNTERCLOCKWISE){
        turnCounterclockwise(stepsToTurn);
    }
}


/*                     ^   _____   ^
 * При движении вперед | *-|___|-* | <--- вот эта тележка
 * (стрелочки показывают направление движения)
 * должна вращать левое колесо против часовой стрелки
 * а правое - по часовой.
 */
void Stepper_28BYJ::moveForward(int stepsToMove) {
    int stepsPassed = 0;
    while(stepsPassed < stepsToMove){
        delayMicroseconds(LEAST_DELAY);
        stepMotorsOpposite(stepsPassed % 8);
        stepsPassed++;
    }
}

/*                      |    _____    |
 * При движении назад   \/  *-|___|-* \/ <--- вот эта тележка
 * должна вращать левое колесо по часовой стрелке
 * а правое - против часовой
 */
void Stepper_28BYJ::moveBackward(int stepsToMove) {
    int stepsLeft = stepsToMove;
    while(stepsLeft > 0){
        delayMicroseconds(LEAST_DELAY);
        stepMotorsOpposite(stepsPassed % 8);
        stepsLeft--;
    }
}

/*
 * Для удобства направление движения определяется
 * знаком аргумента. Положительное вперед, отрицательное назад
 * Иначе пришлось бы добавить второй аргумент.
 * Возможно, для ясности так и стоит поступить?
 */
void Stepper_28BYJ::move(int stepsToMove) {
    int direction = stepsToMove > 0? FORWARD : BACKWARD;

    if(direction == FORWARD){
        moveForward(stepsToMove);
    } else if (direction == BACKWARD){
        moveBackward(stepsToMove);
    }
}

/*
 *   (Суффикс 0b обозначает двоичную запись числа)
 *   Биты двоичной записи числа  идут справа налево по значимости
 *                       0b00000000
 *    Наиболее значимый <----------- наименее значимый
 *    И нумеруются соответственно.
 *
 *      C0 - BLUE
 *      C1 - PINK
 *      C2 - YELLOW
 *      C3 - ORANGE
 *      Шаг     C   C1	C2	C3
 *        1     0   0	0	1
 *        2     0   0	1	1
 *        3     0   0	1	0
 *        4     0   1	1	0
 *        5     0   1	0	0
 *        6     1   1	0	0
 *        7     1   0	0	0
 *        8     1   0	0	1
 *
 *   PORTD отображается на цифровые выводы 0-7
 *   PORTB отображается на цифровые выводы 8-13 (См. https://www.arduino.cc/en/Reference/PortManipulation)
 *
 * Как выставлять сигналы на нужные ноги?
 * Побитовое или (операция |) 0000 и 0101 даст 0101, это позволяет выставлять 1 на нужные порты
 * Побитовое и (операция &) 0011 и 0101 даст 0001, это позволяет обнулять нужные выводы
 *
 *         0  1  2  3  4  5  6  7         8  9 10 11 12 13
 *  PORTB                         PORTD =                   ===>
 */


/*
 * Последовательно передавая числа от 0 до 7
 * моторы будут вращаться по часовой стрелке
 * Вот так.
 *   |   _____   ^
 *  \/ *-|___|-* |
 *
 * Последовательно передавая числа от 7 до 0
 * моторы будут вращаться против часовой стрелки
 *   ^   _____   |
 *   | *-|___|-* \/
 *
 *   Т.е.  на 4 управлающих пина первого и
 *   на 4 управляющих пина второго мотора будут подаваться
 *   одинаковые сигналы.
 *
 */
void Stepper_28BYJ::stepMotors(int thisStep) {
    byte reg2, reg1;
    reg1 = PORTD & 0b00000011; // 0 и 1 биты PORTD соотв. выводам RT TX, т.е. отвечают за сериал.
    reg2 = PORTB & 0b11111100;
    switch (thisStep) {
        case 0:    // 0001
            PORTD = reg1 | 0b01000100;
            PORTB = reg2 | 0b00000000;
            break;
        case 1:    // 0011
            PORTD = reg1 | 0b11001100;
            PORTB = reg2 | 0b00000000;
            break;
        case 2:    //0010
            PORTD = reg1 | 0b10001000;
            PORTB = reg2 | 0b00000000;
            break;
        case 3:    //0110
            PORTD = reg1 | 0b10011000;
            PORTB = reg2 | 0b00000001;
            break;
        case 4:    // 0100
            PORTD = reg1 | 0b00010000;
            PORTB = reg2 | 0b00000001;
            break;
        case 5:    // 1100
            PORTD = reg1 | 0b00110000;
            PORTB = reg2 | 0b00000011;
            break;
        case 6:    //1000
            PORTD = reg1 | 0b00100000;
            PORTB = reg2 | 0b00000010;
            break;
        case 7:    //1001
            PORTD = reg1 | 0b01100100;
            PORTB = reg2 | 0b00000010;
            break;
    }
}


/*
 * Последовательно передавая числа от 0 до 7
 * левый мотор будет вращаться по часовой стрелке, а правый - против часовой
 * Вот так.
 *   |   _____    |
 *  \/ *-|___|-* \/
 * Последовательно передавая числа от 7 до 0
 * левый мотор будет вращаться против часовой стрелки, а правый - по часовой
 * Вот так.
 *   ^   _____   ^
 *   | *-|___|-* |
 *
 * Т.е. передавая число, для одного мотора будет выставляться соотв. сигналы
 * Для другого - симметричные ( 0001 - 1001, 0011 - 1000 и т.д.)
 * 0b11000000 0b00000010
 * 0b11100000 0b00000000
 * 0b10100000 0b00000000
 * 0b00110000 0b00000000
 * 0b00010000 0b00000001
 * 0b00011000 0b00000001
 * 0b00001000 0b00000011
 * 0b01001000 0b00000010
 */

//void Stepper_28BYJ::stepMotorsOpposite(int thisStep) {
//    byte reg2, reg1;
//    reg1 = PORTD & 0b00000011; // 0 и 1 биты PORTD соотв. выводам RT TX, т.е. отвечают за сериал.
//    reg2 = PORTB & 0b11111100;
//    switch (thisStep) {
//        case 0:    // 0001
//            PORTD = reg1 | 0b11000000;
//            PORTB = reg2 | 0b00000010;
//            break;
//        case 1:    // 0011
//            PORTD = reg1 | 0b11100000;
//            PORTB = reg2 | 0b00000000;
//            break;
//        case 2:    //0010
//            PORTD = reg1 | 0b10100000;
//            PORTB = reg2 | 0b00000000;
//            break;
//        case 3:    //0110
//            PORTD = reg1 | 0b00110000;
//            PORTB = reg2 | 0b00000000;
//            break;
//        case 4:    // 0100
//            PORTD = reg1 | 0b00010000;
//            PORTB = reg2 | 0b00000001;
//            break;
//        case 5:    // 1100
//            PORTD = reg1 | 0b00011000;
//            PORTB = reg2 | 0b00000001;
//            break;
//        case 6:    //1000
//            PORTD = reg1 | 0b00001000;
//            PORTB = reg2 | 0b00000011;
//            break;
//        case 7:    //1001
//            PORTD = reg1 | 0b01001000;
//            PORTB = reg2 | 0b00000010;
//            break;
//    }
//}

void Stepper_28BYJ::stepMotorsOpposite(int thisStep) {
    byte reg2, reg1;
    reg1 = PORTD & 0b00000011; // 0 и 1 биты PORTD соотв. выводам RT TX, т.е. отвечают за сериал.
    reg2 = PORTB & 0b11111100;
    switch (thisStep) {
        case 0:    // 0001
            PORTD = reg1 | 0b01000100;
            PORTB = reg2 | 0b00000010;
            break;
        case 1:    // 0011
            PORTD = reg1 | 0b00001100;
            PORTB = reg2 | 0b00000010;
            break;
        case 2:    //0010
            PORTD = reg1 | 0b00001000;
            PORTB = reg2 | 0b00000011;
            break;
        case 3:    //0110
            PORTD = reg1 | 0b00011000;
            PORTB = reg2 | 0b00000001;
            break;
        case 4:    // 0100
            PORTD = reg1 | 0b10010000;
            PORTB = reg2 | 0b00000001;
            break;
        case 5:    // 1100
            PORTD = reg1 | 0b10110000;
            PORTB = reg2 | 0b00000000;
            break;
        case 6:    //1000
            PORTD = reg1 | 0b10100000;
            PORTB = reg2 | 0b00000000;
            break;
        case 7:    //1001
            PORTD = reg1 | 0b11100100;
            PORTB = reg2 | 0b00000000;
            break;
    }
}


void Stepper_28BYJ::setStepsPerTurn(int stepsPerTurn) {
    this->stepsPerTurn = stepsPerTurn;
}



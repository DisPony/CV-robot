

#include "ResponsiveDualStepper.h"

// При повороте нужно чаще проверять появление новых команд
// т.к. при  езде 500 шагов = ~ 2-3см, но 45" поворота.
#define STEPS_PERIOD 500
#define TURN_PERIOD 50

ResponsiveDualStepper::ResponsiveDualStepper(byte maskPortD, byte maskPortB, Interaction* interaction)
        : DualStepper(maskPortD, maskPortB), interaction(interaction) {}

//
void ResponsiveDualStepper::move(long stepsToMove) {
    int stepsLeft = abs(stepsToMove);
    int direction = stepsToMove > 0? FORWARD : BACKWARD;
    while(stepsLeft != 0){
        int stepsPart;
        if(stepsLeft > STEPS_PERIOD){
            stepsPart = STEPS_PERIOD;
            stepsLeft -= STEPS_PERIOD;
        } else {
            stepsPart = stepsLeft;
            stepsLeft = 0;
        }
        DualStepper::move(stepsPart * direction);
        if(interaction->proceed() == STOP_MOVEMENT){
            stepsLeft = 0;
        }
    }
}

void ResponsiveDualStepper::turn(long stepsToTurn) {
    int stepsLeft = abs(stepsToTurn);
    int direction = stepsToTurn > 0? CLOCKWISE : COUNTERCLOCKWISE;
    while(stepsLeft != 0){
        int stepsPart;
        if(stepsLeft > TURN_PERIOD){
            stepsPart = TURN_PERIOD;
            stepsLeft -= TURN_PERIOD;
        } else {
            stepsPart = stepsLeft;
            stepsLeft = 0;
        }
        DualStepper::turn(stepsPart * direction);
        if(interaction->proceed() == STOP_MOVEMENT){
            stepsLeft = 0;
        }
    }
}

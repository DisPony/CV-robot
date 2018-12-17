

#include "ResponsiveDualStepper.h"

#define STEPS_BETWEEN_AVAILABILITY 500

ResponsiveDualStepper::ResponsiveDualStepper(byte maskPortD, byte maskPortB, Interaction* interaction)
        : DualStepper(maskPortD, maskPortB), interaction(interaction) {}

//
void ResponsiveDualStepper::move(long stepsToMove) {
    int stepsLeft = abs(stepsToMove);
    int direction = stepsToMove > 0? FORWARD : BACKWARD;
    while(stepsLeft != 0){
        int stepsPart;
        if(stepsLeft > STEPS_BETWEEN_AVAILABILITY){
            stepsPart = STEPS_BETWEEN_AVAILABILITY;
            stepsLeft -= STEPS_BETWEEN_AVAILABILITY;
        } else {
            stepsPart = stepsLeft;
            stepsLeft = 0;
        }
        DualStepper::move(stepsPart * direction);
        interaction->proceed();
    }

}

void ResponsiveDualStepper::turn(long stepsToTurn) {
    int stepsLeft = abs(stepsToTurn);
    int direction = stepsToTurn > 0? CLOCKWISE : COUNTERCLOCKWISE;
    while(stepsLeft != 0){
        int stepsPart;
        if(stepsLeft > STEPS_BETWEEN_AVAILABILITY){
            stepsPart = STEPS_BETWEEN_AVAILABILITY;
            stepsLeft -= STEPS_BETWEEN_AVAILABILITY;
        } else {
            stepsPart = stepsLeft;
            stepsLeft = 0;
        }
        DualStepper::turn(stepsPart * direction);
        interaction->proceed();
    }
}

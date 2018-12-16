

#include "ResponsiveDualStepper.h"
#include "DualStepper.h"

#define STEPS_BETWEEN_AVAILABILITY 500

ResponsiveDualStepper::ResponsiveDualStepper(byte maskPortD, byte maskPortB, Interaction interaction)
        : DualStepper(maskPortD, maskPortB), interaction(interaction) {}

void ResponsiveDualStepper::move(int stepsToMove) {
    int stepsLeft = abs(stepsToMove);
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
        DualStepper::move(stepsPart);
        if(Serial.available()){
            interaction.proceed();
        }
    }

}

void ResponsiveDualStepper::turn(int stepsToTurn) {
    DualStepper::turn(stepsToTurn);
}

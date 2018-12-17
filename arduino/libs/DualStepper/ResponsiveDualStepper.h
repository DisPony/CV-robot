
#include "DualStepper.h"
#include "Interaction.h"

#ifndef LIBS_RESPONSIVEDUALSTEPPER_H
#define LIBS_RESPONSIVEDUALSTEPPER_H


class ResponsiveDualStepper : public DualStepper {
private:
Interaction* interaction;
public:
    static const byte STOP_MOVEMENT = 10;
    ResponsiveDualStepper(byte maskPortD, byte maskPortB, Interaction* interaction);
    void move(long stepsToMove) override;
    void turn(long stepsToTurn) override;
};


#endif //LIBS_RESPONSIVEDUALSTEPPER_H

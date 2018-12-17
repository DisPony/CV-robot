//
// Created by Никита on 15.12.2018.
//

#ifndef LIBS_SERIALINTERACTION_H
#define LIBS_SERIALINTERACTION_H

/*
 * У Arduino нет средств для параллельного исполнения кода
 * кроме прерываний (не совсем параллельное исполнение).
 * Этот класс предоставляет поведение, которое могут
 * включать в себя другие классы и исполнять в промежутках между
 * основной работой.
 */
class Interaction {
public:
    virtual void proceed()= 0;
};


#endif //LIBS_SERIALINTERACTION_H

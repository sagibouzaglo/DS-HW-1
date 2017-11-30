//
// Created by Amir on 30/11/2017.
//

#include <iostream>
#include <sstream>
#include "../Trainer.h"
#include <assert.h>

int main(){
    Trainer trainer1(23);
    assert(trainer1.getTrainerID()==23);
    assert(trainer1.getTopGladiatorID()==-1);
    assert(trainer1.addGladiator(7,7)==SUCCESS);
    assert(trainer1.getTopGladiatorID()==7);
    assert(trainer1.addGladiator(8,8)==SUCCESS);
    assert(trainer1.getTopGladiatorID()==8);
    assert(trainer1.freeGladiator(8,8)==SUCCESS);
    assert(trainer1.freeGladiator(1,1)==FAILURE);
    assert(trainer1.getTopGladiatorID()==7);
    assert(trainer1.addGladiator(6,7)==SUCCESS);
    assert(trainer1.addGladiator(6,5)==FAILURE);
    assert(trainer1.addGladiator(20,1)==SUCCESS);
    assert(trainer1.getTopGladiatorID()==6);

}
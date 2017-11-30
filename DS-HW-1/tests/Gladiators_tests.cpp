//
// Created by Amir on 30/11/2017.
//

#include <iostream>
#include <sstream>
#include "../Gladiator.h"
#include <assert.h>

int main(){
    Gladiator glad1(1,1,1);
    assert(glad1.GetID()==1);
    assert(glad1.GetLevel()==1);
    assert(glad1.LevelUp(1)==SUCCESS);
    assert(glad1.GetLevel()==2);
    assert(glad1.ChangeID(5)==SUCCESS);
    assert(glad1.LevelMultiply(5)==SUCCESS);
    assert(glad1.GetLevel()==10);
}
//
// Created by Amir on 03/12/2017.
//

#include "library1.h"
#include "Colosseum.h"

#define NULL_CHECK(condition) \
    if(!(condition)) { \
        return INVALID_INPUT; \
    } \

void* Init(){

    Colosseum *DS=new Colosseum();
    return (void*)DS;
}

StatusType AddTrainer(void *DS, int trainerID){
    NULL_CHECK(DS);
    return ((Colosseum*)DS)-> AddTrainer (trainerID);
}

StatusType BuyGladiator(void *DS, int gladiatorID, int trainerID, int level){
    NULL_CHECK(DS);
    return ((Colosseum*)DS)-> BuyGladiator(gladiatorID,trainerID,level);
}

StatusType FreeGladiator(void *DS, int gladiatorID){
    NULL_CHECK(DS);
    return ((Colosseum*)DS)->FreeGladiator(gladiatorID);
}

StatusType LevelUp(void *DS, int gladiatorID, int levelIncrease){
    NULL_CHECK(DS);
    return ((Colosseum*)DS)->LevelUp(gladiatorID,levelIncrease);
}

StatusType UpgradeGladiator(void *DS, int gladiatorID, int upgradedID){
    NULL_CHECK(DS);
    return ((Colosseum*)DS)->UpgradeGladiator(gladiatorID,upgradedID);
}

StatusType GetTopGladiator(void *DS, int trainerID, int *gladiatorID){
    NULL_CHECK(DS);
    return ((Colosseum*)DS)->GetTopGladiator(trainerID,gladiatorID);
}

StatusType GetAllGladiatorsByLevel(void *DS, int trainerID, int **gladiators, int *numOfGladiator){
    NULL_CHECK(DS);
    return ((Colosseum*)DS)->GetAllGladiatorsByLevel(trainerID,gladiators,numOfGladiator);
}

StatusType UpdateLevels(void *DS, int stimulantCode, int stimulantFactor){
    NULL_CHECK(DS);
    return ((Colosseum*)DS)->UpdateLevels(stimulantCode,stimulantFactor);
}

void Quit(void** DS){
    if(DS==NULL)
        return;
    Colosseum** col=((Colosseum**)DS);
    delete *col;
    *DS=NULL;
}
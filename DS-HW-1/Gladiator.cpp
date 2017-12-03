//
// Created by Amir on 30/11/2017.
//

#include "Gladiator.h"

/**---------------------------------------------------------------------------*/
Gladiator::Gladiator(int ID, int trainerID, int level): ID(ID), trainerID(trainerID),
level(level) {}
/**---------------------------------------------------------------------------*/
//Gladiator::~Gladiator() {}//////////////////////////////////////////////////////////////////////////////
/**---------------------------------------------------------------------------*/
Gladiator::Gladiator(const Gladiator& glad):ID(glad.ID),trainerID(glad.trainerID),
                                 level(glad.level){}
/**---------------------------------------------------------------------------*/
StatusType Gladiator::LevelUp(int levelincrease) {
    this->level=this->level+levelincrease;
    return SUCCESS;
}
/**---------------------------------------------------------------------------*/
int Gladiator::GetLevel() const {
    return this->level;
}
/**---------------------------------------------------------------------------*/
StatusType Gladiator::ChangeID(int new_ID) {
    this->ID=new_ID;
    return SUCCESS;
}
/**---------------------------------------------------------------------------*/
StatusType Gladiator::LevelMultiply(int factor) {
    this->level=this->level*factor;
    return SUCCESS;
}
/**---------------------------------------------------------------------------*/
int Gladiator::GetID() const{
    return this->ID;
}
/**---------------------------------------------------------------------------*/
int Gladiator::GetTrainerID() const {
    return this->trainerID;
}
/**---------------------------------------------------------------------------*/
Gladiator& Gladiator::operator=(const Gladiator &gladiator) {
    this->ID=gladiator.ID;
    this->trainerID=gladiator.trainerID;
    this->level=gladiator.level;
    return *this;
}
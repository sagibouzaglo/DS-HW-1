//
// Created by Amir on 30/11/2017.
//
#include "Trainer.h"

#define RANDOM_LVL 7

/**---------------------------------------------------------------------------*/
Trainer::Trainer(int ID):ID(ID),number_of_gladiators(0),glad_tree(),best_gladiator(
        nullptr) {}
/**---------------------------------------------------------------------------*/
//Trainer::~Trainer() {
 //   delete
   // delete toDestory;
//}
/**---------------------------------------------------------------------------*/
Trainer::Trainer(const Trainer &toCopy):ID(toCopy.ID),number_of_gladiators(toCopy.number_of_gladiators)
                ,glad_tree(toCopy.glad_tree),best_gladiator(toCopy.best_gladiator){}
/**---------------------------------------------------------------------------*/
StatusType Trainer::addGladiator(int glad_ID, int glad_lvl) {
    Gladiator* temp_glad=new Gladiator(glad_ID,this->ID,glad_lvl);
    //If there is no such GLAD_ID
    if(!(this->glad_tree.Search(*(temp_glad),CompareByLevel()))){
        this->glad_tree.Insert(*temp_glad,CompareByLevel());
        delete temp_glad;
        return SUCCESS;
    }
        //There exists a gladiator with this ID
    else{
        delete temp_glad;
        return FAILURE;
    }

}
/**---------------------------------------------------------------------------*/
StatusType Trainer::lvlUpGladiator(int glad_ID, int lvlincrease) {
    Gladiator* temp_glad=new Gladiator(glad_ID,this->ID,RANDOM_LVL);
    if(this->glad_tree.Search(*(temp_glad),CompareByLevel())){
        this->glad_tree.GetRoot().LevelUp(lvlincrease);
        delete temp_glad;
        return SUCCESS;
    }
    else{
        delete temp_glad;
        return FAILURE;
    }
}

/**---------------------------------------------------------------------------*/
StatusType Trainer::freeGladiator(int glad_ID) {
    Gladiator* temp_glad=new Gladiator(glad_ID,this->ID,RANDOM_LVL);
    if(this->glad_tree.Search(*(temp_glad),CompareByLevel())){
        this->glad_tree.Delete(*temp_glad,CompareByLevel());
        delete temp_glad;
        return SUCCESS;
    }
    else{
        delete temp_glad;
        return FAILURE;
    }
}
/**---------------------------------------------------------------------------*/
Gladiator* Trainer::getTopGladiator() const {
    return this->best_gladiator;
}
/**---------------------------------------------------------------------------*/
int Trainer::getTrainerID() const {
    return this->ID;
}



//
// Created by Amir on 30/11/2017.
//
#include "Trainer.h"


/**---------------------------------------------------------------------------*/
Trainer::Trainer(int ID) : ID(ID), number_of_gladiators(0), glad_tree(),
                           best_gladiator_ID(-1), best_gladiator_lvl(-1) {}

/**---------------------------------------------------------------------------*/
Trainer::~Trainer() {}

/**---------------------------------------------------------------------------*/
Trainer::Trainer(const Trainer &toCopy) : ID(toCopy.ID), number_of_gladiators(
        toCopy.number_of_gladiators), glad_tree(toCopy.glad_tree),
                                          best_gladiator_ID(
                                                  toCopy.best_gladiator_ID),
                                          best_gladiator_lvl(
                                                  toCopy.best_gladiator_lvl) {}

/**---------------------------------------------------------------------------*/
bool Trainer::best_update(int GladID,int GladLvl){
    if(this->best_gladiator_lvl>GladLvl){
        return false;
    }
    if(this->best_gladiator_lvl<GladLvl || this->best_gladiator_ID>GladID){
        this->best_gladiator_ID=GladID;
        this->best_gladiator_lvl=GladLvl;
        return true;
    }
    return false;
}
/**---------------------------------------------------------------------------*/
StatusType Trainer::addGladiator(int glad_ID, int glad_lvl) {
    Gladiator temp_glad(glad_ID, this->ID, glad_lvl);
    //If there is no such GLAD_ID
    if (this->glad_tree.Insert(temp_glad, CompareGladiatorByLevel())) {
        best_update(glad_ID,glad_lvl);
        this->number_of_gladiators++;
        return SUCCESS;
    }
        //There exists a gladiator with this ID
    else {
        return FAILURE;
    }

}

/**---------------------------------------------------------------------------*/
StatusType Trainer::freeGladiator(int glad_ID, int glad_lvl) {
    Gladiator temp_glad(glad_ID, this->ID, glad_lvl);
    if (this->glad_tree.Delete(temp_glad, CompareGladiatorByLevel())) {
        this->number_of_gladiators--;
        if(this->best_gladiator_ID==glad_ID){
            if(this->number_of_gladiators==0){
                best_gladiator_ID=-1;
                best_gladiator_lvl=0;
            }else{
                this->glad_tree.Find_Max(CompareGladiatorByLevel());
                this->best_gladiator_ID=this->glad_tree.GetRoot().GetID();
                this->best_gladiator_lvl=this->glad_tree.GetRoot().GetLevel();
            }

        }
        return SUCCESS;
    } else {
        return FAILURE;
    }
}

/**---------------------------------------------------------------------------*/
StatusType Trainer::lvlUpGladiator(int glad_ID, int glad_lvl, int lvlincrease) {
    if (this->freeGladiator(glad_ID, glad_lvl) == SUCCESS) {
        this->addGladiator(glad_ID, glad_lvl + lvlincrease);
        return SUCCESS;
    } else {
        return FAILURE;
    }
}

/**---------------------------------------------------------------------------*/
int Trainer::getTopGladiatorID() const {
    return this->best_gladiator_ID;
}

/**---------------------------------------------------------------------------*/
int Trainer::getTrainerID() const {
    return this->ID;
}
/**---------------------------------------------------------------------------*/
int Trainer::getNumberOfGladiatoes() const{
    return this->number_of_gladiators;
}



/**---------------------------------------------------------------------------*/
StatusType Trainer::getAllGladiatorsByLevel(int **gladiators,
                                            int *numberofgladiators) {
    *numberofgladiators = this->number_of_gladiators;
    *gladiators = (int *) malloc(sizeof(int) * this->number_of_gladiators);
    CopyGladiatorID func(*gladiators);
    this->glad_tree.BackwardsInOrder(func);
}


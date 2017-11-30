//
// Created by Amir on 30/11/2017.
//
#include "Trainer.h"


/**---------------------------------------------------------------------------*/
Trainer::Trainer(int ID):ID(ID),number_of_gladiators(0),glad_tree(),best_gladiator_ID(-1) {}
/**---------------------------------------------------------------------------*/
Trainer::~Trainer() {}
/**---------------------------------------------------------------------------*/
Trainer::Trainer(const Trainer &toCopy):ID(toCopy.ID),number_of_gladiators(toCopy.number_of_gladiators)
                ,glad_tree(toCopy.glad_tree),best_gladiator_ID(toCopy.best_gladiator_ID){}
/**---------------------------------------------------------------------------*/
StatusType Trainer::addGladiator(int glad_ID, int glad_lvl) {
    Gladiator* temp_glad=new Gladiator(glad_ID,this->ID,glad_lvl);
    //If there is no such GLAD_ID
    if(!(this->glad_tree.Search(*(temp_glad),CompareByLevel()))){
        this->glad_tree.Insert(*temp_glad,CompareByLevel());
        this->glad_tree.Find_Max(CompareByLevel());
        this->best_gladiator_ID=this->glad_tree.GetRoot().GetID();
        this->number_of_gladiators++;
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
StatusType Trainer::freeGladiator(int glad_ID,int glad_lvl) {
    Gladiator* temp_glad=new Gladiator(glad_ID,this->ID,glad_lvl);
    if(this->glad_tree.Search(*(temp_glad),CompareByLevel())){
        this->glad_tree.Delete(*temp_glad,CompareByLevel());
        this->glad_tree.Find_Max(CompareByLevel());
        this->best_gladiator_ID=this->glad_tree.GetRoot().GetID();
        delete temp_glad;
        this->number_of_gladiators--;
        return SUCCESS;
    }
    else{
        delete temp_glad;
        return FAILURE;
    }
}
/**---------------------------------------------------------------------------*/
StatusType Trainer::lvlUpGladiator(int glad_ID,int glad_lvl, int lvlincrease) {
    Gladiator* temp_glad=new Gladiator(glad_ID,this->ID,glad_lvl);
    if(this->glad_tree.Search(*(temp_glad),CompareByLevel())){
        this->glad_tree.GetRoot().LevelUp(lvlincrease);
        this->glad_tree.Find_Max(CompareByLevel());
        this->best_gladiator_ID=this->glad_tree.GetRoot().GetID();
        delete temp_glad;
        return SUCCESS;
    }
    else{
        delete temp_glad;
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



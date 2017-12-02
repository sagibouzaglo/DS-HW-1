//
// Created by Amir on 30/11/2017.
//
#include "Colosseum.h"
#define RANDOM_LVL 7
#define RANDOM_TRAINER 7

/**---------------------------------------------------------------------------*/
StatusType Colosseum::AddTrainer(int trainerID) {
    if (trainerID <= 0) {
        return INVALID_INPUT;
    }
    Trainer new_trainer(trainerID);
    if (this->trainers_tree.Insert(new_trainer, CompareTrainer())) {
        delete &new_trainer;
        return SUCCESS;
    } else {
        delete &new_trainer;
        return FAILURE;
    }
}

/**---------------------------------------------------------------------------*/
StatusType Colosseum::BuyGladiator(int gladID, int trainerID, int gladlvl) {
    if (gladID <= 0 || trainerID <= 0 || gladlvl <= 0) {
        return INVALID_INPUT;
    }
    Trainer trainer(trainerID);
    //If the trainers ID exists
    if(this->trainers_tree.Search(trainer,CompareTrainer())){
        Gladiator gladiator(gladID,trainerID,gladlvl);
        //Try inserting the new glad to the system
        if(this->glad_ID_tree.Insert(gladiator,CompareGladiatorByID())){
            //insert to lvls tree
            this->glad_lvl_tree.Insert(gladiator,CompareGladiatorByLevel());
            //insert to the trainers tree
            this->trainers_tree.GetRoot().addGladiator(gladID,gladlvl);
            //update system's best glad's
            this->best_glad_ID=this->glad_lvl_tree.Find_Max(CompareGladiatorByLevel())->GetID();
            delete &trainer,&gladiator;
            this->NumberOfGladiators++;
            return SUCCESS;
        }
        delete &gladiator;
    }
    delete &trainer;
    return FAILURE;
}
/**---------------------------------------------------------------------------*/
StatusType Colosseum::FreeGladiator(int gladID) {
    if(gladID<=0){
        return INVALID_INPUT;
    }
    Gladiator gladiator(gladID,RANDOM_TRAINER,RANDOM_LVL);
    //Search for the given gladiator's ID
    if(this->glad_ID_tree.Search(gladiator,CompareGladiatorByID())){
        //If we reached this point the gladiator exists in the system;
        delete &gladiator;
        //Make a copy of the gladiator we wish to remove, and the trainer to
        //remove him from
        Gladiator glad_cpy(gladID,this->glad_ID_tree.GetRoot().GetTrainerID(),
                             this->glad_ID_tree.GetRoot().GetLevel());
        Trainer trainer_cpy(glad_cpy.GetTrainerID());
        //Remove from lvl_tree
        this->glad_lvl_tree.Delete(glad_cpy,CompareGladiatorByLevel());
        //Remove from ID_tree
        this->glad_ID_tree.Delete(glad_cpy,CompareGladiatorByID());
        //Remove from the wanted Trainer tree
        this->trainers_tree.Search(trainer_cpy,CompareTrainer());
        assert(this->trainers_tree.GetRoot().getTrainerID()==trainer_cpy.getTrainerID());
        this->trainers_tree.GetRoot().freeGladiator(glad_cpy.GetID(),glad_cpy.GetLevel());
        //Update Best gladiator in the system
        this->best_glad_ID=this->glad_lvl_tree.Find_Max(CompareGladiatorByLevel())->GetID();
        //Finished updating everything
        delete &glad_cpy,&trainer_cpy;
        this->NumberOfGladiators--;
        return SUCCESS;

    }
    //The gladiator doesnt exist in the system
    delete &gladiator;
    return FAILURE;
}
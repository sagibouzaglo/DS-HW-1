//
// Created by Amir on 30/11/2017.
//
#include "Colosseum.h"
#define RANDOM_LVL 7
#define RANDOM_TRAINER 7


bool Colosseum::update_sys_best(int glad_ID, int glad_Lvl) {
    if(this->best_glad_lvl>glad_Lvl){
        return false;
    }
    if(this->best_glad_lvl<glad_Lvl || this->best_glad_ID>glad_ID){
        this->best_glad_lvl=glad_Lvl;
        this->best_glad_ID=glad_ID;
        return true;
    }
    return false;
}
/**---------------------------------------------------------------------------*/
StatusType Colosseum::AddTrainer(int trainerID) {
    if (trainerID <= 0) {
        return INVALID_INPUT;
    }
    Trainer new_trainer(trainerID);
    if (this->trainers_tree.Insert(new_trainer, CompareTrainer())) {
        return SUCCESS;
    } else {
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
        //Try inserting the new glad to the system's ID_tree
        if(this->glad_ID_tree.Insert(gladiator,CompareGladiatorByID())){
            //insert to lvls tree
            this->glad_lvl_tree.Insert(gladiator,CompareGladiatorByLevel());
            //insert to the trainers tree
            this->trainers_tree.GetRoot().addGladiator(gladID,gladlvl);
            //update system's best glad's
            this->update_sys_best(gladID,gladlvl);
            this->NumberOfGladiators++;
            return SUCCESS;
        }
    }
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
        this->NumberOfGladiators--;
        Gladiator glad_cpy(gladID,this->glad_ID_tree.GetRoot().GetTrainerID(),this->glad_ID_tree.GetRoot().GetLevel());
        Trainer trainer_cpy(glad_cpy.GetTrainerID());
        this->glad_lvl_tree.Delete(glad_cpy,CompareGladiatorByLevel());
        if(this->best_glad_ID==gladID){
            if(this->NumberOfGladiators==0){
                this->best_glad_ID=-1;
                this->best_glad_lvl=0;
            } else{
                this->glad_lvl_tree.Find_Max(CompareGladiatorByLevel());
                this->best_glad_ID=this->glad_lvl_tree.GetRoot().GetID();
                this->best_glad_lvl=this->glad_lvl_tree.GetRoot().GetLevel();
            }
        }
        //Remove from ID_tree
        this->glad_ID_tree.Delete(glad_cpy,CompareGladiatorByID());
        //Remove from the wanted Trainer tree
        this->trainers_tree.Search(trainer_cpy,CompareTrainer());
        assert(this->trainers_tree.GetRoot().getTrainerID()==trainer_cpy.getTrainerID());
        this->trainers_tree.GetRoot().freeGladiator(glad_cpy.GetID(),glad_cpy.GetLevel());

        //Finished updating everything
        return SUCCESS;

    }
    //The gladiator doesnt exist in the system
    return FAILURE;
}
/**---------------------------------------------------------------------------*/
StatusType Colosseum::LevelUp(int gladiatorID, int levelIncrease){
    if(gladiatorID<=0 || levelIncrease<=0){
        return INVALID_INPUT;
    }
    Gladiator gladiator(gladiatorID,RANDOM_TRAINER,RANDOM_LVL);
    if(this->glad_ID_tree.Search(gladiator,CompareGladiatorByID())){
        //If we reached this point the gladiator exists in the system
        Gladiator glad_cpy(gladiatorID,this->glad_ID_tree.GetRoot().GetTrainerID(),
        this->glad_ID_tree.GetRoot().GetLevel());
        //Remove gladiator from system
        this->FreeGladiator(gladiatorID);
        //Add the "new" gladiator to the system
        this->BuyGladiator(glad_cpy.GetID(),glad_cpy.GetTrainerID(),glad_cpy.GetLevel()+levelIncrease);
        return SUCCESS;
    }
    //Gladiator doesnt exist in system
   // delete &gladiator;
    return FAILURE;
}
/**---------------------------------------------------------------------------*/

StatusType Colosseum::GetTopGladiator( int trainerID, int* gladiatorID){
    if ((trainerID == 0) || (gladiatorID == nullptr)){
        return INVALID_INPUT;
    }
    if (trainerID<0){
        *gladiatorID=this->best_glad_ID;
        return SUCCESS;
    }
    Trainer trainerCopy(trainerID);
    //If the trainers ID exists
    if(this->trainers_tree.Search(trainerCopy,CompareTrainer())){
       *gladiatorID = this->trainers_tree.GetRoot().getTopGladiatorID();
        return SUCCESS;
    }
    return FAILURE;
}
/**---------------------------------------------------------------------------*/

StatusType Colosseum::GetAllGladiatorsByLevel(int trainerID, int **gladiators,
                                              int *numOfGladiator) {

    if(trainerID==0 || gladiators==nullptr||numOfGladiator==nullptr){
        return INVALID_INPUT;
    }
    if(trainerID<0){
        *numOfGladiator = this->NumberOfGladiators;
        *gladiators = (int *) malloc(sizeof(int) * this->NumberOfGladiators);
        CopyGladiatorID func(*gladiators);
        this->glad_lvl_tree.BackwardsInOrder(func);
        return SUCCESS;
    } else{
        Trainer trainer(trainerID);
        if(this->trainers_tree.Search(trainer,CompareTrainer())){
            this->trainers_tree.GetRoot().getAllGladiatorsByLevel(gladiators,numOfGladiator);
            return SUCCESS;
        } else{
            return FAILURE;
        }
    }
}
/**---------------------------------------------------------------------------*/
StatusType Colosseum::UpgradeGladiator(int gladiatorID, int upgradedID) {
    if(gladiatorID <=0 || upgradedID<=0){
        return INVALID_INPUT;
    }
    if(gladiatorID==upgradedID){
        return FAILURE;
    }
    Gladiator Upglad(upgradedID,RANDOM_TRAINER,RANDOM_LVL);
    //Find if there is no gladiator with upgradedID
    if(!(this->glad_ID_tree.Search(Upglad,CompareGladiatorByID()))){
        //Find if therE IS a gladiator with gladID
        Gladiator gladiator(gladiatorID,RANDOM_TRAINER,RANDOM_LVL);
        if(this->glad_ID_tree.Search(gladiator,CompareGladiatorByID())){
            //Make a cpy of the glad to upgrade
            Gladiator Glad_Cpy(gladiatorID,this->glad_ID_tree.GetRoot().GetTrainerID(),
            this->glad_ID_tree.GetRoot().GetLevel());

            //Change in ID tree
            this->glad_ID_tree.GetRoot().ChangeID(upgradedID);
            //Change in lvl_tree
            this->glad_lvl_tree.Search(Glad_Cpy,CompareGladiatorByLevel());
            this->glad_lvl_tree.GetRoot().ChangeID(upgradedID);
            if(this->best_glad_ID==gladiatorID){
                this->best_glad_ID=upgradedID;
            }
            //Change in trainer's tree
            Trainer trainer(Glad_Cpy.GetTrainerID());
            this->trainers_tree.Search(trainer,CompareTrainer());
            this->trainers_tree.GetRoot().UpgradeGladiator(Glad_Cpy,upgradedID);
            return SUCCESS;
        }
        return FAILURE;
    }
    return FAILURE;
}

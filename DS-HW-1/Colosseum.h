//
// Created by Amir on 30/11/2017.
//

#ifndef DS_HW_1_COLOSSEUM_H
#define DS_HW_1_COLOSSEUM_H


#include "Trainer.h"

/**
 * While Implementing the Gladiators ID tree we Have to make sure that we extract
 * His level!!!!!!!!!
 * In order to use that in Gladiators Levels Ordered Tree
 *
 *
 */
class Colosseum{
    SplayTree<Gladiator> glad_lvl_tree;
    SplayTree<Gladiator> glad_ID_tree;
    SplayTree<Trainer> trainers_tree;
    int best_glad_ID;
    int best_glad_lvl;
    int NumberOfGladiators ;

    bool update_sys_best(int glad_ID,int glad_Lvl);
public:
    Colosseum():best_glad_ID(-1),best_glad_lvl(0),NumberOfGladiators(0){}
    ~Colosseum(){
        delete &glad_ID_tree;
        delete &glad_lvl_tree;
        delete &trainers_tree;
    }
    Colosseum(const Colosseum& col){}///////////////////////////////////////////
    /* Description:   This function inserts a new trainer to the Coloss
     * Input:         Trainer's ID
     * Output:        None.
     * Return Values: INVALID INPUT-if the given id was <=0
     *                SUCCESS- if the trainer was add successfully
     *                FAILURE-if the given ID already exists in the system
     */
    StatusType AddTrainer(int trainerID);
    /* Description:   This function inserts a new Gladiator to a given trainer
    * Input:         Glad's ID and lvl and the trainer ID to whom glad will be added
    * Output:        None.
    * Return Values: INVALID INPUT-if the given idis or lvl was <=0
    *                SUCCESS- if the glad was add successfully
    *                FAILURE-if the given glad ID already exists in the system
     *                or the wanted trainer ID doesnt exist
    */
    StatusType BuyGladiator(int gladID,int trainerID,int gladlvl);
    /* Description:   This function removes a Gladiator from the system
     * Input:         Glad's ID
     * Output:        None.
     * Return Values: INVALID INPUT-if the given id was <=0
     *                SUCCESS- if the glad was successfully removed
     *                FAILURE-if the given glad ID doesnt exist in the system
     */
    StatusType FreeGladiator(int gladID);
    /* Description:   This function levels up a Gladiator from the system
     * Input:         Glad's ID
     *                The number of lvls to be increased
     * Output:        None.
     * Return Values: INVALID INPUT-if the given id was <=0
     *                SUCCESS- if the glad was successfully removed
     *                FAILURE-if the given glad ID doesnt exist in the system
     */
    StatusType LevelUp(int gladiatorID, int levelIncrease);
    /* Description:   This function return the top Gladiator of the trainer
     *                  or system
     * Input:         trainers ID
     *                pointer to where the ID will be written
     * Output:        None.
     * Return Values: INVALID INPUT-trainer ID ==0 or gladiatorID==NULL
     *                SUCCESS- if the glad was successfully retrieved
     *                FAILURE-if the given trainer ID doesnt exist in the system
     */
    StatusType GetTopGladiator(int trainerID, int * gladiatorID);
    /* Description:   This function returns All of a given trainer(or system)
     *  gladiators sorted as requested
     * Input:         trainers ID
     *                pointer to where the gladiators IDs will be copied
     *                pointer to where the number of gladiators will be copied
     * Output:        None.
     * Return Values: INVALID INPUT-trainer ID ==0 or pointers==NULL
     *                SUCCESS- if the glad was successfully removed
     *                FAILURE-if the given trainer ID doesnt exist in the system
     */
    StatusType GetAllGladiatorsByLevel(int trainerID, int **gladiators, int *numOfGladiator);

    /* Description:   This function changes a given gladiator's ID
     * Input:         gladiator current ID
     *                gladiator future ID
     * Output:        None.
     * Return Values: INVALID INPUT-trainer one of the outputs<=0
     *                SUCCESS- if the glad ID was successfully changed
     *                FAILURE-no Such gladiatorID or upgradedID already found
     */
    StatusType UpgradeGladiator(int gladiatorID, int upgradedID);

    /* Description:   This function Upgrades the lvls of gladiators who fit the
     *                condition
     * Input:         stimulantCode
     *                stimulantFactor
     * Output:        None.
     * Return Values: INVALID INPUT-one of the codes<=1
     *                SUCCESS- if everything went well
     */
    StatusType UpdateLevels(int stimulantCode, int stimulantFactor);
};
#endif //DS_HW_1_COLOSSEUM_H

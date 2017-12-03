//
//  Trainer.h
//  DS-HW-1
//
//  Created by sagi bouzaglo on 27/11/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#ifndef Trainer_h
#define Trainer_h

#include "Gladiator.h"
#include "Splay_Tree.h"

class Trainer {
    int ID;
    int number_of_gladiators;
    SplayTree<Gladiator> glad_tree;
    int best_gladiator_ID;
    int best_gladiator_lvl;

    bool best_update(int GladID, int GladLvl);

public:
    Trainer(int ID);

    ~Trainer();

    Trainer(const Trainer &toCopy);

    StatusType addGladiator(int glad_ID, int glad_lvl);

    //Because we maintain order through lvls we have to know glads_lvl
    StatusType freeGladiator(int glad_ID, int glad_lvl);

    StatusType lvlUpGladiator(int glad_ID, int glad_lvl, int lvlincrease);

    int getTopGladiatorID() const;

    int getTrainerID() const;

    int getNumberOfGladiators() const;

    StatusType
    getAllGladiatorsByLevel(int **gladiators, int *numberofgladiators);

    void UpgradeGladiator(const Gladiator &glad, int upgradedID);

    void UpdateLevels(int stimulantCode, int stimulantFactor);

    SplayTree<Gladiator> &GetGladiatorsTree();

};

class CompareTrainer {
public:
    explicit CompareTrainer() {}

    int operator()(const Trainer &trainer1, const Trainer &trainer2) const {
        return (trainer2.getTrainerID() - trainer1.getTrainerID());
    }
};

/**---------------------------------------------------------------------------*/
class CopyGladiatorID {
    int *arr;
    int i;
public:
    explicit CopyGladiatorID(int *arr) : arr(arr), i(0) {}

    void operator()(Gladiator &glad) {
        arr[i] = glad.GetID();
        i++;
    }
};


/**---------------------------------------------------------------------------*/
class CopyGladiatorPointer {
    Gladiator **arr;
    int i;
public:
    explicit CopyGladiatorPointer(Gladiator **ptr_to_first_ptr) : arr(
            ptr_to_first_ptr), i(0) {}

    void operator()(Gladiator &glad) {
        arr[i] = &glad;
        i++;
    }
};

/**---------------------------------------------------------------------------*/

/*
class UpdateLevels{
    int stimulantCode;
    int stimulantFactor;
public:
    explicit UpdateLevels(int code, int factor)
            : stimulantCode(code), stimulantFactor(factor){}

    void operator()(Trainer &trainer) {
        int num = trainer.getNumberOfGladiators();
        Gladiator **locations = (Gladiator **) malloc(
                sizeof(Gladiator *) * num);
        GetLocations(num, locations, trainer.GetGladiatorsTree());
        Gladiator *gladiators = (Gladiator *) malloc(sizeof(Gladiator) * num);
        CpyGlads(num, gladiators, locations);
        Gladiator *To_Change[num] = {nullptr}, *Not_to_Change[num] = {nullptr};
        GetChangedandUnchaged(num, stimulantCode, stimulantFactor, gladiators,
                              To_Change, Not_to_Change);
        Gladiator **merged = (Gladiator **) malloc(sizeof(Gladiator *) * num);
        CompareGladiatorByLevel function;
        merge(merged, Not_to_Change, To_Change, num, function);
        PutBack(num, locations, merged);
    }
};
*/

#endif /* Trainer_h */

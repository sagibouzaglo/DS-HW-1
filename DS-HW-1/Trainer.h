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

#define NULL_ARGUMENT_CHECK(condition) \
    if(!(condition)) { \
        return ALLOCATION_ERROR; \
    } \

class Trainer {
    int ID;
    int number_of_gladiators;
    SplayTree<Gladiator> glad_tree;
    int best_gladiator_ID;
    int best_gladiator_lvl;


public:
    Trainer(int ID);

    //~Trainer();

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


    SplayTree<Gladiator> &GetGladiatorsTree();

    bool best_update(int GladID, int GladLvl);

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




class CopyGladiatorPointer {
    Gladiator** arr;
    int i;
public:
    explicit CopyGladiatorPointer(Gladiator** ptr_to_first_ptr) : arr(ptr_to_first_ptr),i(0){}

    void operator()(Gladiator& glad) {
        arr[i]= &glad;
        i++;
    }
};

static void GetLocations(int num, Gladiator** locations,SplayTree<Gladiator>& tree){
    CopyGladiatorPointer func(locations);
    tree.BackwardsInOrder(func);
}
template <class Function>
static void merge(Gladiator** merged,int num,Gladiator** Unchanged,int NC,
                  Gladiator** Changed,int C,Function& function){
    int c=0,nc=0;
    int M=0;
    while (c<C&& nc<NC){
        if(function(*Changed[c],*Unchanged[nc])>1){
            merged[M++]=Unchanged[nc++];
        } else{
            merged[M++]=Changed[c++];
        }
    }
    while (c<C){
        merged[M++]=Changed[c++];
    }
    while (nc<NC){
        merged[M++]=Unchanged[nc++];
    }
}

static void CpyGlads(int num,Gladiator* gladiators,Gladiator** locations){
    for (int k = 0; k <num ; ++k) {
        gladiators[k]=*locations[k];
    }
}

static void GetChangedandUnchaged(int num,int stimulantCode,int stimulantFactor,
                                  Gladiator* gladiators,Gladiator** Changed,Gladiator** UnChanged,
                                  int *num_of_changed,int* num_of_unchanged){
    int C=0,NC=0;
    for (int i = 0; i <num ; ++i) {
        if(gladiators[i].GetID()%stimulantCode==0){
            gladiators[i].LevelMultiply(stimulantFactor);
            Changed[C++]=&gladiators[i];
        } else{
            UnChanged[NC++]=&gladiators[i];
        }
    }
    *num_of_changed=C;
    *num_of_unchanged=NC;
}

static void PutBack(int num,Gladiator **locations,Gladiator** merged){
    for (int j = 0; j <num ; ++j) {
        *locations[j]=*merged[j];
    }
}

class TrainersUpgradeLevels{
    int stimulantCode;
    int stimulantFactor;
public:
    explicit TrainersUpgradeLevels(int code, int factor)
            : stimulantCode(code), stimulantFactor(factor){}

    StatusType operator()(Trainer &trainer) {
        int num = trainer.getNumberOfGladiators();
        Gladiator **locations = (Gladiator **) malloc(
                sizeof(Gladiator *) * num);
        NULL_ARGUMENT_CHECK(locations);
        GetLocations(num, locations, trainer.GetGladiatorsTree());
        Gladiator *gladiators = (Gladiator *) malloc(sizeof(Gladiator) * num);
        NULL_ARGUMENT_CHECK(gladiators);
        CpyGlads(num, gladiators, locations);
        Gladiator **To_Change =(Gladiator **) malloc(sizeof(Gladiator*) * num);
        NULL_ARGUMENT_CHECK(To_Change);
        Gladiator **Not_to_Change = (Gladiator **) malloc(sizeof(Gladiator*) * num);
        NULL_ARGUMENT_CHECK(Not_to_Change);
        int C,NC;
        GetChangedandUnchaged(num, stimulantCode, stimulantFactor, gladiators,
                              To_Change, Not_to_Change,&C,&NC);
        Gladiator **merged = (Gladiator **) malloc(sizeof(Gladiator *) * num);
        NULL_ARGUMENT_CHECK(merged);
        CompareGladiatorByLevel function;
        merge(merged,num, Not_to_Change,NC, To_Change, C, function);
        if(num!=0){
            trainer.best_update(merged[0]->GetID(),merged[0]->GetLevel());
        }
        PutBack(num, locations, merged);
        free(locations);
        free(gladiators);
        free(To_Change);
        free(Not_to_Change);
        free(merged);
        return SUCCESS;
    }
};


#endif /* Trainer_h */

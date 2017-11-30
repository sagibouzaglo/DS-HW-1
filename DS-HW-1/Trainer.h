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
public:
    Trainer(int ID);

    ~Trainer();

    Trainer(const Trainer &toCopy);

    StatusType addGladiator(int glad_ID, int glad_lvl);

    //Because we maintain order through lvls we have to know glads_lvl
    StatusType freeGladiator(int glad_ID,int glad_lvl);

    StatusType lvlUpGladiator(int glad_ID,int glad_lvl, int lvlincrease);

    int getTopGladiatorID() const;

    int getTrainerID() const;

};

#endif /* Trainer_h */

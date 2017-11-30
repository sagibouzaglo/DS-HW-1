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

class Trainer{
    int ID;
    int number_of_gladiators;
    SplayTree<Gladiator> glad_tree;
    Gladiator* best_gladiator;
public:
    Trainer(int ID);
    ~Trainer();
    Trainer(const Trainer& toCopy);
    StatusType addGladiator(int glad_ID,int glad_lvl);
    StatusType freeGladiator(int glad_ID);
    StatusType lvlUpGladiator(int glad_ID,int lvlincrease);
    Gladiator* getTopGladiator();

};

#endif /* Trainer_h */

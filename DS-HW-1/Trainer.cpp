//
// Created by Amir on 30/11/2017.
//
#include "Trainer.h"


/**---------------------------------------------------------------------------*/
Trainer::Trainer(int ID):ID(ID),number_of_gladiators(0),glad_tree(),best_gladiator(
        nullptr) {}
/**---------------------------------------------------------------------------*/
Trainer::~Trainer() {
    SplayTree<Gladiator>* toDestory=this->&glad_tree;
    delete toDestory;
}
/**---------------------------------------------------------------------------*/
Trainer::Trainer(const Trainer &toCopy):ID(toCopy.ID),number_of_gladiators(toCopy.number_of_gladiators)
                ,glad_tree(toCopy.glad_tree),best_gladiator(toCopy.best_gladiator){}
/**---------------------------------------------------------------------------*/
StatusType Trainer::addGladiator(int glad_ID, int glad_lvl) {
    Gladiator* temp_glad=new Gladiator(glad_ID,this->ID,glad_lvl);
    this->glad_tree.Search(*(temp_glad),CompareByID());
}


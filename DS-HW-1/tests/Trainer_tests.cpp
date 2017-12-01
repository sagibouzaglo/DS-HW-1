//
// Created by Amir on 30/11/2017.
//

#include <iostream>
#include <sstream>
#include "../Trainer.h"
#include <assert.h>

int main(){
    Trainer trainer1(23);
    assert(trainer1.getTrainerID()==23);
    assert(trainer1.getTopGladiatorID()==-1);
    assert(trainer1.addGladiator(7,7)==SUCCESS);
    assert(trainer1.getTopGladiatorID()==7);
    assert(trainer1.addGladiator(8,8)==SUCCESS);
    assert(trainer1.getTopGladiatorID()==8);
    assert(trainer1.freeGladiator(8,8)==SUCCESS);
    assert(trainer1.freeGladiator(1,1)==FAILURE);
    assert(trainer1.getTopGladiatorID()==7);
    assert(trainer1.addGladiator(6,7)==SUCCESS);
    assert(trainer1.addGladiator(6,5)==FAILURE);
    assert(trainer1.addGladiator(20,1)==SUCCESS);
    assert(trainer1.getTopGladiatorID()==6);
    //Glad tree is ( (ID,LVL) (20,1),(7,7),(6,7)
   /* for(int i=1;i<20;i++){
        if(i%2==0){
            trainer1.addGladiator(5*i,2*i);
        } else{
            trainer1.addGladiator(23*i,i);
        }
    }*/
    int * gladiators;
    int  number_of_gladiators;
    trainer1.getAllGladiatorsByLevel(&gladiators,&number_of_gladiators);
    std::cout << "Printing gladiators:(ID)\n";
    for(int i=0;i<number_of_gladiators;i++){
        std::cout <<"("<< gladiators[i] <<") " ;
    }
    delete gladiators;
    trainer1.getTrainerID();

}
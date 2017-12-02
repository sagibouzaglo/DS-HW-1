//
// Created by Amir on 02/12/2017.
//

#include "../Colosseum.h"
#include <iostream>
#include <sstream>

#define BARCA 1
#define MANU 2
#define REAL 3

#define MESSI 10
#define FELLAINI 31
#define CR7 7
#define SUAREZ 9
#define BALE 11
#define RASHFORD 19


#define GOD 100
#define B_DOR 99
#define CAPTAIN 10
#define AVG 5

int main(){
    Colosseum* colosseum=new Colosseum;
    //Check Colosseum add trainer:
    assert(colosseum->AddTrainer(0)==INVALID_INPUT);
    assert(colosseum->AddTrainer(BARCA)==SUCCESS);
    assert(colosseum->AddTrainer(BARCA)==FAILURE);
    assert(colosseum->AddTrainer(REAL)==SUCCESS);
    assert(colosseum->AddTrainer(MANU)==SUCCESS);
    //Check Colosseum BuyGladiator
    assert(colosseum->BuyGladiator(0,7,7)==INVALID_INPUT);
    assert(colosseum->BuyGladiator(7,0,7)==INVALID_INPUT);
    assert(colosseum->BuyGladiator(0,7,7)==INVALID_INPUT);
    assert(colosseum->BuyGladiator(MESSI,BARCA,GOD)==SUCCESS);
    assert(colosseum->BuyGladiator(FELLAINI,50,1)==FAILURE);//No such trainer
    assert(colosseum->BuyGladiator(MESSI,REAL,GOD)==FAILURE);//Glad exists
    assert(colosseum->BuyGladiator(CR7,REAL,B_DOR)==SUCCESS);
    assert(colosseum->BuyGladiator(FELLAINI,MANU,CAPTAIN)==SUCCESS);
    assert(colosseum->BuyGladiator(RASHFORD,MANU,AVG)==SUCCESS);
    assert(colosseum->BuyGladiator(SUAREZ,BARCA,AVG)==SUCCESS);
    assert(colosseum->BuyGladiator(BALE,REAL,AVG)==SUCCESS);
    colosseum->BuyGladiator(BALE,REAL,AVG);
    //
    int i=1;
    i++;
    i--;
    return 0;
}
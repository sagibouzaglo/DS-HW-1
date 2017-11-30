//
//  Gladiator.h
//  DS-HW-1
//
//  Created by sagi bouzaglo on 27/11/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#ifndef Gladiator_h
#define Gladiator_h

#include "library1.h"

class Gladiator {
    int ID;
    int trainerID;
    int level;
public:
    Gladiator(int ID, int trainerID, int level);

    //~Gladiator();

    Gladiator(const Gladiator &glad);

    int GetID() const;

    StatusType LevelUp(int levelincrease);

    int GetLevel() const;

    StatusType ChangeID(int new_ID);

    StatusType LevelMultiply(int factor);


};

class CompareByID {

public:
    explicit CompareByID() {}

    int operator()(const Gladiator &glad1, const Gladiator &glad2) const {
        return (glad1.GetID() == glad2.GetID());
    }
};

class CompareByLevel {

public:
    explicit CompareByLevel() {}

    int operator()(const Gladiator &glad1, const Gladiator &glad2) const {
        //WE CANNOT ALLOW IDENTICALS IDS
        if (glad1.GetID() == glad2.GetID()) {
            return 0;
        }//Gladiators doesnt have same level
        else if (glad1.GetLevel() != glad2.GetLevel()) {
            return glad2.GetLevel() - glad1.GetLevel();
        }//Gladiators have same lvl, Its would be difficult to understand logic
            //in the following line but its OK
        else{
            return glad1.GetID()-glad2.GetID();
        }
    }
};


#endif /* Gladiator_h */

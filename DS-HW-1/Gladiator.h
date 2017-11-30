//
//  Gladiator.h
//  DS-HW-1
//
//  Created by sagi bouzaglo on 27/11/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#ifndef Gladiator_h
#define Gladiator_h

class Gladiator {
    int ID;
    int trainerID;
    int level;
public:
    Gladiator(int ID, int trainerID, int level) : ID(ID), trainerID(trainerID),
                                                  level(level) {}
    ~Gladiator()= default;
    Gladiator(const Gladiator& glad){}

};


#endif /* Gladiator_h */

//
//  Object.hpp
//  Bio
//
//  Created by Ryan Schmitz on 2016-03-24.
//  Copyright © 2016 Ryan Schmitz. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include <stdio.h>
#include "shapes.h"

enum ObjectType {
    UNDEFINED_TYPE,
    ORGANISM,
    FOOD
};


class Object {
public:
    
    typedef Point<float> PositionType;
    typedef std::vector<Object*> ObjectsType;

    Object() : mType(UNDEFINED_TYPE) { }
    
    virtual ~Object() { }
    
    void Type(ObjectType newType) { mType = newType; }
    ObjectType Type() { return mType; }
    
    void Position(PositionType position) { mPosition = position; }
    PositionType Position() { return mPosition; }
    
    virtual void Update(ObjectsType& rObjects) = 0;
    
private:
    
    ObjectType   mType;
    PositionType mPosition;
};

typedef std::vector<Object*> ObjectsType;

#endif /* Object_hpp */

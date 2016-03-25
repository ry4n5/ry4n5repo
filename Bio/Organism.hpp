//
//  Organism.hpp
//  Bio
//
//  Created by Ryan Schmitz on 2016-03-24.
//  Copyright © 2016 Ryan Schmitz. All rights reserved.
//

#ifndef Organism_hpp
#define Organism_hpp

#include <stdio.h>
#include "Object.hpp"
#include "NeuralNetwork.hpp"

class Organism : public virtual Object {
public:
    
    Organism() : mNeuralNetwork(3, 20, 2) { }
    
    virtual void Update(ObjectsType& rObjects) {
        AssessObjects(rObjects);
    }
    
    void AssessObjects(ObjectsType& rObjects) {
        for(ObjectsType::iterator it = rObjects.begin(); it!= rObjects.end(); ++it) {
            AssessObject(**it);
        }
        MakeDecision();
        
        std::vector<float> target_outputs;
        target_outputs.push_back(1.f); // replace with x direction of nearest food
        target_outputs.push_back(1.f); // replace with y direction of nearest food
        mNeuralNetwork.PropagateBackwards(target_outputs, 0.5f, 0.1f); // N = 0.5, M=0.1, figure out what these are
    }
    
    void AssessObject(Object& rObject) {
        std::vector<float> inputs;
        inputs.push_back((float)rObject.Type());
        inputs.push_back(rObject.Position().X());
        inputs.push_back(rObject.Position().Y());
        mNeuralNetwork.FeedForward(inputs);
    }
    
    void MakeDecision() { }
    
private:
    void SetupNN () {
        
    }
    
    
    NeuralNetwork   mNeuralNetwork;
    
};


#endif /* Organism_hpp */

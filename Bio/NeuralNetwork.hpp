//
//  NeuralNetwork.hpp
//  Bio
//
//  Created by Ryan Schmitz on 2016-03-24.
//  Copyright © 2016 Ryan Schmitz. All rights reserved.
//

#ifndef NeuralNetwork_hpp
#define NeuralNetwork_hpp

#include <stdio.h>
#include <vector>
#include <cassert>
#include <cmath>

class NeuralNetwork {
    
public:
    
    typedef float InputType;
    typedef float HiddenType;
    typedef float OutputType;
    typedef float WeightType;
    
    typedef std::vector<InputType> InputsType;
    typedef std::vector<HiddenType> HiddensType;
    typedef std::vector<OutputType> OutputsType;
    typedef std::vector<WeightType> WeightsType;
    
    
    NeuralNetwork(int numInputs, int numHiddens, int numOutputs) {
        mInputs.resize(numInputs);
        mHiddens.resize(numHiddens);
        mOutputs.resize(numOutputs);
        mInputWeights.resize(numInputs * numHiddens);
        mOutputWeights.resize(numOutputs * numHiddens);
    }
    
    
    void FeedForward(InputsType& rInputs) {
        assert(rInputs.size() == mInputs.size());
        mInputs = rInputs;
        WeightsType::iterator in_weight_it = mInputWeights.begin();
        for(HiddensType::iterator hidden_it = mHiddens.begin(); hidden_it!= mHiddens.end(); ++hidden_it) {
            float sum = 0.f;
            for(InputsType::iterator input_it = mInputs.begin(); input_it!= mInputs.end(); ++input_it) {
                sum += (*input_it) * (*in_weight_it++);
            }
            *hidden_it = ApplySigmoid(sum);
        }
        
        WeightsType::iterator out_weight_it = mOutputWeights.begin();
        for(OutputsType::iterator output_it = mOutputs.begin(); output_it!= mOutputs.end(); ++output_it) {
            float sum = 0.f;
            for(HiddensType::iterator hidden_it = mHiddens.begin(); hidden_it!= mHiddens.end(); ++hidden_it) {
                sum += (*hidden_it) * (*out_weight_it++);
            }
            *output_it = ApplySigmoid(sum);
        }
    }
    
    
private:
    float ApplySigmoid(float value) {
        return tanh(value);
    }
    
    InputsType  mInputs;
    HiddensType mHiddens;
    OutputsType mOutputs;
    WeightsType mInputWeights;
    WeightsType mOutputWeights;
    
};

#endif /* NeuralNetwork_hpp */

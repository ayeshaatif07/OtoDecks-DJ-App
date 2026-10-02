/*
  ==============================================================================

ReverbEffect.h
Created: 22 Feb 2025 7:52:45pm
Author:  Aayesha Atif

  ==============================================================================
*/

//---------------------------this whole file is written by me

#pragma once
#include <JuceHeader.h>
#include <juce_dsp/juce_dsp.h>

//==============================================================================

//class responsible for applying a reverb effect to audio
class ReverbEffect {
public:
    ReverbEffect();
    ~ReverbEffect();
    
    //prepares the reverb effect for processing
    void prepare(juce::dsp::ProcessSpec& spec);
    void prepareToPlay(double sampleRate, int samplesPerBlockExpected);
    void process(juce::AudioBuffer<float>& buffer);
    //setting the reverb amount
    void setReverbAmount(float amount);
    void setReverbLevel(float level);
    
private:
    juce::dsp::Reverb reverb;
    juce::dsp::Reverb::Parameters reverbParams; // storing reverb parameterz
};



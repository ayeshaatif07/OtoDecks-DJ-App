/*
  ==============================================================================

TrebleEffect.h
Created: 4 Mar 2025 11:52:40pm
Author:  Aayesha Atif

  ==============================================================================
*/

//----------------------this whole file is written by me

#pragma once
#include <JuceHeader.h>

//==============================================================================

class TrebleEffect {
public:
    TrebleEffect();
    ~TrebleEffect();

    //prepares the filter for playback
    void prepareToPlay(double sampleRate, int samplesPerBlock);

    //processes the audio block and applies treble filtering
    void process(juce::AudioBuffer<float>& buffer);

    //setingg the treble level
    void setTrebleGain(float newGain);

private:
    juce::dsp::IIR::Filter<float> trebleFilter;  //declare the filter
    juce::dsp::ProcessSpec spec;  //declare the ProcessSpec for DSP setup
    float trebleGain;

    void updateFilter();  //declare function to update filter coefficients
};

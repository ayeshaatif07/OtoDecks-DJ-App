/*
  ==============================================================================

ReverbEffect.cpp
Created: 22 Feb 2025 7:52:45pm
Author:  Aayesha Atif

  ==============================================================================
*/

//----------------------------this whole file is written by me

#include "ReverbEffect.h"

//==============================================================================

ReverbEffect::ReverbEffect() {
    reverbParams.roomSize = 0.0f; //controls the simulated rooms size
    reverbParams.wetLevel = 0.0f; //adjusts the amount of reverb applied
    reverbParams.dryLevel = 1.0f; //keeps the original signal level
    reverbParams.damping = 0.5f;  //cnntrols highhfrequency damping
    reverbParams.width = 1.0f;    //adjusts stereo width of the reverb effect
    reverbParams.freezeMode = 0.0f; //controls how much the reverb effect is "frozen"
    reverb.setParameters(reverbParams);
}

ReverbEffect::~ReverbEffect() {}

//prepares the reverb effect for playbackk
void ReverbEffect::prepare(juce::dsp::ProcessSpec& spec) {
    reverb.prepare(spec);
}

//called before playback starts and  initializes processing parameters
void ReverbEffect::prepareToPlay(double sampleRate, int samplesPerBlockExpected) {
    juce::dsp::ProcessSpec spec { sampleRate, static_cast<juce::uint32>(samplesPerBlockExpected), 2 };
    reverb.prepare(spec);
}

//processes incoming audio and applies the reverb effectt
void ReverbEffect::process(juce::AudioBuffer<float>& buffer) {
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    reverb.process(context);
}

//adjusts the amount of reverb applied to the signal
void ReverbEffect::setReverbAmount(float amount) {
    amount = juce::jlimit(0.0f, 1.0f, amount);//Ensure the value is within thee range
    reverbParams.roomSize = amount;
    reverbParams.wetLevel = amount;
    reverb.setParameters(reverbParams);
}

//adjusts the overall reverb level separately from the amount
void ReverbEffect::setReverbLevel(float level) {
    level = juce::jlimit(0.0f, 1.0f, level); //ensure thee valid range
    reverbParams.wetLevel = level;
    reverb.setParameters(reverbParams);
}




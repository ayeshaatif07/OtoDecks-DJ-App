/*
  ==============================================================================

TrebleEffect.cpp
Created: 4 Mar 2025 11:52:40pm
Author:  Aayesha Atif

  ==============================================================================
*/

//--------------------------this whole file is written by me

#include "TrebleEffect.h"

//==============================================================================

TrebleEffect::TrebleEffect() : trebleGain(0.0f) {}

TrebleEffect::~TrebleEffect() {}

void TrebleEffect::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 1;  // ensureing mono processing

    trebleFilter.prepare(spec);
    updateFilter();
}

void TrebleEffect::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);

    //process each chanel separately
    for (size_t ch = 0; ch < buffer.getNumChannels(); ++ch)
    {
        auto channelBlock = block.getSingleChannelBlock(ch);
        juce::dsp::ProcessContextReplacing<float> context(channelBlock);
        trebleFilter.process(context);
    }
}

void TrebleEffect::setTrebleGain(float newGain)
{
    trebleGain = juce::jlimit(-10.0f, 30.0f, newGain); //keep gain within range
    updateFilter();
}

void TrebleEffect::updateFilter() {
    float frequency = 4000.0f; //adjusting the frequencies above 4kHz
    float Q = 0.7f; //quality factor
    auto shelfCoefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(
        spec.sampleRate, frequency, Q, juce::Decibels::decibelsToGain(trebleGain)
    );
    *trebleFilter.coefficients = *shelfCoefficients;
}

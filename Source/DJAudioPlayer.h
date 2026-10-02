/*
  ==============================================================================

DJAudioPlayer.h
Created: 22 Feb 2025 7:52:45pm
Author:  Aayesha Atif

  ==============================================================================
*/


#pragma once
#include <JuceHeader.h>
#include "ReverbEffect.h"
#include "TrebleEffect.h"

using namespace juce;

//==============================================================================

class DJAudioPlayer : public juce::AudioSource {
public:
    DJAudioPlayer(juce::AudioFormatManager& _formatManager);
    ~DJAudioPlayer();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void loadURL(juce::URL audioURL);
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSecs);
    void setPositionRelative(double pos);

    void start();
    void stop();

    double getPositionRelative();

    //----------my own code start
    
    //set reverb and treble effect dynamically
    void setReverbAmount(float amount);
    void setReverbLevel(float level);
    void setTreble(float level);
    
    //----------my own code end
    
private:
    AudioFormatManager& formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    ResamplingAudioSource resampleSource{&transportSource, false, 2};
    
    
    //-------my own code start
    
    ReverbEffect reverbEffect;
    TrebleEffect trebleEffect;
    
    //-------my own code end
    
};


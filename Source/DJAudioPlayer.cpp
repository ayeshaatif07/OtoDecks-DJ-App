/*
==============================================================================

DJAudioPlayer.cpp
Created: 22 Feb 2025 7:52:45pm
Author:  Aayesha Atif

==============================================================================
*/

#include "DJAudioPlayer.h"

//==============================================================================

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager)
: formatManager(_formatManager)
{}

DJAudioPlayer::~DJAudioPlayer()
{}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    //-------------my own code start
    
    //added prepare to play for the rverb and treble efect
    reverbEffect.prepareToPlay(sampleRate, samplesPerBlockExpected);
    trebleEffect.prepareToPlay(sampleRate, samplesPerBlockExpected);
    
    //-------------my own code end
}

void DJAudioPlayer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    if (readerSource.get() == nullptr) {
            bufferToFill.clearActiveBufferRegion();
            return;
        }
        resampleSource.getNextAudioBlock(bufferToFill);
    
    //-------------my own code start
    
        //apply treble and reverb processing to the audio buffer
        trebleEffect.process(*bufferToFill.buffer);
        reverbEffect.process(*bufferToFill.buffer);
    
    //-------------my own code end
}

void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

void DJAudioPlayer::loadURL(URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr)
    {
        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource (reader, true));
        transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset (newSource.release());
    }
}

void DJAudioPlayer::setGain(double gain)
{
    if (gain < 0 || gain > 1.0)
    {
        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1" << std::endl;
    }
    else {
        transportSource.setGain(gain);
    }
}

void DJAudioPlayer::setSpeed(double ratio)
{
    if (ratio < 0 || ratio > 100.0)
    {
        std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 100" << std::endl;
    }
    else {
        resampleSource.setResamplingRatio(ratio);
    }
}

void DJAudioPlayer::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double pos)
{
    if (pos < 0 || pos > 1.0)
    {
        std::cout << "DJAudioPlayer::setPositionRelative pos should be between 0 and 1" << std::endl;
    }
    else {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}

void DJAudioPlayer::start()
{
    transportSource.start();
}

void DJAudioPlayer::stop()
{
    transportSource.stop();
}

double DJAudioPlayer::getPositionRelative()
{
    if (transportSource.getLengthInSeconds() > 0)
        return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
    else
        return 0.0;
}

//-------------my own code start

//set the reverb amount applied to the audio
void DJAudioPlayer::setReverbAmount(float amount)
{
    reverbEffect.setReverbAmount(amount);
}

//adjusting the overall reverb levell
void DJAudioPlayer::setReverbLevel(float level)
{
    reverbEffect.setReverbLevel(level);
}

//set the treble gain for high-frequency enhancement
void DJAudioPlayer::setTreble(float trebleGain)
{
    trebleEffect.setTrebleGain(trebleGain);
}

//-------------my own code end


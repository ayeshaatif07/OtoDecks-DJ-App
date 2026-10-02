/*
  ==============================================================================

DeckGUI.h
Created: 22 Feb 2025 7:52:45pm
Author:  Aayesha Atif

  ==============================================================================
*/

//some additions have been made in this file by me

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "ReverbEffect.h"
#include "TrebleEffect.h"

using namespace juce;

//==============================================================================

//----------------my own code start

//class of look and feel for the button and the slider
class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel();
    ~CustomLookAndFeel() override;

    void drawButtonBackground(juce::Graphics& g, juce::Button& button,
                              const juce::Colour& backgroundColour,
                              bool isMouseOverButton, bool isButtonDown) override;
    
    void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPos, float minSliderPos, float maxSliderPos,
                          const juce::Slider::SliderStyle style, juce::Slider& slider) override;
};

//-----------------my own code end

class DeckGUI    :public Component,
                  public Button::Listener,
                  public Slider::Listener,
                  public FileDragAndDropTarget,
                  public Timer
{
public:
   DeckGUI(DJAudioPlayer* player,
          AudioFormatManager &  formatManagerToUse,
          AudioThumbnailCache &  cacheToUse );
   ~DeckGUI();

   void paint (Graphics&) override;
   void resized() override;

    /** implement Button::Listener */
   void buttonClicked (Button *) override;

   /** implement Slider::Listener */
   void sliderValueChanged (Slider *slider) override;

   bool isInterestedInFileDrag (const StringArray &files) override;
   void filesDropped (const StringArray &files, int x, int y) override;

   void timerCallback() override;

private:
   juce::FileChooser fChooser{"Select a file..."};
    
    CustomLookAndFeel customLookAndFeel;

    TextButton playButton{"PLAY"};
    TextButton stopButton{"PAUSE"};
    TextButton loadButton{"LOAD"};

    //------------------my code start
    
    //initialisation of sliders and labels
    Slider volSlider;
    Slider speedSlider;
    Slider posSlider;
    Slider reverbSlider;
    Slider trebleSlider;
    
    Label volLabel, speedLabel, posLabel, reverbLabel, trebleLabel;

    WaveformDisplay waveformDisplay;

    DJAudioPlayer* player;
    ReverbEffect reverbEffect;
    TrebleEffect trebleEffect;
    
    //-------------------my code end
    
   JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};





/*
  ==============================================================================

DeckGUI.cpp
Created: 22 Feb 2025 7:52:45pm
Author:  Aayesha Atif

  ==============================================================================
*/

//updated GUI for the ottodecks app
//changed background, added gradient effect
//changed button style, sliders style , colour of waveform, added labels

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"

//==============================================================================

DeckGUI::DeckGUI(DJAudioPlayer* _player,
               AudioFormatManager & formatManagerToUse,
               AudioThumbnailCache & cacheToUse) : player(_player),
              waveformDisplay(formatManagerToUse, cacheToUse)
{
    
    
    setLookAndFeel(&customLookAndFeel);
    
    //adding buttons in the GUI
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    
    //adding sliders in the GUI
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(reverbSlider);
    addAndMakeVisible(trebleSlider);
    
    //adding waveform in the GUI
    addAndMakeVisible(waveformDisplay);
    
    //adding Labels for Sliders myself
    addAndMakeVisible(volLabel);
    addAndMakeVisible(speedLabel);
    addAndMakeVisible(posLabel);
    addAndMakeVisible(reverbLabel);
    addAndMakeVisible(trebleLabel);
    
    //event listeners for the buttons
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    
    //event listeners for the sliders
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);
    reverbSlider.addListener(this);
    trebleSlider.addListener(this);
    
    //setting the range
    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.1, 1.0, 0.01);
    posSlider.setRange(0.0, 1.0);
    reverbSlider.setRange(0.0, 1.0, 0.0);
    trebleSlider.setRange(0.0, 10.0);
    
    
    //-----------------------------START OF MY PART OF THE CODE THAT I HAVE WRITTENN(1)
    
    
    //setting thee Label Text
    volLabel.setText("Volume", juce::dontSendNotification);
    speedLabel.setText("Speed", juce::dontSendNotification);
    posLabel.setText("Music Track", juce::dontSendNotification);
    reverbLabel.setText("Reverb", juce::dontSendNotification);
    trebleLabel.setText("Treble", juce::dontSendNotification);
    
    //styling the Labels
    volLabel.setJustificationType(Justification::centred);
    speedLabel.setJustificationType(Justification::centred);
    posLabel.setJustificationType(Justification::centred);
    reverbLabel.setJustificationType(Justification::centred);
    trebleLabel.setJustificationType(Justification::centred);
    
    //ensure slider text boxes only display values and do not take inputT
    volSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    reverbSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    trebleSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    
    //changing the style of the slider VERTICAL AND ROTARY
    volSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    speedSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    posSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    reverbSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    trebleSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    
    startTimer(500);

}

//look and feel classes have been implemented

CustomLookAndFeel::CustomLookAndFeel()
{
    setColour(juce::Slider::thumbColourId, juce::Colours::lightgrey);   //colour ofd the cirsles of reverb and treble sliders
    setColour(juce::Slider::trackColourId, juce::Colours::lightcoral);   //colou r of the sliders body
    setColour(juce::TextButton::buttonColourId, juce::Colours::grey);   //play,stop, load colours
}

CustomLookAndFeel::~CustomLookAndFeel() {}

void CustomLookAndFeel::drawButtonBackground(juce::Graphics& g, juce::Button& button,
                                             const juce::Colour& backgroundColour,
                                             bool isMouseOverButton, bool isButtonDown)
{
    
    auto bounds = button.getLocalBounds().toFloat();
    auto baseColour = backgroundColour;
    if (isMouseOverButton) baseColour = baseColour.brighter();
    if (isButtonDown) baseColour = baseColour.darker();

    //change the buttons to circular buttons
    float diameter = juce::jmin(bounds.getWidth(), bounds.getHeight()) - 5.0f;
    juce::Rectangle<float> circleBounds((bounds.getCentreX() - (diameter / 2 + 5)),
                                        bounds.getCentreY() - diameter / 2, diameter + 15, diameter - 5);

    g.setColour(baseColour);
    g.fillEllipse(circleBounds);

    //add 2 button borders to black and grey colour
    g.setColour(juce::Colours::black.withAlpha(0.8f));
    g.drawEllipse(circleBounds, 5.0f);
    
    g.setColour(juce::Colours::grey);
    g.drawEllipse(circleBounds, 1.0f);

}


void CustomLookAndFeel::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
                                         float sliderPos, float minSliderPos, float maxSliderPos,
                                         const juce::Slider::SliderStyle style, juce::Slider& slider)
{
    if (slider.getSliderStyle() == juce::Slider::LinearVertical)
    {
        // the body(stick) of the slider
        g.setColour(slider.findColour(juce::Slider::trackColourId));
        g.fillRect(juce::Rectangle<float>(static_cast<float>(x + width / 2 - 2), static_cast<float>(y),
                                          4.0f, static_cast<float>(height)));
        
        //the square on the sliders
        g.setColour(slider.findColour(juce::Slider::thumbColourId));
        g.fillRect(juce::Rectangle<float>(static_cast<float>(x + width / 2 - 5), static_cast<float>(sliderPos - 5),
                                          11.0f, 11.0f));
    
    }

    else if(slider.getSliderStyle() == juce::Slider::LinearHorizontal)
        {
        // position slider bar and ellipse
        g.setColour(slider.findColour(juce::Slider::trackColourId));
        g.fillRect(juce::Rectangle<float>(static_cast<float>(x), static_cast<float>(y + height / 2 - 2),
                                          static_cast<float>(width), 4.0f));

        //position slider bar and ellipse
        g.setColour(slider.findColour(juce::Slider::trackColourId));
        g.setColour(slider.findColour(juce::Slider::thumbColourId));
        g.fillEllipse(juce::Rectangle<float>(static_cast<float>(sliderPos) - 5.0f, static_cast<float>(y + height / 2 - 5),
                                            10.0f, 10.0f));
        }

        //apply the horizontal stick with the square of the vol and speed slider that would slide up and down
        if (slider.getSliderStyle() == juce::Slider::LinearVertical)
        {
            g.setColour(juce::Colours::lightgrey);
            g.fillRect(juce::Rectangle<float>(static_cast<float>(x) + 10, static_cast<float>(sliderPos - 2),
                                              static_cast<float>(width - 20), 4.0f));
        }
}

DeckGUI::~DeckGUI()
{
   setLookAndFeel(nullptr);
   stopTimer();
}

void DeckGUI::paint (Graphics& g)
{
    g.setColour (Colours::darkred);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    juce::ColourGradient backgroundGradient(juce::Colours::darkred, 0, 0,
                                                juce::Colours::black, getWidth(), getHeight(), false);
    g.setGradientFill(backgroundGradient);
    g.fillAll();
}

void DeckGUI::resized()
{
   double rowH = getHeight() / 8;
    
    //setting locations of the sliders and buttons
    playButton.setBounds(0, 0, getWidth() / 2, rowH);
    stopButton.setBounds(getWidth() / 2, 0, getWidth() / 2, rowH);
    loadButton.setBounds(0, (getHeight() / 8) , getWidth() , getHeight() / 8);
    
    posSlider.setBounds(0, rowH * 2, getWidth(), rowH);

    waveformDisplay.setBounds(0, rowH * 3, getWidth(), rowH * 2);
    
    volSlider.setBounds(30, (getHeight() * 3) / 4, 40, getHeight() / 5);
    speedSlider.setBounds(getWidth() - 80, (getHeight() * 3) / 4, 40, getHeight() / 5);
    reverbSlider.setBounds(0, (getHeight() / 8) * 7, getWidth(), getHeight() / 8);
    trebleSlider.setBounds(0, (getHeight() / 8) * 5.5, getWidth() , getHeight() / 8);
    
    // Setting Labels Position
    volLabel.setBounds(20, (getHeight() * 3) / 4 - 20, 50, 20);
    speedLabel.setBounds(getWidth() - 80, (getHeight() * 3) / 4 - 20, 40, 20);
    posLabel.setBounds((getWidth() / 2) - 40, (getHeight() / 8) * 2.6, 80, 20);
    reverbLabel.setBounds(getWidth() / 2 - 40, (getHeight() / 8) * 7 - 20, 80, 20);
    trebleLabel.setBounds((getWidth() / 2) - 40, (getHeight() / 8) * 5.2, 80, 20);
    
   //-------------------------------ENDD OF MY PART OF THE CODE THAT I HAVE WRITTENN(1)
    
}

void DeckGUI::buttonClicked(Button* button)
{
   if (button == &playButton)
   {
       std::cout << "Play button was clicked " << std::endl;
       player->start();
   }
    if (button == &stopButton)
   {
       std::cout << "Stop button was clicked " << std::endl;
       player->stop();

   }
   if (button == &loadButton)
   {
      auto fileChooserFlags =
       FileBrowserComponent::canSelectFiles;
       fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
       {
           File chosenFile = chooser.getResult();
           if (chosenFile.exists()){
               player->loadURL(URL{chooser.getResult()});
               waveformDisplay.loadURL(URL{chooser.getResult()});
           }
       });
   }
}

void DeckGUI::sliderValueChanged (Slider *slider)
{
   if (slider == &volSlider)
   {
       player->setGain(slider->getValue());
   }

   if (slider == &speedSlider)
   {
       player->setSpeed(slider->getValue());
   }

   if (slider == &posSlider)
   {
       player->setPositionRelative(slider->getValue());
   }

    //---------------------------------------START OF THE CODE THAT I HAVE WRITTEN(2)
    if (slider == &reverbSlider)
    {
        float reverbAmount = reverbSlider.getValue();
        player->setReverbAmount(reverbAmount);
    }
    if (slider == &trebleSlider)
    {
        player->setTreble(trebleSlider.getValue());
    }
    
    //---------------------------------------END OF THE CODE THAT I HAVEE WRITTTEN(2)
}

bool DeckGUI::isInterestedInFileDrag (const StringArray &files)
{
    std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
    return true;
}

void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
    std::cout << "DeckGUI::filesDropped" << std::endl;
    if (files.size() > 0)
    {
    player->loadURL(URL{File{files[0]}});
    }
}

void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}






















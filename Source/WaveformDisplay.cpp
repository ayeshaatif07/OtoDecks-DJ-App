/*
  ==============================================================================

WaveformDisplay.cpp
Created: 22 Feb 2025 7:52:45pm
Author:  Aayesha Atif

  ==============================================================================
*/

//#include "../JuceLibraryCode/JuceHeader.h"
#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================

WaveformDisplay::WaveformDisplay(AudioFormatManager & 	formatManagerToUse,
                                 AudioThumbnailCache & 	cacheToUse) :
                                 audioThumb(1000, formatManagerToUse, cacheToUse), 
                                 fileLoaded(false), 
                                 position(0)
                          
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

  audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (Graphics& g)
{
// i only changed thw colour of the waveform to black and outer line to marroon and red 
    g.fillAll(juce::Colours::darkred.darker(1.2f)); //change to darker red
    g.setColour (juce::Colours::red);
    g.drawRect (getLocalBounds(), 1);   //draw outline around the component

    g.setColour (Colours::darkred.darker(1.2f));
    g.drawRect (getLocalBounds(), 1);   //draw an outline around the component

    g.setColour (Colours::black);
    if(fileLoaded)
    {
      audioThumb.drawChannel(g, 
        getLocalBounds(), 
        0, 
        audioThumb.getTotalLength(), 
        0, 
        1.0f
      );
    g.setColour(Colours::maroon);
    g.drawRect(position * getWidth(), 0, getWidth() / 30, getHeight());
        
    }
    
    else
    {
    g.setColour(Colours::white);
    g.setFont (20.0f);
    g.drawText ("File not loaded...", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
    }
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void WaveformDisplay::loadURL(URL audioURL)
{
  audioThumb.clear();
  fileLoaded  = audioThumb.setSource(new URLInputSource(audioURL));
  if (fileLoaded)
  {
    std::cout << "wfd: loaded! " << std::endl;
    repaint();
  }
  else {
    std::cout << "wfd: not loaded! " << std::endl;
  }

}

void WaveformDisplay::changeListenerCallback (ChangeBroadcaster *source)
{
    std::cout << "wfd: change received! " << std::endl;

    repaint();
}

void WaveformDisplay::setPositionRelative(double pos)
{
  if (pos != position)
  {
    position = pos;
    repaint();
  }
  
}





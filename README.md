# OtoDecks DJ App

A two-deck DJ application written in C++ with the [JUCE](https://juce.com/) framework. Load two tracks, play them at the same time, and shape the sound of each deck with volume, speed, reverb and treble controls while watching the waveform of each track.

## Features

- **Two independent decks**, mixed together into one output.
- **Load tracks** with the LOAD button, or drag and drop an audio file onto a deck.
- **Transport controls:** play and pause for each deck.
- **Volume slider** and **speed slider** (0.1x to 1.0x) for each deck.
- **Track position slider** to jump to any point in the track.
- **Waveform display** that shows the loaded track and the current playback position.
- **Reverb knob** that adds room reverb to the deck.
- **Treble knob** that boosts the high frequencies with a high-shelf filter.
- **Custom look and feel** for the buttons and sliders.

## Object-Oriented Design

| Class | Responsibility |
|-------|----------------|
| `OtoDecksApplication` (`Main.cpp`) | Application entry point and main window |
| `MainComponent` | Owns the two players and two deck GUIs, and mixes them with a `MixerAudioSource` |
| `DJAudioPlayer` | Audio source for one deck: loading, play/stop, gain, speed, position and the effects |
| `DeckGUI` | The user interface for one deck: buttons, sliders, drag and drop |
| `CustomLookAndFeel` | Custom drawing for buttons and linear sliders |
| `WaveformDisplay` | Draws the track waveform and the playhead |
| `ReverbEffect` | Reverb processing with `juce::dsp::Reverb` |
| `TrebleEffect` | Treble boost with a `juce::dsp::IIR` high-shelf filter |

## Project Structure

| File / folder | Purpose |
|---------------|---------|
| `NewProject.jucer` | The Projucer project file |
| `Source/Main.cpp` | Application and window |
| `Source/MainComponent.*` | The main component with both decks |
| `Source/DJAudioPlayer.*` | Per-deck audio player |
| `Source/DeckGUI.*` | Per-deck user interface and custom look and feel |
| `Source/WaveformDisplay.*` | Waveform display |
| `Source/ReverbEffect.*`, `Source/TrebleEffect.*` | Audio effects |

## Build and Run

You need [JUCE](https://juce.com/get-juce/) and a C++ compiler or IDE supported by it, such as Xcode on macOS or Visual Studio on Windows.

```bash
git clone https://github.com/ayeshaatif07/OtoDecks-DJ-App.git
```

Then:

1. Open `NewProject.jucer` in the Projucer.
2. In the Projucer, set the path to your JUCE `modules` folder (the project file expects it at `../../JUCE/modules`).
3. Click **Save Project and Open in IDE**.
4. Build and run the app from your IDE.

Once the app opens, press LOAD on a deck (or drag in an audio file), then press PLAY.

## Author and Credits

- **Author:** Ayesha Atif
- **Coursework:** Object Oriented Programming (OOP) – Semester 3 Final
- Built with the [JUCE](https://juce.com/) framework.

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
#ifndef THISPLUGIN_EDITOR_STOFF
#define THISPLUGIN_EDITOR_STOFF
#include "juce_core/system/juce_StandardHeader.h"
#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SALookAndFeel.h"
#include "../JuceLibraryCode/BinaryData.h"

//==============================================================================
/**
*/
class DystortionAudioProcessorEditor  : public juce::AudioProcessorEditor,  public juce::Button::Listener//, private juce::Slider::Listener
{
public:
    DystortionAudioProcessorEditor (DystortionAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~DystortionAudioProcessorEditor() override;
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void buttonClicked (juce::Button* button)override;
    

private:
    juce::AudioProcessorValueTreeState& valueTreeState;
    //void sliderValueChanged (juce::Slider* slider) override;
    juce::SALookAndFeel SALookAndFeel;
    DystortionAudioProcessor& audioProcessor;
    //float gain = audioProcessor.gain;
    juce::Slider gainslider1;
    juce::ImageButton donatebb;
    Image donatebutover = ImageCache::getFromMemory (BinaryData::donatebuthover_png, BinaryData::donatebuthover_pngSize);
    Image donatebut = ImageCache::getFromMemory (BinaryData::donatebut_png, BinaryData::donatebut_pngSize);
    Image knobNormal;
    int rx;
    int ry;
    juce::Colour sea1;
    juce::Colour sand1;
    Image background1;
  public:
    std::unique_ptr<SliderAttachment> gainSliderState1;
};
#endif

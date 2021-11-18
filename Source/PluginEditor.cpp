/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
DystortionAudioProcessorEditor::DystortionAudioProcessorEditor (DystortionAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), valueTreeState (vts)
{
    setSize (400, 600);
    donatebut = donatebut.rescaled(125, 45);
    donatebutover = donatebutover.rescaled(125, 45);
    rx = 400;
    ry = 600;
    addAndMakeVisible (gainslider1);
    gainSliderState1.reset (new SliderAttachment (valueTreeState, GAIN_ID, gainslider1));
    addAndMakeVisible (donatebb);
    //donatebb.setLookAndFeel(&SALookAndFeel);
    donatebb.addListener (this);
    donatebb.setBounds (137, (getHeight()-getHeight()/10), 125, 45);
    donatebb.setImages (false, false, true, donatebut, 1.0f, {}, donatebutover, 1.0f, {}, donatebut, 0.8f, {});
    gainslider1.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    gainslider1.setRange (1.0, 10.0, 0.001);
    gainslider1.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    gainslider1.setPopupDisplayEnabled (false, false, this);
    gainslider1.setTextValueSuffix ("");
    //gainslider1.addListener (this);
    gainslider1.setBounds (100, 120, 200, 200);
    gainslider1.setValue(audioProcessor.gainatom);
    gainslider1.setLookAndFeel(&SALookAndFeel);
    background1 = ImageCache::getFromMemory (BinaryData::pedal_back_10_2x100_jpg, BinaryData::pedal_back_10_2x100_jpgSize);
}
void DystortionAudioProcessorEditor::buttonClicked (juce::Button* button)
    {
        if(button == &donatebb){
            URL("https://www.paypal.com/donate?hosted_button_id=9ELH753DDE98Y").launchInDefaultBrowser(); 
        }
    }
/*void DystortionAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    audioProcessor.gain = gainslider1.getValue();


}*/
DystortionAudioProcessorEditor::~DystortionAudioProcessorEditor()
{
    
}

//==============================================================================
void DystortionAudioProcessorEditor::paint (juce::Graphics& g)
{
    
    g.drawImage(background1,	
                0,
                0,
                getWidth(),
                getHeight(),   
                0,
                0,
                background1.getWidth(),
                background1.getHeight());

}
void DystortionAudioProcessorEditor::resized()
{
    donatebut = donatebut.rescaled((getWidth()*0.3125), (getHeight()*0.075));
    donatebutover = donatebutover.rescaled((getWidth()*0.3125), (getHeight()*0.075));
    gainslider1.setBounds ((getWidth() /4), (getHeight()*0.2), getWidth() /2, getWidth() /2);
    donatebb.setBounds ((getWidth()*0.34375), (getHeight()-getHeight()/10), (getWidth()*0.3125), (getHeight()*0.075));
}

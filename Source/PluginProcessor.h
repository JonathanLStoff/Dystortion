/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/
#ifndef THISPLUGIN_PROCESSOR_STOFF
#define THISPLUGIN_PROCESSOR_STOFF
//#define JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
#include "juce_core/system/juce_PlatformDefs.h"
#pragma once
#include <array>
#include <cmath>
#include <JuceHeader.h>
#define GAIN_ID "gain"
#define GAIN_NAME "Gain"

//==============================================================================
/**
*/
class DystortionAudioProcessor : public juce::AudioProcessor
{
public:
    //==============================================================================
    DystortionAudioProcessor();
    ~DystortionAudioProcessor() override;
    //AudioParameterFloat gain;
    float gain;
    std::atomic<float> gainatom;
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    static constexpr auto fftOrder = 10;
    static constexpr auto fftSize  = 1 << fftOrder;
    float fftSizeDiv;
    float abssam;
    int index1;
    float sampleRatesizemax;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill);
    void pushNextSampleIntoFifo (float sample) noexcept;
    //void timerCallback();
    float dblevelmins;
    //void updateFilter();
private:
    
    std::array<float, fftSize> fifo;
    int totalNumInputChannels;
    int totalNumOutputChannels;
    int freqz1;                    
    std::array<float, fftSize * 2> fftData;             
    int fifoIndex = 0;   
    //dsp::ProcessorDuplicator<dsp::IIR::Filter <float>, dsp::IIR::Coefficients<float>> highpassfil;
    //dsp::Gain<float> gaintoadd;
    float input35;
    float input3;
    float input2;
    float input1;
    float input4;
    float inputdu;
    float gain1z;
    float reverbar[101];
    int randar2;
    float reverb3;
    bool bleh;
    dsp::ProcessSpec spec;
    int revint = 0;
    float* reverb2;
    bool loopreverb = false;                  
    int srate1;
    juce::dsp::FFT FFTTEST;
    juce::AudioProcessorValueTreeState parameters;
    std::atomic<float>* gainParameter = nullptr;
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DystortionAudioProcessor)
    
};
#endif

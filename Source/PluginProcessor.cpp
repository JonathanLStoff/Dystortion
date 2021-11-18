/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "JucePluginDefines.h"
#include "PluginEditor.h"
#include <cmath>
#include <complex>
#include <stdlib.h>
#include <iostream>


//==============================================================================
DystortionAudioProcessor::DystortionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
    
, FFTTEST (fftOrder), parameters(*this, nullptr, juce::Identifier("Dystortion"),
    {
        std::make_unique<juce::AudioParameterFloat> (GAIN_ID, GAIN_NAME, 1.0f, 10.0f, 1.0f),
    }) //, highpassfil(dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), 45.f, 0.1f))
{
  gainParameter = parameters.getRawParameterValue (GAIN_ID);
  parameters.state = juce::ValueTree(juce::Identifier("Dystortion"));
    //addParameter(gain = new AudioParameterFloat("gain", "Gain", 0.0f, 1.0f, 0.0f));
}

DystortionAudioProcessor::~DystortionAudioProcessor()
{

}

//==============================================================================
const juce::String DystortionAudioProcessor::getName() const
{
    
    return JucePlugin_Name;
}

bool DystortionAudioProcessor::acceptsMidi() const
{
    
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DystortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DystortionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DystortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DystortionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DystortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DystortionAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DystortionAudioProcessor::getProgramName (int index)
{
    return {};
}

void DystortionAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DystortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    srate1 = sampleRate;
    gain = *gainParameter;
    gainatom = gain;
    //std::cout << gain;
    //spec.sampleRate = sampleRate;
    //spec.maximumBlockSize = samplesPerBlock;
    //spec.numChannels = getTotalNumOutputChannels();
    //highpassfil.reset();
    //highpassfil.prepare(spec);
    //std::cout << sampleRate;
    
}

void DystortionAudioProcessor::releaseResources()
{
    //highpassfil.reset();
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DystortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    #if JucePlugin_IsMidiEffect
        juce::ignoreUnused (layouts);
        return true;
    #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif
    
    return true;
#endif
}

#endif
/*void DystortionAudioProcessor::updateFilter()
{
    *highpassfil.state = *dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), 45.f, 0.1f);
}*/
 
void DystortionAudioProcessor::pushNextSampleIntoFifo (float sample) noexcept
    {
        if (fifoIndex == fftSize)
        {
                std::fill (fftData.begin(), fftData.end(), 0.0f);
                std::copy (fifo.begin(), fifo.end(), fftData.begin());
            fifoIndex = 0;
        }
        fifo[(size_t) fifoIndex++] = sample;
    }
void DystortionAudioProcessor::processBlock (juce::AudioBuffer<float>&  buffer, juce::MidiBuffer& midiMessages)
{
    gain = *gainParameter;
    gainatom = gain;
    juce::ScopedNoDenormals noDenormals;
    totalNumInputChannels  = getTotalNumInputChannels();
    totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    dsp::AudioBlock<float> block1(buffer);
    auto* channelDataL = buffer.getWritePointer (0);
    //fftSizeDiv  = (1.f/float(fftSize - 1));
    for (auto i = 0; i < buffer.getNumSamples(); ++i) pushNextSampleIntoFifo (channelDataL[i]);
    FFTTEST.performFrequencyOnlyForwardTransform(fftData.data());
    float maxy = 0.f;
    for (auto i = 0; i < (fftSize/2); i++){
        abssam = std::abs(fftData[i]);
        if (abssam > maxy){
            maxy = abssam;
            index1 = i;
        }   
    }
    freqz1 = (srate1 * (1.f/float(fftSize - 1))) * index1;
    //freqz1 = sampleRatesizemax * index1;
    //highpassfil.process(dsp::ProcessContextReplacing<float> (block1));
    if(freqz1 > 400){
        dblevelmins = -(107.f* pow(freqz1, 2))/42034669600.f - (10175117.f*freqz1)/10508667400.f;
    }
    else {
        dblevelmins = 0.f;
    }
    if(loopreverb == true){
        reverb3 = reverbar[revint];
    }
    else {
        reverb3 = 0.f;
    }
    //dblevelmins = dblevelmins + reverb3;
    //gaintoadd.setGainDecibels(dblevelmins);
    //dblevelmins = pow(10, (dblevelmins + reverb3)*0.05f);
    randar2 = rand() % 511;
    if (gain > 1.0f){
        buffer.applyGain(pow(10, (dblevelmins)*0.05f));
        gain1z = gain*gain;
        //std::cout << gain1z;
        //std::cout << " ";
    }
    for (int i = 0; i < buffer.getNumSamples(); i++) 
       {    //output smaller than input issue, background needs to be opimized
       
            auto input = channelDataL[i];
            if (input != 0.0f){
            auto output = input;
            //if (gain > 1){
                input1 = input * gain1z; //Opamp
                input2 = std::copysign(abs(input1)/(1+abs(input1)),input1);
                input3 = input1 * (300/(300-((gain1z)*2.5))); //transistor
                //input3 = input1 * (300/(300-((gain1z)*2.5))); //transistor
                input35 = (input2 + input3)/2;
                input4 =  std::copysign(abs(input35)/(1+abs(input35)),input35); 
                inputdu = abs(input)*2;
                input4 = inputdu+(input4 - inputdu)/3.5;
                output = tanh(input4);
                if(i==randar2){
                    reverbar[revint] = output;
                }
            //}
            channelDataL[i] = output;
            if(getTotalNumInputChannels() > 2){
                auto* channelDataR = buffer.getWritePointer (1);
                channelDataR[i] = output;
             }
        
       }
       
       revint++;
       if (revint >= 101 ){
        revint = 1;
        if(loopreverb == false){
            loopreverb = true;
        }
       }
       //block1.clear();
}
}

/*void DystortionAudioProcessor::timerCallback()
    {
        if (nextFFTBlockReady)
        {
            nextFFTBlockReady = false;
        }
    }*/
//==============================================================================
bool DystortionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DystortionAudioProcessor::createEditor()
{
    return new DystortionAudioProcessorEditor (*this, parameters);
    //return new DystortionAudioProcessorEditor (this);
}

//==============================================================================
void DystortionAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void DystortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if(xmlState.get() != nullptr)
    {
        if(xmlState->hasTagName(parameters.state.getType())){
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
            gainParameter = parameters.getRawParameterValue (GAIN_ID);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DystortionAudioProcessor();
}

#include "PluginProcessor.h"
#include "PluginEditor.h"

PhaseSpaceProcessor::PhaseSpaceProcessor()
     : AudioProcessor (BusesProperties()
                     .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                     .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{
    phasePoints.reserve(maxPoints);
}

PhaseSpaceProcessor::~PhaseSpaceProcessor()
{
}

void PhaseSpaceProcessor::prepareToPlay (double, int)
{
}

void PhaseSpaceProcessor::releaseResources()
{
}

void PhaseSpaceProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Clear any output channels that don't have input
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Create phase space points from audio
    const auto* inputData = buffer.getReadPointer(0);
    auto numSamples = buffer.getNumSamples();

    // Take samples in pairs for x,y coordinates
    for (int i = 0; i < numSamples - 1; i += 2)
    {
        juce::Point<float> point(inputData[i], inputData[i + 1]);
        phasePoints.push_back(point);
        
        if (phasePoints.size() > maxPoints)
            phasePoints.erase(phasePoints.begin());
    }

    // Pass audio through unchanged
    for (int channel = 0; channel < totalNumOutputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        memcpy(channelData, buffer.getReadPointer(channel), sizeof(float) * buffer.getNumSamples());
    }
}

juce::AudioProcessorEditor* PhaseSpaceProcessor::createEditor()
{
    return new PhaseSpaceEditor (*this);
}

void PhaseSpaceProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::ValueTree state("PhaseSpaceState");
    state.setProperty("rotation", rotationEnabled, nullptr);
    state.setProperty("zoom", zoom, nullptr);

    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void PhaseSpaceProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml.get() != nullptr)
    {
        juce::ValueTree state = juce::ValueTree::fromXml(*xml);
        rotationEnabled = state.getProperty("rotation", rotationEnabled);
        zoom = state.getProperty("zoom", zoom);
    }
}

// This creates the plugin instance
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PhaseSpaceProcessor();
}
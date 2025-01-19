#pragma once
#include <juce_audio_processors/juce_audio_processors.h>

class PhaseSpaceProcessor : public juce::AudioProcessor
{
public:
    PhaseSpaceProcessor();
    ~PhaseSpaceProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return JucePlugin_Name; }

    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // Phase space data
    std::vector<juce::Point<float>> getPhasePoints() const { return phasePoints; }
    void clearPhasePoints() { phasePoints.clear(); }
    
    bool isRotationEnabled() const { return rotationEnabled; }
    void setRotationEnabled(bool enabled) { rotationEnabled = enabled; }
    
    float getZoom() const { return zoom; }
    void setZoom(float newZoom) { zoom = newZoom; }

private:
    std::vector<juce::Point<float>> phasePoints;
    static constexpr size_t maxPoints = 1000;
    bool rotationEnabled = false;
    float zoom = 1.0f;
    float rotation = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhaseSpaceProcessor)
};
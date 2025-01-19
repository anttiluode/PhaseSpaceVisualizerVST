#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <juce_gui_extra/juce_gui_extra.h>

class PhaseSpaceEditor : public juce::AudioProcessorEditor,
                        public juce::Timer
{
public:
    explicit PhaseSpaceEditor (PhaseSpaceProcessor&);
    ~PhaseSpaceEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    PhaseSpaceProcessor& processorRef;
    float rotation = 0.0f;
    
    juce::TextButton rotateButton { "Rotate" };
    juce::Slider zoomSlider;
    juce::Label zoomLabel { {}, "Zoom:" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhaseSpaceEditor)
};
#include "PluginProcessor.h"
#include "PluginEditor.h"

PhaseSpaceEditor::PhaseSpaceEditor (PhaseSpaceProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    setSize (800, 600);
    startTimerHz(60); // 60fps refresh rate

    // Setup rotation button
    addAndMakeVisible(rotateButton);
    rotateButton.setToggleState(processorRef.isRotationEnabled(), juce::dontSendNotification);
    rotateButton.onClick = [this]()
    {
        processorRef.setRotationEnabled(rotateButton.getToggleState());
    };

    // Setup zoom slider
    addAndMakeVisible(zoomSlider);
    addAndMakeVisible(zoomLabel);
    zoomSlider.setRange(0.1, 5.0, 0.1);
    zoomSlider.setValue(processorRef.getZoom(), juce::dontSendNotification);
    zoomSlider.onValueChange = [this]()
    {
        processorRef.setZoom((float)zoomSlider.getValue());
    };
}

PhaseSpaceEditor::~PhaseSpaceEditor()
{
    stopTimer();
}

void PhaseSpaceEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

    auto bounds = getLocalBounds().reduced(20);
    auto center = bounds.getCentre().toFloat();
    
    // Get phase points from processor
    auto points = processorRef.getPhasePoints();
    if (points.size() > 1)
    {
        // Calculate scale based on zoom
        float scale = juce::jmin(bounds.getWidth(), bounds.getHeight()) * 0.4f * processorRef.getZoom();

        // Update rotation if enabled
        if (processorRef.isRotationEnabled())
            rotation += 0.01f;

        // Draw phase space
        for (size_t i = 0; i < points.size() - 1; ++i)
        {
            auto start = points[i];
            auto end = points[i + 1];

            // Scale points
            start *= scale;
            end *= scale;

            // Apply rotation if enabled
            if (processorRef.isRotationEnabled())
            {
                float cosRot = std::cos(rotation);
                float sinRot = std::sin(rotation);

                auto rotatePoint = [&](juce::Point<float>& p)
                {
                    float x = p.x * cosRot - p.y * sinRot;
                    float y = p.x * sinRot + p.y * cosRot;
                    p.x = x;
                    p.y = y;
                };

                rotatePoint(start);
                rotatePoint(end);
            }

            // Center points
            start += center;
            end += center;

            // Create rainbow color effect
            float hue = (float)i / (float)points.size();
            auto color = juce::Colour::fromHSV(hue, 1.0f, 1.0f, 1.0f);
            g.setColour(color);

            g.drawLine(start.x, start.y, end.x, end.y, 2.0f);
        }
    }
}

void PhaseSpaceEditor::resized()
{
    auto bounds = getLocalBounds();
    auto controlsArea = bounds.removeFromTop(40);
    
    rotateButton.setBounds(controlsArea.removeFromLeft(100).reduced(5));
    
    zoomLabel.setBounds(controlsArea.removeFromLeft(50).reduced(5));
    zoomSlider.setBounds(controlsArea.removeFromLeft(200).reduced(5));
}

void PhaseSpaceEditor::timerCallback()
{
    repaint();
}
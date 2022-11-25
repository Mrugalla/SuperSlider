#pragma once
#include <JuceHeader.h>

struct SuperSlider :
    public juce::Slider
{
    using Slider = juce::Slider;
    using Style = Slider::SliderStyle;
    using BoxPos = Slider::TextEntryBoxPosition;
    using Mouse = juce::MouseEvent;
    using Wheel = juce::MouseWheelDetails;

    static constexpr float NormalWheel = .8f;
    static constexpr float SensitiveWheel = .05f;

	SuperSlider() :
		Slider()
    {
        setSliderStyle(Style::RotaryVerticalDrag);
    }

    void mouseWheelMove(const Mouse& mouse, const Wheel& wheel) override
    {
        auto newWheel = wheel;
        const auto speed = mouse.mods.isCtrlDown() ? SensitiveWheel : NormalWheel;
        newWheel.deltaY *= speed;
		
        Slider::mouseWheelMove(mouse, newWheel);
    }
};

struct MainComponent :
    public juce::Component
{
    MainComponent() :
		gain()
    {
        addAndMakeVisible(gain);

        setSize(300, 200);
    }

    void paint (juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::black);
    }

    void resized() override
    {
        gain.setBounds(getLocalBounds());
        gain.setTextBoxStyle(SuperSlider::BoxPos::TextBoxBelow, false, getWidth(), getHeight() / 10);
    }
	
    SuperSlider gain;
};

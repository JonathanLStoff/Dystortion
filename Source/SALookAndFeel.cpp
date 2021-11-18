/*
  ==============================================================================

    SALookAndFeel.cpp
    Author:  Stoff Audio

  ==============================================================================
*/
#include "SALookAndFeel.h"
#include <iostream>
//==============================================================================
namespace juce
{
SALookAndFeel::SALookAndFeel()
{
    //knobNormal = ImageCache::getFromMemory (BinaryData::Gain_knob_png, BinaryData::Gain_knob_pngSize);
}

SALookAndFeel::~SALookAndFeel()
{
}
void SALookAndFeel::drawRotarySlider (Graphics &g, int x, int y, int width, int height, float sliderPosProportional, const float rotaryStartAngle, const float rotaryEndAngle, Slider &slider)
{
        float sliderspot;
        sliderspot = (sliderPosProportional * MathConstants<float>::twoPi) *.823;
        float widthf = width;
        g.setImageResamplingQuality (Graphics::ResamplingQuality(2));
        rotator = rotator.rotation(sliderspot, (widthf /2), (widthf /2)).translated(0, 0);
        knobrot = knobNormal.rescaled(width, width);
        g.drawImageTransformed(knobrot, rotator);
        g.drawImage(knobshad,  
                0,
                0,
                width,
                height,   
                0,
                0,
                knobshad.getWidth(),
                knobshad.getHeight());
        knoblightrot = knoblight.rescaled(width, width);
        g.drawImageTransformed(knoblightrot, rotator);
        //g.drawImageTransformed (knobNormal, (AffineTransform::rotation(sliderPosProportional*rotaryEndAngle, x, y)), false);
            
}


}

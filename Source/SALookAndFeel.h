/*
  ==============================================================================

    SALookAndFeel.h
    Author:  Stoff Audio

  ==============================================================================
*/

#ifndef SALOOKANDFEEL_H_INCLUDED
#define SALOOKANDFEEL_H_INCLUDED


#include "JuceHeader.h"
#include "../JuceLibraryCode/BinaryData.h"

//==============================================================================
/*
*/
namespace juce {
class SALookAndFeel    : public LookAndFeel_V4
{
public:
    SALookAndFeel();
    virtual ~SALookAndFeel();
    virtual void drawRotarySlider (Graphics &g, int x, int y, int width, int height, float sliderPosProportional, const float rotaryStartAngle, const float rotaryEndAngle, Slider &slider)override;
    //virtual void drawImageButton(Graphics &, Image *, int imageX, int imageY, int imageW, int imageH, const Colour &overlayColour, float imageOpacity, ImageButton &)override;

private:
    //void sliderValueChanged (juce::Slider* slider);
    Image knobNormal = ImageCache::getFromMemory (BinaryData::Gain_knobnoshad01_png, BinaryData::Gain_knobnoshad01_pngSize);
    AffineTransform rotator;
    Image knobrot;
    Image knoblightrot;
    Image knobshad = ImageCache::getFromMemory (BinaryData::Gain_knoblayersshadow2_png, BinaryData::Gain_knoblayersshadow2_pngSize);
    Image knoblight = ImageCache::getFromMemory (BinaryData::Gain_knoblayerslight_png, BinaryData::Gain_knoblayerslight_pngSize);
    
};


#endif  // SALookANDFEEL_H_INCLUDED
}
/*
  ==============================================================================

    MultipurposeButton.cpp
    Created: 1 Jul 2013 11:14:26pm
    Author:  admin

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MultipurposeButton.h"

MultipurposeButton::MultipurposeButton(const String& buttonName, const String& toolTip) : TextButton (buttonName, toolTip)
{
	setButtonStyle(1);
	toggleState = false;
}

void MultipurposeButton::setButtonStyle (int buttonStyleValue) {
	buttonStyle = buttonStyleValue;
}


bool MultipurposeButton::getToggleState()
{
	return toggleState;
}

void MultipurposeButton::mouseUp (const MouseEvent &event) {
	if (event.originalComponent == this) {
		if ((buttonStyle & ButtonStyle::Toggle) != 0)
			toggleState = !toggleState;
	}

	TextButton::mouseUp(event);
}

void MultipurposeButton::paintButton (Graphics& g,
                              bool isMouseOverButton,
                              bool isButtonDown)
{
    LookAndFeel& lf = getLookAndFeel();


//#ifndef __LOOKANDFEELCUSTOM_H_61F5A105__

    lf.drawButtonBackground (g, *this,
                             findColour (getToggleState() ? buttonOnColourId
                                                          : buttonColourId),
                             isMouseOverButton,
                             isButtonDown);

 /*   
#else
	lf.drawMultipurposeButtonBackground (g, *this,
                             findColour (getToggleState() ? buttonOnColourId
                                                          : buttonColourId),
                             isMouseOverButton,
                             isButtonDown);
	
#endif
	if (!_toggleState) */lf.drawButtonText (g, *this,
                       isMouseOverButton,
                       isButtonDown);
}
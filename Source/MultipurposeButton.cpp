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
	buttonIcon = 0;
	iconWidthMultiplier = 1.0f;
	iconTextGapReduction = 7;
	labelGap = 5;

	DBG("INIT MULTIPURPOSE BUTTON ICON");
	//init icon
	iconLabel.setBounds(0, 0, 16, 20);
	iconLabel.setFont(Font("FontAwesome", 12.f, 0));
	defaultIcon = L"";
	iconLabel.setText (defaultIcon, NotificationType::dontSendNotification);
	//iconLabel.setText (L"", NotificationType::dontSendNotification);//L""
	//(juce_wchar) 0x2022
	//iconLabel.setColour(Label::backgroundColourId, Colour::fromString("FFFF0000"));//setOpaque(false);//
	iconLabel.setOpaque(false);
    iconLabel.setColour(Label::textColourId, Colour::fromString("FFFFFFFF"));
    iconLabel.setEditable(false);
    iconLabel.setName("Icon");
	textLabel.setBorderSize(0, 0);
	iconLabel.setJustificationType(Justification(Justification::centred));
    addAndMakeVisible(&iconLabel);
	iconLabel.setInterceptsMouseClicks(false, false);
	iconLabel.setVisible(false);

	//init text
	textLabel.setBounds(0, 0, 16, 16);
	//textLabel.setFont(Font("FontAwesome", 12.f, 0));
	textLabel.setText ("Button text", NotificationType::dontSendNotification);//L""
	//(juce_wchar) 0x2022
	//textLabel.setColour(Label::backgroundColourId, Colour::fromString("FF00FF00"));//setOpaque(false);//
	textLabel.setOpaque(false);
    textLabel.setColour(Label::textColourId, Colour::fromString("FFFFFFFF"));
    textLabel.setEditable(false);
    textLabel.setName("Text");
	textLabel.setBorderSize(0, 0);//textLabel.getVerticalBorderSize());
	textLabel.setJustificationType(Justification(Justification::centredLeft));
    addAndMakeVisible(&textLabel);
	textLabel.setInterceptsMouseClicks(false, false);
	textLabel.setVisible(false);
}

void MultipurposeButton::setButtonStyle (int buttonStyleValue)
{
	DBG("\tMULTIPURPOSE BUTTON setButtonStyle()");
	buttonStyle = buttonStyleValue;

	if ((buttonStyle & ButtonStyle::Icon) != 0) {
		iconLabel.setVisible(true);
	} else {
		iconLabel.setVisible(false);
	}
	if ((buttonStyle & ButtonStyle::Text) != 0) {
		textLabel.setVisible(true);
	} else {
		textLabel.setVisible(false);
	}

	resized();
}

void MultipurposeButton::setButtonIcon (int buttonIconValue)
{
	DBG("setButtonIcon(), buttonIconValue = " + String((int) buttonIconValue));
	buttonIcon = buttonIconValue;
	//String icon = String(CharPointer_UTF8((defaultIcon.toRawUTF8())));
	//
	const char* raw = defaultIcon.toRawUTF8();
	int numBytes = sizeof(raw);//defaultIcon.getNumBytesAsUTF8();
	char *aux = new char[numBytes];
	DBG(String("\tnumBytes = " + String(numBytes)));
	DBG("SIZEOF RAW = " + String(sizeof(raw)));
	for (int i = numBytes - 1; --i >= 0;) {
		DBG(String("\traw[" + String(i) + String("] = ") + String(((juce::uint8) raw[i]))));
		//WIP
		aux[i] = raw[i] + buttonIconValue;
		buttonIconValue = 0;
		DBG(String("\taux[" + String(i) + String("] = ") + String(((juce::uint8) aux[i]))));
	}
	aux[numBytes - 1] = 0;
	DBG("declare string icon");
	String icon = String(CharPointer_UTF8(aux));
	//
	//icon = icon.substring(0, icon.length()-1)+((char)(icon[icon.length()-1]+1));
	DBG("set icon");
	iconLabel.setText (icon, NotificationType::dontSendNotification);
	DBG("delete aux");
	delete aux;
}

void MultipurposeButton::resized()
{
	DBG("\t\tMULTIPURPOSE BUTTON resized()");
	Rectangle<int> r (getLocalBounds());
	if ((buttonStyle & ButtonStyle::Icon) != 0) {
		int iconWidth = (int) (r.getHeight() * iconWidthMultiplier);
		iconLabel.setBounds(0, 0, iconWidth, r.getHeight());
		int textLabelWidth = (r.getWidth() <= iconWidth) ? 1 : r.getWidth() - iconWidth;	//labelGap
		textLabel.setBounds(iconWidth - iconTextGapReduction, 0, textLabelWidth, r.getHeight());
	} else {
		textLabel.setBounds(0, 0, r.getWidth(), r.getHeight());
	}
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
	if (!_toggleState) */
	//OLD BUTTON TEXT DRAWING
	/*lf.drawButtonText (g, *this,
                       isMouseOverButton,
                       isButtonDown);*/
}
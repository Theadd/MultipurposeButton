/*
  ==============================================================================

    MultipurposeButton.h
    Created: 1 Jul 2013 11:14:26pm
    Author:  admin

  ==============================================================================
*/

#ifndef __MULTIPURPOSEBUTTON_H_C1F1AE13__
#define __MULTIPURPOSEBUTTON_H_C1F1AE13__


class MultipurposeButton : public TextButton
{
public:
	int buttonStyle;
	bool toggleState;
	/** The types of button available.

		A combination of these flags are used by setButtonStyle(), only one or none of the last three styles are meant to be set on.

        @see setButtonStyle, setButtonText, setButtonImages
    */
    enum ButtonStyle
    {
		Text = 1,		/**< Text button with a label on it. */
		Image = 2,		/**< Text button with an image on it. */
		Rounded = 4,	/**< A rounded button. */
		Toggle = 8,		/**< A traditional toggle button. */
		Switch = 16,	/**< A two values horizontal switch button. */
		Dropdown = 32	/**< A button which shows a list of multiple values. */
    };
	
	MultipurposeButton(const String& buttonName = String::empty, const String& toolTip = String::empty);

	/** Sets the button style.

        The value passed in is a bitwise combination of any of the values in the
        ButtonStyle enum. Regarding Toggle, Switch and Dropdown, only one or none of them are meant to be set on.
		By setting none of them, it will behave as a normal button.

        E.g. You can create a rounded switch button with images by providing a value of 22 which is 4 + 16 + 2.
		Since the button is set to use images, this should be specified using setButtonImages.
    */
    void setButtonStyle (int buttonStyle);

	bool getToggleState();

	void mouseUp (const MouseEvent &event);
protected:

	void paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown);

private:

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultipurposeButton)
};



#endif  // __MULTIPURPOSEBUTTON_H_C1F1AE13__

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
	Label iconLabel;
	Label textLabel;
	int buttonStyle;
	int buttonIcon;
	bool toggleState;
	float iconWidthMultiplier;
	int iconTextGapReduction;
	int labelGap;
	String defaultIcon;

	/** The types of button available.

		A combination of these flags are used by setButtonStyle(), only one or none of the last three styles are meant to be set on.

        @see setButtonStyle, setButtonText, setButtonImages
    */
    enum ButtonStyle
    {
		Text = 1,		/**< Text button with a label on it. */
		Image = 2,		/**< Text button with an image on it. */
		Icon = 4,
		Rounded = 8,	/**< A rounded button. */
		Toggle = 16,		/**< A traditional toggle button. */
		Switch = 32,	/**< A two values horizontal switch button. */
		Dropdown = 64	/**< A button which shows a list of multiple values. */
    };

	enum ButtonIcon
	{
		icon_glass = 0,
		icon_music = 1,
		icon_search = 2,
		icon_envelope_alt = 3,
		icon_heart = 4,
		icon_star = 5,
		icon_star_empty = 6,
		icon_user = 7,
		icon_film = 8,
		icon_th_large = 9,
		icon_th = 10,
		icon_th_list = 11,
		icon_ok = 12,
		icon_remove = 13,
		icon_zoom_in = 14,
		icon_zoom_out = 15,
		icon_off = 16,
		icon_signal = 17,
		icon_cog = 18,
		icon_trash = 19,
		icon_home = 20,
		icon_file_alt = 21,
		icon_time = 22,
		icon_road = 23,
		icon_download_alt = 24,
		icon_download = 25,
		icon_upload = 26,
		icon_inbox = 27,
		icon_play_circle = 28,
		icon_repeat = 29,
		icon_refresh = 30,
		icon_list_alt = 31,
		icon_lock = 32,
		icon_flag = 33,
		icon_headphones = 34,
		icon_volume_off = 35,
		icon_volume_down = 36,
		icon_volume_up = 37,
		icon_qrcode = 38
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

	void setButtonIcon (int buttonIcon);

	bool getToggleState();

	void resized();

	void mouseUp (const MouseEvent &event);
protected:

	void paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown);

private:

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultipurposeButton)
};



#endif  // __MULTIPURPOSEBUTTON_H_C1F1AE13__

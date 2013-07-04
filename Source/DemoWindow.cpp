/*
  ==============================================================================

    DemoWindow.cpp
    Created: 1 Jul 2013 11:13:10pm
    Author:  admin

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Styles/LookAndFeelCustom.h"
#include "MultipurposeButton.h"

class Container1 : public Component, 
				   public ChangeListener
{
public:

    Container1() : Component()
    {
        setBounds(0, 0, 310, 350);
        setName("Container");
        TextButton1.setBounds(29, 28, 50, 25);
        TextButton1.setName("TextButton1");
        TextButton1.setButtonText("Right");
        TextButton1.setConnectedEdges(2);
        addAndMakeVisible(&TextButton1);
        TextButton2.setBounds(79, 28, 55, 25);
        TextButton2.setName("TextButton2");
        TextButton2.setButtonText("Middle");
        TextButton2.setConnectedEdges(3);
        addAndMakeVisible(&TextButton2);
        TextButton3.setBounds(134, 28, 50, 25);
        TextButton3.setName("TextButton3");
        TextButton3.setButtonText("Left");
        TextButton3.setConnectedEdges(1);
        addAndMakeVisible(&TextButton3);
        TextButton4.setBounds(209, 28, 100, 25);
        TextButton4.setName("TextButton4");
		TextButton4.setComponentEffect(new DropShadowEffect());
        TextButton4.setButtonText("1");
        TextButton4.setConnectedEdges(0);
        addAndMakeVisible(&TextButton4);
        TextButton5.setBounds(239, 65, 200, 35);
        TextButton5.setName("TextButton5");
		TextButton5.setComponentEffect(new DropShadowEffect());
        TextButton5.setButtonText("2");
        TextButton5.setConnectedEdges(0);
		//TextButton5.setLookAndFeel(&LookAndFeel());
			//DropShadowEffect shadow;
			//shadow.setShadowProperties (DropShadow (Colours::red, 3, Point<int>()));

			//TextButton5.setComponentEffect (&shadow);
			//TextButton4.setComponentEffect (&shadow);
        addAndMakeVisible(&TextButton5);
        TextButton6.setBounds(29, 58, 50, 25);
        TextButton6.setName("TextButton6");
        TextButton6.setButtonText("Wide");
        TextButton6.setConnectedEdges(0);
        addAndMakeVisible(&TextButton6);
        ToggleButton1.setBounds(29, 98, 65, 25);
        ToggleButton1.setName("ToggleButton1");
        ToggleButton1.setButtonText("Toggle");
        addAndMakeVisible(&ToggleButton1);
        ToggleButton2.setBounds(94, 98, 65, 25);
        ToggleButton2.setName("ToggleButton2");
        ToggleButton2.setButtonText("Toggle");
        addAndMakeVisible(&ToggleButton2);
        ToggleButton3.setBounds(169, 98, 65, 25);
        ToggleButton3.setName("ToggleButton3");
        ToggleButton3.setButtonText("Toggle");
        addAndMakeVisible(&ToggleButton3);
		selector.setBounds(5, 130, 300, 300);
		addAndMakeVisible(&selector);
		
		selector.setCurrentColour(Colour((juce::uint8) 83, (juce::uint8) 94, (juce::uint8) 104, (juce::uint8) 255));
		selector.addChangeListener(this);


		Label1.setBounds(0, 0, 165, 24);
		Label1.setFont(Font("FontAwesome", 12.f, 0));
		Label1.setText (L"", NotificationType::dontSendNotification);
		//(juce_wchar) 0x2022
		Label1.setColour(Label::backgroundColourId, Colour::fromString("FFFFFFFF"));
        Label1.setColour(Label::textColourId, Colour::fromString("FF000000"));
        Label1.setEditable(true);
        Label1.setName("Label");
        addAndMakeVisible(&Label1);

		TextButton1.setButtonStyle(5);
		TextButton2.setButtonStyle(5);
		TextButton2.setButtonIcon(MultipurposeButton::ButtonIcon::icon_ok);
		TextButton3.setButtonStyle(1);
		TextButton4.setButtonStyle(5);
		TextButton5.setButtonStyle(5);


    }

    void mouseUp (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            Component::mouseUp(event);
    }

    void mouseDrag (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            Component::mouseDrag(event);
    }

    void mouseDoubleClick (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            Component::mouseDoubleClick(event);
    }

	void paint(Graphics &g)
	{
		g.setOpacity(1.0f);
		g.setTiledImageFill(ImageCache::getFromMemory (BinaryData::background_png, BinaryData::background_pngSize), 127, 127, 1.0f);
		g.fillAll();
		//g.setColour(Colours::red);
		//g.drawHorizontalLine(5, 0.0f, (float) getWidth());
		//g.drawImage(ImageCache::getFromMemory (BinaryData::background_png, BinaryData::background_pngSize),10, 10, 35, 35, 0, 0, 35, 35);
	}

	void changeListenerCallback (ChangeBroadcaster *source)
	{
		if (source == &selector) {
			LookAndFeelCustom::getInstance()->setColour(TextButton::buttonColourId, selector.getCurrentColour());
			TextButton1.repaint();
			TextButton2.repaint();
			TextButton3.repaint();
			TextButton4.repaint();
			TextButton5.repaint();
			TextButton6.repaint();
			ToggleButton1.repaint();
			ToggleButton2.repaint();
			ToggleButton3.repaint();
		}
	}

private:
    MultipurposeButton TextButton1;
    MultipurposeButton TextButton2;
    MultipurposeButton TextButton3;
    MultipurposeButton TextButton4;
    MultipurposeButton TextButton5;
    MultipurposeButton TextButton6;
    ToggleButton ToggleButton1;
    ToggleButton ToggleButton2;
    ToggleButton ToggleButton3;
	ColourSelector selector;
	Label Label1;

};


class DemoWindow    : public DocumentWindow
{
public:
    DemoWindow()  : DocumentWindow ("Window",
                                     Colours::lightgrey,
                                     DocumentWindow::allButtons)
    {
        setLookAndFeel(LookAndFeelCustom::getInstance());
		LookAndFeelCustom::getInstance()->setColour(TextButton::buttonColourId, Colour(Colour((juce::uint8) 83, (juce::uint8) 94, (juce::uint8) 104, (juce::uint8) 255)));
		LookAndFeelCustom::getInstance()->setColour(TextButton::textColourOffId, Colours::transparentWhite.withAlpha(0.9f));
		LookAndFeelCustom::getInstance()->setColour(TextButton::textColourOnId, Colours::blue.withAlpha(0.9f));
		//FreeTypeFaces::addFaceFromMemory(7.f, 12.f, true, BinaryData::mine, BinaryData::mineSize);
        setBounds(75, 45, 310, 350);
        setName("Multipurpose Buttons");
        setTitleBarHeight(26);
        setTitleBarButtonsRequired(7, 0);
        setTitleBarTextCentred(1);
        setUsingNativeTitleBar(1);
        setContentOwned (&container1, true);

        setResizable(true, true);
        setVisible (true);
    }

    void closeButtonPressed()
    {
        JUCEApplication::getInstance()->systemRequestedQuit();
    }

    void mouseUp (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            DocumentWindow::mouseUp(event);
    }

    void mouseDrag (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            DocumentWindow::mouseDrag(event);
    }

    void mouseDoubleClick (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            DocumentWindow::mouseDoubleClick(event);
    }

private:
    Container1 container1;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DemoWindow)
};


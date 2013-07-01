/*
  ==============================================================================

    LookAndFeelCustom.cpp
    Created: 1 Jul 2013 11:15:41pm
    Author:  admin

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../MultipurposeButton.h"
#include "LookAndFeelCustom.h"

namespace LookAndFeelHelpers
{
    static Colour createBaseColour (const Colour& buttonColour,
                                    const bool hasKeyboardFocus,
                                    const bool isMouseOverButton,
                                    const bool isButtonDown) noexcept
    {
        const float sat = hasKeyboardFocus ? 1.3f : 0.9f;
        const Colour baseColour (buttonColour.withMultipliedSaturation (sat));

        if (isButtonDown)      return baseColour.contrasting (0.2f);
        if (isMouseOverButton) return baseColour.contrasting (0.1f);

        return baseColour;
    }

    static TextLayout layoutTooltipText (const String& text, const Colour& colour) noexcept
    {
        const float tooltipFontSize = 13.0f;
        const int maxToolTipWidth = 400;

        AttributedString s;
        s.setJustification (Justification::centred);
        s.append (text, Font (tooltipFontSize, Font::bold), colour);

        TextLayout tl;
        tl.createLayoutWithBalancedLineLengths (s, (float) maxToolTipWidth);
        return tl;
    }

    static Typeface::Ptr getTypefaceForFontFromLookAndFeel (const Font& font)
    {
        return LookAndFeel::getDefaultLookAndFeel().getTypefaceForFont (font);
    }
}


ScopedPointer<LookAndFeelCustom> LookAndFeelCustom::m_pInstance = nullptr; 

LookAndFeelCustom* LookAndFeelCustom::getInstance()
{
   if (!m_pInstance) {
      m_pInstance = new LookAndFeelCustom;
   }

   return m_pInstance.get();
}

void LookAndFeelCustom::destroy()
{
	m_pInstance = nullptr;
}

//==============================================================================
LookAndFeelCustom::LookAndFeelCustom()
{
    setColour (TextButton::buttonColourId,          Colour (0xffbbbbff));
    setColour (ListBox::outlineColourId,            findColour (ComboBox::outlineColourId));
    setColour (ScrollBar::thumbColourId,            Colour (0xffbbbbdd));
    setColour (ScrollBar::backgroundColourId,       Colours::transparentBlack);
    setColour (Slider::thumbColourId,               Colours::yellow);
    setColour (Slider::trackColourId,               Colour (0x7f000000));
    setColour (Slider::textBoxOutlineColourId,      Colours::green);
    setColour (ProgressBar::backgroundColourId,     Colours::white.withAlpha (0.6f));
    setColour (ProgressBar::foregroundColourId,     Colours::green.withAlpha (0.7f));
    setColour (PopupMenu::backgroundColourId,             Colour (0xffeef5f8));
    setColour (PopupMenu::highlightedBackgroundColourId,  Colour (0xbfa4c2ce));
    setColour (PopupMenu::highlightedTextColourId,        Colours::black);
    setColour (TextEditor::focusedOutlineColourId,  findColour (TextButton::buttonColourId));

    //scrollbarShadow.setShadowProperties (2.2f, 0.5f, 0, 0);
}

LookAndFeelCustom::~LookAndFeelCustom()
{
}

void LookAndFeelCustom::drawRotarySlider	(	Graphics & 	g,
									 int 	x,
									 int 	y,
									 int 	width,
									 int 	height,
									 float 	sliderPosProportional,
									 float 	rotaryStartAngle,
									 float 	rotaryEndAngle,
									 Slider & 	slider )
{	 
	// This is the binary image data that uses very little CPU when rotating
	Image myStrip = ImageCache::getFromMemory (BinaryData::knobstrip_png, BinaryData::knobstrip_pngSize);	

	/*
	//THIS IS THE LAME VERSION THAT DRAWS FROM A FILE (40-50% CPU)
	File temp(T("C:\\Users\\nrclark\\programming\\Juce-look-and-feel-examples\\Assets\\knobman\\knobstrip.png"));
	Image myStrip = ImageFileFormat::loadFrom(temp);
	*/
	
	const double fractRotation = (slider.getValue() - slider.getMinimum())  /   (slider.getMaximum() - slider.getMinimum()); //value between 0 and 1 for current amount of rotation
	const int nFrames = myStrip.getHeight()/myStrip.getWidth(); // number of frames for vertical film strip
	const int frameIdx = (int)ceil(fractRotation * ((double)nFrames-1.0) ); // current index from 0 --> nFrames-1

	const float radius = jmin (width / 2.0f, height / 2.0f) ;
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius - 1.0f;
    const float ry = centreY - radius - 1.0f;

	g.drawImage(myStrip,	
				(int)rx,	(int)ry,						2*(int)radius,			2*(int)radius,   //Dest 
				0,			frameIdx*myStrip.getWidth(),	myStrip.getWidth(),		myStrip.getWidth()); //Source

}
	



//==============================================================================
// All of the stuff from here down has just been copied from the oldLookAndFeel 
// class and hacked a bit to toy with it.
//==============================================================================
void LookAndFeelCustom::drawButtonBackground (Graphics& g,
                                                 Button& button,
                                                 const Colour& backgroundColour,
                                                 bool isMouseOverButton,
                                                 bool isButtonDown)
{
	DBG((String("DRAWING BUTTON "+button.getName())));
	bool isGlobal = true;	//sets if its a MultipurposeButton or not
	MultipurposeButton *lf;
	try {
		lf = dynamic_cast<MultipurposeButton*> (&button);
	} catch (...) {
		isGlobal = false;
	}

	if (isGlobal && lf == NULL)
		isGlobal = false;

	if (isGlobal) {
		if (!isButtonDown)
			isButtonDown = lf->getToggleState();
	}
    /*const int width = button.getWidth();
    const int height = button.getHeight();

    const float outlineThickness = button.isEnabled() ? ((isButtonDown || isMouseOverButton) ? 1.2f : 0.7f) : 0.4f;
    const float halfThickness = outlineThickness * 0.5f;

    const float indentL = halfThickness;	//button.isConnectedOnLeft()   ? 0.1f : halfThickness;
    const float indentR = halfThickness;	//button.isConnectedOnRight()  ? 0.1f : halfThickness;
    const float indentT = halfThickness;	//button.isConnectedOnTop()    ? 0.1f : halfThickness;
    const float indentB = halfThickness;	//button.isConnectedOnBottom() ? 0.1f : halfThickness;

    const Colour baseColour (LookAndFeelHelpers::createBaseColour (backgroundColour,
                                                                   button.hasKeyboardFocus (true),
                                                                   isMouseOverButton, isButtonDown)
                               .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));

    drawGlassLozenge (g,
                      indentL,
                      indentT,
                      width - indentL - indentR,
                      height - indentT - indentB,
                      baseColour, outlineThickness, 5.0f,
                      button.isConnectedOnLeft(),
                      button.isConnectedOnRight(),
                      button.isConnectedOnTop(),
                      button.isConnectedOnBottom());
	*/
	bool flatOnLeft = button.isConnectedOnLeft();
	bool flatOnRight = button.isConnectedOnRight();
	bool flatOnTop = button.isConnectedOnTop();
	bool flatOnBottom = button.isConnectedOnBottom();
	bool roundedUpperLeft = (!(flatOnLeft || flatOnTop));
	bool roundedUpperRight = (!(flatOnRight || flatOnTop));
	bool roundedBottomLeft = (!(flatOnLeft || flatOnBottom));
	bool roundedBottomRight = (!(flatOnRight || flatOnBottom));

    const int width = button.getWidth();
    const int height = button.getHeight();

    const float indent = 2.0f;
    const int cornerSize = 5;	//jmin (roundToInt (width * 0.4f), roundToInt (height * 0.4f));

    Path p;
    p.addRoundedRectangle (0.0f, 0.0f, width, height, cornerSize, cornerSize,
                                 ! (flatOnLeft || flatOnTop),
                                 ! (flatOnRight || flatOnTop),
                                 ! (flatOnLeft || flatOnBottom),
                                 ! (flatOnRight || flatOnBottom));
	/*
    Colour bc (backgroundColour.withMultipliedSaturation (0.3f));

    if (isMouseOverButton)
    {
        if (isButtonDown)
            bc = bc.brighter();
        else if (bc.getBrightness() > 0.5f)
            bc = bc.darker (0.1f);
        else
            bc = bc.brighter (0.1f);
    }*/
	Colour colour = (isMouseOverButton) ? backgroundColour.brighter(0.1f) : backgroundColour;
	if (!isButtonDown) {
        ColourGradient cg (colour, 0, 0,
                           colour.darker (0.7f), 0, 0 + height, false);

        cg.addColour (0.1, colour.brighter(0.1f));
        //cg.addColour (0.4, colour);
        //cg.addColour (0.97, colour.withMultipliedAlpha (0.3f));

        g.setGradientFill (cg);
        g.fillPath (p);
		g.setColour(colour.brighter(0.4f));
		
		g.drawHorizontalLine(1, (roundedUpperLeft) ? 4 : 1, (roundedUpperRight) ? width - 4 : width);
		if (roundedUpperLeft) {
			g.setColour(colour.brighter(0.2f));
			g.drawHorizontalLine(1, 3, 4);
			//g.setColour(colour.brighter(0.2f));
			g.drawHorizontalLine(2, 2, 3);
		}
		if (roundedUpperRight) {
			g.setColour(colour.brighter(0.2f));
			g.drawHorizontalLine(1, width - 4, width - 3);
			//g.setColour(colour.brighter(0.2f));
			g.drawHorizontalLine(2, width - 3, width - 2);
		}
		//g.setGradientFill (ColourGradient (colour.brighter (10.0f), 0, height / 2, Colours::transparentWhite, 0, height, false));
		//g.setGradientFill (ColourGradient (colour.brighter (10.0f), 0, 0 + height * 0.06f, Colours::transparentWhite, 0, 0 + height * 0.4f, false));
		//g.fillPath (p);
		//g.setTiledImageFill(ImageCache::getFromMemory (BinaryData::background_png, BinaryData::background_pngSize), 0, 0, 1.0f);
		//g.setGradientFill (ColourGradient (colour.brighter (0.1f), width - 1, 0, colour.brighter (0.5f), width - 1, height, false));
		//g.fillRect(width - 1, 0, 1, height);
    }

	if (isButtonDown) {
		//g.setOpacity(1.0f);
		//g.fillAll(colour);
		
		//ColourGradient cg (colour.brighter(0.1f), width / 2, height / 2, Colours::black.withAlpha(0.6f), width - 10, width - 10, true);
		ColourGradient cg (Colours::black.withAlpha(0.6f), 0, 0, Colours::black.withAlpha(0.6f), 0, 0 + height, false);
		cg.addColour (0.3, Colours::transparentBlack);
		cg.addColour (0.7, Colours::transparentBlack);
        //cg.addColour (0.3, colour.darker(0.1f));
		//cg.addColour (0.7, colour.darker(0.1f));
		//cg.addColour (0.4, colour);
        //cg.addColour (0.97, colour.withMultipliedAlpha (0.3f));

        //g.setGradientFill (cg);
        //g.fillPath (p);

		//ColourGradient laterals (Colours::darkgrey.withAlpha(0.6f), 0, height, Colours::darkgrey.withAlpha(0.6f), width, height, false);
		ColourGradient laterals (Colours::black.withAlpha(0.6f), 0, 0, Colours::black.withAlpha(0.6f), 0, 0 + height, false);

		laterals.addColour (0.3, Colours::transparentBlack);
		laterals.addColour (0.7, Colours::transparentBlack);
		g.setGradientFill (laterals);
		g.addTransform(AffineTransform::rotation(2.0f));
        g.fillPath (p);//, AffineTransform::identity.rotated(1.57079633f));
		g.addTransform(AffineTransform::identity);
	}

    //g.setColour (bc);
    //g.fillPath (p);

    //g.setColour (colour.contrasting().withAlpha ((isMouseOverButton) ? 0.6f : 0.4f));
	//draw border
	g.setColour(Colours::black);
	g.setOpacity(1.0f);
    g.strokePath (p, PathStrokeType(1.0f));//PathStrokeType ((isMouseOverButton) ? 1.0f : 1.0f));
	//g.strokePath (p, PathStrokeType(1.0f));


	//Draw brighter 1px vertical gradient on the right
	if (!isButtonDown) {
		g.setGradientFill (ColourGradient (colour, width - 1, 0, Colours::grey.withAlpha(0.7f), width - 1, height, false));
		if (!roundedUpperRight && !roundedBottomRight)
			g.fillRect(width - 1, 2, 1, height - 3);
	

		//draw darker 1px vertical line on the left
		if (!roundedUpperLeft && !roundedBottomLeft) {
			g.setColour(Colours::darkgrey.withAlpha(0.3f));
			g.fillRect(0, 2, 1, height - 3);
		}
	}

	//fix pixels
	if (!isButtonDown) {
		if (!roundedUpperRight) {
			g.setColour(colour.brighter(0.4f));
			g.drawHorizontalLine(1, width - 1, width);
		}
		if (!roundedUpperLeft) {
			g.setColour(colour.brighter(0.4f));
			g.drawHorizontalLine(1, 0, 1);
		}
	}

	//Redraw border
	g.setColour(Colours::black);
	g.setOpacity(1.0f);
	g.drawHorizontalLine(0, (roundedUpperLeft) ? 4 : 0, (roundedUpperRight) ? width - 4 : width);
	g.drawHorizontalLine(height, (roundedBottomLeft) ? 4 : 0, (roundedBottomRight) ? width - 4 : width);
	if (!(!roundedUpperLeft && !roundedBottomLeft))
		g.drawVerticalLine(0, (roundedUpperLeft) ? 4 : 0, (roundedBottomLeft) ? height - 4 : height);
	if (!(!roundedUpperRight && !roundedBottomRight))
	g.drawVerticalLine(width, (roundedUpperRight) ? 4 : 0, (roundedBottomRight) ? height - 4 : height);

	/*DropShadow shadowType = DropShadow();
	DropShadower ds(shadowType);
	button.setOpaque(true);
	ds.setOwner(&button);*/

	
	
}

void LookAndFeelCustom::drawTickBox (Graphics& g,
                                        Component& /*component*/,
                                        float x, float y, float w, float h,
                                        const bool ticked,
                                        const bool isEnabled,
                                        const bool /*isMouseOverButton*/,
                                        const bool isButtonDown)
{
    Path box;
    box.addRoundedRectangle (0.0f, 2.0f, 6.0f, 6.0f, 1.0f);

    g.setColour (isEnabled ? Colours::blue.withAlpha (isButtonDown ? 0.3f : 0.1f)
                           : Colours::lightgrey.withAlpha (0.1f));

    AffineTransform trans (AffineTransform::scale (w / 9.0f, h / 9.0f).translated (x, y));

    g.fillPath (box, trans);

    g.setColour (Colours::black.withAlpha (0.6f));
    g.strokePath (box, PathStrokeType (0.9f), trans);

    if (ticked)
    {
        Path tick;
        tick.startNewSubPath (1.5f, 3.0f);
        tick.lineTo (3.0f, 6.0f);
        tick.lineTo (6.0f, 0.0f);

        g.setColour (isEnabled ? Colours::black : Colours::grey);
        g.strokePath (tick, PathStrokeType (2.5f), trans);
    }
}

void LookAndFeelCustom::drawToggleButton (Graphics& g,
                                             ToggleButton& button,
                                             bool isMouseOverButton,
                                             bool isButtonDown)
{
    /*if (button.hasKeyboardFocus (true))
    {
        g.setColour (button.findColour (TextEditor::focusedOutlineColourId));
        g.drawRect (0, 0, button.getWidth(), button.getHeight());
    }

    const int tickWidth = jmin (20, button.getHeight() - 4);

    drawTickBox (g, button, 4.0f, (button.getHeight() - tickWidth) * 0.5f,
                 (float) tickWidth, (float) tickWidth,
                 button.getToggleState(),
                 button.isEnabled(),
                 isMouseOverButton,
                 isButtonDown);

    g.setColour (button.findColour (ToggleButton::textColourId));
    g.setFont (jmin (15.0f, button.getHeight() * 0.6f));

    if (! button.isEnabled())
        g.setOpacity (0.5f);
	*/
	if (!isButtonDown)
		isButtonDown = button.getToggleState();
	bool flatOnLeft = false;	//button.isConnectedOnLeft();
	bool flatOnRight = false;	//button.isConnectedOnRight();
	bool flatOnTop = false;	//button.isConnectedOnTop();
	bool flatOnBottom = false;	//button.isConnectedOnBottom();
	bool roundedUpperLeft = (!(flatOnLeft || flatOnTop));
	bool roundedUpperRight = (!(flatOnRight || flatOnTop));
	bool roundedBottomLeft = (!(flatOnLeft || flatOnBottom));
	bool roundedBottomRight = (!(flatOnRight || flatOnBottom));

	const int width = button.getWidth();
    const int height = button.getHeight();

    const float indent = 2.0f;
    const int cornerSize = 5;	//jmin (roundToInt (width * 0.4f), roundToInt (height * 0.4f));

    Path p;
    p.addRoundedRectangle (0.0f, 0.0f, width, height, cornerSize, cornerSize,
                                 ! (flatOnLeft || flatOnTop),
                                 ! (flatOnRight || flatOnTop),
                                 ! (flatOnLeft || flatOnBottom),
                                 ! (flatOnRight || flatOnBottom));
	/*
    Colour bc (backgroundColour.withMultipliedSaturation (0.3f));

    if (isMouseOverButton)
    {
        if (isButtonDown)
            bc = bc.brighter();
        else if (bc.getBrightness() > 0.5f)
            bc = bc.darker (0.1f);
        else
            bc = bc.brighter (0.1f);
    }*/
	Colour backgroundColour = findColour(TextButton::buttonColourId);
	Colour colour = (isMouseOverButton) ? backgroundColour.brighter(0.1f) : backgroundColour;
	if (!isButtonDown) {
        ColourGradient cg (colour, 0, 0,
                           colour.darker (0.7f), 0, 0 + height, false);

        cg.addColour (0.1, colour.brighter(0.1f));
        //cg.addColour (0.4, colour);
        //cg.addColour (0.97, colour.withMultipliedAlpha (0.3f));

        g.setGradientFill (cg);
        g.fillPath (p);
		g.setColour(colour.brighter(0.4f));
		
		g.drawHorizontalLine(1, (roundedUpperLeft) ? 4 : 1, (roundedUpperRight) ? width - 4 : width);
		if (roundedUpperLeft) {
			g.setColour(colour.brighter(0.2f));
			g.drawHorizontalLine(1, 3, 4);
			//g.setColour(colour.brighter(0.2f));
			g.drawHorizontalLine(2, 2, 3);
		}
		if (roundedUpperRight) {
			g.setColour(colour.brighter(0.2f));
			g.drawHorizontalLine(1, width - 4, width - 3);
			//g.setColour(colour.brighter(0.2f));
			g.drawHorizontalLine(2, width - 3, width - 2);
		}
		//g.setGradientFill (ColourGradient (colour.brighter (10.0f), 0, height / 2, Colours::transparentWhite, 0, height, false));
		//g.setGradientFill (ColourGradient (colour.brighter (10.0f), 0, 0 + height * 0.06f, Colours::transparentWhite, 0, 0 + height * 0.4f, false));
		//g.fillPath (p);
		//g.setTiledImageFill(ImageCache::getFromMemory (BinaryData::background_png, BinaryData::background_pngSize), 0, 0, 1.0f);
		//g.setGradientFill (ColourGradient (colour.brighter (0.1f), width - 1, 0, colour.brighter (0.5f), width - 1, height, false));
		//g.fillRect(width - 1, 0, 1, height);
    }

	if (isButtonDown) {
		//g.setOpacity(1.0f);
		//g.fillAll(colour);
		
		ColourGradient cg (colour.brighter(0.1f), width / 2, height / 2,
                           Colours::black.withAlpha(0.6f), width - 10, width - 10, true);

        //cg.addColour (0.3, colour.darker(0.1f));
		//cg.addColour (0.7, colour.darker(0.1f));
		//cg.addColour (0.4, colour);
        //cg.addColour (0.97, colour.withMultipliedAlpha (0.3f));

        g.setGradientFill (cg);
        g.fillPath (p);

		//ColourGradient laterals (Colours::darkgrey.withAlpha(0.6f), 0, height, Colours::darkgrey.withAlpha(0.6f), width, height, false);
		ColourGradient laterals (Colours::black.withAlpha(0.6f), 0, 0,
                           Colours::black.withAlpha(0.6f), 0, 0 + height, false);

		laterals.addColour (0.3, Colours::transparentBlack);
		laterals.addColour (0.7, Colours::transparentBlack);
		g.setGradientFill (laterals);
        g.fillPath (p);
	}

    //g.setColour (bc);
    //g.fillPath (p);

    //g.setColour (colour.contrasting().withAlpha ((isMouseOverButton) ? 0.6f : 0.4f));
	//draw border
	g.setColour(Colours::black);
	g.setOpacity(1.0f);
    g.strokePath (p, PathStrokeType(1.0f));//PathStrokeType ((isMouseOverButton) ? 1.0f : 1.0f));
	//g.strokePath (p, PathStrokeType(1.0f));


	//Draw brighter 1px vertical gradient on the right
	if (!isButtonDown) {
		g.setGradientFill (ColourGradient (colour, width - 1, 0, Colours::grey.withAlpha(0.7f), width - 1, height, false));
		if (!roundedUpperRight && !roundedBottomRight)
			g.fillRect(width - 1, 2, 1, height - 3);
	

		//draw darker 1px vertical line on the left
		if (!roundedUpperLeft && !roundedBottomLeft) {
			g.setColour(Colours::darkgrey.withAlpha(0.3f));
			g.fillRect(0, 2, 1, height - 3);
		}
	}

	//fix pixels
	if (!isButtonDown) {
		if (!roundedUpperRight) {
			g.setColour(colour.brighter(0.4f));
			g.drawHorizontalLine(1, width - 1, width);
		}
		if (!roundedUpperLeft) {
			g.setColour(colour.brighter(0.4f));
			g.drawHorizontalLine(1, 0, 1);
		}
	}

	//Redraw border
	g.setColour(Colours::black);
	g.setOpacity(1.0f);
	g.drawHorizontalLine(0, (roundedUpperLeft) ? 4 : 0, (roundedUpperRight) ? width - 4 : width);
	g.drawHorizontalLine(height, (roundedBottomLeft) ? 4 : 0, (roundedBottomRight) ? width - 4 : width);
	if (!(!roundedUpperLeft && !roundedBottomLeft))
		g.drawVerticalLine(0, (roundedUpperLeft) ? 4 : 0, (roundedBottomLeft) ? height - 4 : height);
	if (!(!roundedUpperRight && !roundedBottomRight))
	g.drawVerticalLine(width, (roundedUpperRight) ? 4 : 0, (roundedBottomRight) ? height - 4 : height);

    const int textX = 0;

	g.setColour(findColour(TextButton::textColourOffId));
    g.drawFittedText (button.getButtonText(),
                      textX, 4,
                      button.getWidth() - textX - 2, button.getHeight() - 8,
                      Justification::centred, 10);
}

void LookAndFeelCustom::drawProgressBar (Graphics& g, ProgressBar& progressBar,
                                            int width, int height,
                                            double progress, const String& textToShow)
{
    if (progress < 0 || progress >= 1.0)
    {
        LookAndFeel::drawProgressBar (g, progressBar, width, height, progress, textToShow);
    }
    else
    {
        const Colour background (progressBar.findColour (ProgressBar::backgroundColourId));
        const Colour foreground (progressBar.findColour (ProgressBar::foregroundColourId));

        g.fillAll (background);
        g.setColour (foreground);

        g.fillRect (1, 1,
                    jlimit (0, width - 2, roundToInt (progress * (width - 2))),
                    height - 2);

        if (textToShow.isNotEmpty())
        {
            g.setColour (Colour::contrasting (background, foreground));
            g.setFont (height * 0.6f);

            g.drawText (textToShow, 0, 0, width, height, Justification::centred, false);
        }
    }
}

void LookAndFeelCustom::drawScrollbarButton (Graphics& g,
                                                ScrollBar& bar,
                                                int width, int height,
                                                int buttonDirection,
                                                bool isScrollbarVertical,
                                                bool isMouseOverButton,
                                                bool isButtonDown)
{
    if (isScrollbarVertical)
        width -= 2;
    else
        height -= 2;

    Path p;

    if (buttonDirection == 0)
        p.addTriangle (width * 0.5f, height * 0.2f,
                       width * 0.1f, height * 0.7f,
                       width * 0.9f, height * 0.7f);
    else if (buttonDirection == 1)
        p.addTriangle (width * 0.8f, height * 0.5f,
                       width * 0.3f, height * 0.1f,
                       width * 0.3f, height * 0.9f);
    else if (buttonDirection == 2)
        p.addTriangle (width * 0.5f, height * 0.8f,
                       width * 0.1f, height * 0.3f,
                       width * 0.9f, height * 0.3f);
    else if (buttonDirection == 3)
        p.addTriangle (width * 0.2f, height * 0.5f,
                       width * 0.7f, height * 0.1f,
                       width * 0.7f, height * 0.9f);

    if (isButtonDown)
        g.setColour (Colours::white);
    else if (isMouseOverButton)
        g.setColour (Colours::white.withAlpha (0.7f));
    else
        g.setColour (bar.findColour (ScrollBar::thumbColourId).withAlpha (0.5f));

    g.fillPath (p);

    g.setColour (Colours::black.withAlpha (0.5f));
    g.strokePath (p, PathStrokeType (0.5f));
}

void LookAndFeelCustom::drawScrollbar (Graphics& g,
                                          ScrollBar& bar,
                                          int x, int y,
                                          int width, int height,
                                          bool isScrollbarVertical,
                                          int thumbStartPosition,
                                          int thumbSize,
                                          bool isMouseOver,
                                          bool isMouseDown)
{
    g.fillAll (bar.findColour (ScrollBar::backgroundColourId));

    g.setColour (bar.findColour (ScrollBar::thumbColourId)
                    .withAlpha ((isMouseOver || isMouseDown) ? 0.4f : 0.15f));

    if (thumbSize > 0.0f)
    {
        Rectangle<int> thumb;

        if (isScrollbarVertical)
        {
            width -= 2;
            g.fillRect (x + roundToInt (width * 0.35f), y,
                        roundToInt (width * 0.3f), height);

            thumb.setBounds (x + 1, thumbStartPosition,
                             width - 2, thumbSize);
        }
        else
        {
            height -= 2;
            g.fillRect (x, y + roundToInt (height * 0.35f),
                        width, roundToInt (height * 0.3f));

            thumb.setBounds (thumbStartPosition, y + 1,
                             thumbSize, height - 2);
        }

        g.setColour (bar.findColour (ScrollBar::thumbColourId)
                        .withAlpha ((isMouseOver || isMouseDown) ? 0.95f : 0.7f));

        g.fillRect (thumb);

        g.setColour (Colours::black.withAlpha ((isMouseOver || isMouseDown) ? 0.4f : 0.25f));
        g.drawRect (thumb.getX(), thumb.getY(), thumb.getWidth(), thumb.getHeight());

        if (thumbSize > 16)
        {
            for (int i = 3; --i >= 0;)
            {
                const float linePos = thumbStartPosition + thumbSize / 2 + (i - 1) * 4.0f;
                g.setColour (Colours::black.withAlpha (0.15f));

                if (isScrollbarVertical)
                {
                    g.drawLine (x + width * 0.2f, linePos, width * 0.8f, linePos);
                    g.setColour (Colours::white.withAlpha (0.15f));
                    g.drawLine (width * 0.2f, linePos - 1, width * 0.8f, linePos - 1);
                }
                else
                {
                    g.drawLine (linePos, height * 0.2f, linePos, height * 0.8f);
                    g.setColour (Colours::white.withAlpha (0.15f));
                    g.drawLine (linePos - 1, height * 0.2f, linePos - 1, height * 0.8f);
                }
            }
        }
    }
}

ImageEffectFilter* LookAndFeelCustom::getScrollbarEffect()
{
    return &scrollbarShadow;
}


//==============================================================================
void LookAndFeelCustom::drawPopupMenuBackground (Graphics& g, int width, int height)
{
    g.fillAll (findColour (PopupMenu::backgroundColourId));

    g.setColour (Colours::black.withAlpha (0.6f));
    g.drawRect (0, 0, width, height);
}

void LookAndFeelCustom::drawMenuBarBackground (Graphics& g, int /*width*/, int /*height*/,
                                                  bool, MenuBarComponent& menuBar)
{
    g.fillAll (menuBar.findColour (PopupMenu::backgroundColourId));
}


//==============================================================================
void LookAndFeelCustom::drawTextEditorOutline (Graphics& g, int width, int height, TextEditor& textEditor)
{
    if (textEditor.isEnabled())
    {
        g.setColour (textEditor.findColour (TextEditor::outlineColourId));
        g.drawRect (0, 0, width, height);
    }
}

//==============================================================================
void LookAndFeelCustom::drawComboBox (Graphics& g, int width, int height,
                                         const bool isButtonDown,
                                         int buttonX, int buttonY,
                                         int buttonW, int buttonH,
                                         ComboBox& box)
{
    g.fillAll (box.findColour (ComboBox::backgroundColourId));

    g.setColour (box.findColour ((isButtonDown) ? ComboBox::buttonColourId
                                                : ComboBox::backgroundColourId));
    g.fillRect (buttonX, buttonY, buttonW, buttonH);

    g.setColour (box.findColour (ComboBox::outlineColourId));
    g.drawRect (0, 0, width, height);

    const float arrowX = 0.2f;
    const float arrowH = 0.3f;

    if (box.isEnabled())
    {
        Path p;
        p.addTriangle (buttonX + buttonW * 0.5f,            buttonY + buttonH * (0.45f - arrowH),
                       buttonX + buttonW * (1.0f - arrowX), buttonY + buttonH * 0.45f,
                       buttonX + buttonW * arrowX,          buttonY + buttonH * 0.45f);

        p.addTriangle (buttonX + buttonW * 0.5f,            buttonY + buttonH * (0.55f + arrowH),
                       buttonX + buttonW * (1.0f - arrowX), buttonY + buttonH * 0.55f,
                       buttonX + buttonW * arrowX,          buttonY + buttonH * 0.55f);

        g.setColour (box.findColour ((isButtonDown) ? ComboBox::backgroundColourId
                                                    : ComboBox::buttonColourId));
        g.fillPath (p);
    }
}

Font LookAndFeelCustom::getComboBoxFont (ComboBox& box)
{
    Font f (jmin (15.0f, box.getHeight() * 0.85f));
    f.setHorizontalScale (0.9f);
    return f;
}

//==============================================================================
static void drawTriangle (Graphics& g, float x1, float y1, float x2, float y2, float x3, float y3, const Colour& fill, const Colour& outline) noexcept
{
    Path p;
    p.addTriangle (x1, y1, x2, y2, x3, y3);
    g.setColour (fill);
    g.fillPath (p);

    g.setColour (outline);
    g.strokePath (p, PathStrokeType (0.3f));
}

void LookAndFeelCustom::drawLinearSlider (Graphics& g,
                                             int x, int y,
                                             int w, int h,
                                             float sliderPos,
                                             float minSliderPos,
                                             float maxSliderPos,
                                             const Slider::SliderStyle style,
                                             Slider& slider)
{
    g.fillAll (slider.findColour (Slider::backgroundColourId));

    if (style == Slider::LinearBar)
    {
        g.setColour (slider.findColour (Slider::thumbColourId));
        g.fillRect (x, y, (int) sliderPos - x, h);

        g.setColour (slider.findColour (Slider::textBoxTextColourId).withMultipliedAlpha (0.5f));
        g.drawRect (x, y, (int) sliderPos - x, h);
    }
    else
    {
        g.setColour (slider.findColour (Slider::trackColourId)
                           .withMultipliedAlpha (slider.isEnabled() ? 1.0f : 0.3f));

        if (slider.isHorizontal())
        {
            g.fillRect (x, y + roundToInt (h * 0.8f),
                        w, roundToInt (h * 0.2f));
        }
        else
        {
            g.fillRect (x + roundToInt (w * 0.5f - jmin (3.0f, w * 0.1f)), y,
                        jmin (4, roundToInt (w * 0.2f)), h);
        }

        float alpha = 0.35f;

        if (slider.isEnabled())
            alpha = slider.isMouseOverOrDragging() ? 1.0f : 0.7f;

        const Colour fill (slider.findColour (Slider::thumbColourId).withAlpha (alpha));
        const Colour outline (Colours::black.withAlpha (slider.isEnabled() ? 0.7f : 0.35f));

        if (style == Slider::TwoValueVertical || style == Slider::ThreeValueVertical)
        {
            drawTriangle (g, x + w * 0.5f + jmin (4.0f, w * 0.3f), minSliderPos,
                          x + w * 0.5f - jmin (8.0f, w * 0.4f), minSliderPos - 7.0f,
                          x + w * 0.5f - jmin (8.0f, w * 0.4f), minSliderPos,
                          fill, outline);

            drawTriangle (g, x + w * 0.5f + jmin (4.0f, w * 0.3f), maxSliderPos,
                          x + w * 0.5f - jmin (8.0f, w * 0.4f), maxSliderPos,
                          x + w * 0.5f - jmin (8.0f, w * 0.4f), maxSliderPos + 7.0f,
                          fill, outline);
        }
        else if (style == Slider::TwoValueHorizontal || style == Slider::ThreeValueHorizontal)
        {
            drawTriangle (g, minSliderPos, y + h * 0.6f - jmin (4.0f, h * 0.3f),
                          minSliderPos - 7.0f, y + h * 0.9f ,
                          minSliderPos, y + h * 0.9f,
                          fill, outline);

            drawTriangle (g, maxSliderPos, y + h * 0.6f - jmin (4.0f, h * 0.3f),
                          maxSliderPos, y + h * 0.9f,
                          maxSliderPos + 7.0f, y + h * 0.9f,
                          fill, outline);
        }

        if (style == Slider::LinearHorizontal || style == Slider::ThreeValueHorizontal)
        {
            drawTriangle (g, sliderPos, y + h * 0.9f,
                          sliderPos - 7.0f, y + h * 0.2f,
                          sliderPos + 7.0f, y + h * 0.2f,
                          fill, outline);
        }
        else if (style == Slider::LinearVertical || style == Slider::ThreeValueVertical)
        {
            drawTriangle (g, x + w * 0.5f - jmin (4.0f, w * 0.3f), sliderPos,
                          x + w * 0.5f + jmin (8.0f, w * 0.4f), sliderPos - 7.0f,
                          x + w * 0.5f + jmin (8.0f, w * 0.4f), sliderPos + 7.0f,
                          fill, outline);
        }
    }
}

Button* LookAndFeelCustom::createSliderButton (const bool isIncrement)
{
    if (isIncrement)
        return new ArrowButton ("u", 0.75f, Colours::white.withAlpha (0.8f));
    else
        return new ArrowButton ("d", 0.25f, Colours::white.withAlpha (0.8f));
}

ImageEffectFilter* LookAndFeelCustom::getSliderEffect()
{
    return &scrollbarShadow;
}

int LookAndFeelCustom::getSliderThumbRadius (Slider&)
{
    return 8;
}

//==============================================================================
void LookAndFeelCustom::drawCornerResizer (Graphics& g,
                                              int w, int h,
                                              bool isMouseOver,
                                              bool isMouseDragging)
{
    g.setColour ((isMouseOver || isMouseDragging) ? Colours::lightgrey
                                                  : Colours::darkgrey);

    const float lineThickness = jmin (w, h) * 0.1f;

    for (float i = 0.0f; i < 1.0f; i += 0.3f)
    {
        g.drawLine (w * i,
                    h + 1.0f,
                    w + 1.0f,
                    h * i,
                    lineThickness);
    }
}

//==============================================================================
Button* LookAndFeelCustom::createDocumentWindowButton (int buttonType)
{
    Path shape;

    if (buttonType == DocumentWindow::closeButton)
    {
        shape.addLineSegment (Line<float> (0.0f, 0.0f, 1.0f, 0.9f), 0.45f);
        shape.addLineSegment (Line<float> (1.0f, 0.0f, 0.0f, 1.0f), 0.35f);

        ShapeButton* const b = new ShapeButton ("close",
                                                Colour (0x7fff3333),
                                                Colour (0xd7ff3333),
                                                Colour (0xf7ff3333));

        b->setShape (shape, true, true, true);
        return b;
    }
    else if (buttonType == DocumentWindow::minimiseButton)
    {
        shape.addLineSegment (Line<float> (0.0f, 0.5f, 1.0f, 0.5f), 0.25f);

        DrawableButton* b = new DrawableButton ("minimise", DrawableButton::ImageFitted);
        DrawablePath dp;
        dp.setPath (shape);
        dp.setFill (Colours::black.withAlpha (0.3f));
        b->setImages (&dp);
        return b;
    }
    else if (buttonType == DocumentWindow::maximiseButton)
    {
        shape.addLineSegment (Line<float> (0.5f, 0.0f, 0.5f, 1.0f), 0.25f);
        shape.addLineSegment (Line<float> (0.0f, 0.5f, 1.0f, 0.5f), 0.25f);

        DrawableButton* b = new DrawableButton ("maximise", DrawableButton::ImageFitted);
        DrawablePath dp;
        dp.setPath (shape);
        dp.setFill (Colours::black.withAlpha (0.3f));
        b->setImages (&dp);
        return b;
    }

    jassertfalse;
    return nullptr;
}

void LookAndFeelCustom::positionDocumentWindowButtons (DocumentWindow&,
                                                          int titleBarX,
                                                          int titleBarY,
                                                          int titleBarW,
                                                          int titleBarH,
                                                          Button* minimiseButton,
                                                          Button* maximiseButton,
                                                          Button* closeButton,
                                                          bool positionTitleBarButtonsOnLeft)
{
    titleBarY += titleBarH / 8;
    titleBarH -= titleBarH / 4;

    const int buttonW = titleBarH;

    int x = positionTitleBarButtonsOnLeft ? titleBarX + 4
                                          : titleBarX + titleBarW - buttonW - 4;

    if (closeButton != nullptr)
    {
        closeButton->setBounds (x, titleBarY, buttonW, titleBarH);
        x += positionTitleBarButtonsOnLeft ? buttonW + buttonW / 5
                                           : -(buttonW + buttonW / 5);
    }

    if (positionTitleBarButtonsOnLeft)
        std::swap (minimiseButton, maximiseButton);

    if (maximiseButton != nullptr)
    {
        maximiseButton->setBounds (x, titleBarY - 2, buttonW, titleBarH);
        x += positionTitleBarButtonsOnLeft ? buttonW : -buttonW;
    }

    if (minimiseButton != nullptr)
        minimiseButton->setBounds (x, titleBarY - 2, buttonW, titleBarH);
}

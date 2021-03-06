/*
 * Displays a group of radio buttons in a dialog box when the button in the window is clicked. 
 */

#include "helloworld.h"
#include "MyDialogBox.h"
#include "TurnDialog.h"

// Creates a new button with the label "Hello World".
HelloWorld::HelloWorld() : button("Bring up dialog box"), button1("Bring up dialog box 2"){
	// Sets the border width of the window.
	set_border_width( 10 );
       
	// When the button receives the "clicked" signal, it will call the onButtonClicked() method defined below.
	button.signal_clicked().connect( sigc::mem_fun( *this, &HelloWorld::onButtonClicked ) );
	
	button1.signal_clicked().connect(sigc::mem_fun(*this, &HelloWorld::onButtonClicked2));
	// This packs the button into the Window (a container).
	
	add(mainWindow);	
	mainWindow.add( button );
	mainWindow.add(button1);
	
	// The final step is to display this newly created widget.
	show_all();
} // HelloWorld::HelloWorld

HelloWorld::~HelloWorld() {}

void HelloWorld::onButtonClicked() {
    // Create the message dialog box with stock "Ok" button. Waits until the "Ok" button has been pressed.
    MyDialogBox dialog( *this, "Winner" );
} // HelloWorld::onButtonClicked

void HelloWorld::onButtonClicked2() {
    TurnDialog dialog(*this, "Error");
}

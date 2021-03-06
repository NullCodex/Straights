/*
 * Displays a group of radio buttons in a dialog box when the button in the window is clicked. 
 */

#ifndef GTKMM_EXAMPLE_HELLOWORLD_H
#define GTKMM_EXAMPLE_HELLOWORLD_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>

class HelloWorld : public Gtk::Window {
public:
	HelloWorld();
	virtual ~HelloWorld();
	
protected:
    // Signal handlers:
    virtual void onButtonClicked();
    virtual void onButtonClicked2();
    
	// Member widgets:
    Gtk::VBox		 mainWindow;
    Gtk::Button          button;           // Button to trigger the dialog box
    Gtk::Button		 button1;
}; // HelloWorld

#endif

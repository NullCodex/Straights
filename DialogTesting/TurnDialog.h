/*
 *  MyDialogBox.h
 *  
 * Creates a dialog box that holds a radio button group with each radio button associated with a colour.
 * Outputs the colour chosen by the user.
 *
 *  Created by Caroline Kierstead on 28/05/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */

#ifndef __TURN_DIALOG_H
#define __TURN_DIALOG_H
#include <gtkmm/dialog.h>
#include <gtkmm/box.h>
#include <gtkmm/messagedialog.h>
#include <string>
#include <vector>
using std::string;
using std::vector;

class TurnDialog : Gtk::MessageDialog {
public:
	// Specifies the parent window of the dialog box and the title of the dialog box.
	TurnDialog( Gtk::Window & parentWindow, string title);
	virtual ~TurnDialog();
	
private:

}; // TurnDialog
#endif

/*
 *  MyDialogBox.cc
 *
 *  Created by Caroline Kierstead on 28/05/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */
#include "TurnDialog.h"
#include <gtkmm/stock.h>
#include <iostream>
#

// Specifies the parent window of the dialog box and the title of the dialog box.
TurnDialog::TurnDialog( Gtk::Window & parentWindow, string title) : MessageDialog( parentWindow, title ) {
	show_all_children();
	int result = run();
	switch(result) {
		case Gtk::RESPONSE_OK: {
			std::cout << "Error clicked " << std::endl;		
		}
		break;	
	}		
	
} // TurnDialog::TurnDialog

TurnDialog::~TurnDialog() {
} // TurnDialog::~TurnDialog

/*
 *  MyDialogBox.cc
 *
 *  Created by Caroline Kierstead on 28/05/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */
#include "MyDialogBox.h"
#include <gtkmm/stock.h>
#include <gtkmm.h>
#include <iostream>


// Specifies the parent window of the dialog box and the title of the dialog box.
MyDialogBox::MyDialogBox( Gtk::Window & parentWindow, string title) : MessageDialog( parentWindow, title ) {
	show_all_children();
	int result = run();
	switch(result) {
		case Gtk::RESPONSE_OK: {
			std::cout << "Winner clicked" << std::endl;		
		}
		break;	
	}		
	
} // MyDialogBox::MyDialogBox

MyDialogBox::~MyDialogBox() {
} // MyDialogBox::~MyDialogBox

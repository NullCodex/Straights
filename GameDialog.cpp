#include "GameDialog.h"
#include <gtkmm/stock.h>
#include <gtkmm.h>
#include <iostream>


// Specifies the parent window of the dialog box and the title of the dialog box.
GameDialog::GameDialog( Gtk::Window & parentWindow, string title) : MessageDialog( parentWindow, title ) {
	show_all_children();
	int result = run();
	switch(result) {
		case Gtk::RESPONSE_OK: {
			std::cout << "Winner clicked" << std::endl;		
		}
		break;	
	}		
	
} // GameDialog::GameDialog

GameDialog::~GameDialog() {
} // GameDialog::~GameDialog

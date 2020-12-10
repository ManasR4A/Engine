// Overloads annd addes some functions for GLib

#pragma once
#include "assert.h"
#include "../GLib/GLib.h"
#include "iostream"


/*	Loads a file from the disk to the memory
	@param			The File path.
	@return			size_t The output for the file.
*/
void* LoadFile(const char * i_pFilename, size_t& o_sizeFile);


// Create sprites from the filename
GLib::Sprite* CreateSprite(const char * i_pFilename);

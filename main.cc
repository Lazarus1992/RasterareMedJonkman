//------------------------------------------------------------------------------
// main.cc
// (C) 2015-2016 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "exampleapp.h"

int
main(int argc, const char** argv)
{
	/*Example::*/JontesProjekt app;
	//app.Setup();
	if (app.Open())
	{
		app.Run();
		app.Close();
	}
	app.Exit();
	
}
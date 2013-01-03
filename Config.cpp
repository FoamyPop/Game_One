#include "Config.h"

Config::Config(const char* filename)
{
	config.open(filename);
	if(!config.is_open())
	{
	#ifdef _WIN32
		MessageBox(NULL, "Error Opening Config.ini. This file should be located in the same directory as the executable", "Config Error", MB_OK | MB_ICONERROR);
	#else
		std::cout << "Error Opening Config File" << std::endl;
	#endif
	}
	config >> header;
	config >> window >> title;	
	config >> w >> a;	
	config >> h >> b;
	config >> BPP >> c;
	config >> f >> v;
	width = a;
	height = b;
	bpp = c;
}

void Config::writeTo()
{

}

Config::~Config(void)
{
	config.close();
}

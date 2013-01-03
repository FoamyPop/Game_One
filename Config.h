#pragma once

#include <string>
#include <fstream>

#ifdef _WIN32
#include <Windows.h>
#endif

class Config
{
public:
	Config(const char* filename);
	int SCREEN_WIDTH()
	{
		return width;
	}
	int SCREEN_HEIGHT()
	{
		return height;
	}
	int SCREEN_BPP()
	{
		return bpp;
	}
	int fullscreen()
	{
		return v;
	}
	std::string TITLE()
	{
		return title;
	}
	~Config(void);
	void writeTo();
private:
	std::ifstream config;
	int width;
	int height;
	int bpp;
	std::string header;
	std::string window;
	std::string title;
	std::string w;
	std::string h;
	std::string BPP;
	std::string f;
	int a;
	int b;
	int c;
	int v;
};
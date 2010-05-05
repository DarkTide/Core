/****************************************************************************
 *      color_console.h: A console coloring utility
 *      This is part of the yafray package
 *      Copyright (C) 2010 Rodrigo Placencia Vazquez
 *		(pixel_t class wa originally written by someone else, don't know exactly who)
 *
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2.1 of the License, or (at your option) any later version.
 *
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 *
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library; if not, write to the Free Software
 *      Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
 
#ifndef Y_COLOR_CONSOLE_H
#define Y_COLOR_CONSOLE_H

#include <iostream>
#ifdef _WIN32
	#include <wincon.h>
#endif

__BEGIN_YAFRAY

typedef unsigned int yColor;

enum
{
#if !defined(_WIN32)
	Black,
	Red,
	Green,
	Yellow,
	Blue,
	Magenta,
	Cyan,
	White,
	Default
#else
	Black 		= 0x0000,
	Red			= FOREGROUND_RED,
	Green		= FOREGROUND_GREEN,
	Yellow		= FOREGROUND_RED | FOREGROUND_GREEN,
	Blue		= FOREGROUND_BLUE,
	Magenta		= FOREGROUND_BLUE | FOREGROUND_RED,
	Cyan		= FOREGROUND_BLUE | FOREGROUND_GREEN,
	White		= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	Default		= 0xFFFF;
#endif
};

struct setColor
{
	setColor() : fgCol(Default), bgCol(Default), intense(false) {}
	setColor(yColor fgColor, yColor bgColor, bool intensecolor = false)
	{
		#ifdef _WIN32
		fgCol = fgColor;
		bgCol = (bgColor != Default) ? bgColor << 4 : Default;
		#else
		fgCol = (fgColor != Default) ? fgColor + 30 : Default;
		bgCol = (bgColor != Default) ? bgColor + 40 : Default;
		#endif
		intense = intensecolor;
	}
	setColor(yColor fgColor, bool intensecolor = false)
	{
		#ifdef _WIN32
		fgCol = fgColor;
		#else
		fgCol = (fgColor != Default) ? fgColor + 30 : Default;
		#endif
		bgCol = Default;
		intense = intensecolor;
	}
	
	yColor fgCol;
	yColor bgCol;
	bool intense;
};


std::ostream &operator<<(std::ostream& o, const setColor& c);

__END_YAFRAY

#endif

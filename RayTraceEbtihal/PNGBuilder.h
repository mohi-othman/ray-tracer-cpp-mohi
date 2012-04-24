//Class to generate PNG image from view.
//Uses boost::gil and pnglib

#ifndef PNGBUILDER_H
#define PNGBUILDER_H

#include "View.h"
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>
#include <iostream>
#include "Globals.h"

class PNGBuilder
{
public:
	void GeneratePNG(View v, const char *filename);
	void GenerateDepth(View v, const char *filename);
};

#endif
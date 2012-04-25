#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL

#include "PNGBuilder.h"


using namespace std;
using namespace boost::gil;

//Generate PNG image of the rendered scene
void PNGBuilder::GeneratePNG(View v, const char *filename)
{
	int width = v.Width;
	int height = v.Height;	
	
	rgb8_image_t img(width, height);       
	
	for(int y = 0; y<height; y++)
	{
		for(int x = 0; x<width; x++)		
		{			
			Vector3D clr = v.GetPixel(x,y).color.ConvertToRGBValue();
			
			rgb8_pixel_t p(clr.x, clr.y, clr.z);

			view(img)(x,y) = p;
			
		}

	}

	png_write_view(filename, const_view(img));
}

//Generate grayscale depth image of the rendered scene
void PNGBuilder::GenerateDepth(View v, const char *filename)
{
    //Get minimum and maximum depth
	int width = v.Width;
	int height = v.Height;	
	float maxDepth = 0;
	float minDepth = INFINITY;

	for(int y = 0; y<height; y++)
	{
		for(int x = 0; x<width; x++)		
		{			
			float depth = v.GetPixel(x,y).depth;

			if(depth < INFINITY)
            {
				maxDepth = Max(depth, maxDepth);
                minDepth = Min(depth, minDepth);
            }
		}
	}
    
    //create buffer zone around depths for better looking image
    minDepth--;
    maxDepth++;

	rgb8_image_t img(width, height);       
	
	for(int y = 0; y<height; y++)
	{
		for(int x = 0; x<width; x++)		
		{			
			float clr;
			float depth = v.GetPixel(x,y).depth;
			if(depth < INFINITY)
				clr = (1 - ((depth-minDepth) / (maxDepth-minDepth))) * 256;
			else
				clr = 0;
			
			rgb8_pixel_t p(clr, clr, clr);
			
			view(img)(x,y) = p;
			
		}

	}

	png_write_view(filename, const_view(img));
}



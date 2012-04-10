//Class for storing colors

#ifndef COLOR_H
#define COLOR_H

#include "Vector3D.h"

class Color
{
public:
    struct {float r,g,b;};

    //Zeroed out constructor
    Color() : r(0.0f), g(0.0f), b(0.0f) {};     

    //Specific color constructor    
    Color(float Red, float Green, float Blue) : r( Red ), g( Green ), b( Blue ) {};	

    //Converts to 0-255 RGB values
    Vector3D ConvertToRGBValue()
    {
        float R = r * 255;
        float G = g * 255;
        float B = b * 255;

        R = (R < 0 ? 0 : R);
        G = (G < 0 ? 0 : G);
        B = (B < 0 ? 0 : B);

        R = (R > 255 ? 255 : R);
        G = (G > 255 ? 255 : G);
        B = (B > 255 ? 255 : B);

        return Vector3D(floor(R), floor(G), floor(B));
    }
    
    //Operator overloads
    friend Color operator + ( const Color& c1, const Color& c2 )    { return Color( c1.r + c2.r, c1.g + c2.g, c1.b + c2.b ); }
    friend Color operator + ( const Color& c1, Color* c2 )          { return Color( c1.r + c2->r, c1.g + c2->g, c1.b + c2->b ); }
    void operator += ( Color& C ) { r += C.r; g += C.g; b += C.b; }
    void operator += ( Color* C ) { r += C->r; g += C->g; b += C->b; }

    friend Color operator - ( const Color& c1, const Color& c2 )    { return Color( c1.r - c2.r, c1.g - c2.g, c1.b - c2.b ); }
    friend Color operator - ( const Color& c1, Color* c2 )          { return Color( c1.r - c2->r, c1.g - c2->g, c1.b - c2->b ); }
    void operator -= ( Color& C ) { r -= C.r; g -= C.g; b -= C.b; }
    void operator -= ( Color* C ) { r -= C->r; g -= C->g; b -= C->b; }

    friend Color operator * ( float s, const Color& c2 )            { return Color( s * c2.r, s * c2.g, s * c2.b ); }
    friend Color operator * ( const Color& c2, float s)             { return Color( s * c2.r, s * c2.g, s * c2.b ); }
    friend Color operator * ( const Color& c1, const Color& c2 )    { return Color( c1.r * c2.r, c1.g * c2.g, c1.b * c2.b ); }
    friend Color operator * ( const Color& c1, Color* c2 )          { return Color( c1.r * c2->r, c1.g * c2->g, c1.b * c2->b ); }
    void operator *= ( Color& C ) { r *= C.r; g *= C.g; b *= C.b; }
    void operator *= ( Color* C ) { r *= C->r; g *= C->g; b *= C->b; }



};
#endif
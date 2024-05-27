#ifndef _FUNC
#define _FUNC

int IsBinding(Texture2D _tex)
{
    int width = 0; int height = 0;
    _tex.GetDimensions(width, height);
    
    if(0 == width || 0 == height)
        return false;
    
    return true;
}

#endif
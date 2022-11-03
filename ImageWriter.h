#ifndef IMAGEWRITER_H
#define IMAGEWRITER_H

#include "Helper.h"
class ImageWriter
{
public:
    bool        IsAvailable     ( void );
    QString     GetLastError    ( void );
    bool        WriteTiff       (  const tFrameInfo &frame, const char* filename);
};

#endif // IMAGEWRITER_H

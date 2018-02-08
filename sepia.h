//
//  sepia.hpp
//  a4q3
//
//  Created by Enze Si on 2017-11-16.
//  Copyright © 2017 Enze Si. All rights reserved.
//

#ifndef sepia_h
#define sepia_h

#include "decorator.h"

class Sepia: public Decorator {
    public:
    Sepia(Image* image): Decorator{image} {}
    void render(PPM &ppm) override;
};


#endif /* sepia_h */

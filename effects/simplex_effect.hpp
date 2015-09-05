//The MIT License (MIT)
//
//Copyright (c) <2012>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this 
// software and associated documentation files (the "Software"), to deal in the Software 
// without restriction, including without limitation the rights to use, copy, modify, 
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
// permit persons to whom the Software is furnished to do so, subject to the following 
// conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
// CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
// OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// 
// ===============================================================================
// The original Java code was placed in the public domain by its original author,
// Stefan Gustavson. You may use it as you see fit,
// but attribution is appreciated.
//
// -Based on example code by Stefan Gustavson (stegu@itn.liu.se).
// -Optimisations by Peter Eastman (peastman@drizzle.stanford.edu).
// -Better rank ordering method by Stefan Gustavson in 2012.
// -C++ port and minor type and algorithm changes by Josh Koch (jdk1337@gmail.com).
// -Modified by Daniel Williams (daniel.mcclintic.williams@gmail.com)
//    Adapted to use GL Math vectors, 
//    added comments
//    Added randomization of gradient array
//
//

#ifndef __SIMPLEX_HPP__
#define __SIMPLEX_HPP__

#include "terrain_effect.hpp"

namespace MeshGen{

    class TerrainMap;

    class SimplexEffect: public TerrainEffect {
    protected:
	float persistence = 0.8;
	float frequency = 0.95/mesh->scale;

    public:
	SimplexEffect();

	void init();

	void set_persistence( const float _persistence);
	void set_frequency( const float _frequency);

	virtual void apply_effect(const int num, const float min_scale, const float max_scale);
	
    private:

    
    }; // class

} // namespace
#endif

//The MIT License (MIT)
//
//Copyright (c) <2013>
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
// =====================
// Author:
//       Daniel Williams
//


#ifndef __TERRAIN_EFFECT_HPP__
#define __TERRAIN_EFFECT_HPP__
#include "../asteroid.hpp"


namespace MeshGen {

    class TerrainEffect{
    protected:
	const static int name_string_size=128;
	static char name[name_string_size];

	Mesh * mesh;
	ivec2 map_width_u;
	float map_cell_size_m;
	float effect_scale_factor_m;

    public:
	TerrainEffect();
	virtual ~TerrainEffect();
	void setMesh(Mesh * _map);
	virtual void apply_effect(const int num, const float min_scale, const float max_scale)=0;
	
    };
}
#endif //#define __TERRAIN_EFFECT_HPP__

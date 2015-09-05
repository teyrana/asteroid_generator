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
// =====================
// Author:
//       Daniel Williams
//

#ifndef __TERRAIN_CELL_HPP__
#define __TERRAIN_CELL_HPP__
#include "common.hpp"
#include "Atmosphere.hpp"

namespace MeshGen {

    class TerrainCell: public MeshNode {
    public:

        // this is a divisor:
	//    dirt is eroded at a rate of 1
	//    rock at a rate of 1/hardness
	static const float rock_hardness;
	static const float sea_level;

    public:
	// in ascending height order:   rock <= dirt <= water
	float rock;  // hard material.  generically bedrock
	float dirt;  // all soft material.
	float water; // height of water surface water.
	// if water <= dirt, this implies no water.
	// indications amount of plant cover on this ground
	// [0,1]: % of water absorbed into water table instead of erosion process.
	// may also effect velocity
	float ground_cover;
	
	enum value_t {VAL_ROCK, VAL_DIRT, VAL_WATER, VAL_GND_COVER};
	enum limit_t {LIMIT_UPPER, LIMIT_LOWER};
    public: 
	// ====== ====== ====== ====== Gets / Sets ====== ====== ====== ======
	    
	// remove all standing water from this cell
	TerrainCell* desicate();
	float erode(float dirt);

	float inline getMax(){
	    return std::max(std::max(rock, dirt), water);}

	float inline getMin(){
	    return std::min(std::min(rock, dirt), water);}

	float inline getWaterDepth(){
	    return water - dirt;}

	void set_zero();
	void set_max();
	void set_min();

	void set(float _val);

	TerrainCell* set(float rock, float dirt, float water);
	TerrainCell* set(TerrainCell* other);
	TerrainCell* set_dirt(float new_dirt_height);
		
	TerrainCell* add(TerrainCell* other);
	TerrainCell* add(float scalar);
	TerrainCell* div(float divisor);
	TerrainCell* mult(float factor);
	TerrainCell* mult(TerrainCell* other);

	TerrainCell* subt(const TerrainCell * other);
	TerrainCell* subt(float scalar);

	TerrainCell* test_max(TerrainCell* other);
	TerrainCell* test_min(TerrainCell* other);
	void clamp_water_level();
	TerrainCell* clamp(value_t field_id, float rval, limit_t limit_type);
	TerrainCell* clamp_all(const float lower_limit, const float upper_limit);
	TerrainCell* set_lower_limit(const float lower_limit);
	TerrainCell* set_upper_limit(const float upper_limit);
	void print(FILE* targ, const char* msg, const int xi, const int yi);
    };
	
}

#endif // #ifndef __TERRAIN_CELL_HPP__

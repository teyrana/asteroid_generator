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


#include "Terrain.hpp"
using namespace std;
using namespace MeshGen;

const float TerrainCell::rock_hardness=20.0f;
const float TerrainCell::sea_level=0.0f;

// ====== ====== ====== ====== Functions ====== ====== ====== ======

// ====== ====== ====== ====== Sets ====== ====== ====== ======

void TerrainCell::set_zero(){ 
    dirt=0; rock=0; water=0;}

void TerrainCell::set(float _val){
    dirt = _val;rock = _val;water = _val;}
void TerrainCell::set_max(){
	set(numeric_limits<float>::max());}

void TerrainCell::set_min(){
	set(numeric_limits<float>::min());}

TerrainCell* TerrainCell::set_dirt(float new_dirt_height){
    dirt = new_dirt_height;
    if(rock > dirt){
        rock = dirt;}
    return this;
}

TerrainCell* TerrainCell::set(float _rock, float _dirt, float _water){
	dirt = _dirt;
	rock = _rock;
	water = _water;
	return this;
}

TerrainCell* TerrainCell::set(TerrainCell* other)
{
    dirt = other->dirt;
    rock = other->rock;
    water = other->water;
    return this;
}

// ====== ====== ====== ====== Operators ====== ====== ====== ======
TerrainCell* TerrainCell::add(TerrainCell* other){
    dirt +=other->dirt;
    rock +=other->rock;
    water += other->water;
    return this;
}

TerrainCell* TerrainCell::add(float scalar){
    dirt +=scalar;
    rock +=scalar;
    water +=scalar;
    return this;
}

TerrainCell* TerrainCell::div(float divisor){
    rock /= divisor;
	dirt /= divisor;
	water /= divisor;
	return this;
}

TerrainCell* TerrainCell::mult(float factor){
    dirt *=factor;
    rock *=factor;
    water *=factor;
    return this;
}

TerrainCell* TerrainCell::mult(TerrainCell* other){
    dirt *= other->dirt;
    rock *= other->rock;
    water *= other->water;
    return this;
}

TerrainCell* TerrainCell::subt( const TerrainCell * other){
    dirt -= other->dirt;
    rock -= other->rock;
    water -= other->water;
    return this;
}

TerrainCell* TerrainCell::subt(float scalar){
    dirt -= scalar;
    rock -= scalar;
    water -= scalar;
    return this;
}


// ====== ====== ====== ====== Other Methods ====== ====== ====== ======
void TerrainCell::clamp_water_level(){
	// preserve sea level
	clamp(VAL_WATER, sea_level, LIMIT_LOWER);
	// ensure water is at least as high as ground level
	clamp(VAL_WATER, dirt, LIMIT_LOWER);
}

TerrainCell* TerrainCell::clamp(value_t field_id, float clamp_value, limit_t limit_type){
	float * lval;
	switch(field_id){
	case VAL_ROCK: lval = &rock; break;
	case VAL_DIRT: lval = &dirt; break;
	default:
	case VAL_WATER: lval = &water; break;
	case VAL_GND_COVER: lval = &ground_cover; break;
	}

	if(LIMIT_UPPER==limit_type){
		if(*lval > clamp_value){
			*lval = clamp_value;
		}
	}else if(LIMIT_LOWER==limit_type){
		if(*lval < clamp_value){
			*lval = clamp_value;
		}
	}
	return this;
}

TerrainCell* TerrainCell::clamp_all(const float lo_limit, const float up_limit){
	set_lower_limit(lo_limit);
	set_upper_limit(up_limit);
	return this;
}

TerrainCell* TerrainCell::desicate(){
	water = dirt;
	return this;
}

float TerrainCell::erode(const float ds){
	float dirt_here = dirt - rock;
	if(ds < dirt_here){
		dirt -= ds;
		return ds;
	}else{
		float rock_eroded = (ds - dirt_here)/rock_hardness;
		rock -= rock_eroded;
		dirt = rock;
		return rock_eroded + dirt_here;
	}
}

void TerrainCell::print(FILE* targ, const char* msg, const int xi, const int yi){
	fprintf(logfile, "%s:[% 3d, % 3d]:(%8.4g/%8.4g/%8.4g)\n", msg,  xi, yi, rock, dirt, water);	
}

TerrainCell* TerrainCell::test_max(TerrainCell* other)
{
    if (other->dirt > dirt) {
        dirt = other->dirt;
    }
    if (other->rock > rock) {
        rock = other->rock;
    }
    if (other->water > water) {
        water = other->water;
    }
            
    return this;
}

TerrainCell* TerrainCell::test_min(TerrainCell* other)
{
    if (other->dirt < dirt) {
        dirt = other->dirt;
    }
    if (other->rock < rock) {
        rock = other->rock;
    }
    if (other->water < water) {
        water = other->water;
    }
            
    return this;
}

TerrainCell* TerrainCell::set_lower_limit(const float lower_limit){
	dirt = std::max(dirt, lower_limit);
    rock = std::max(rock, lower_limit);
    water = std::max(rock, lower_limit);
	return this;
}

TerrainCell* TerrainCell::set_upper_limit(const float upper_limit){
    dirt = std::min(dirt, upper_limit);
    rock = std::min(rock, upper_limit);
    water = std::min(rock, upper_limit);
    return this;
}

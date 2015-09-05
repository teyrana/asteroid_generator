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


#ifndef __EROSION_EFFECT_HPP__
#define __EROSION_EFFECT_HPP__

#include "terrain_effect.hpp"
#include "../Atmosphere.hpp"

using namespace MeshGen;

namespace MeshGen{

    // ====== // ======  Velocity Cell // ====== // ======
    struct VelocityCell{
	vec3 velocity;
    };
    
    // ====== // ======  WindCell // ====== // ======
    class WindCell{
    public:
	vec3 velocity;
	float azimuth_r; // direction of departure from this cell
        float flow;  // i.e. volume flow rate
        
	WindCell* set(float _az_r, float _flow){
            azimuth_r = _az_r; flow = _flow; return this; }
    };

    class ErosionEffect: public TerrainEffect {
	
	// ====== ====== Overhead ====== ====== 
    protected:
	VelocityCell* velocityMap;
	
	// moore neighborhood
	static const int moore_neighborhood_count;
	static const int moore_neighborhood_list[8][2];

    // ====== ====== Erosion Functions Functions ====== ====== 
    protected:
	// hydraulic erosion
	static const int gradient_length=2;
	
	static const int erode_water_scale_factor=6;
	
	int erode_water_iteration_max;
        float erode_precip_rate_myr; // precipitation rate.  how much water from each iteration
	float erode_precip_rate_stddev_u;
        int erode_precip_freq; // precipitation frequency.  how many iterations between preciptiation
        float erode_rate_coef; 
        //float erode_rate_scale;
	float erode_rate_exp;
	//float erode_scale_water_u;
        float evap_rate_myr; // evaporation rate.  how much water from each iteration
        float evap_ratio;
        float sea_level_m;  // sea level is at 0 altitude;  in native format

        int erode_wind_iteration_max;
	static const int erode_wind_scale_factor=6;
        float erode_wind_atmo_density_kgm3;
        float erode_wind_azimuth_r;
        float erode_wind_flow_m3s;

	float erode_grav_gravity_mss;

	// ====== ====== External Functions ====== ====== 
    public: 
	ErosionEffect();
	virtual ~ErosionEffect();
	
	void applyWaterErosion();
	void applyWindErosion();
	vec3& getVelocity(const int xi, const int yi);
	void setVelocity(const int xi, const int yi, const vec3 & _in);
	void printVelocity(const char* msg, const int xi, const int yi);
	virtual void setAtmosphere( Atmosphere * atmo);
	
	float calculate_gradient_x(int x_i, int y_i);
	float calculate_gradient_y(int x_i, int y_i);
    };

}
#endif // #ifdef __EROSION_EFFECT_HPP__

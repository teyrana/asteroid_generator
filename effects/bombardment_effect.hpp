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
#ifndef __COLLISION_EFFECT_HPP__
#define __COLLISION_EFFECT_HPP__

#include "terrain_effect.hpp"

namespace MeshGen{

    class Crater{
    private:
	// generation paramaters

        static const float depth_param; // non-dimensional version
        static const float impact_energy_bias;
        static const float radius_effect_param; // includes ejecta.  // non-dimensional version
        static const float rim_height_param; // non-dimensional version
        static const float radius_param;
	static const float striation_magnitude;
        static const float striation_freq;
        static const float striation_subfreq;
		

	vec3 impact_normal_n;
	vec3 impact_point_m;
	vec3 impact_path_n;
        float depth_crater_m; // units: meters
	bool energy_set;
	vec3 gravity_n;
	float gravity_mag_g;
        float impact_energy_MT;   // units: MegaTons
        bool location_set;
	// Radius of the crater itself. 
        float radius_crater_m; // units: meters
        // radius of terrain to affect
        float radius_effect_m;   // units: meters
        float rim_height_m; // units:meters


    public:
	// ====== ====== ====== Calculate Methods ====== ====== ======
	void apply_delta_at( vec3 & target_location_m, const vec3 target_normal_n, const vec3 target_gravity_n);
    public:
	// ====== ====== ====== sets ====== ====== ======
	void set_energy(float input, float impact_energy_min, float impact_energy_max);
	void set_center( const float _x_impact, const float _y_impact, const float _z_impact);
	void set_center( const vec3 _impact_xyz);
	void set_gravity( const vec3 _gravity_vector_g, const float _gravity_mag_g );
	void set_normal( const vec3 _normal_n );
	
        Crater* reset();
	
    public:
	// ====== ====== ====== ====== gets ====== ====== ====== ======
	float get_crater_radius(){return radius_crater_m;}
	float get_crater_depth(){return depth_crater_m;}
	float get_radius_effect(){return radius_effect_m;}
	float get_impact_energy_MT_TNT(){return impact_energy_MT;}
	float get_impact_energy_J(){return impact_energy_MT*((float)4.184e15);}
	void print_info( FILE* dest);
	
    public:
	// ====== ====== ====== ====== Constructors ====== ====== ====== ======
	Crater();
	~Crater();
	
    };

    class BombardmentEffect: public TerrainEffect {
    public:
	BombardmentEffect();
	~BombardmentEffect();
	
	void ApplyMeteorImpacts(
	    const int impact_count = 550,
            const float impact_energy_min= 0.06, 
            const float impact_energy_max= 1.8);
	virtual void apply_effect( const int num, const float min_scale, const float max_scole);
    };

}

#endif //#ifndef __BOMBARDMENT_HPP__

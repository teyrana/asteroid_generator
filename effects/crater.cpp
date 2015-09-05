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

#include "../common.hpp"
#include "bombardment_effect.hpp"
#include "simplexnoise.hpp"
using namespace MeshGen;

const float Crater::radius_param = 190.0f;
const float Crater::depth_param = -0.16f; 
const float Crater::rim_height_param = 0.21f;
const float Crater::radius_effect_param = 4.0f;
const float Crater::impact_energy_bias = 16.0f;
        
Crater::Crater()
    :impact_point_m( vec3(0,0,0)),
     impact_path_n( vec3(0,1,0)),
     depth_crater_m(0),
     energy_set(false),
     gravity_n( vec3(1,0,0)),
     gravity_mag_g( 1.0f),
     impact_energy_MT(0),
     location_set(false),
     radius_crater_m(0),
     radius_effect_m(0),
     rim_height_m(0)
{
    reset();
}

Crater::~Crater(){
}

// ====== ====== ====== ====== Methods ====== ====== ====== ======

void Crater::apply_delta_at( vec3 & target_point_m, const vec3 target_normal_n, const vec3 target_gravity_n){

    vec3 target_direction_m = target_point_m - impact_point_m;
    float distance_m =  glm::length( target_direction_m );

    if (distance_m > radius_effect_m){
	return; // nothing to be done.
    }

    // (1) calculate preliminary numbers
    //vec3 target_direction_n = normalize(target_direction_m);
    float distance_n = distance_m / radius_crater_m;
    vec3 targ_dir_perp_m = target_direction_m - dot( impact_normal_n, target_direction_m)*impact_normal_n;
    //float distance_perp_m = length(targ_dir_perp_m);
    float targ_dist_perp_n = length(targ_dir_perp_m)/ radius_crater_m;
    float azimuth_d = atan2(target_point_m.x, target_point_m.z)/M_PI*180;

    //fprintf( stdout, "  pre = ( %g, %g, %g)=%g \n", target_point_m.x, target_point_m.y, target_point_m.z, distance_m);
    //fprintf( stdout, "  lat = ( %g, %g, %g)=%g \n", targ_dir_perp_m.x, targ_dir_perp_m.y, targ_dir_perp_m.z, glm::length(targ_dir_perp_m));

    
    // (2) Add random noise
    const float octave_count = 2;
    const float persistence = 0.96;

    //shuffle_permutation_table( 2, time(NULL));

    // (3) Calculate Parabolic Excavation Term
    // y = cd * (d**2 - radius_peak);
    // -- excavation should be wrt normal
    // 1) impact point is at parabola's focus
    // 2) crater bottom is at x=0, y=-crater_depth, sideways = 0;
    // 3) crater/surface intersect is at x=radius_peak_tune, y=0; sideways = 0;
    const float crater_depth= 0.28f;
    const float radius_peak_tune_excavation = 0.9f;
    const float shape = 1/pow(radius_peak_tune_excavation, 2);

    // equivalent to crater depth on a flat plain
    float excavation_magnitude_m = radius_crater_m*crater_depth*( shape*pow(targ_dist_perp_n, 2) - 1); // crater floor

    // (4) calculate excavation noise, and opply
    const float excavation_noise_frequency = 1.55 / radius_crater_m;
    const float excavation_noise_scale = 0.02*radius_crater_m;
    float noise_exc_m = distance_n*distance_n*excavation_noise_scale*octave_noise_2d( octave_count, persistence, excavation_noise_frequency,
					     azimuth_d, distance_m/12);
    vec3 new_point_excavation_m = impact_point_m + targ_dir_perp_m + (excavation_magnitude_m+noise_exc_m)*impact_normal_n;

    // (5) Calculate Pushback Slope Terms
    // -- also wrt local normal
    const float peak_height= 0.12;
    const float radius_peak = 1.0;
    const float slope = -2.5f;
    float pushback_magnitude_m = radius_crater_m*peak_height*exp( slope*(distance_n - radius_peak) );

    // (6) calculate noise, and opply
    float pushback_noise_frequency = 2.6 / radius_crater_m;
    const float pushback_noise_scale = 0.45;
    float pushback_noise_n = octave_noise_2d( octave_count, persistence, pushback_noise_frequency,
					     azimuth_d, distance_m/6);
    vec3 new_point_pushback_m = target_point_m + pushback_magnitude_m*(1+pushback_noise_scale*pushback_noise_n)*impact_normal_n;
    
    // (7) calculate heights
    vec3 crater_nadir_m = impact_point_m - impact_normal_n*crater_depth*radius_crater_m;
    //float height_crater_nadir_m = dot(impact_normal_n, crater_nadir_m);
    float height_here_old_m = dot( target_point_m, impact_normal_n);
    float height_here_excavation_m = dot( new_point_excavation_m, impact_normal_n);
    float height_here_pushback_m = dot( new_point_pushback_m, impact_normal_n);

    // DEBUG
    // if ( distance_n < 0.01){
    // 	fprintf( stdout, "  Here = ( %g, %g, %g) \n", target_point_m.x, target_point_m.y, target_point_m.z);
    // 	fprintf( stdout, "          delta = %20.20g \n", height_crater_nadir_m - height_here_new );
    // }

    // (8) use heights to choose new location to use
    if (height_here_old_m > height_here_excavation_m ){
    	target_point_m = new_point_excavation_m;
	return;
    }else if (height_here_excavation_m < height_here_pushback_m){	
	target_point_m = new_point_excavation_m;
	return;
    }else{
	target_point_m = new_point_pushback_m;
	return;
    }

    //vec3 delta_ejecta = -target_gravity_n * radius_crater_m* calculate_magnitude_ejecta_n( distance_n, dist_along_path_n );
    //vec3 total_delta = window_function* (delta_excavation + delta_ejecta);

    //float z_inside = (rim_height_param - depth_param) * (distance_m * distance_m)/radius_crater_m + depth_crater_m + z_center_initial_m;

    //float az_el_correction = cos(elevation_ejecta_r) * cos(azimuth_r - azimuth_ejecta_r) + 1
    //+ striation_magnitude * cos(azimuth_r * striation_freq * cos(azimuth_r * striation_subfreq));
    // (4) calculate ejecta striations
    //float delta_ejecta = calculate_magnitude_ejecta_n( distance_n, 0 ); // const float azimuth_r);


    // control should never reach here
    return;
}


void Crater::print_info( FILE* dest){
    fprintf( dest, "..>>Generating Impact.\n");
    fprintf( dest, "......Impact Energy:          % 6.4g MT TNT\n", impact_energy_MT);
    fprintf( dest, "......Impact position =      [% 6.4g, % 6.4g, % 6.4g] m\n", impact_point_m.x, impact_point_m.y, impact_point_m.z);
    fprintf( dest, "......Impactor path =        [% 6.4g, % 6.4g, % 6.4g] m\n", impact_path_n.x, impact_path_n.y, impact_path_n.z);
    fprintf( dest, "......Gravity Magnitude =     % 3.1gg\n", gravity_mag_g );
    fprintf( dest, "......Gravity direction =    [% 6.4g, % 6.4g, % 6.4g] m\n", gravity_n.x, gravity_n.y, gravity_n.z);
    fprintf( dest, "......Crater Radius =         % 6.4g m\n", radius_crater_m);
    fprintf( dest, "......Effect Radius =         % 6.4g m\n", radius_effect_m);
    //fprintf( dest, "......z_basin, z_rim=    % 6.4g, % 6.4g m\n",  depth_crater_m+z_center_initial_m, rim_height_m+z_center_initial_m);
    //fprintf( dest, "......X Bounds= [% 6.4g, % 6.4g] m\n", (x_impact - radius_effect), (x_impact + radius_effect));
    //fprintf( dest, "......Y Bounds= [% 6.4g, % 6.4g] m\n", (y_impact - radius_effect), (y_impact + radius_effect));
}

Crater* Crater::reset(){
    energy_set = false;
    location_set = false;

    // shuffle the table twice, with seed == current time
    shuffle_permutation_table( 1, time(NULL));

    return this;
}

void Crater::set_center(float _x_impact, float _y_impact, float _z_impact){
    set_center( vec3(  _x_impact, _y_impact,  _z_impact));
}

void Crater::set_center( const vec3 _impact_m){
    impact_point_m = _impact_m;
    location_set=true;
}

// input is where the RNG goes.  input should be between 0 and 1.
void Crater::set_energy(float input, float impact_energy_min, float impact_energy_max){
    if ( input < 0 ){
	input = 0.0f;
    }else if ( input > 1.0f ){
	input = 1.0f;
    }

    //const float impact_energy_bias;
    // units: MegaTons TNT equivalent.  // (1 MT TNT == 4.184 PJ == 4.184e15 J)
    impact_energy_MT = std::exp(input * impact_energy_bias) * impact_energy_max / exp(impact_energy_bias)+impact_energy_min;

    // R ~= root(pow(v,2)*M, 3);   -- Stanyukovich and Fedynsky
    // ==> so ours is faster, and roughly the same.
    //radius_crater_m = radius_param * sqrt(impact_energy_MT) * pow(sin(elevation_ejecta_r), 1/3);  
    radius_crater_m = radius_param * sqrt(impact_energy_MT);
    radius_effect_m = radius_effect_param * radius_crater_m;  // Radius of effect // units: meters
    depth_crater_m = depth_param*radius_crater_m;    // units: meters
    rim_height_m = rim_height_param*radius_crater_m;

    energy_set=true;
    return;
}

void Crater::set_normal( const vec3 _normal_n ){
    if( FLT_MAX < (1-length(_normal_n))){
	this->impact_normal_n = normalize(_normal_n);
    }else{
	this->impact_normal_n = _normal_n;
    }
}

void Crater::set_gravity( const vec3 _gravity_n, const float _gravity_mag_g ){
    gravity_n = normalize(_gravity_n);
    gravity_mag_g = _gravity_mag_g;
}


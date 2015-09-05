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
// see header:  Simplex.hpp
//

#include <glm/gtx/noise.hpp>
#include "simplex_effect.hpp"
#include "simplexnoise.hpp"

using namespace MeshGen;

SimplexEffect::SimplexEffect()
    :persistence (0.8),
     frequency ( 1.0)
{

}

void SimplexEffect::apply_effect(const int num, const float min_scale, const float max_scale){
    const float octave_count = num;

    assert ( max_scale > min_scale);
    float min_noise = FLT_MAX;
    float max_noise = FLT_MIN;

    // fprintf(stdout, "  ?? simplex hills:\n");
    // fprintf(stdout, "               frequency:      %g \n", frequency);
    // fprintf(stdout, "            octave count:      %g \n", octave_count);
    // fprintf(stdout, "             persistence:      %g \n", persistence);
    // fprintf(stdout, "               min scale:      %g \n", min_scale);
    // fprintf(stdout, "               max scale:      %g \n", max_scale);

    shuffle_permutation_table( 2, time(NULL));
    for( uint cur_node_i = 0; cur_node_i < mesh->node_list.size(); cur_node_i++){
        vec3 & here_m = mesh->node_list[cur_node_i].location_m;
	const vec3 normal_here_m = mesh->node_list[cur_node_i].normal_n;

	float noise_value = scaled_octave_noise_3d( octave_count, persistence, frequency, min_scale, max_scale, here_m.x, here_m.y, here_m.z);

	here_m = here_m + normal_here_m* noise_value;

	if( noise_value < min_noise){
	    min_noise = noise_value;
	}
	if( noise_value > max_noise){
	    max_noise = noise_value;
	}

    }

    fprintf(stdout, "                 noise size range:      [%g, %g] (%g) \n", min_noise, max_noise, max_noise-min_noise);
    
    return;
}

void SimplexEffect::set_persistence( const float _persistence){
    this->persistence = _persistence;
}

void SimplexEffect::set_frequency( const float _frequency){
    this->frequency = _frequency;
}

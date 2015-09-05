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

#include <random>

#include "bombardment_effect.hpp"

using namespace MeshGen;

BombardmentEffect::BombardmentEffect(){}
BombardmentEffect::~BombardmentEffect(){}

void BombardmentEffect::apply_effect( const int num, const float min_scale, const float max_scale){
    ApplyMeteorImpacts( num, min_scale, max_scale);
}

void BombardmentEffect::ApplyMeteorImpacts( int impact_count, float impact_energy_min, float impact_energy_max){
// ====== ====== Apply Meteor Impacts: ====== ====== 
// Meteor Impacts are applied with a negative exponential distribution w.r.t energy (i.e. lots of small impacts, very few large ones)
// This distribution is roughly realistic, but hand tuned for looks. This distribution may be modified by the crater class parameters.
// 
// Asteroid:          Energy (MT)      Radius(m)    Depth(m)    Rim Height(M)
// ------------------------------------------------------------------------------------------
// 9942 Apophis         510 MT         n/a
// Barringer Crater:     3-10 MT       593 m        170         45
// Chicxulub Crater:     96 TT         60 km
//
//
// MT == Megatons TNT equivalent == 4184 GJ
//
// Physics:
//   [1] "Earth Impact Effects Program: A Web-based computer program for calculating the 
//   regional environmental consequences of a meteoroid impact on
//   Earth". Gareth S. COLLINS, H. Jay MELOSH, and Robert A. MARCUS.
//   Metorites and Planetary Science 40, Nr 6, 817-840
//   http://impact.ese.ic.ac.uk/ImpactEffects/effects.pdf
// n.b.   Elongated crater structures are expected only at impacts at angles lower than 12 degrees from the horizontal. 

    assert( mesh->node_list.size() > 0);
    
    float impact_energy_max_seen = 0;
    Crater impact;
    
    fprintf(logfile, "..>>Generating %d Impacts\n", impact_count);
    fflush(logfile);

    // the Mersenne Twister with a popular choice of parameters
    // in C++11 #include <random>
    // random number generator (rng) *only* for crater placement
    std::mt19937 index_rng;
    std::mt19937 energy_rng;
    std::uniform_int_distribution<uint> index_distribution( 0, mesh->node_list.size());
    std::exponential_distribution<double> energy_dist( 3.5f); // param=lambda
    index_rng.seed( time(NULL));
    energy_rng.seed( time(NULL));

    for (int impact_num =0; impact_num < impact_count; impact_num++){
	impact.reset();

	//fprintf(logfile, "    >> Generating Impact #%d\n", impact_num );
	//fprintf(stdout, "    >> Generating Impact #%d\n", impact_num );

	// randomly select a vertex
	uint random_node_index = index_distribution( index_rng );

	//fprintf(stdout, "       at index:  # %d\n", random_node_index);
	MeshNode & impact_node = mesh->node_list[random_node_index];
	vec3 & impact_location_m = impact_node.location_m;

	//fprintf( stdout, "     ?? vert %u/%lu= [%g, %g, %g] (m) \n", vertex_i, mesh->vertex_list.size(), impact_location_u.x, impact_location_u.y, impact_location_u.z);
	impact.set_center( impact_location_m );	
	impact.set_normal( impact_node.normal_n);
	float gravity_magnitude_g = 1.0f;
	const vec3 & gravity_direction_n = impact_node.gravity_n;
	impact.set_gravity( impact_node.gravity_n, gravity_magnitude_g );

	// randomly generate impact_energy
	float impact_energy = energy_dist( energy_rng );
        impact.set_energy(impact_energy, impact_energy_min, impact_energy_max);
        //float radius_effect_m = impact.get_radius_effect();
        if (impact_energy > impact_energy_max_seen) {
            impact_energy_max_seen = impact_energy;
        }

	// DEBUG
	//impact.print_info( stdout);
	
	//fprintf( stdout, "     ?? vert %u/%lu= [%g, %g, %g] (m) \n", vertex_i, mesh->vertex_list.size(), impact_location_u.x, impact_location_u.y, impact_location_u.z);
	//fprintf( stdout, "     ?? vert %u/%lu= [%g, %g, %g] (m) \n", vertex_i, mesh->vertex_list.size(), impact_location_m.x, impact_location_m.y, impact_location_m.z);

        for (uint cur_node_i = 0; cur_node_i < mesh->node_list.size(); cur_node_i++){
	    vec3& cur_vert_n = mesh->node_list[ cur_node_i ].location_m;
	    impact.apply_delta_at( cur_vert_n, -gravity_direction_n, gravity_direction_n);
	}
	
    }

    fprintf(logfile, "        Max Impact Energy Seen: % 6.2g MT\n", impact_energy_max_seen);
    fflush(logfile);
    return;



}


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

#include "volcano_effect.hpp"
using namespace MeshGen;

// ====== // ====== VolcanoEffect.cpp // ====== // ======

// void VolcanoEffect::applyEffect(const int num, const float min_scale, const float max_scale){
	
// 	// float volcano_biggest_seen = 0;
// 	// VolcanoFeature primary;
// 	// VolcanoFeature secondary;

// 	// fprintf(logfile, "  >>Generating %d Volcanoes\n", num);
// 	// fflush(logfile);

// 	// // choose Lava type, and thus, primary feature type
// 	// primary.magma_source.setFelsicArchetype();
// 	// secondary.magma_source = primary.magma_source;
// 	// //	float random_number = ((float) rand())/RAND_MAX;  // check scaling on this.... 

// 	// //for (int impact_num =0; impact_num < num; impact_num++){
// 	// //	//impact.reset();

// 	// //	float random_number = ((float) rand())/RAND_MAX;  // check scaling on this.... 
//  //       float impact_energy = impact.calculate_energy(random_number,  impact_energy_max, impact_energy_min);
//  //       float radius_effect = impact.get_radius_effect();
//  //       if (impact_energy > impact_energy_max_seen)
//  //       {
//  //           impact_energy_max_seen = impact_energy;
//  //       }
// 	//	
//  //       int x_index_impact = (int)(((float)(map_width_x_c-gradient_length*2))*( (float)rand()/((float)RAND_MAX)))+gradient_length;
//  //       int y_index_impact = (int)(((float)(map_width_y_c-gradient_length*2))*( (float)rand()/((float)RAND_MAX)))+gradient_length;
// 	//	float x_impact = ((float)x_index_impact) * cell_size;
//  //       float y_impact = ((float)y_index_impact) * cell_size;
// 	//	
//  //       // these should be guaranteed by the way we generate the x,y impact indices
//  //       check("!! test 01 failed: bombard\n", (x_index_impact >= gradient_length));
//  //       check("!! test 02 failed: bombard\n", (x_index_impact < (map_width_x_c - gradient_length)));
//  //       check("!! test 03 failed: bombard\n", (y_index_impact >= gradient_length));
//  //       check("!! test 04 failed: bombard\n", (y_index_impact < (map_width_y_c - gradient_length)));

// 	//	//float height_impact = map->get( x_index_impact, y_index_impact)->dirt;
// 	//	impact.set_center(x_impact, y_impact, map->get( x_index_impact, y_index_impact)->dirt);

//  //       // calculate the gradient at the impact point:    grad(z) = z_x + z_y
//  //       float grad_x = (map->get(x_index_impact+2,y_index_impact)->dirt - map->get(x_index_impact-2,y_index_impact)->dirt)/4;
//  //       float grad_y = (map->get(x_index_impact,y_index_impact+2)->dirt - map->get(x_index_impact,y_index_impact-2)->dirt)/4;
//  //       impact.calculate_parameters(grad_x, grad_y);

//  //       // calculate nominal bounds
//  //       int xlim_low = x_index_impact - (int)(radius_effect / cell_size);
//  //       int xlim_hi = x_index_impact + (int)(radius_effect / cell_size);
//  //       int ylim_low = y_index_impact - (int)(radius_effect / cell_size);
//  //       int ylim_hi = y_index_impact + (int)(radius_effect / cell_size);
//  //       // only apply bounds within the map
//  //       xlim_low = max(xlim_low, 0);
//  //       ylim_low = max(ylim_low, 0);
//  //       xlim_hi = std::min(xlim_hi, map_width_x_c);
//  //       ylim_hi = std::min(ylim_hi, map_width_y_c);

// 	//	
//  //       //fprintf(logfile, "..>>Generating Impact.\n");
//  //       //fprintf(logfile, "......Impact Energy:          % 6.4g MT TNT\n", impact_energy_j);
//  //       //fprintf(logfile, "......Impact x,y, z=           [% 6.4g, % 6.4g, % 6.4g] m\n", x_center_m, y_center_m, z_center_initial_m);
//  //       //fprintf(logfile, "......Radius of Effect:    % 6.4g m\n", radius_effect_m);
//  //       //fprintf(logfile, "......Impact Radius =   % 6.4g m\n", radius_crater_m);
//  //       //fprintf(logfile, "......z_basin, z_rim=    % 6.4g, % 6.4g m\n",  depth_crater_m+z_center_initial_m, z_center_initial_m, rim_height_m+z_center_initial_m);
//  //       //fprintf(logfile, "......Grad x,y=  [% 6.4g, % 6.4g] m\n", grad_x, grad_y);
//  //       //fprintf(logfile, "......Ejecta Az/El= {0:0.00}/{1:0.00} deg\n", azimuth_ejecta_r * 180 / M_PI, elevation_ejecta_r*180/M_PI );
//  //       ////fprintf(logfile, "......X Bounds= [% 6.4g, % 6.4g] m\n", (x_impact - radius_effect), (x_impact + radius_effect));
//  //       ////fprintf(logfile, "......Y Bounds= [% 6.4g, % 6.4g] m\n", (y_impact - radius_effect), (y_impact + radius_effect));
// 	//	//fprintf(logfile, "     Radius of Effect: %g  m\n", radius_effect);
// 	//	//fprintf(logfile, "     Impact x,y:   [%d, %d]\n", x_index_impact, y_index_impact);
// 	//	//fprintf(logfile, "     grad before impact:   [%g, %g]\n", grad_x, grad_y);
// 	//	//fflush(logfile);

//  //       for (int xi = xlim_low; xi < xlim_hi; xi++){
//  //           for (int yi = ylim_low; yi < ylim_hi; yi++){

//  //               float x = ((float)xi) * cell_size;
//  //               float y = ((float)yi) * cell_size;
//  //               float z = map->get(xi,yi)->dirt;

//  //               float new_z = impact.calculate_new_z(x, y, z);
//  //               map->get( xi,yi)->set_dirt(new_z)->desicate();

//  //           }
//  //       }

// 	//}

// 	fprintf(logfile, "        Biggest Volcano Found: % 6.2g m\n", volcano_biggest_seen);
// 	fprintf(logfile, "  >> Finished creating Volcanoes.\n");fflush(logfile);
// 	return;
	
//}

// void VolcanoEffect::addVolcano(VolcanoFeature * feature){
	
// }

// VolcanoEffect::VolcanoEffect(){

// }

// VolcanoEffect::~VolcanoEffect(){

// }

// ====== // ====== class VolcanoFeature // ====== // ======
// float VolcanoFeature::calculate_viscosity_ER_pas(float phi, float T, float T_ref, float mu_ref){
	// Einstein-Roscoe relation:
	// [1] http://www2.ess.ucla.edu/~jewitt/class/Surfaces_Papers/Griffith_00.pdf

	// $phi0 + phif <= 1$
	// OR: $phi0 + phif = phi_max $

	// T0 == T_ref;
	// mu0 == mu_ref;
	// where phi_0 is the initial (vent) crystal fraction,
	//float phi0=0; // no initial crystallization
	// phif is the total further amount of crystallization that occurs during flow
	//float phi_f; // crystallization rate?  phi_f==phi(t)?
	//float Tsol = 0; //? // Tsol is the solidus temperature.
	// phi(x)  = phi_0 + phi_f(T0-T)/(T0-Tsol);


	// valid for basaltic lavas
	// phi = fraction crystallized
	// T_ref, mu_ref = reference conditions ("such as those at the vent")
	//float phi_max=0.50; // max crystal fraction that allows flow
							// \phi_max ~= 0.45-0.6 for silicate melts
							// measurements: 400-6000 Pas
	//const static float gamma=0.4f; // [1]
	//mu(T,phi) = mu0 * pow(1-phi/phi_max),-2.5)*exp(gamma*(T0-T));
//	return 0;
//}

const char* VolcanoFeature::getFeatureTypeName(volcano_feature_t type){
	static char* toret=0;
	if(0!=toret){
		delete toret; }

	switch(type){
	case FEATURE_CINDER_CONE:
	case FEATURE_PRIMARY_CINDER_CONE: toret = strdup("Cinder Cone Volcano"); break;
	default:
	case FEATURE_PRIMARY_COMPOSITE: toret = strdup("Composite Volcano"); break;
	case FEATURE_PRIMARY_SHIELD: toret = strdup("Shield Volcano"); break;
	case FEATURE_LAVA_DOME: toret = strdup("Lava Dome"); break;
	case FEATURE_LAVA_FLOW: toret = strdup("Lava Flow"); break;
	}
	return toret;
}

VolcanoFeature::VolcanoFeature(){}

VolcanoFeature::~VolcanoFeature(){}

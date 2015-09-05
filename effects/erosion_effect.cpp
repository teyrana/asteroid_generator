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

#include "../Terrain.hpp"
#include "erosion_effect.hpp"

using namespace MeshGen;

// const int ErosionEffect::moore_neighborhood_count=8;
// const int ErosionEffect::moore_neighborhood_list[8][2] = {{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},};

// ErosionEffect::ErosionEffect(){
//     velocityMap = new VelocityCell[map_width_u.x*map_width_u.y];
// }

// ErosionEffect::~ErosionEffect(){
//     if(0!= velocityMap){
// 	delete velocityMap;
//     }
// }

// vec3& ErosionEffect::getVelocity(const int xi, const int yi){
//     return velocityMap[xi*map_width_u.x + yi].velocity;
// }

// void ErosionEffect::setVelocity(const int xi, const int yi, const vec3 & _in){
//     velocityMap[xi*map_width_u.x + yi].velocity = _in;
// }

// void ErosionEffect::printVelocity(const char* msg, const int xi, const int yi){
//     vec3 vel = velocityMap[xi*map_width_u.x+yi].velocity;
//     fprintf(logfile, "%s:[%d, %d]:(%6.4g/%6.4g/%6.4g)\n", msg,  xi, yi, vel.x, vel.y, vel.z);	
// }

// // [1] "Visual Simulation of Hydraulic Erosion" Bedrich Benes and Rafael Forsbach.  Campus Cuidad de Mexico.
// //      http://www2.tech.purdue.edu/cgt/facstaff/bbenes/private/papers/Benes02WSCG.pdf
// // 
// #define NOISE_RAIN
// #define SINGLE_OUTFLOW
// void ErosionEffect::applyWaterErosion(){
//     fprintf(logfile, "..>> Applying Water Erosion \n\n");

//     int xi, yi;

//     // these use the same height units as the height map itself (meters)
//     //float[,] map_water=new float[map_width_u.x, map_width_u.y];
//     //float[,] map_sediment = new float[map_width_u.x, map_width_u.y];
//     //float precipitation = erode_atmo_density * erode_precip_rate;  // unitless
//     //float evaporation = erode_evap_rate;

//     // reset water values to zero depth
//     for (xi = 0; xi < map_width_u.x; xi++) {
//         for (yi = 0; yi < map_width_u.y; yi++) {
// 	    //fprintf(logfile, "    ..>> Initializing Map: %d,%d \n", xi,yi); // fflush(logfile);
// 	    trn->get_ortho(xi,yi)->desicate();
// 	    setVelocity(xi, yi, vec3(1,2,3));
//         }
//     }

//     int erode_cycle_num = 0;
//     for (erode_cycle_num=0; erode_cycle_num < erode_water_iteration_max; erode_cycle_num++) {
        
// 	// 1) Rainfall
//         if (0 == (erode_cycle_num % erode_precip_freq) ){
//             fprintf(logfile, "    ..>> Rain Erosion Iteration: %d \n", erode_cycle_num); fflush(logfile);
//             for (xi = 0; xi < map_width_u.x; xi++) {
//                 for (yi = 0; yi < map_width_u.y; yi++) {
// #ifdef DETERMINISTIC_RAIN
// 		    trn->get_ortho(xi,yi)->water = trn->get_ortho(xi,yi)->water + erode_precip_rate_myr;
// #endif
// #ifdef NOISE_RAIN
// 		    trn->get_ortho(xi,yi)->water = trn->get_ortho(xi,yi)->water + erode_precip_rate_myr
// 		    +erode_precip_rate_myr * (erode_precip_rate_stddev_u*2* ((float)rand()/RAND_MAX)-erode_precip_rate_stddev_u);
// #endif
// #ifdef PERLIN_RAIN
		    
// #endif
//                 }
//             }
//         }else{
// 	    fprintf(logfile, "    ..>> Dry Erosion Iteration: %d \n", erode_cycle_num); fflush(logfile);
// 	}
	
// 	//fprintf(logfile, "    size=[ %d, %d]\n", map_width_u.x, map_width_u.y);
// 	//fprintf(logfile, "    ..>> atmo: 0x%p\n", atmo);
// 	//fprintf(logfile, "    ..>> map:  0x%p\n", map);
// 	//trn->print_cell("    Initial ", 0,0);
// 	//fprintf(logfile, "\n");
// 	//fflush(logfile);

//         // 2) Water Movement (downhill)
//         for (xi = 0; xi < map_width_u.x; xi++) {
//             for (yi = 0; yi < map_width_u.y; yi++) {
// 		TerrainCell* here = trn->get_ortho(xi,yi);
//                 float depth_water_here = here->getWaterDepth();
//                 if( 0.1 > depth_water_here){
// 		    continue;}

// #ifdef ALL_OUTFLOW	
// 		//fprintf(logfile, ">>>>  At: [{0:0.00}, {1:0.00}]",xi,yi));
//                 int adj_index, xi_adj, yi_adj;
//                 float adj_height;
//                 int xi_min = xi, yi_min = yi;
//                 //int xi_min2 = xi, yi_min2 = yi;
//                 float min_adj_water=std::numeric_limits<float>::max();
//                 //float min2_adj_water=std::numeric_limits<float>::max();
//                 // Search all neighbors for the lowest height.
//                 //     when found, record it's number, and indices.
//                 for(adj_index = 0; adj_index < moore_neighborhood_count; adj_index++){
//                     xi_adj = xi +moore_neighborhood_list[adj_index][0];
//                     yi_adj = yi +moore_neighborhood_list[adj_index][1];
//                     //Console.Error.Write(String.Format("      checking adjacency {0:0} at: [{1:0}, {2:0}]", adj_index, xi_adj, yi_adj));
//                     if((xi_adj < 0)||(xi_adj > (map_width_u.x-1))||(yi_adj < 0) || (yi_adj > (map_width_u.y-1)) ){
//                         continue;
// 		    }
//                     adj_height = trn->get_ortho(xi_adj, yi_adj)->water;
//                     //fprintf(logfile, "={0:0.00}", adj_height));
//                     if(adj_height < min_adj_water){
//                         min_adj_water = adj_height;
//                         xi_min = xi_adj;
//                         yi_min = yi_adj;
//                     }else if(adj_height < min2_adj_water){
//                         min2_adj_water = adj_height;
//                         xi_min2 = xi_adj;
//                         yi_min2 = yi_adj;
//                     }
//                 }
				
//                 // if an adjancancy is lower, adjust water
//                 if ( min_adj_water < here->water ) {
                                
//                     // \delta w_i = \delta w \frac{h_i}{sum}
//                     // where $\delta w_i$ is the amount of water to be
//                     // moved to the ith vertex and the $h_i$ is the difference 
//                     // of the lower neighboring vertex.
//                     float dw = (here->water - min_adj_water)/2;
//                     if( dw > (depth_water_here)){
//                         dw = depth_water_here; }
                    
//                     float ds_lin = erode_rate_coef * dw;// * (depth_water_here*depth_water_here);  // vanilla version
// 		    float ds_exp = erode_rate_coef*(exp(-dw) + pow(dw,erode_rate_exp))*depth_water_here;
// 		    fprintf(logfile, "      moving sediment: ds_lin=%6.4g, ds_exp=%6.4g\n", ds_lin, ds_exp);
//                     float ds = ds_lin; 
                    
// 		    //trn->print_cell( "      Here,pre  ", xi,yi);
// 		    //trn->print_cell( "      Adj1,pre  ", xi_min,yi_min);
// 		    //fprintf(logfile, "      moving sediment: dw=%6.4g, depth_water=%6.4g ds=%6.4g\n", dw, depth_water_here, ds);
// 		    //fprintf(logfile, "      chk_01=%g \n", ds);

// 		    trn->get_ortho(xi, yi)->water -= dw;
// 		    ds = trn->get_ortho(xi, yi)->erode(ds);
// 		    trn->get_ortho(xi_min, yi_min)->water += dw;
// 		    trn->get_ortho(xi_min, yi_min)->dirt += ds;
// 		}
// #endif
// #ifdef SINGLE_OUTFLOW
// 		//fprintf(logfile, ">>>>  At: [%d, %d]\n",xi,yi);
//                 int adj_index, xi_adj, yi_adj;
//                 float adj_height;
//                 int xi_min = xi, yi_min = yi;
//                 //int xi_min2 = xi, yi_min2 = yi;
//                 float min_adj_water=std::numeric_limits<float>::max();
//                 //float min2_adj_water=std::numeric_limits<float>::max();
//                 // Search all neighbors for the lowest height.
//                 //     when found, record it's number, and indices.
//                 for(adj_index = 0; adj_index < moore_neighborhood_count; adj_index++){
//                     xi_adj = xi +moore_neighborhood_list[adj_index][0];
//                     yi_adj = yi +moore_neighborhood_list[adj_index][1];
//                     //Console.Error.Write(String.Format("      checking adjacency {0:0} at: [{1:0}, {2:0}]", adj_index, xi_adj, yi_adj));
//                     if((xi_adj < 0)||(xi_adj > (map_width_u.x-1))||(yi_adj < 0) || (yi_adj > (map_width_u.y-1)) ){
//                         continue;
// 		    }
//                     adj_height = trn->get_ortho(xi_adj, yi_adj)->water;
//                     //fprintf(logfile, "={0:0.00}", adj_height));
//                     if(adj_height < min_adj_water){
//                         min_adj_water = adj_height;
//                         xi_min = xi_adj;
//                         yi_min = yi_adj;
// 			//}else if(adj_height < min2_adj_water){
// 			//    min2_adj_water = adj_height;
// 			//    xi_min2 = xi_adj;
// 			//    yi_min2 = yi_adj;
//                     }
//                 }
				
//                 // if an adjancancy is lower, adjust water
//                 if ( min_adj_water < here->water ) {
                                
//                     // \delta w_i = \delta w \frac{h_i}{sum}
//                     // where $\delta w_i$ is the amount of water to be
//                     // moved to the ith vertex and the $h_i$ is the difference 
//                     // of the lower neighboring vertex.
//                     float dw = (here->water - min_adj_water)/2;
//                     if( dw > (depth_water_here)){
//                         dw = depth_water_here; }
                    
//                     float ds_lin = erode_rate_coef * dw;// * (depth_water_here*depth_water_here);  // vanilla version
// 		    //float ds_exp = erode_rate_coef*(exp(-dw) + pow(dw,erode_rate_exp))*depth_water_here;
// 		    //fprintf(logfile, "      moving sediment: ds_lin=%6.4g, ds_exp=%6.4g\n", ds_lin, ds_exp);
//                     float ds = ds_lin; 
                    
// 		    trn->print_cell( "      Here,pre   ", xi,yi);
// 		    trn->print_cell( "      Adj1,pre   ", xi_min,yi_min);
// 		    fprintf(logfile, "      moving sediment: dw=%6.4g, depth_water=%6.4g ds=%6.4g\n", dw, depth_water_here, ds);

// 		    trn->get_ortho(xi, yi)->water -= dw;
// 		    ds = trn->get_ortho(xi, yi)->erode(ds);
// 		    trn->get_ortho(xi_min, yi_min)->water += dw;
// 		    trn->get_ortho(xi_min, yi_min)->dirt += ds;

// 		    trn->print_cell( "      Here,post: ", xi, yi);
// 		    trn->print_cell( "      Adj1,post: ", xi_min, yi_min);
// 		    fprintf(logfile, "      moving sediment: dw=%6.4g, depth_water=%6.4g ds=%6.4g\n", dw, depth_water_here, ds);
// 		    fprintf(logfile, "\n\n");
// 		    fflush(logfile);

// 		}
// #endif

//             }
//         }
//         // debug
	
//         // 3) adjust water depth from evaporation (and sea level)
//         for (xi = 0; xi < map_width_u.x; xi++) {
//             for (yi = 0; yi < map_width_u.y; yi++) {
// 		float depth_water = trn->get_ortho(xi,yi)->getWaterDepth();
//                 float dw = (depth_water )*(evap_ratio) +evap_rate_myr;
// 		if(dw > depth_water){
// 		    dw = depth_water;}
//                 trn->get_ortho(xi,yi)->water += dw;

// 		//trn->get_ortho(xi,yi)->clamp_water_level();
//             }
// 	}

	
//     } // erode iteration

//     fprintf(logfile, "  >> Erosion finished.\n");
//     fprintf(logfile, "\n");
//     return;
// }

// // ====== ====== algo ====== ======
// /// Pseudo Code Algorithm:
// //Step 1:
// //Add prevailing wind to edge of map
// //
// //Steps 2-?:
// //Propogation wind across map:
// //
// //    Step 2:
// //       Compare to upwind cells:
// //
// //       For uphill:
// //           lower wind speed
// //           drop sand (nonlinear)
// //
// //       for downhill
// //           raise wind speed
// //           pick up sand  (nonlinear)
// //           ignore rock
// //
// //      for direction change:
// //           angle = alpha
// //           erode dirt/rock  (propto alpha)
// //
// //
// //Assumption:
// //    (1) Saltation: sand grains bounce along the ground in the wind.
// //        About 95 percent of sand grains move in this manner.
// //        >> Assume all.
// //        test cases:
// //            randomized dirt  + rock) => sand dunes
// //                dirt pillars
// //                rock pillars + dirt
// void ErosionEffect::applyWindErosion(){

//     WindCell** wind = (WindCell**) new WindCell[map_width_u.x*map_width_u.y];

//     WindCell prevailingWind;

//     prevailingWind.azimuth_r=(float)M_PI/6;
//     prevailingWind.flow=10;
//     //prevailingWind.carried=10;
            
//     // ====== Initialization: Zero out wind array
//     for(int xi=0; xi<map_width_u.x; xi++){
//         for(int yi=0; yi<map_width_u.y; yi++){
//             //trn->get_ortho(xi,yi)->check();
//             //setVelocity(xi, yi, vec3(0));
//         }
//     }
            
//     int iteration_num=0;
//     for(iteration_num=0; iteration_num < erode_wind_iteration_max; iteration_num++){
                
//         // ====== Step 1: Insert sand-laden wind onto the windward edge of the map
//         int xi,yi;
//         if(( 0 < prevailingWind.azimuth_r)&&(prevailingWind.azimuth_r < M_PI)){
//             // apply to southern edge
//             yi=map_width_u.y;
//         }else{
//             // apply to northern edge
//             yi=0;
//         }
//         for(xi=0; xi<map_width_u.x; xi++){
//             wind[xi][yi] = prevailingWind;
//         }
                
//         if(((0 < prevailingWind.azimuth_r)&&(prevailingWind.azimuth_r < ((float)0.5f*M_PI))) || 
// 	   (((3/2*M_PI)< prevailingWind.azimuth_r)&&( prevailingWind.azimuth_r < ((float)2.0f*M_PI)))){
//             // apply to western edge
//             xi= map_width_u.x;
//         }else{
//             // apply to eastern edge
//             xi=0;
//         }
// 	for(yi=0; yi<map_width_u.y; yi++){
//             wind[xi][yi] = prevailingWind;
//         }
                
                
//         // propagate wind across map
//         for(xi=0; xi<map_width_u.x; xi++){
//             for(yi=0; yi<map_width_u.y; yi++){
// 		//WindCell delta;//=new WindCell();
                        
// 		// ====== Step 2: calculate flow magnitude change
// 		//float wind_az_here = wind[xi][yi].azimuth_r;
// 		//float sector;
// 		//float clamped_azimuth_r = (float) (M_PI/4.0f) * modf((float)(wind_az_here/(M_PI/4.0f)), sector);

// 		//float weight1 =  cos(clamped_azimuth_r);
// 		//float weight2 =  sin(clamped_azimuth_r);
// //                        [adj1, adj2] <= sector
// //                            [height1, height2] = [adj1, adj2]
// //                            Upwind_height = weight1*height1 + weight2*height2;
// //                        delta.flow = dirt_upwind - dirt_here;
// //                        wind[adj1] += weight1*delta.wind;
// //                        wind[adj2] += weight2*delta.wind;
                        
//                 // ====== Step 3: push grains forward
// //                        delta.carried = delta_flow;
// //                        // WindCell clamp(WindCell to_clamp, TerrainCell criteria)
// //                        delta.carried = clamp(delta.carried, heights[xi,yi]);
// //                        assert((weight1*delta.carried+
// //                                weight1*delta.carried)==delta.carried);
// //                        terr[here] -= delta.dirt;
// //                        terr[adj1] += weight1*delta.dirt;
// //                        terr[adj2] += weight2*delta.dirt;
                        
//                 // ====== Step 4: turn wind sideways


// 		// 4)a) if the azimuth points toward an adjacency, adjust the
// //adjacencies to poll
// //                if(0==az0)_
// //                  adj1i--;
// //                  // wrap adjacency 1 index
// //                  if(-1==adj1i){
// //                      adj1i==7;}
// //                }else if(PI/2 == az0){
// //                   //ditto
// //                }
// //
// //                //4)b)
// //                float dEl = Math.Abs(here_height-upwind_height); //
// //delta_Elevation
// //                If h(adj1) > h(adj2)){
// //                    dAz = 1*dEl;
// //                else
// //                    dAz = -1*dEl;
// //                }
// //
// //                Downwind(adj1) = az_here + dAz;
// //                Downwind(adj1) = az_here + dAz;
// //

                        
//             }
//         }
//         for(xi=0; xi<map_width_u.x; xi++){
//             for(yi=0; yi<map_width_u.y; yi++){
//                 // trn->get_ortho(xi,yi].check(); ?
//                 //if angle of dirt is greater than angle_of_repose (30-34 deg)
//                 //    enforce (Thermal erosion) max slope (need only square adj?)
//                 //ignore rock
//             }
//         }
//     }
// }

// float ErosionEffect::calculate_gradient_x(int x_i, int y_i){
//     float grad = 0.0;

//     if (x_i < gradient_length) {
//         // Take forward differences on left
//         grad = (trn->get_ortho(x_i + gradient_length, y_i)->dirt - trn->get_ortho(x_i, y_i)->dirt) / 2;
//     } else if (x_i > map_width_u.x - gradient_length){
//         // Take backward differences on right
//         grad = (trn->get_ortho(x_i , y_i)->dirt - trn->get_ortho(x_i - gradient_length, y_i)->dirt) / gradient_length;
//     } else {
//         // Take centered differences on interior points
//         grad = (trn->get_ortho(x_i + gradient_length, y_i)->dirt - trn->get_ortho(x_i - gradient_length, y_i - 2)->dirt) / (2*gradient_length);
//     }
//     return grad;
// }

// float ErosionEffect::calculate_gradient_y(int x_i, int y_i){
//     float grad =0.0;

//     if (y_i < gradient_length) {
//         // Take forward differences at start
//         grad = (trn->get_ortho(x_i, y_i+ gradient_length)->dirt - trn->get_ortho(x_i, y_i )->dirt) / gradient_length;
//     } else if (y_i > map_width_u.y - gradient_length){
//         // Take backward differences at end
//         grad = (trn->get_ortho(x_i, y_i)->dirt - trn->get_ortho(x_i, y_i - gradient_length)->dirt) / gradient_length;
//     } else {
//         // Take centered differences on interior points
//         grad = (trn->get_ortho(x_i, y_i - gradient_length)->dirt - trn->get_ortho(x_i, y_i+gradient_length)->dirt) / (2*gradient_length);
//     }
//     return grad;
// }

// void ErosionEffect::setAtmosphere(Atmosphere * _atmo){
//     this->atm = _atmo;
//     fprintf(logfile, "    Setting Erosion Atmosphere Parameters: %s\n", atm->get_climate_t_names(atm->get_climate()));
	 
//     // default values
//     erode_water_iteration_max = 12;
//     erode_precip_rate_myr = atm->precipitation_myr;
//     erode_precip_rate_stddev_u = 0.2f;
//     erode_precip_freq = 1;
//     erode_rate_coef = 1.0f; // values above 1 create artifacting
//     erode_rate_exp = 2.0f;
//     //erode_rate_scale = 0.8f;
//     //erode_scale_water_u=4.0;
//     evap_rate_myr = atm->evaporation_myr;
//     evap_ratio = 0.15f;
	
//     erode_wind_iteration_max=1;
//     erode_wind_atmo_density_kgm3 = atm->density_kgm3;
//     erode_wind_azimuth_r=0; // azimuth in radians
//     erode_wind_flow_m3s = atm->windflow_m3s; // m/s
	
//     erode_grav_gravity_mss = atm->gravity_mss;

// }


//The MIT License (MIT)
//
//Copyright (c) <2015>
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

#include "Atmosphere.hpp"
#include "Terrain.hpp"
#include "effects/bombardment_effect.hpp"
//#include "flat_effects/ErosionEffect.hpp"
//#include "flat_effects/VolcanoEffect.hpp"
//#include "VoronoiDiagramGenerator.hpp"
//#include "float_effects/SimplexEffect.hpp"
using namespace MeshGen;


Terrain::Terrain()
    :topo_type(TOPOLOGY_PLAINS),
     geo_type(GEOLOGY_ROCK),
     scale_factor(100)
{

}

Terrain::~Terrain(){
    //delete heights;
}

void Terrain::calculate_statistics(){
    heights_min.set_max();
    heights_max.set_min();
    heights_mean.set_zero();
    heights_std_dev.set_zero();
    heights_range.set_zero();

    int indexHere=0;
    TerrainCell* here=0;// = new TerrainCell();
    TerrainCell sum;// = new TerrainCell();
    TerrainCell sumsq;// = new TerrainCell();
    sum.set_zero();


    return;
}
	
void Terrain::cull_outliers(){

    // const float crop_threshold = 10;
    // const float std_dev_cull_threshold = 32;

    // calculate_statistics();
    // if ((heights_std_dev.rock < std_dev_cull_threshold)&&
    // 	(heights_std_dev.dirt < std_dev_cull_threshold)&&
    // 	(heights_std_dev.water < std_dev_cull_threshold)){
    //     return;
    // }

    // float height_here;
    // float lo_lim=heights_mean.dirt - crop_threshold*heights_std_dev.dirt;
    // float up_lim=heights_mean.dirt + crop_threshold*heights_std_dev.dirt;
    // int xi=0, yi=0, num_outliers=0;
    // for (xi = 0; xi < map_width_c.x; xi++){
    //     for (yi = 0; yi < map_width_c.y; yi++){
    //         height_here = get_ortho(xi, yi)->dirt;

    //         if (height_here > up_lim){
    // 		get_ortho(xi, yi)->dirt = up_lim;
    //             num_outliers++;
    //         }
    //         if (height_here < lo_lim){
    // 		get_ortho(xi, yi)->dirt = lo_lim;
    //             num_outliers++;
    //         }

    //     }
    // }

    // fprintf(logfile, "....WARNING: standard deviation is too big.  Culled %d outliers.\n", num_outliers);
    // fprintf(logfile, "         Mean [Min, Max]:          %6.4g [ %6.4g, %6.4g ]\n", 
    // 	    heights_mean.dirt, heights_min.dirt, heights_max.dirt);
//    fprintf(logfile, "         Range, standard_deviation   %6.4g, %6.4g \n", heights_range.dirt, heights_std_dev.dirt);
//            fprintf(logfile, "    >> Rock Heights"));
//            fprintf(logfile, "         Mean [Min, Max]:          {0:00} [ {1:0.00}, {2:0.00} ]", 
//                                                  heights_mean.rock, heights_min.rock, heights_max.rock));
//            fprintf(logfile, "         Range, standard_deviation   {0:0.00}, {1:0.00}", heights_range.rock, heights_std_dev.rock));
//            fprintf(logfile, "    >> Water Heights"));
//            fprintf(logfile, "         Mean [Min, Max]:          {0:00} [ {1:0.00}, {2:0.00} ]", 
//                                                  heights_mean.water, heights_min.water, heights_max.water));
//            fprintf(logfile, "         Range, standard_deviation   {0:0.00}, {1:0.00}", heights_range.water, heights_std_dev.water));
//
    return;
}


void Terrain::create_levels( int num_levels = 3, float _new_heights_min = 0){
    // NYI

//            float snap_height = 25;
//
//            if (2 > num_levels)
//            {
//                num_levels = 2;
//                snap_height = 1;
//            }
//            calculate_statistics();
//
//            float level_depth = (heights_range.getMax() - _new_heights_min) / (num_levels - 1);
//            fprintf(logfile, "....Splitting Map into {0:00} levels: ", num_levels));
//            fprintf(logfile, "......Level height increment= {0:0.00} ", level_depth));
//            fprintf(logfile, "......Height Min, Max = [ {0:0.00}, {1:0.00} ]", heights_min, heights_max));
//
//            int xi, yi;
//            for (xi = 0; xi < map_width_x_c; xi++)
//            {
//                for (yi = 0; yi < map_width_y_c; yi++)
//                {
//                    heights[xi,yi].subt(heights_min.getMin());
//                    heights[xi,yi].add(_new_heights_min);
//
//                    for(int lev_i = 0; lev_i < num_levels; lev_i++){
//                        if (Math.Abs(lev_i * level_depth - heights[xi, yi].dirt) < snap_height)
//                        {
//                            heights[xi, yi].set_dirt( lev_i * level_depth);
//                        }
//                    }
//
//                    Debug.Assert(heights[xi, yi].dirt >= 0, "create_levels(...) function failed.");
//                    Debug.Assert(heights[xi, yi].rock >= 0, "create_levels(...) function failed.");
//                    Debug.Assert(heights[xi, yi].water >= 0, "create_levels(...) function failed.");
//                    
//                }
//            }
//           
//            return;
}



const char * Terrain::get_topology_t_names(topology_t topo_type){
    switch(topo_type){
    case TOPOLOGY_ASTEROID: return "Asteroid"; break;
    case TOPOLOGY_CLIFF: return "Cliff"; break;
    case TOPOLOGY_DELTA: return "Delta"; break; 
    case TOPOLOGY_HILLY: return "Hilly"; break;
    case TOPOLOGY_ISLANDS: return "Islands"; break;
    case TOPOLOGY_MOUNTAIN_VALLEY: return "Mountain Valley"; break;
    case TOPOLOGY_PLAINS: return "Plains"; break;
    default:
	return "Unrecognized Topology"; break;
    }
}
const char * Terrain::get_geology_t_names(geology_t geo_type){
    switch(geo_type){
    case GEOLOGY_DIRT: return "dirt"; break;
    case GEOLOGY_DIRT_BEDROCK: return "Dirt over Bedrock"; break;
    case GEOLOGY_KARST: return "Karst"; break;
    case GEOLOGY_ROCK: return "Rock"; break;
    case GEOLOGY_VOLCANO: return "Volcano"; break;
    default:
	return "unrecognized topology"; break;
    }
}


// ========================= MAIN MAP GENERATION METHOD ========================


void Terrain::generate_topology(){
    fprintf(logfile, "    Generating Initial Terrain: %s\n", get_topology_t_names(topo_type)); fflush(logfile);
    switch (topo_type) {
    case TOPOLOGY_PLAINS:
	generate_topology_plain();
	break;
    default:
    case TOPOLOGY_CLIFF:
	generate_topology_cliff( scale);
	break;
    case TOPOLOGY_HILLY:
	generate_topology_hilly();
	break;
    case TOPOLOGY_ISLANDS:
	generate_topology_islands();
	break;

		
    }
}

void Terrain::generate_topology_cliff( const float scale_factor ){

    // const float offset = 0.020f;
    // // raise half of map to scale factor
    // fprintf(stdout, "  ?? cliff height: == %g \n", scale_factor);
    // fprintf(stdout, "  ?? cliff offset: == %g \n", this->scale*offset);
    // for( uint cur_vert_i = 0; cur_vert_i < vertex_list.size(); cur_vert_i++){
    // 	vec3 & here_m = vertex_list[cur_vert_i];

    // 	if ( here_m.x < this->scale*offset){
    // 	    here_m.y = scale_factor;
    // 	}else{
    // 	    here_m.y = 0;

    // 	    // debug
    // 	    if (here_m.z < 0){
    // 		// create ramp:
    // 		here_m.y = scale_factor+this->scale*0.010f - (scale_factor/50)*here_m.x;
    // 		if (0 > here_m.y ){
    // 		    here_m.y=0;
    // 		}
    // 	    }


    // 	}

    // }

}


void Terrain::generate_topology_plain(){
    int xi,yi;
	
    // // zero entire height map
    // for (xi = 0; xi < map_width_c.x; xi++){
    // 	for (yi = 0; yi < map_width_c.y; yi++){
    // 	    TerrainCell* cellHere = get_ortho(xi,yi);
			
    // 	    cellHere->rock = 0;
    //         cellHere->dirt = 0;
    //         cellHere->water = 0;
    // 	}
    // }

}

void Terrain::generate_topology_ramp(){
    generate_topology_plain();

    // // raise half of map to scale factor
    // for( uint cur_vert_i = 0; cur_vert_i < vertex_list.size(); cur_vert_i++){
    // 	TerrainCell* cellHere = get_ortho(xi,yi);
			
    // 	cellHere->rock = 0;
    // 	cellHere->dirt = terrain_base_scale_factor*(xi/map_width_c.x);
    // 	cellHere->water = cellHere->dirt;
    // }
}

void Terrain::generate_topology_fourier_hills( ){
    //vec3 magn = vec3( -6, 0, 4);
    vec3 magn = vec3( -50, 0, 0);
    vec3 freq = vec3( scale, 0, scale/2);

    fprintf(stdout, "  ?? scale == %g \n", scale);
    for( uint cur_node_i = 0; cur_node_i < node_list.size(); cur_node_i++){
	vec3 & here_m = node_list[cur_node_i].location_m;

	here_m.y = magn.x*sin( here_m.x*M_PI/freq.x ) + magn.z*sin( here_m.z*M_PI/freq.z );
	//TerrainCell* cellHere = get_ortho(xi,yi);
	    
    }
    
}

void Terrain::generate_topology_hilly(){
    // generate Simplex Noise
    // basically a wrapper for the 'Simplex' class

    // SimplexEffect simplex_noise;
    // simplex_noise.setMap(this);
    // simplex_noise.init();

    // fprintf(logfile, "    Simplex Noise Initialized.\n");
	
    // simplex_noise.populate_rolling_hills();

    // fprintf(logfile, "    Hilly Terrain Finished.\n");
    // calculate_statistics();
    return;
}

void Terrain::generate_topology_islands(){

    //VoronoiDiagramGenerator vorgen;

    //vorgen.generate_reghex();


    //float xValues[4] = {-22, -17, 4,22};
    //float yValues[4] = {-9, 31,13,-5};
    //int count = 4;

	
    //vdg.generateVoronoi(xValues, yValues, count, -100,100,-100,100,3);

    //vdg.resetIterator();

    //float x1,y1,x2,y2;

    //printf("\n-------------------------------\n");
    //while(vdg.getNext(x1,y1,x2,y2))
    //{
    //	printf("GOT Line (%f,%f)->(%f,%f)\n", x1, y1, x2, y2);
    //}

    return;
}

void Terrain::print_cell(const char* msg, const int xi, const int yi){

}

void Terrain::print_map(){
    // fprintf(logfile, ">>>>Dumping Map Values: \n");
    
    // int xi, yi;
    // for (xi = 0; xi < map_width_c.x; xi++){
    //     for (yi = 0; yi < map_width_c.y; yi++){
    // 	    TerrainCell * cellHere = get_ortho(xi, yi);

    // 	    fprintf(logfile, "    at [%d,%d]:  z={ %6.2g, %6.2g, %6.2g}  @%p \n", xi, yi, 
    // 		    cellHere->rock, cellHere->dirt, cellHere->water, (void*)cellHere);

    // 	}
    // 	fprintf(logfile, "_");
    // }

    // fprintf(logfile, " ==========================================================\n");
    return;
}

void Terrain::print_statistics(bool full_display){

    // fprintf(logfile,"\n   ====== ====== Statistics: ====== ====== ====== ====== \n");
    // fprintf(logfile, "    >> Dirt Heights \n");
    // fprintf(logfile, "         [Min, Mean, Max]:          [%6.4g/ %6.4g/ %6.4g ]\n", 
    // 	    heights_min.dirt, heights_mean.dirt, heights_max.dirt);
    // fprintf(logfile, "         Range, standard_deviation    %6.4g/  %6.4g\n", heights_range.dirt, heights_std_dev.dirt);
    // if (full_display) {
    //     fprintf(logfile, "    >> Rock Heights \n");
    //     fprintf(logfile, "         [Min, Mean, Max]:          [ %6.4g,  %6.4g,  %6.4g]\n",
    // 		heights_min.rock, heights_mean.rock, heights_max.rock);
    //     fprintf(logfile, "         Range, standard_deviation    %6.4g,  %6.4g \n", heights_range.rock, heights_std_dev.rock);
    //     fprintf(logfile, "    >> Water Heights.\n");
    //     fprintf(logfile, "         [Min, Mean, Max]:          [ %6.4g,  %6.4g,  %6.4g]\n", 
    // 		heights_min.water, heights_mean.water, heights_max.water);
    //     fprintf(logfile, "         Range, standard_deviation    %6.4g,  %6.4g \n", heights_range.water, heights_std_dev.water);
    // }
    // fprintf(logfile,"    ====== ====== ====== ====== ====== ====== ====== ====== ====== \n\n");
    // fflush(logfile);
    return;
}

void Terrain::offset_elevation(float _new_min){
    calculate_statistics();

    // calculate how much to scale 
    //fprintf(logfile, ">>>>Scale Elevation....  \n");
    //fprintf(logfile, "         New_min:          %6.4g \n", _new_min);
    //fprintf(logfile, "         Range, standard_deviation   %6.4g, %6.4g \n", heights_range.dirt, heights_std_dev.dirt);

    // int xi, yi;
    // for (xi = 0; xi < map_width_c.x; xi++){
    //     for (yi = 0; yi < map_width_c.y; yi++){
    // 	    //lower entire map to lowest elevation
    // 	    //get_ortho(xi,yi).subtract( _new_min);
    // 	    get_ortho(xi,yi)->subt( _new_min);
    //     }
    // }

    return;
}

void Terrain::scale_elevation(float _to_range){
    calculate_statistics();

    // heights_range.set_lower_limit(1.0);
    // // calculate how much to scale 
    // float new_min = heights_min.getMin();
    // float rescale_factor = _to_range / (heights_max.getMax() - heights_min.getMin());
    // fprintf(logfile, "    >>>>Scale Elevation....  \n");
    // fprintf(logfile, "         New_min:          %6.4g \n", new_min);
    // fprintf(logfile, "         Scale_factor:         %6.4g \n", rescale_factor);
    // fprintf(logfile, "         Range, standard_deviation   %6.4g, %6.4g \n", heights_range.dirt, heights_std_dev.dirt);
    // fflush(logfile);

    // int xi, yi;
    // for (xi = 0; xi < map_width_c.x; xi++){
    //     for (yi = 0; yi < map_width_c.y; yi++){
    // 	    TerrainCell* cell_here = get_ortho(xi,yi);

    // 	    //lower entire map to lowest elevation
    // 	    cell_here->subt( new_min);
            
    //         // then scale map to match the desired range
    // 	    cell_here->mult( rescale_factor);

    //     }
    // }

    fprintf(logfile, "    .. done scaling. \n"); fflush(logfile);
    return;
}

void Terrain::set_preset_asteroid(){
    fprintf(logfile, "   Setting Preset: Asteroid\n");
    atmo.setAsteroidClimate();
    topo_type = TOPOLOGY_ASTEROID;
    geo_type = GEOLOGY_DIRT_BEDROCK; 
    return;
}
        
void Terrain::set_preset_test(){
    fprintf(logfile, "    Setting Preset: Test\n");
    atmo.setTestClimate();
    topo_type = TOPOLOGY_CLIFF;
    geo_type = GEOLOGY_DIRT_BEDROCK;
    return;
}

void Terrain::set_preset_forest(){
    fprintf(logfile, "    Setting Preset: Forest\n");
    atmo.setTemperateClimate();
    topo_type = TOPOLOGY_CLIFF;
    geo_type = GEOLOGY_DIRT_BEDROCK;
}



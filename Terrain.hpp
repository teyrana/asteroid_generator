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

#ifndef __TERRAIN_HPP__
#define __TERRAIN_HPP__
#include "common.hpp"
#include "Mesh.hpp"
#include "TerrainCell.hpp"
#include "Atmosphere.hpp"

namespace MeshGen {


    class Terrain: public Mesh{
    public: 
        // general map parameters
       
        enum topology_t {TOPOLOGY_ASTEROID, TOPOLOGY_CLIFF, TOPOLOGY_DELTA, 
			 TOPOLOGY_HILLY, TOPOLOGY_ISLANDS, TOPOLOGY_MOUNTAIN_VALLEY, TOPOLOGY_PLAINS };
	static const char* get_topology_t_names(topology_t topo_type);
	enum geology_t {GEOLOGY_DIRT, GEOLOGY_DIRT_BEDROCK, GEOLOGY_KARST, 
			GEOLOGY_ROCK, GEOLOGY_VOLCANO};
	static const char* get_geology_t_names(geology_t geo_type);


	Atmosphere atmo;
	// enums generally describe the map
	topology_t topo_type;
        geology_t geo_type;
        float scale_factor;
		
    protected:

	// statistical measures
        TerrainCell heights_min;
        TerrainCell heights_max;
        TerrainCell heights_mean;
        TerrainCell heights_std_dev;
        TerrainCell heights_range;
        int num_outliers;

	// ====== ====== Diagnostic Functions ====== ====== 
    public:
	void calculate_statistics();
	void print_map();
	void print_statistics(bool full_display=true);
	void print_cell(const char* msg, const int xi, const int yi);

	// ====== ====== Generation Functions ====== ====== 
    public:
	void generate_graph();
	void generate_topology_cliff( const float scale_factor );
	void generate_topology_fourier_hills();
	void generate_topology_hilly();
	void generate_topology_islands();
	void generate_topology_plain();
	void generate_topology_ramp();
	void generate_topology();
	void generate_voronoi_terrain();

	void create_levels(int num_levels, float _new_height_min);
	void offset_elevation(float _new_min);
	void set_preset_asteroid();
	void set_preset_test();
	void set_preset_forest();
	void scale_elevation(float _to_range);
	void cull_outliers();

	// ====== ====== External Functions ====== ====== 
    public: 
	void generate_terrain();
	Terrain();
	virtual ~Terrain();
	void reset(TerrainCell* newHeights);

    };


}
#endif // #ifndef __TERRAIN_HPP__

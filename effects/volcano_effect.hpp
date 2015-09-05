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

#ifndef __VOLCANO_EFFECT_HPP__
#define __VOLCANO_EFFECT_HPP__

#include "../Terrain.hpp"
#include "terrain_effect.hpp"
using namespace MeshGen;

namespace MeshGen {

    class LavaType{
    public:
	enum composition_t { LAVA_FELSIC, LAVA_ANDESITIC, LAVA_MAFIC};
	composition_t composition;
			
	float frac_silica_u; // units: none. 0-1
	float frac_crystal_max_u;
	float temperature_exit_C;
	float temperature_solidus_C;
	float viscosity_exit_pas;
	
	// float temperature_C;
	// float viscosity_pas; // units: Pa-s
	
	// ====== // ====== class LavaType // ====== // ======
    public:
	const char* getLavaTypeName(composition_t type);
	const char* getMagmaTypeName(composition_t type);
	
	LavaType* setType(composition_t type);
	LavaType* setFelsicArchetype();
	LavaType* setAndesiticArchetype();
	LavaType* setMaficArchetype();
    };
    
    class VolcanoFeature{
    public:
	enum volcano_feature_t {
	    // Cinder Cone Volcano (aka Scoria Cone)
	    // size: <300m high (simple cone); material: cinders
	    // A cone of cinders, ejected explosively from a central bowl crater
	    FEATURE_PRIMARY_CINDER_CONE,

	    // Composite Volcanoes (aka Stratovolcanoes)
	    // size: 1-10km in dia (concave upwards); material: lava flows / pyroclastics
	    // They are typically steep-sided, symmetrical cones of large dimension
	    // built of alternating layers of lava flows, volcanic ash, cinders, blocks,
	    // and bombs and may rise as much as 8,000 feet above their bases.
	    FEATURE_PRIMARY_COMPOSITE,

	    // Shield volcanoes:
	    // Size: 10s km dia (dome shaped); material: lava flows (basalt)
	    // built almost entirely of fluid lava flows.
	    FEATURE_PRIMARY_SHIELD,

	    FEATURE_CINDER_CONE,
	    FEATURE_LAVA_DOME,
	    FEATURE_LAVA_FLOW,   // combine w/lava lave?
	    FEATURE_LAVA_TUBE // optional?
	};

    public:
	LavaType magma_source;
	int xi_center, yi_center;
	float size;

    public:
	VolcanoFeature();
	~VolcanoFeature();
	const char* getFeatureTypeName(volcano_feature_t type);

    public:
	enum flow_type_t {
	    // 'A'a is basaltic lava characterized by a rough or rubbly surface
	    // composed of broken lava blocks called clinker
	    // -- typically erupt at temperatures of 1000 - 1100 °C
	    // -- high viscosity
	    FLOW_TYPE_AA,

	    // Pahoehoe is basaltic lava that has a smooth, billowy, undulating,
	    // or ropy surface.
	    // -- low viscosity
	    // -- typically erupt at 1100-1200 °C
	    // Pahoehoe can turn into ?a?a if it becomes turbulent from meeting
	    // impediments or steep slopes.
	    FLOW_TYPE_PAHOEHOE
	};


	// The effusion rates for:
	//  andesite to dacite lavas (10 to 0.05 m^3/s)
	// basalt (0.5 to 5000 m^3/s)
	float effusion_rate_m3s; // units: cubic meters / sec

	float calculate_viscosity_ER_pas(float phi, float T, float T_ref, float mu_ref);

    };

    class VolcanoEffect: public TerrainEffect {
    public:
	//virtual void applyEffect(const int num, const float min_scale, const float max_scale);
	void addVolcano( VolcanoFeature * feature);

    public:
	VolcanoEffect();
	virtual ~VolcanoEffect();
    };

}
#endif

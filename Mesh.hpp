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

#ifndef __MESH_HPP__
#define __MESH_HPP__

#include "common.hpp"

namespace MeshGen{
    // ====== ====== Helper Classes ====== ======
    struct MeshNode {
	vec3 location_m;
	vec3 normal_n;
	vec3 gravity_n;

	uint neighbor_count=0;
	static const uint max_neighbor_count=6;
	uint neighbors[ max_neighbor_count];
    };

    struct Face{
	uint_t num; // index in face list
	uvec3 vert_i; // index in vertex list
	uvec3 adj_i; // index in face list of face adjacencies
	uvec3 norm_i; // index in normal list
	
	Face* set_adjacencies(const uint_t first, const uint_t second, const uint_t third);
	Face* set_normals(const uint_t first, const uint_t second, const uint_t third);
	Face* set_vertices(const uint_t first, const uint_t second, const uint_t third);
	
	//vec2    *texcoord;
	//texture *tex;
    };
	
    //struct Edge{
	//	Vertex* ends[2];
	//	Face* adj[2];
    //};
    

    // ====== ====== Mesh Class ====== ======
    class Mesh {
    public:
	// vectors allow constant time random read.
	// and we expect these to be mostly static (once constructed).
	// n.b. while constructing, should probably use a double-linked-list or something
	std::vector<MeshNode> node_list;
	std::vector<Face> face_list;

	float scale;

	//std::vector<Edge> edge_list; // NYI
	//std::vector<vec2> tex_cd_list; // texture coordinate list
	//std::vector<Texture> texture_list; // list of textures

	// ======= ======= mesh.cpp ======= ======= 
    public:
	void add_face_vn( uvec3 * vert_i, uvec3 * norm_i );
	void add_node ( vec3 * location, vec3 * gravity, vec3* normal);
	void add_vertex( vec3 * vertex_location );

	void clear();
	void dump_summary( FILE * dest);
	void dump_list_detail( FILE* dest);
	void dump_vec( FILE* dest, const char* preamble, const vec3 & _vec );

	virtual void generate(){}

	// generate the GL buffers to draw the mesh
	void generate_normals();
	void generate_colors();

	virtual void init(){}

		
	/// \brief attempts to load the requested file & guess its file type. 
	/// \bug switches on the ending. is case sensitive
	int load(const char* fname);

	void load_square();
	void load_tetrahedron();
	void load_icosahedron();

	void load_header_vf( const uint vll, const uint fll,
			  const float vl[][3], const float fl[][3] );
	void load_header_vnf( const uint vll, const uint nll, const uint fll,
			  const float vl[][3], const float nl[][3], const uint fl[][6] );

	// 2d planes of points, with normals pointing up. 
	void load_grid( const uint width, const uint length, const float scale);
	// preset
	void load_grid_128();

	// preset spheres
	void load_sphere_1280();
	void load_sphere_5120();
	void load_sphere_20480();
	void load_sphere_81920();

	Mesh();

	// centers the model (roughly) around its center of mass
	void center_mass();
	// centers the model (roughly) around its minimum bounding sphere
	void center_bounds();

	// eliminates duplicate vertices
	void consolidate_vertices();

	void render();
	void render_test();
	void reset();
	void subdivide(const uint num_pts);
	void set_scale( const float new_scale);
	void set_normal( const uint index, vec3 * normal_direction); 

	void write_to_obj_vf( const char* obj_fname);
	void write_to_obj_vnf( const char* obj_fname); 
	void write_to_header( const char* prefix);

	virtual ~Mesh();

    protected:

	//texture* gettex(const char* label);
	//int load_mtl(const char *fname);
	//int read_2vector(char * cln, vector2* buf);
	//int read_3vector(char * cln, vector3* buf);
	//int read_face(char *cln,face* targ,texture* tex);
	//texture* read_mtl_tag(char* tagln);

	/** \fn load_obj(FILE* inf)
	 *  \brief loads an ".obj" file on the given stream int the class
	 *  \version lightly tested
	 * 
	 *  -This class will import a .obj file into the internal code structure 
	 *  -This does not support all features of the .obj format.
	 *      Currently Supported Tags: v,vt,vn,f,usemtl
	 *      May support: s 
	 *      Want to ignore: g vp
	 *  -will load the associated mtl file
	 */
	int load_obj(FILE* inf); //in mesh_load.cpp
	


    };

}
#endif //#ifndef __GUI_HPP__

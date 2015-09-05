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


#include "Mesh.hpp"

//#include "mesh/sphere_80.hpp"
// #include "mesh/sphere_320.hpp"

// #include "mesh/sphere_5120.hpp"
// #include "mesh/sphere_20480.hpp"
// #include "mesh/sphere_81920.hpp"

#include "mesh/grid_128.hpp"

#include "mesh/sphere_1280.hpp"
#include "mesh/sphere_5120.hpp"
#include "mesh/sphere_20480.hpp"
#include "mesh/sphere_81920.hpp"

using namespace MeshGen;

// ====== ======= ====== Face Code ====== ====== =======
Face* Face::set_adjacencies(const uint_t first, const uint_t second, const uint_t third){
    adj_i[0]=first;
    adj_i[1]=second;
    adj_i[2]=third;
    return this;
}

Face* Face::set_normals(const uint_t first, const uint_t second, const uint_t third){
    norm_i[0]=first;
    norm_i[1]=second;
    norm_i[2]=third;
    return this;
}


Face* Face::set_vertices( const uint_t first, const uint_t second, const uint_t third){
    vert_i[0]=first;
    vert_i[1]=second;
    vert_i[2]=third;
    return this;
}


// ====== ======= ====== Mesh Code ====== ====== =======


void Mesh::add_face_vn( uvec3 * corner_vertex_indices, uvec3 * corner_normal_indices){
    Face *new_face = new Face();
    uvec3 & vi = *corner_vertex_indices;
    uvec3 & ni = *corner_normal_indices;

    new_face->num = face_list.size();
    new_face->set_vertices( vi.x, vi.y, vi.z);
    new_face->set_normals( ni.x, ni.y, ni.z);
    face_list.push_back( *new_face );
}

void Mesh::add_node( vec3 * location, vec3 * gravity, vec3 * normal ){
    MeshNode * new_node=new MeshNode();;
    new_node->location_m = *location;
    new_node->gravity_n = *gravity;
    new_node->normal_n = *normal;
    node_list.push_back( *new_node);
    return;
}

void Mesh::add_vertex( vec3 * vertex_location ){
    MeshNode * new_node = new MeshNode();
    new_node->location_m = *vertex_location;
    new_node->normal_n = normalize(*vertex_location);
    new_node->gravity_n = (-1.0f)*new_node->normal_n;
    node_list.push_back( *new_node);
    return;
}

void Mesh::clear(){
    node_list.clear();
    face_list.clear();
}

void Mesh::dump_summary( FILE* dest){
    fprintf( dest, ">>Mesh List Summary: ");
    fprintf( dest, "  N: %lu", node_list.size());
    fprintf( dest, "  f: %lu\n", face_list.size());
}

void Mesh::dump_vec( FILE* dest, const char* preamble, const vec3 & _vec ){
    fprintf( dest, "\t%s: {%6.2g,\t%6.2g,\t%6.2g ) @%p\n", preamble, _vec.x, _vec.y, _vec.z, (void*)&_vec);
}

void Mesh::dump_list_detail(FILE * dest){
    
    fprintf( dest, ">> ======= ====== Dumping Mesh List Details ======= ====== \n");
    fprintf( dest, "  Node: %lu\n", node_list.size());
    for(uint i=0;i<node_list.size();i++){
	vec3 & loc = node_list[i].location_m;
	fprintf( dest, "\t%d @%p\t{%2.2g,\t%2.2g,\t%2.2g,\t)\n", i, (void*)&loc, loc.x, loc.y, loc.z);
	vec3 & grav = node_list[i].gravity_n;
	fprintf( dest, "\t\t\t {%2.2g,\t%2.2g,\t%2.2g,\t}\n", grav.x, grav.y, grav.z);
	vec3 & norm = node_list[i].normal_n;
	fprintf( dest, "\t\t\t {%2.2g,\t%2.2g,\t%2.2g,\t}\n", norm.x, norm.y, norm.z);
    }

    fprintf( dest, "  Face data: %lu\n", face_list.size());
    for(uint i=0;i<face_list.size();i++){
	Face & f = face_list[i];
	fprintf( dest, "\t%d @%p\t{\n", i, (void*)&f);
	fprintf( dest, "\t\tv:{  %3d,  %3d,  %3d)\n", f.vert_i[0], f.vert_i[1], f.vert_i[2]);
	fprintf( dest, "\t\tn:{  %3d,  %3d,  %3d)\n", f.norm_i[0], f.norm_i[1], f.norm_i[2]);
    }
}

// scale = edge to edge dimension of square grid
void Mesh::load_grid( const uint x_count, const uint z_count, const float _scale){
    this->clear();
    this->scale = _scale;
    const vec3 size = vec3( scale, scale, scale); // outer dimensions of grid to generate
    const vec3 origin = size * -0.5f;

    // first, create vertices
    // row by row: 
    for( uint xi = 0; xi <= x_count; xi++){
	for( uint zi = 0; zi <= z_count; zi++){
	    float x_coord = origin.x + ((float)xi)/((float)x_count) * size.x;
	    float z_coord = origin.y + ((float)zi)/((float)z_count) * size.z;
	    vec3 * loc = new vec3( x_coord, 0, z_coord);
	    
	    add_node( loc, new vec3(0, -1, 0), new vec3(0, 1, 0));
	}
    }

    // generate triangles
    for( uint xi = 0; xi < x_count; xi++){
	for( uint zi = 0; zi < z_count; zi++){
	    uint v1i = xi + zi*(z_count+1);
	    uint v2i = xi+1 + zi*(z_count+1);
	    uint v3i = xi + (zi+1)*(z_count+1);
	    uint v4i = xi+1 + (zi+1)*(z_count+1);

	    // top face
	    this->add_face_vn( new uvec3( v1i, v2i, v3i), new uvec3( 0,0,0));

	    // bottom face
	    this->add_face_vn( new uvec3( v2i, v4i, v3i), new uvec3( 0,0,0));
	}
    }
}

void Mesh::load_grid_128(){
    this->clear();
    load_header_vnf( grid_128_vertex_list_length, grid_128_normal_list_length, grid_128_face_list_length,
		     grid_128_vertex_list, grid_128_normal_list, grid_128_face_list);
}

void Mesh::load_square(){
    this->clear();

    this->add_vertex( new vec3( 0.00, 0.00, 0.00));
    this->add_vertex( new vec3( 1.00, 0.00, 0.00));
    this->add_vertex( new vec3( 0.00, 0.00, 1.00));
    this->add_vertex( new vec3( 1.00, 0.00, 1.00));

    this->add_face_vn( new uvec3( 0, 1, 2), new uvec3( 0,0,0));
    this->add_face_vn( new uvec3( 1, 3, 2), new uvec3( 0,0,0));
    return;
}

void Mesh::load_tetrahedron(){
    // NOT a regular tetrahedron :(

    this->clear();
    // g tetrahedron

    this->add_vertex( new vec3( -0.50, -0.50, 0.00));
    this->add_vertex( new vec3( 0.50, -0.50, 0.00));
    this->add_vertex( new vec3( 0.00, 0.50, 0.5));
    this->add_vertex( new vec3( 0.00, 0.50, -0.5));

    this->add_face_vn( new uvec3( 0, 2, 1), new uvec3( 0, 2, 1));
    this->add_face_vn( new uvec3( 0, 3, 2), new uvec3( 0, 3, 2));
    this->add_face_vn( new uvec3( 0, 1, 3), new uvec3( 0, 1, 3));
    this->add_face_vn( new uvec3( 1, 2, 3), new uvec3( 1, 2, 3));
    return;
}

void Mesh::load_icosahedron(){
    this->clear();

    this->add_vertex( new vec3( 0,  -0.525731,  0.850651));
    this->add_vertex( new vec3( 0.850651,  0,  0.525731));
    this->add_vertex( new vec3( 0.850651,  0,  -0.525731));
    this->add_vertex( new vec3( -0.850651,  0,  -0.525731));
    this->add_vertex( new vec3( -0.850651,  0,  0.525731));
    this->add_vertex( new vec3( -0.525731,  0.850651,  0));
    this->add_vertex( new vec3( 0.525731,  0.850651,  0));
    this->add_vertex( new vec3( 0.525731,  -0.850651,  0));
    this->add_vertex( new vec3( -0.525731,  -0.850651,  0));
    this->add_vertex( new vec3( 0,  -0.525731,  -0.850651));
    this->add_vertex( new vec3( 0, 0.525731,  -0.850651));
    this->add_vertex( new vec3( 0,  0.525731,  0.850651));

    this->add_face_vn( new uvec3( 1,  2,  6), new uvec3( 1,  2,  6) );
    this->add_face_vn( new uvec3( 1,  7,  2), new uvec3( 1, 7, 2));
    this->add_face_vn( new uvec3( 3,  4,  5), new uvec3( 3, 4, 5));
    this->add_face_vn( new uvec3( 4,  3,  8), new uvec3( 4, 3, 8));
    this->add_face_vn( new uvec3( 6,  5, 11), new uvec3( 6, 5, 11));
    this->add_face_vn( new uvec3( 5,  6, 10), new uvec3( 5, 6, 10));
    this->add_face_vn( new uvec3( 9, 10, 2),  new uvec3( 9, 10, 2));
    this->add_face_vn( new uvec3( 10, 9, 3),  new uvec3( 10, 9, 3));
    this->add_face_vn( new uvec3( 7, 8, 9),   new uvec3( 7, 8, 9));
    this->add_face_vn( new uvec3( 8, 7,  0),  new uvec3( 8, 7, 0));
    this->add_face_vn( new uvec3( 11, 0, 1),  new uvec3( 11, 0, 1));
    this->add_face_vn( new uvec3( 0, 11, 4),  new uvec3( 0, 11, 4));
    this->add_face_vn( new uvec3( 6, 2, 10),  new uvec3( 6, 2, 10));
    this->add_face_vn( new uvec3( 1, 6, 11),  new uvec3( 1, 6, 11));
    this->add_face_vn( new uvec3( 3, 5, 10),  new uvec3( 3, 5, 10));
    this->add_face_vn( new uvec3( 5, 4, 11),  new uvec3( 5, 4, 11));
    this->add_face_vn( new uvec3( 2, 7, 9),   new uvec3( 2, 7, 9));
    this->add_face_vn( new uvec3( 7, 1, 0),   new uvec3( 7, 1, 0));
    this->add_face_vn( new uvec3( 3, 9, 8),   new uvec3( 3, 9, 8));
    this->add_face_vn( new uvec3( 4, 8, 0),   new uvec3( 4, 8, 0));

    return;
}


void Mesh::load_sphere_1280(){
    load_header_vnf( sphere_1280_vertex_list_length, sphere_1280_normal_list_length, sphere_1280_face_list_length,
		     sphere_1280_vertex_list, sphere_1280_normal_list, sphere_1280_face_list);
}

void Mesh::load_sphere_5120(){
    load_header_vnf( sphere_5120_vertex_list_length, sphere_5120_normal_list_length, sphere_5120_face_list_length,
		     sphere_5120_vertex_list, sphere_5120_normal_list, sphere_5120_face_list);
}
void Mesh::load_sphere_20480(){
    load_header_vnf( sphere_20480_vertex_list_length, sphere_20480_normal_list_length, sphere_20480_face_list_length,
		     sphere_20480_vertex_list, sphere_20480_normal_list, sphere_20480_face_list);
}
void Mesh::load_sphere_81920(){
    load_header_vnf( sphere_81920_vertex_list_length, sphere_81920_normal_list_length, sphere_81920_face_list_length,
		     sphere_81920_vertex_list, sphere_81920_normal_list, sphere_81920_face_list);
}


// void Mesh::load_header_vf( const uint vll, const uint fll,
// 			const float vl[][3], const float fl[][3] ){
//     clear();
//     for ( uint vi=0; vi < vll; vi++ ){
// 	add_vertex( new vec3( vl[vi][0], vl[vi][1], vl[vi][2]));
// 	// DEBUG! 
// 	add_normal( new vec3( vl[vi][0], vl[vi][1], vl[vi][2]));
//     }

//     for ( uint fi=0; fi < fll; fi++ ){
// 	add_face_v( new ivec3( fl[fi][0], fl[fi][1], fl[fi][2]));
//     }
// }
    
void Mesh::load_header_vnf( const uint vll, const uint nll, const uint fll,
			const float vl[][3], const float nl[][3], const uint fl[][6] ){
    clear();
    for ( uint vi=0; vi < vll; vi++ ){
	add_vertex( new vec3( vl[vi][0], vl[vi][1], vl[vi][2]));

    }

    for ( uint ni=0; ni < nll; ni++ ){
	set_normal( ni, new vec3( nl[ni][0], nl[ni][1], nl[ni][2]));
    }

    for ( uint fi=0; fi < fll; fi++ ){
	add_face_vn( new uvec3( fl[fi][0], fl[fi][2], fl[fi][4]),
		     new uvec3( fl[fi][1], fl[fi][3], fl[fi][5]) );
    }

    this->scale = 1.0;
}


Mesh::Mesh(){
    this->reset();
}

void Mesh::reset(){
    scale = 1.0f;
    this->clear();
}

void Mesh::set_scale( const float new_scale){

    float old_scale = this->scale;
    this->scale = new_scale;
    
    for(uint ni=0; ni<node_list.size(); ni++){
	vec3 & loc = node_list[ni].location_m;
	loc *= new_scale/old_scale;
    }

    return;
}

void Mesh::set_normal( const uint index, vec3 * normal_direction ){
    
    //normal_list.push_back( *normal_direction );
}

void Mesh::subdivide(const uint iterations=1){
    //       NOT thread safe.
    // Before:
    //     Faces:         Vertices:
    //         *               0
    //        / \             / \
    //       / 0 \           /   \
    //      *-----*         1-----2
    // 
    // After:            
    //     Faces:         Vertices:
    //         *               0
    //        / \             / \
    //       / 1 \           /   \
    //      *-----*         4-----3
    //     / \ 0 / \       / \   / \
    //    / 2 \ / 3 \     /   \ /   \
    //   *-----*-----*   1-----5-----2
    // 
    // Adjacencies are ignored...
    uint iteration_count=1;
    for ( ; iteration_count <= iterations; iteration_count++){
	fprintf(stderr, "..in subdivide. iteration = %u\n", iteration_count);
	
	const uint size_old_face_list = this->face_list.size();
	for( uint cur_face_index=0; cur_face_index < size_old_face_list; cur_face_index++){
	    // create new faces
	    Face *faces[4] = {};
	    MeshNode * node[6] = {};
	    uint node_i[6] = {};
	    
	    faces[0] = &( face_list[ cur_face_index]);
	    //fprintf( stderr, "....subdividing face #%u / %u, loc=%p \n", cur_face_index, size_old_face_list, (void*)faces[0]);
	    faces[1] = new Face();
	    faces[2] = new Face();
	    faces[3] = new Face();
	    
	    // load old nodes
	    node[0] = &node_list[ faces[0]->vert_i[0]];
	    node[1] = &node_list[ faces[0]->vert_i[1]];
	    node[2] = &node_list[ faces[0]->vert_i[2]];
	    // create new nodes
	    node[3] = new MeshNode();
	    node[4] = new MeshNode();
	    node[5] = new MeshNode();

	    // set new vertices
	    node[3]->location_m = normalize(node[0]->location_m + node[2]->location_m);
	    node[4]->location_m = normalize(node[0]->location_m + node[1]->location_m);
	    node[5]->location_m = normalize(node[1]->location_m + node[2]->location_m);

	    // create new normals
	    node[3]->normal_n = normalize( node[0]->normal_n + node[2]->normal_n);
	    node[4]->normal_n = normalize(node[0]->normal_n + node[1]->normal_n);
	    node[5]->normal_n = normalize(node[1]->normal_n + node[2]->normal_n);

	    // set new vertex indices 
	    node_i[0] = faces[0]->vert_i[0];
	    node_i[1] = faces[0]->vert_i[1];
	    node_i[2] = faces[0]->vert_i[2];
	    node_i[3] = node_list.size();
	    node_list.push_back( *node[3]);
	    node_i[4] = node_list.size();
	    node_list.push_back( *node[4]);
	    node_i[5] = node_list.size();
	    node_list.push_back( *node[5]);

	    // adjust vertices
	    faces[0]->set_vertices( node_i[3], node_i[4], node_i[5] );
	    faces[0]->set_normals( node_i[3], node_i[4], node_i[5] );

	    faces[1]->set_vertices( node_i[0], node_i[4], node_i[3] );
	    faces[1]->set_normals(  node_i[0], node_i[4], node_i[3] );
	    faces[1]->num = face_list.size();
	    face_list.push_back( *faces[1]);

	    faces[2]->set_vertices( node_i[4], node_i[1], node_i[5] );
	    faces[2]->set_normals(  node_i[4], node_i[1], node_i[5] );
	    faces[2]->num = face_list.size();
	    face_list.push_back( *faces[2]);

	    faces[3]->set_vertices( node_i[3], node_i[5], node_i[2] );
	    faces[3]->set_normals(  node_i[3], node_i[5], node_i[2] );
	    faces[3]->num = face_list.size();
	    face_list.push_back( *faces[3]);

	    // optional...?
	    // delauney flip/rotate

	}

    } // iteration_count

    return;
}

void Mesh::center_mass(){
    vec3 sum(0);
    vec3 offset(0);

    for(uint vi=0; vi<node_list.size(); vi++){
	sum+=node_list[vi].location_m;
    }
    offset = sum/((float)node_list.size());
	
    for(uint vi=0; vi<node_list.size(); vi++){
	node_list[vi].location_m-=offset;
    }
    return;
}

void Mesh::center_bounds(){
    vec3 max(FLT_MIN);
    vec3 min(FLT_MAX);
    vec3 offset(0);

    for(uint vi=0; vi<node_list.size(); vi++){
	for(uint ei=0; ei<3; ei++){
	    if(max[ei] < node_list[vi].location_m[ei]){
		max[ei] = node_list[vi].location_m[ei];
	    }
	    if(min[ei] > node_list[vi].location_m[ei]){
		min[ei] = node_list[vi].location_m[ei];
	    }
	}
    }
    offset = 0.5f*(max-min);
	
    for(uint vi=0; vi<node_list.size(); vi++){
	node_list[vi].location_m -= offset;
    }
    return;
}

void Mesh::consolidate_vertices(){
    // a copy of the original that stays in it's pre-form.
    std::vector<MeshNode> node_list_copy = this->node_list;

    // the original stays in ploce, and we modify it.
    fprintf( stdout, "  >> removing duplicate vertices");
    // remove the duplicate vertices in the vertex_list
    uint nio=0; // vo = vertex index, outer loop
    uint nii=0; // vi = vertex index, inner loop
    uint nlist_size = node_list.size();
    for (nio=0; nio < nlist_size; nio++){
    	const MeshNode & ref_node = node_list[nio];
	const vec3 ref_vertex = ref_node.location_m;
     	for (nii=0; nii < nlist_size; nii++){
    	    const MeshNode & comp_node = node_list[ nii];
	    const vec3 comp_vertex = comp_node.location_m;
    	    bvec3 eq_vec = glm::epsilonEqual( ref_vertex, comp_vertex, FLT_EPSILON );
    	    if ( ( nio != nii ) && (eq_vec.x && eq_vec.y && eq_vec.z)){
    		fprintf(stderr, "detected dup node: %u =?= %u \n", nio, nii);
		node_list.erase( node_list.begin()+nii);
    		nii--;
    		nlist_size--;
     	    }
     	}
    }
    fputc('\n', stdout);

    fprintf( stdout, "  >> rectifying face references");
    uint face_counter = -1;
    for (std::vector<Face>::iterator cur_face = face_list.begin(); cur_face != face_list.end(); cur_face++) {
	face_counter++;
	if ( 0 == (face_counter % 100)){
	    fputc( '.', stdout); fflush(stdout); }

	// rectify vertex references
	//fprintf(stderr, "@ face: %u \n", cur_face->num);
	for (uint cur_face_vertex_index=0; cur_face_vertex_index < 3; cur_face_vertex_index++){
	     const MeshNode & ref_node = node_list_copy[cur_face->vert_i[cur_face_vertex_index]];
	     vec3 ref_vertex = ref_node.location_m;

	     // if normal reference is the same in the new AND old list, it
	     // hasn't changed. move on.
	     // if it HAS changed, THEN search for the new location.

	//     //fprintf(stderr, " at corner: #%u = %u \n", cur_face_vertex_index, cur_face->node_i[cur_face_vertex_index] );
	//     for ( uint node_list_index=0; node_list_index < node_list.size(); node_list_index++){
	// 	const MeshNode & ref_node = node_list[ node_list_index];
	// 	vec3 comp_vertex = ref_node.location_m;
	// 	bvec3 eq_vec = glm::epsilonEqual( ref_vertex, comp_vertex, FLT_EPSILON );
	// 	if ( eq_vec.x && eq_vec.y && eq_vec.z ){
	// 	    //fprintf(stderr, ".... reseting "....
	// 	    // 	    cur_face->node_i[cur_face_vertex_index], vec_list_index);
	// 	    cur_face->node_i[cur_face_vertex_index] = vec_list_index;
	// 	    break;
	// 	}
	//     }
	}

    }
    fputc('\n', stdout);

    return; 
}


// writes just vertices and faces
void Mesh::write_to_obj_vf( const char* obj_fname){
// .OBJ Format Documentation:
// https://en.wikipedia.org/wiki/Wavefront_.obj_file

    FILE* objf = fopen( obj_fname, "w");

    if( NULL == objf ){
	fprintf(stderr, "!! Could not save to file: unable to get file handle.\n");
	return;
    }

    // write header
    fprintf(objf, "# Wavefront OBJ File\n");
    fprintf(objf, "# Custom .OBJ  Output Code \n");
    fprintf(objf, "#    Written by custom mesh generator\n");
    fprintf(objf, "#    Daniel Williams, 2014\n");
    fprintf(objf, "#    \n");
    fflush( objf);
    
    // write vertex list
    fprintf(objf, "# Vertex List (%lu): \n", node_list.size());

    for (std::vector<MeshNode>::iterator iter = this->node_list.begin(); iter != node_list.end(); iter++) {
	vec3 v = iter->location_m;
	fprintf(objf, "v %g %g %g \n", v.x, v.y, v.z);
    }
    fprintf(objf, "\n");
    fflush( objf);

    // write face list
    fprintf(objf, "# Face List(%lu): \n", face_list.size());
    for (std::vector<Face>::iterator iter = this->face_list.begin(); iter != face_list.end(); iter++) {
	Face f = *iter;
	// note that C/C++ is 0-indexed, and the .OBJ format is 1-indexed
	fprintf(objf, "f %u// %u// %u// \n", f.vert_i[0]+1, f.vert_i[1]+1, f.vert_i[2]+1);
    }
    fprintf(objf, "\n");
    fflush( objf);

    // write footer
    fprintf(objf, "# EOF \n");
    fprintf(objf, "\n");
    fflush( objf);
    fclose(objf);

    fprintf( stdout, "  >> terrain written to %s\n", obj_fname);
    return;
}

// writes vertices, normals, and faces
void Mesh::write_to_obj_vnf( const char* obj_fname){
// .OBJ Format Documentation:
// https://en.wikipedia.org/wiki/Wavefront_.obj_file

    FILE* objf = fopen( obj_fname, "w");

    // write header
    fprintf(objf, "# Wavefront OBJ File\n");
    fprintf(objf, "# Custom .OBJ  Output Code \n");
    fprintf(objf, "#    Written by custom mesh generator\n");
    fprintf(objf, "#    Daniel Williams, 2014\n");
    fprintf(objf, "#    \n");
    fflush( objf);
    
    // write vertex list
    fprintf(objf, "# Vertex List (%lu): \n", node_list.size());
    for (std::vector<MeshNode>::iterator iter = this->node_list.begin(); iter != node_list.end(); iter++) {
	vec3 v = iter->location_m;
	fprintf(objf, "v %g %g %g \n", v.x, v.y, v.z);
    }
    fprintf(objf, "\n");
    fflush( objf);

    // write vertex texture coord list
    fprintf(objf, "# Texture Coordinate List (%lu): \n", (unsigned long)0 ); 
    fprintf(objf, "#   (NYI) \n");
    // for (std::vector<vec3>::iterator iter = this->vertex_list.begin(); iter != vertex_list.end(); iter++) {
    // 	Vertex vt = *iter;
    // 	fprintf(objf, "vt %g %g %g \n", 
    // }
    fprintf(objf, "\n");
    fflush( objf);

    // write normal list
    fprintf(objf, "# Vertex Normal List (%lu): \n", node_list.size());
    for (std::vector<MeshNode>::iterator iter = this->node_list.begin(); iter != node_list.end(); iter++) {
	vec3 vn = iter->normal_n;
	fprintf(objf, "vn %g %g %g \n", vn.x, vn.y, vn.z);
    }
    fprintf(objf, "\n");
    fflush( objf);

    // write face list
    fprintf(objf, "# Face List(%lu): \n", face_list.size());
    for (std::vector<Face>::iterator iter = this->face_list.begin(); iter != face_list.end(); iter++) {
	Face f = *iter;
	// note that C/C++ is 0-indexed, and the .OBJ format is 1-indexed
	fprintf(objf, "f %u//%u %u//%u %u//%u \n", f.vert_i[0]+1, f.norm_i[0]+1, f.vert_i[1]+1, f.norm_i[1]+1, f.vert_i[2]+1, f.norm_i[2]+1);
    }
    fprintf(objf, "\n");
    fflush( objf);

    // write footer
    fprintf(objf, "# EOF \n");
    fprintf(objf, "\n");
    fflush( objf);
    fclose(objf);

    fprintf( stdout, "  >> terrain written to %s\n", obj_fname);
    return;
}

void Mesh::write_to_header( const char* prefix ){
    const uint fname_len=50;
    char hpp_fname[fname_len];
    const uint tri_count = face_list.size();
    snprintf( hpp_fname, fname_len, "%s_%u.hpp", prefix, tri_count);

    FILE* hf = fopen( hpp_fname, "w");

    // write header
    // yea, this is a hack.  But have you seen the code to convert
    // even simple strings to upper case? Eeesh. 
    if (0 == strcmp( prefix, "grid")){
	fprintf( hf,"#ifndef __GRID_%u_HPP__\n", tri_count);
	fprintf(hf, "#define __GRID_%u_HPP__\n", tri_count);
    }else if (0 == strcmp( prefix, "sphere")){
	fprintf( hf,"#ifndef __SPHERE_%u_HPP__\n", tri_count);
	fprintf(hf, "#define __SPHERE_%u_HPP__\n", tri_count);
    }
    fputc( '\n', hf);
    fprintf(hf, "using namespace MeshGen; \n");
    fputc( '\n', hf);
    fputc( '\n', hf);
    fflush( hf);
    
    // write vertex list
    fprintf(hf, "// Vertex List (%lu): \n", node_list.size());
    fprintf(hf, "const uint %s_%u_node_list_length = %lu;\n", prefix, tri_count, node_list.size());
    fprintf(hf, "float %s_%u_node_list[%lu][3]={\n", prefix, tri_count, node_list.size());
    for (std::vector<MeshNode>::iterator iter = this->node_list.begin(); iter != node_list.end(); iter++) {
	vec3 v = iter->location_m;
	fprintf(hf, "{ %g, %g, %g}, \n", v.x, v.y, v.z);
    }
    fprintf(hf, "};\n\n");
    fflush( hf);

    // write vertex texture coord list
    // fprintf(hf, "// Texture Coordinate List (%lu): \n", (unsigned long)0 ); 
    // fprintf(hf, "//   (NYI) \n");
    // for (std::vector<vec3>::iterator iter = this->node_list.begin(); iter != node_list.end(); iter++) {
    // 	Vertex vt = *iter;
    // 	fprintf(hf, "vt %g %g %g \n", 
    // }
    // fprintf(hf, "\n");
    // fflush( hf);

    // write normal list
    fprintf(hf, "// Vertex Normal List (%lu): \n", node_list.size());
    fprintf(hf, "const uint %s_%u_normal_list_length = %lu;\n", prefix, tri_count, node_list.size());
    fprintf(hf, "float %s_%u_normal_list[%lu][3]={\n", prefix, tri_count, node_list.size());
    for (std::vector<MeshNode>::iterator iter = this->node_list.begin(); iter != node_list.end(); iter++) {
    	vec3 vn = iter->normal_n;
     	fprintf(hf, "{ %g, %g, %g },\n", vn.x, vn.y, vn.z);
    }
    fprintf(hf, "};\n\n");
    fflush( hf);

    // write facelist
    fprintf(hf, "// Face List(%lu): \n", face_list.size());
    fprintf(hf, "const uint %s_%u_face_list_length = %lu;\n", prefix, tri_count, face_list.size());
    fprintf(hf, "uint %s_%u_face_list[%lu][6]={\n", prefix, tri_count, face_list.size());
    for (std::vector<Face>::iterator iter = this->face_list.begin(); iter != face_list.end(); iter++) {
	Face f = *iter;
	fprintf(hf, "{ %u, %u, %u, %u, %u, %u }, \n",
		f.vert_i[0], f.norm_i[0],
		f.vert_i[1], f.norm_i[1],
		f.vert_i[2], f.norm_i[2]);
    }
    fprintf(hf, "};\n\n");
    fflush( hf);

    // write footer
    fprintf( hf, "\n");
    fprintf( hf, "#endif \n\n");
    fflush( hf);
    fclose( hf);

    
    fprintf( stdout, "  >> terrain written to %s\n", hpp_fname);

    return;
}

Mesh::~Mesh(){
	
    // clear vector internal data
    // while vector is not empty.... delete item
    this->clear();


}

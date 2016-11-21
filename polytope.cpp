#include "polytope.h"

poly_vertex::poly_vertex(double c0, double c1, double c2) {
	x = c0;
	y = c1;
	z = c2;
	prev = 0;
	next = 0;
}

poly_vertex::poly_vertex() {
	x = 0.0;
	y = 0.0;
	z = 0.0;
	prev = 0;
	next = 0;
}

poly_edge::poly_edge(poly_vertex* v0, poly_vertex* v1)
{
  vertices[0] = v0;
  vertices[1] = v1;
  edge_vec = new vec_3D(v0, v1);
  prev = 0;
  next = 0;
}

vec_3D poly_edge::get_vector()
{
	return *edge_vec;
}

poly_face::poly_face(poly_vertex* v0, poly_vertex* v1, poly_vertex* v2, poly_edge* e0, poly_edge* e1, poly_edge* e2) {
  edges[0] = e0;
  edges[1] = e1;
  edges[2] = e2;
  vertices[0] = v0;
  vertices[1] = v1;
  vertices[2] = v2;
  normal = cross_product(edges[0]->get_vector(), edges[1]->get_vector());
  prev = 0;
  next = 0;
  visible = false;
}

vec_3D poly_face::get_normal()
{
	return normal;
}

void poly_face::mark_visible()
{
	visible = true;
	return;
}

void poly_face::operator=(const poly_face &rhs)
{
	edges[0] = rhs.edges[0];
	edges[1] = rhs.edges[1];
	edges[2] = rhs.edges[2];
	vertices[0] = rhs.vertices[0];
	vertices[1] = rhs.vertices[1];
	vertices[2] = rhs.vertices[2];
	return;
}

double dot_product(const vec_3D &vec1, const vec_3D &vec2)
{
	return (vec1.mag * vec2.mag) * 
		((vec1.dir[0] * vec2.dir[0]) + (vec1.dir[1] * vec2.dir[1]) + (vec1.dir[2] * vec2.dir[2]));
}

vec_3D cross_product(const vec_3D &vec1, const vec_3D &vec2)
{
	//performs basic 3D determinant
	double vec1_comp[3] = { vec1.dir[0] * vec1.mag, vec1.dir[1] * vec1.mag, vec1.dir[2] * vec1.mag };
	double vec2_comp[3] = { vec2.dir[0] * vec2.mag, vec2.dir[1] * vec2.mag, vec2.dir[2] * vec2.mag };
	double i = (vec1_comp[1] * vec2_comp[2]) - (vec1_comp[2] * vec2_comp[1]);
	double j = (vec1_comp[0] * vec2_comp[2]) - (vec1_comp[2] * vec2_comp[0]);
	double k = (vec1_comp[0] * vec2_comp[1]) - (vec1_comp[1] * vec2_comp[0]);
	vec_3D* new_vector = new vec_3D(i, j, k);
	return *new_vector;
}

vec_3D::vec_3D()
{
	mag = 0;
	dir[0] = 0;
	dir[1] = 0;
	dir[2] = 0;
}

vec_3D::vec_3D(poly_vertex* v0, poly_vertex* v1)
{
	mag = sqrt(pow(v0->x - v1->x, 2) + pow(v0->y - v1->y, 2) + pow(v0->z - v1->z, 2));
	dir[0] = (v0->x - v1->x) / mag;
	dir[1] = (v0->y - v1->y) / mag;
	dir[2] = (v0->z - v1->z) / mag;
}

vec_3D::vec_3D(double i, double j, double k)
{
	mag = sqrt(pow(i, 2) + pow(j, 2) + pow(k, 2));
	dir[0] = i / mag;
	dir[1] = j / mag;
	dir[2] = k / mag;
}
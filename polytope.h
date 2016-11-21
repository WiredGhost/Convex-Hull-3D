#include <math.h>

#ifndef POLYTOPE_H
#define POLYTOPE_H

template <typename T>
void remove(T self)
{
	self->next->prev = self->prev;
	self->prev->next = self->next;
	delete this;
	return;
}

template <typename T>
void append(T head, T obj)
{
	T cur = head;
	while (cur->next)
	{
		cur = cur->next;
	}
	cur->next = obj;
	obj->prev = cur;
	return;
}

template <typename T>
T get_next(T self)
{
	return self->next;
}

class poly_vertex {
public:
	poly_vertex(double c0, double c1, double c2);
	poly_vertex();
	template <typename T> friend void remove(T self);
	template <typename T> friend void append(T self, T obj);
	template <typename T> friend T get_next(T self);
	double x, y, z;
private:
	poly_vertex* next;
	poly_vertex* prev;
};

class vec_3D {
public:
	vec_3D();
	vec_3D(poly_vertex* v0, poly_vertex* v1);
	vec_3D(double i, double j, double k);
	friend double dot_product(const vec_3D &vec1, const vec_3D &vec2);
	friend vec_3D cross_product(const vec_3D &vec1, const vec_3D &vec2);
	double mag;
	double dir[3];
};

class poly_edge {
public:
  poly_edge(poly_vertex* v0, poly_vertex* v1);
  template <typename T> friend void remove(T self);
  template <typename T> friend void append(T self, T obj);
  template <typename T> friend T get_next(T self);
  vec_3D get_vector();
  poly_vertex* vertices[2]; // from and to respectively
  vec_3D* edge_vec;
private:
	poly_edge* next;
	poly_edge* prev;
};

class poly_face {
public:
  poly_face(poly_vertex* v0, poly_vertex* v1, poly_vertex* v2, poly_edge* e0, poly_edge* e1, poly_edge* e2);
  vec_3D get_normal();
  void mark_visible();
  template <typename T> friend void remove(T self);
  template <typename T> friend void append(T self, T obj);
  template <typename T> friend T get_next(T self);
  void operator=(const poly_face &rhs);
  poly_vertex* vertices[3];
  poly_edge* edges[3];
private:
	poly_face* next;
	poly_face* prev;
	vec_3D normal;
	bool visible;
};


#endif
/*
convex_hull_3D.cpp

computes a convex hull, should have an input file "input.txt" containing points in 3-tuples, ex)
1.0 1.0 1.0
2.0 3.0 5.0
8.0 2.0 9.0
-3.0 -6.0 0.0
0.0 0.0 0.0
4.0 2.0 4.0
....etc

computes 3D convex hull iteratively and sends output to "output.txt"

*/


using namespace std;

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "polytope.h"

//head units for each linked list
poly_vertex* points = new poly_vertex(0.0, 0.0, 0.0);
poly_edge* edges = new poly_edge(points, points);
poly_face* faces = new poly_face(points, points, points, edges, edges, edges);

//output edge and vertex list for Unity plot
//AS OF RIGHT NOW ASSUMES NO NULL VALUES
void buildOutput()
{
	poly_vertex* curv = points;
	poly_edge* cure = edges;
	ofstream outputFile;
	outputFile.open("C:\\Users\\eddie\\Documents\\CHull_IO\\chull_output.txt");
	//compile vertex list
	outputFile << "Vertices:" << endl;
	while (get_next(curv) != 0)
	{
		curv = get_next(curv);
		outputFile << "[ " << curv->x << ", " << curv->y << ", " << curv->z << " ]" << endl;
	}
	//compile edge list (to and from vertices)
	outputFile << endl << "Edges:" << endl;
	while (get_next(cure) != 0)
	{
		cure = get_next(cure);
		curv = cure->vertices[0];
		outputFile << "[ " << curv->x << ", " << curv->y << ", " << curv->z << " ] to ";
		curv = cure->vertices[1];
		outputFile << "[ " << curv->x << ", " << curv->y << ", " << curv->z << " ]" << endl;
	}
	outputFile.close();
	return;
}

double volume_tetra(poly_vertex* p, poly_face* f)
{
	//calculates the volume of tetrahedron formed by face f with point p
	return 0.0;
}

void add_point(double x, double y, double z)
{
	//simple: create poly_vertex instance, add to points list
	poly_vertex* new_point = new poly_vertex(x, y, z);
	append(points, new_point);
	return;
}

void add_face(poly_vertex* v0, poly_vertex* v1, poly_vertex* v2)
{
	//create face object
	poly_edge* edge0 = new poly_edge(v0, v1);
	poly_edge* edge1 = new poly_edge(v1, v2);
	poly_edge* edge2 = new poly_edge(v2, v0);
	poly_face* new_face = new poly_face(v0, v1, v2, edge0, edge1, edge2);

	//add new objects to lists
	append(edges, edge0);
	append(edges, edge1);
	append(edges, edge2);
	append(faces, new_face);
	
	return;
}

void convex_hull_iterative()
{
	//bring in all lists
	poly_vertex* p = points;
	poly_edge* e = edges;
	poly_face* f = faces;
	vec_3D* v;
	double volume;
	//iterate through all points
	while (get_next(p))
	{
		p = get_next(p);
		//determine if p is within polyhedron
		//iterate through faces: O(n)
		f = faces;
		while (get_next(f))
		{
			f = get_next(f);
			//first, project a vector from p to an arbitrary vertex
			v = new vec_3D(p, f->vertices[0]);
			//then, compute its dot product with face f's normal
			volume = dot_product(*v, f->get_normal());
			//purge v
			delete v;
			if (volume <= 0)
			{
				f->mark_visible();
			}
		}
		//THIS IS YOUR TIME TO SHINE, MITCHELL:
		//at this point, theoretically, all faces are marked "visible from point"
		//now, we must remove the visible faces (while preserving the edges)
		//then, remove any edges that have neither a left or right neighbor (internal edges)
		//then, create faces formed by all edges missing a left neighbor (border edges)
		  //and consequently edges from the endpoints of said edge to the newly added point p
		//this should form our "cone" and complete the convex hull for this iteration
	}
}


int main()
{

  //data input
  //disregard this block, Mitchell
  ifstream inputFile;
  int check = 0;
  string line;
  inputFile.open("C:\\Users\\eddie\\Documents\\CHull_IO\\input.txt");
  if (inputFile.is_open())
  {
	  double xtmp, ytmp, ztmp;
	  while (getline(inputFile, line))
	  {
		  istringstream iss(line);
		  iss >> xtmp >> ytmp >> ztmp;
		  cout << xtmp << " " << ytmp << " " << ztmp << endl;
		  add_point(xtmp, ytmp, ztmp);
		  check++;
	  }
	  if (check < 4) {
		  cout << "Not enough points. Press Enter to abort." << endl;
		  cin.get();
		  return 2;
	  }
  }
  else
  {
	  cout << "Could not open input file. Press Enter to abort." << endl;
	  cin.get();
	  return 1;
  }
  //done

  //then, build the output.
  buildOutput();
  cout << "Run successful. Press Enter to close." << endl;
  cin.get();
  return 0;
}
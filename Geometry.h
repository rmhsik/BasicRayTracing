#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Matrix.h"

class Screen{
	int H,W;
	int **Color;

	public:
		Screen();
		Screen(int w, int h);
		void SetScreen();
		void SetScreen(int w, int h);
		int GetWidth();
		int GetHeight();
		void SetColor(int i, int j, int value);
		int GetColor(int i, int j);
};

class Ray{
	Vec3 o, dir;
	
	public:
		Ray();
		Ray(Vec3 &origin, Vec3 &d);
		void SetRay(Vec3 &origin, Vec3 &d);
		Vec3 GetOrigin();
		Vec3 GetDirection();
};

class Sphere{
	Vec3 C;
	double r;

	public:
		Sphere(Vec3 &ceneter, const double &radius);
		Vec3 NormVec(Vec3 P);
		bool Intersection(Ray &ray, double &t, Vec3 &PI);
};

class Light{
	Vec3 P;

	public:
		Light(Vec3 &Position);
		Vec3 GetPosition();
};
#endif

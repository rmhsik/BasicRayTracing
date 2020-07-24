#include <iostream>
#include <cmath>
#include "Matrix.h"
#include "Geometry.h"

//////////////////////////////////////////
//	Screen Geometry					    //
//////////////////////////////////////////
Screen::Screen(){
	H=W=400;
	Color = new int*[W];
	for(int i=0;i<W;i++){
		Color[i] = new int[H];
	}
}

Screen::Screen(int w, int h){
	H=h;
	W=w;
	Color = new int*[W];
	for(int i=0;i<W;i++){
		Color[i] = new int[H];
	}
}

void Screen::SetScreen(){
	H=W=400;
	Color = new int*[W];
	for(int i=0;i<W;i++){
		Color[i] = new int[H];
	}
}

void Screen::SetScreen(int w, int h){
	H=h;
	W=w;
	Color = new int*[W];
	for(int i=0;i<W;i++){
		Color[i] = new int[H];
	}
}

int Screen::GetWidth(){
	return W;
}

int Screen::GetHeight(){
	return H;
}

void Screen::SetColor(int i, int j, int value){
	Color[i][j] = value;
}

int Screen::GetColor(int i, int j){
	return Color[i][j];
}


//////////////////////////////////////////
//	Sphere Geometry					    //
//////////////////////////////////////////
Sphere::Sphere(Vec3 &center, const double &radius){
	C = center;
	r = radius;
}

Vec3 Sphere::NormVec(Vec3 P){
	Vec3 N;
	N = (C-P)/r;
	return N;
}

bool Sphere::Intersection(Ray &ray, double &t, Vec3 &PI){
	Vec3 o = ray.GetOrigin();
	Vec3 dir = ray.GetDirection();
	Vec3 oc = o-C;
	
	double a = dir.dot(dir);
	double b = 2*oc.dot(dir);
	double c = oc.dot(oc) - r*r;
	
	double disc = b*b-4*a*c;
	double t0,t1;

	if(disc<0){return false;}
	else{
		t0 = (-b+sqrt(b*b-4*a*c))/(2*a);
		t1 = (-b-sqrt(b*b-4*a*c))/(2*a);
		t = (t0<t1) ? t0 : t1;
		PI = dir*t+o;
		return true;
	}
}

void Sphere::SpecularReflectedRay(Ray &ray, Vec3 &PI){	
	Matrix3 R = I() - 2.0*NormVec(PI).outer(NormVec(PI));
	Vec3 ReflectedDirection = R*ray.GetDirection();
	ray.SetRay(PI,ReflectedDirection);
}

//////////////////////////////////////////
//	Ray Geometry					    //
//////////////////////////////////////////

Ray::Ray(){
	//std::cout<<"Tried to create a ray without some parameter.\n";
	//std::exit(1);
}

Ray::Ray(Vec3 &origin, Vec3 &d){
	o=origin;
	dir =d;
}

void Ray::SetRay(Vec3 &origin, Vec3 &d){
	o = origin;
	dir = d;
}

Vec3 Ray::GetOrigin(){
	return o;
}

Vec3 Ray::GetDirection(){
	return dir;
}

bool Ray::Cast(class Sphere* objects, const int NObjects, Vec3& PI, int& idx){
	bool intersection_temp;
	bool intersection = false;
	double t = 20000;
	double t_temp = 200000;
	for (int n = 0; n < NObjects; n++){
		intersection_temp = objects[n].Intersection(*this, t_temp, PI);
		if (intersection_temp && t>t_temp){
			t = t_temp;
			idx = n;
			intersection = true;
		}
	}
	//std::cout<<"Intersection: "<<intersection;
	//std::cout<<" t: "<<t;
	//std::cout<<" Idx: "<<idx<<std::endl;
	return intersection; 	
}

bool Ray::Cast(class Sphere* objects,const int NObjects, Vec3& PI, int& idx, double& tt){
	bool intersection_temp;
	bool intersection = false;
	double t = 20000;
	double t_temp = 200000;
	for (int n = 0; n < NObjects; n++){
		intersection_temp = objects[n].Intersection(*this, t_temp, PI);
		if (intersection_temp && t>t_temp){
			t = t_temp;
			idx = n;
			intersection = true;
			tt = t;
		}
	}
	//std::cout<<"Intersection: "<<intersection;
	//std::cout<<" t: "<<t;
	//std::cout<<" Idx: "<<idx<<std::endl;
	return intersection;
}

//////////////////////////////////////////
//	ShadowRay Geometry				    //
//////////////////////////////////////////
ShadowRay::ShadowRay(Vec3& PI, class Light& light){
	Vec3 LightVecN = (PI - light.GetPosition()).norm();
	Ray::SetRay(PI, LightVecN);
}

bool ShadowRay::Cast(class Sphere* objects, const int Nobjects, Vec3& PI, int& idx){
	Vec3 dummyPI;
	int tempIdx;
	bool intersection = false;
	bool intersection_temp = false;
	double t=2000;
	intersection_temp = Ray::Cast(objects, Nobjects, PI, tempIdx, t);
	if(intersection_temp && tempIdx != idx){
		intersection = true;
	}
	return intersection;
}

//////////////////////////////////////////
//	Light Geometry					    //
//////////////////////////////////////////
Light::Light(Vec3 &Position){
	P = Position;
}

Vec3 Light::GetPosition(){
	return P;
}


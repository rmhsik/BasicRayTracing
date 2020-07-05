#include <cmath>
#include "Matrix.h"

Vec3::Vec3(){x=y=z=0;}
Vec3::Vec3(double i, double j, double k){
	x=i;
	y=j;
	z=k;
}
Vec3 Vec3::operator* (double d){Vec3 vec; vec.x=d*x;vec.y=d*y,vec.z=d*z; return vec;}
Vec3 Vec3::operator- (Vec3 vec){Vec3 vecr; vecr.x = x - vec.x; vecr.y = y-vec.y; vecr.z = z-vec.z; return vecr;}
Vec3 Vec3::operator+ (Vec3 vec){Vec3 vecr; vecr.x = x + vec.x; vecr.y = y+vec.y; vecr.z = z+vec.z; return vecr;}
Vec3 Vec3::operator/ (double d){Vec3 vecr; vecr.x = x/d; vecr.y = y/d; vecr.z = z/d; return vecr;}

double Vec3::dot(class Vec3 vec){return x*vec.x+y*vec.y+z*vec.z;}
Vec3 Vec3::cross(Vec3 vec){Vec3 vecr; vecr.x = y*vec.z - z*vec.y;
			    vecr.y = z*vec.x - x*vec.z;
			    vecr.z = x*vec.y - y*vec.x;
			    return vecr;}
double Vec3::mod(){return sqrt(x*x+y*y+z*z);}
Vec3 Vec3::norm(){Vec3 temp; temp.x = x/mod();temp.y = y/mod();temp.z = z/mod(); return temp;}
double Vec3::angle(class Vec3 vec){return acos((dot(vec))/(mod()*vec.mod()));}

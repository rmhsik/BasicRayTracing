#include <cmath>
#include <iostream>
#include <cassert>
#include "Matrix.h"


//////////////////////////////////////////
//	Vec3 Implementation					//
//////////////////////////////////////////

Vec3::Vec3(){vec[0]=vec[1]=vec[2]=0;}
Vec3::Vec3(double i, double j, double k){
	vec[0]=i;
	vec[1]=j;
	vec[2]=k;
}

Vec3 Vec3::operator* (double d){
	Vec3 vecr;
	vecr(0)=d*vec[0];
	vecr(1)=d*vec[1];
	vecr(2)=d*vec[2]; 
	return vecr;
}

Vec3 operator* (double d, Vec3& Vec){
	return Vec*d;
}
Vec3 Vec3::operator- (Vec3 Vec){
	Vec3 vecr;
	vecr(0) = vec[0] - Vec(0);
	vecr(1) = vec[1] - Vec(1);
	vecr(2) = vec[2] - Vec(2);
	 return vecr;
}

Vec3 Vec3::operator+ (Vec3 Vec){
	Vec3 vecr; 
	vecr(0) = vec[0] + Vec(0);
	vecr(1) = vec[1] + Vec(1); 
	vecr(2) = vec[2] + Vec(2);
	return vecr;}

Vec3 Vec3::operator/ (double d){
	Vec3 vecr; 
	vecr(0) = vec[0]/d;
	vecr(1) = vec[1]/d; 
	vecr(2) = vec[2]/d; 
	return vecr;
}

double& Vec3::operator()(int idx){
	assert( idx>=0 && idx<3);
	return vec[idx];
}

const double& Vec3::operator()(int idx) const{	
	assert( idx>=0 && idx<3);
	return vec[idx];
}

std::ostream &operator<<(std::ostream &out, const Vec3 &Vec){
	out<<"(";
	for(int i=0;i<3;i++){
		if(i!=2)
			out<<Vec(i)<<",";
		else
			out<<Vec(i);
	}
	out<<")"<<std::endl;
	return out;
}

double Vec3::dot(Vec3 Vec){
	return vec[0]*Vec(0)+vec[1]*Vec(1)+vec[2]*Vec(2);
}

Vec3 Vec3::cross(Vec3 Vec){
	Vec3 vecr;
	vecr(0) = vec[1]*Vec(2) - vec[2]*Vec(1);
	vecr(1) = vec[2]*Vec(0) - vec[0]*Vec(2);
	vecr(2) = vec[0]*Vec(1) - vec[1]*Vec(0);
    return vecr;
}

double Vec3::mod(){
	return sqrt(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]);
}

Vec3 Vec3::norm(){
	Vec3 temp; 
	temp(0) = vec[0]/mod();
	temp(1) = vec[1]/mod();
	temp(2) = vec[2]/mod(); 
	return temp;
}

double Vec3::angle(Vec3 Vec){
	return acos((dot(Vec))/(mod()*Vec.mod()));
}

class Matrix3 Vec3::outer(Vec3 Vec){
	Matrix3 M;
	for(int i=0; i<3; i++){
		for(int j=0;j <3; j++){
			M(i,j) = vec[i]*Vec(j);
		}
	}
	return M;
}
//////////////////////////////////////////
//	Matrix3 Implementation		        //
//////////////////////////////////////////

Matrix3::Matrix3(){
	for(int i = 0; i<3;i++){
		for(int j = 0; j<3;j++){
			M[i][j] = 0.0;
		}
	}
}

std::ostream &operator<<(std::ostream &out, const Matrix3 &A){
	for(int i=0;i<3;i++){
		for(int j=0; j<3;j++){
			out<<"|"<<A.M[i][j]<<"|";
		}
	out<<std::endl;
	}
	return out;
}

double& Matrix3::operator()(int idx, int jdx){	
	assert(idx>=0 && idx<3);
	assert(jdx>=0 && jdx<3);
	return M[idx][jdx];
}

Matrix3 Matrix3::operator+(Matrix3 B){
	Matrix3 C;
	for(int i=0; i<3; i++){
		for (int j = 0; j<3; j++){
			C(i,j) = M[i][j] + B(i,j);
		}
	}
	return C;

}

Matrix3 Matrix3::operator-(Matrix3 B){
	Matrix3 C;
	for(int i=0; i<3; i++){
		for (int j = 0; j<3; j++){
			C(i,j) = M[i][j] - B(i,j);
		}
	}
	return C;

}

Matrix3 Matrix3::operator*(Matrix3 B){
	Matrix3 R;
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			for(int k=0; k<3; k++){
				R(i,j) += M[i][k]*B(k,j);
			}
		}
	}
	return R;
}

Matrix3 Matrix3::operator*(double d){
	Matrix3 R;
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			for(int k=0; k<3; k++){
				R(i,j) = d*M[i][k];
			}
		}
	}
	return R;
}

Matrix3 operator* (double d, Matrix3 M){
	return M*d;
}

Vec3 Matrix3::operator*(Vec3 V){
	Vec3 Vr;
	for(int i=0;i<3;i++){
		for(int j=0; j<3;j++){
			Vr(i) += M[i][j]*V(j);
		}
	}
	return Vr;
}

I::I(){
	Matrix3::operator()(0,0) = 1.0;	
	Matrix3::operator()(1,1) = 1.0;
	Matrix3::operator()(2,2) = 1.0;
}

#ifndef MATRIX_H
#define MATRIX_H
#include<ostream>

class Vec3{
   double vec[3];  
   public:
		Vec3();
		Vec3(double i, double j, double k);
		Vec3 operator+ (Vec3 Vec);
		Vec3 operator- (Vec3 Vec);
		Vec3 operator* (double d);
		//Vec3 operator* (double d, Vec3& Vec);
		Vec3 operator/ (double d);
		double& operator() (int idx);
		const double& operator() (int idx) const;
		friend std::ostream &operator<<(std::ostream &out, const Vec3 &Vec);
		double dot(Vec3 Vec);
		Vec3 cross(Vec3 Vec);
		double mod();
		Vec3 norm();
		double angle(Vec3 Vec);
		class Matrix3 outer(Vec3 Vec);
};

// Make product in both directions.
Vec3 operator* (double d, Vec3& Vec);

class Matrix3{
	const int n = 3;
	double M[3][3];		
	public:
		Matrix3();
		friend std::ostream &operator<<(std::ostream &out, const Matrix3 &A);
		double& operator()(int idx, int jdx);
		Matrix3 operator+ (Matrix3 B);
		Matrix3 operator- (Matrix3 B);
		Matrix3 operator*(Matrix3 B);
		Matrix3 operator*(double d);
		Vec3 operator*(Vec3 V);
};

Matrix3 operator* (double d, Matrix3 M);

class I: public Matrix3{
	public:
		I();
};
		
#endif

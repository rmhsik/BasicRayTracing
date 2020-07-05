#ifndef MATRIX_H
#define MATRIX_H

class Vec3{
    public:
        double x, y, z;
        Vec3();
	Vec3(double i, double j, double k);
	Vec3 operator+ (Vec3 vec);
        Vec3 operator- (Vec3 vec);
        Vec3 operator* (double d);
        Vec3 operator/ (double d);

        double dot(class Vec3 vec);
        Vec3 cross(Vec3 vec);
        double mod();
        Vec3 norm();
        double angle(class Vec3 vec);
};
#endif

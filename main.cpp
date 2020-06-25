#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

struct Vec3{
    double x,y,z;
    Vec3(){x=y=z=0;}
    Vec3(double i, double j, double k){x=i;y=j;z=k;}

    Vec3 operator *(double d){Vec3 vec; vec.x=d*x;vec.y=d*y,vec.z=d*z; return vec;}
    Vec3 operator - (Vec3 vec){Vec3 vecr; vecr.x = x - vec.x; vecr.y = y-vec.y; vecr.z = z-vec.z; return vecr;}
    Vec3 operator + (Vec3 vec){Vec3 vecr; vecr.x = x + vec.x; vecr.y = y+vec.y; vecr.z = z+vec.z; return vecr;}
    Vec3 operator / (double d){Vec3 vecr; vecr.x = x/d; vecr.y = y/d; vecr.z = z/d; return vecr;}

    double dot(Vec3 vec){return x*vec.x+y*vec.y+z*vec.z;}
    Vec3 cross(Vec3 vec){Vec3 vecr; vecr.x = y*vec.z - z*vec.y;
                                    vecr.y = z*vec.x - x*vec.z;
                                    vecr.z = x*vec.y - y*vec.x;
                                    return vecr;}
    double mod(){return sqrt(x*x+y*y+z*z);}
    Vec3 norm(){Vec3 temp; temp.x = x/mod();temp.y = y/mod();temp.z = z/mod(); return temp;}
    double angle(Vec3 vec){return acos((dot(vec))/(mod()*vec.mod()));}
};

class Screen{
    int H,W;
    int **Color;
    
    public:
        Screen(){H=W=400; Color = new int*[W]; for (int i=0;i<W;i++){Color[i] = new int[H];}}
        Screen(int h, int w){H=h;W=w;  Color = new int*[W]; for (int i=0;i<W;i++){Color[i] = new int[H];}}
        void SetScreen(){H=W=400;  Color = new int*[W]; for (int i=0;i<W;i++){Color[i] = new int[H];}}
        void SetScreen(int h, int w){H=h;W=w;  Color = new int*[W]; for (int i=0;i<W;i++){Color[i] = new int[H];}}
        int GetWidth(){return W;}
        int GetHeight(){return H;}
        void SetColor(int i, int j,int value){
            Color[i][j] = value;
        }
        int GetColor(int i, int j){
            return Color[i][j];
        }
};

class Ray{
    Vec3 o, dir;
    
    public:
        Ray(){throw "Tried to create a ray without some parameter.";}
        Ray(Vec3 &origin,Vec3 &d){o = origin; dir= d;}
        void SetRay(Vec3 &origin,Vec3 &d){origin = o; dir= d;}
        Vec3 GetOrigin(){return o;}
        Vec3 GetDirection(){return dir;}
};

class Light{
    Vec3 P;

    public:
        Light(Vec3 &Position){P = Position;}
        Vec3 GetPosition(){return P;}
};

class Sphere{
    Vec3 C;
    double r;
    
    public:
        Sphere(Vec3 &center,const double &radius){C = center; r = radius;}
        Vec3 NormVec(Vec3 P){Vec3 N; N = (C-P)/r; return N;}
        bool Intersection(Ray &ray,double &t, Vec3 &PI){
            Vec3 o = ray.GetOrigin();
            Vec3 dir = ray.GetDirection();
            Vec3 oc = o - C;
            double a = dir.dot(dir);
            double b = 2*oc.dot(dir);
            double c = oc.dot(oc) - r*r;

            double disc = b*b-4*a*c;
            double t0,t1;
            if(disc<0){return false;}
            else{t0 = (-b + sqrt(b*b-4*a*c))/(2*a);
                 t1 = (-b - sqrt(b*b-4*a*c))/(2*a); 
                 t = (t0<t1)? t0 : t1;
                 PI = dir*t+o;  //Intersection point of the ray and the sphere
                 return true;}
        }
};

int main(){
    Vec3 center1(160,200,100);
    Vec3 center2(240,240,300);
    Vec3 center3(250,220,100);
    Vec3 dir(0,0,1);
    Vec3 LightPosition(200,150,0);

    Screen screen(400,400);

    int NObjects = 3;
    Sphere sph1(center1,50);
    Sphere sph2(center2,100);
    Sphere sph3(center3,30);

    Light light(LightPosition);
    int W = screen.GetWidth();
    int H = screen.GetHeight();
    
    Sphere *objects[NObjects] ;
    objects[0] = &sph1;
    objects[1] = &sph2;
    objects[2] = &sph3;

    ofstream out("out.pgm");
    out << "P2 \n 400 400 \n 255\n"; 

    cout<<"Initilizing background..."<<endl;
   	for(int i=0;i<W;i++){
       	for(int j=0;j<H;j++){ 
    		screen.SetColor(i,j,60);
    	}
    }
    cout<<"Background finished."<<endl;
    cout<<"Evaluating..."<<endl;

    for(int i=0;i<W;i++){
        for(int j=0;j<H;j++){
            Vec3 PI;
            Vec3 PI_temp;
            Vec3 o(i,j,0);
            Ray ray(o,dir);
            double t_temp = 20000;
            double t = 200000;
            int idx = 0;
            bool intersection = false;
            bool oneintersection = false;
            for (int n=0;n<NObjects;n++){
                intersection = objects[n]->Intersection(ray,t_temp,PI_temp);
                if(intersection && t>t_temp){
                    t = t_temp;
                    PI = PI_temp;
                    idx = n;
                    oneintersection = true;

                    int ColorValue;
	                double K;
	                // Clamp to 1.0
	                Vec3 LightVec = PI-light.GetPosition();
	                Vec3 LightVecN = (PI-light.GetPosition()).norm();

	                Ray ShadowRay(PI,LightVecN);
	                Vec3 dummyPI;
	                bool flag = true;
	                for(int m=0; m<NObjects;m++){
						double dummyt = 200000;
	                	if (objects[m]->Intersection(ShadowRay,dummyt,dummyPI) && m!=n && dummyt<0){
	                		flag = false;
	                		//cout<<dummyt<<endl;
	                	}
	                }

	                if(flag){
	                	K = (LightVec).norm().dot(objects[n]->NormVec(PI));
	                	K = (K < 0) ? 0.0 : K;
	                	K = (K > 1.0) ? 1.0 : K;
	                	ColorValue = (int)(K*255);
	                	screen.SetColor(i,j,ColorValue);
	                }
	                else{
	                	screen.SetColor(i,j,0);
	                }
                }
            }
        }
    }
        
    cout<<"Evaluation finished."<<endl;
    cout<<"Saving to a file..."<<endl;

    for(int i=0;i<W;i++){
        for(int j=0;j<H;j++){
            out<<(int)screen.GetColor(j,i)<<endl;
        }
    }

    cout<<"Saving finished."<<endl;
    return 0;
} 
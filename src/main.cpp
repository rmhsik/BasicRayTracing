#define BG_COLOR 0.24

#include <fstream>
#include <iostream>
#include <cmath>
#include "Matrix.h"
#include "Geometry.h"

using namespace std;


int main(){
    Vec3 center1(160,200,100);
    Vec3 center2(240,240,200);
    Vec3 center3(250,220,50);
    Vec3 center4(250,20,90);
    Vec3 LightPosition(50,200,0);
    Vec3 dir(0,0,1);

    Screen screen(400,400);

    int NObjects = 4;
    Sphere sph1(center1,50);
    Sphere sph2(center2,100);
    Sphere sph3(center3,30);
    Sphere sph4(center4,40);
    
    Light light(LightPosition);
    int W = screen.GetWidth();
    int H = screen.GetHeight();
    
    Sphere *objects[NObjects] ;
    objects[0] = &sph1;
    objects[1] = &sph2;
    objects[2] = &sph3;
    objects[3] = &sph4;
    ofstream out("out.pgm");
    out << "P2 \n 400 400 \n 255\n"; 

    cout<<"Initilizing background..."<<endl;
   	for(int i=0;i<W;i++){
	    for(int j=0;j<H;j++){ 
    		screen.SetColor(i,j,BG_COLOR);
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
			double K = BG_COLOR;
			int ColorValue;
			bool flag, flag2 = true;
            int idx = 0;
            bool intersection = false;
            bool oneintersection = false;
			for(int k=0; k<1; k++){
				for (int n=0;n<NObjects;n++){
					intersection = objects[n]->Intersection(ray,t_temp,PI);
					if(intersection && t>t_temp){
						t = t_temp;
						idx = n;
						flag = flag2 = true;	
						Vec3 LightVec = PI-light.GetPosition();
						Vec3 LightVecN = (PI-light.GetPosition()).norm();
						Ray ShadowRay(PI,LightVecN);
						Vec3 dummyPI;
						K = (LightVec).norm().dot(objects[n]->NormVec(PI));
			
						for(int m=0; m<NObjects;m++){
							double dummyt = 200000;
							if (objects[m]->Intersection(ShadowRay,dummyt,dummyPI) && m!=n &&dummyt<0){
								flag2 = false;
								K = 0;
							}
						}
					}	
				}
			}
			K = (K < 0) ? 0.0 : K;
			K = (K > 1.0) ? 1.0 : K;		
			ColorValue = (int)(K*255);
			screen.SetColor(i,j,ColorValue);		
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

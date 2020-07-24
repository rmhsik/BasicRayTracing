#define BG_COLOR 0.24

#include <fstream>
#include <iostream>
#include <cmath>
#include "Matrix.h"
#include "Geometry.h"

using namespace std;


int main(){
    Vec3 center1(200,160,100);
    Vec3 center2(240,240,300);
    Vec3 center3(250,220,40);
    Vec3 center4(150,200,90);
    Vec3 LightPosition(80,80,-100);
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
            Vec3 o(i,j,0);
            Ray ray(o,dir);
           	double K = BG_COLOR;
			int ColorValue;
            int idx = 0;
        	for(int k=0; k<1; k++){
				if(ray.Cast(*objects, NObjects, PI, idx)){
					// ShadowRay behaviour:
					//	  if cast == True and object is not itself, then:
					//		 Ray from Light Source is bloced: K = 0
					//    if cast == False, then:
					//		 Ray from Light Source is not blocked: K = (ShadowRay.dir)·(object.Norm)
					Vec3 dummyPI;
					ShadowRay SRay(PI, light);
					K = SRay.GetDirection().dot(objects[idx]->NormVec(PI));
					//if(SRay.Cast(*objects, NObjects, dummyPI, idx)){
					//	K=0.0;
					//}
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

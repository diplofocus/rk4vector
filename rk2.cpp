#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>

#include "vect.h"
#include "planets.h"

using namespace std;

const int elements = 5;
const double tmax = 100 * 3.15569e7;
const double dt = 10 * 3600;
const double G = 6.67e-11;

int snapshot = 30;

double cube(double a)
{
  return a*a*a;
}

double sqr(double a)
{
  return a*a;
}

double dist(Vect A, Vect B)
{
  return sqrt(sqr(B.x - A.x) + sqr(B.y - A.y));
}

class Body
{
public:
  Vect r,r1,r2,r3,r4;
  Vect v,v1,v2,v3,v4;
  Vect a,a1,a2,a3,a4;
  float m;

  Body()
  {
    m = 0;
  }

  Body(Vect R, Vect V, double M)
  {
    r = R;
    v = V;
    m = M;
  }
};

//planets
Vect rSun(xSun, ySun, 0);
Vect vSun(vxSun, vySun, 0);
Vect rJupiter(xJupiter, yJupiter, 0);
Vect vJupiter(vxJupiter, vyJupiter, 0);
Vect rSaturn(xSaturn, ySaturn, 0);
Vect vSaturn(vxSaturn, vySaturn, 0);
Vect rUranus(xUranus, yUranus, 0);
Vect vUranus(vxUranus, vyUranus, 0);
Vect rNeptune(xNeptune, yNeptune, 0);
Vect vNeptune(vxNeptune, vyNeptune, 0);
//planets

int main()
{
  ofstream out;
  out.open("out.txt");
  Body bodies[elements];
  for(int i = 0; i < elements; i++)
    bodies[i] = Body();

  bodies[0] = Body(rSun, vSun, mSun);
  bodies[1] = Body(rJupiter, vJupiter, mJupiter);
  bodies[2] = Body(rSaturn, vSaturn, mSaturn);
  bodies[3] = Body(rUranus, vUranus, mUranus);
  bodies[4] = Body(rNeptune, vNeptune, mNeptune);
 

  for(double t = 0; t < tmax; t+=dt)
    {



      for(int i = 0; i < elements; i++)
	{
	  bodies[i].r1 = bodies[i].r;
	  bodies[i].v1 = bodies[i].v;
	  
	  bodies[i].a1.x = 0;
	  bodies[i].a1.y = 0;
	  bodies[i].a2.x = 0;
	  bodies[i].a2.y = 0;
	  bodies[i].a3.x = 0;
	  bodies[i].a3.y = 0;
	  bodies[i].a4.x = 0;
	  bodies[i].a4.y = 0;
	}

      //k1 begin
      for(int i = 0; i < elements; i++)
	{
	  for(int j = 0; j < elements; j++)
	    {
	      if(j == i)
		continue;
	      bodies[i].a1.x += -G * bodies[j].m * (bodies[i].r1.x - bodies[j].r1.x) / cube(dist(bodies[i].r1, bodies[j].r1));
	      bodies[i].a1.y += -G * bodies[j].m * (bodies[i].r1.y - bodies[j].r1.y) / cube(dist(bodies[i].r1, bodies[j].r1));
	    }
	}
      for(int i = 0; i < elements; i++)
	{
	  bodies[i].r1 = bodies[i].r;
	  bodies[i].v1 = bodies[i].v;
	}

      //k1 end


      //k2 begin
      for(int i = 0; i < elements; i++)
	{
	  for(int j = 0; j < elements; j++)
	    {
	      if(j == i)
		continue;
	      bodies[i].a2.x += -G * bodies[j].m * (bodies[i].r2.x - bodies[j].r2.x) / cube(dist(bodies[i].r2, bodies[j].r2));
	      bodies[i].a2.y += -G * bodies[j].m * (bodies[i].r2.y - bodies[j].r2.y) / cube(dist(bodies[i].r2, bodies[j].r2));
	    }
	}

      for(int i = 0; i < elements; i++)
	{
	  bodies[i].v2.x = bodies[i].v.x + bodies[i].a1.x * dt/2;
	  bodies[i].v2.y = bodies[i].v.y + bodies[i].a1.y * dt/2;

	  bodies[i].r2.x = bodies[i].r.x + bodies[i].v1.x * dt/2;
	  bodies[i].r2.y = bodies[i].r.y + bodies[i].v1.y * dt/2;
	}
      //k2 end

      //k3 begin
      for(int i = 0; i < elements; i++)
	{
	  bodies[i].v3.x = bodies[i].v.x + bodies[i].a2.x * dt/2;
	  bodies[i].v3.y = bodies[i].v.y + bodies[i].a2.y * dt/2;

	  bodies[i].r3.x = bodies[i].r.x + bodies[i].v2.x * dt/2;
	  bodies[i].r3.y = bodies[i].r.y + bodies[i].v2.y * dt/2;
	}

      for(int i = 0; i < elements; i++)
	{
	  for(int j = 0; j < elements; j++)
	    {
	      if(j == i)
		continue;
	      bodies[i].a3.x += -G * bodies[j].m * (bodies[i].r3.x - bodies[j].r3.x) / cube(dist(bodies[i].r3, bodies[j].r3));
	      bodies[i].a3.y += -G * bodies[j].m * (bodies[i].r3.y - bodies[j].r3.y) / cube(dist(bodies[i].r3, bodies[j].r3));
	    }
	}
      //k3 end

      //k4 begin
      for(int i = 0; i < elements; i++)
	{
	  bodies[i].v4.x = bodies[i].v.x + bodies[i].a3.x * dt/2;
	  bodies[i].v4.y = bodies[i].v.y + bodies[i].a3.y * dt/2;

	  bodies[i].r4.x = bodies[i].r.x + bodies[i].v3.x * dt/2;
	  bodies[i].r4.y = bodies[i].r.y + bodies[i].v3.y * dt/2;
	}

      for(int i = 0; i < elements; i++)
	{
	  for(int j = 0; j < elements; j++)
	    {
	      if(j == i)
		continue;
	      bodies[i].a4.x += -G * bodies[j].m * (bodies[i].r4.x - bodies[j].r4.x) / cube(dist(bodies[i].r4, bodies[j].r4));
	      bodies[i].a4.y += -G * bodies[j].m * (bodies[i].r4.y - bodies[j].r4.y) / cube(dist(bodies[i].r4, bodies[j].r4));
	    }
	}
      //k4 end

      //sum
      for(int i = 0; i < elements; i++)
	{
	  bodies[i].r.x += dt/6 * (bodies[i].v1.x + 2*bodies[i].v2.x + 2*bodies[i].v3.x + bodies[i].v4.x);
	  bodies[i].r.y += dt/6 * (bodies[i].v1.y + 2*bodies[i].v2.y + 2*bodies[i].v3.y + bodies[i].v4.y);
	  bodies[i].v.x += dt/6 * (bodies[i].a1.x + 2*bodies[i].a2.x + 2*bodies[i].a3.x + bodies[i].a4.x);
	  bodies[i].v.y += dt/6 * (bodies[i].a1.y + 2*bodies[i].a2.y + 2*bodies[i].a3.y + bodies[i].a4.y);

	  out << bodies[i].r.x << " " << bodies[i].r.y << endl;
	}
      //sum

    }//time
  out.close();
}

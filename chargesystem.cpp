#include "chargesystem.h"
#include <algorithm>

 void ChargeSystem::normalize()
 {
   std::for_each(d_particles.begin(), d_particles.end(), [](PhasePoint& io_pnt) { io_pnt.d_p.doNormalize(); } );
 }

 bool ChargeSystem::solve()
 {
   const double c_smallVelocitiesSq = 0.0001*0.0001;
   const int c_maxIters = 1000000;
   normalize();
   int n = d_particles.size();
   std::vector<PhasePoint> newPP( n );
   int iter = 0;
   do
   {
     for( int i = 0; i < n; ++i)
     {
       PhasePoint& pp = d_particles[i];
       PhasePoint& newpp = newPP[i];
       newpp.d_p = pp.d_p + d_t * pp.d_v;
       newpp.d_p.doNormalize();
       newpp.d_v = pp.d_v + d_t * getForce(i); // unit mass
       newpp.d_v -= (newpp.d_p * newpp.d_v) * newpp.d_p; // dv * dp == 0 always
     }
     d_particles.swap(newPP);
     ++iter;
   } 
   while( movement() > c_smallVelocitiesSq && iter < c_maxIters);
   return iter < c_maxIters;
 }

 std::vector<Vector3D> ChargeSystem::getPositions() const
 {
   std::vector<Vector3D> res( d_particles.size() );
   std::transform(d_particles.begin(), d_particles.end(), res.begin(), 
     [](const PhasePoint& i_pnt) { return i_pnt.d_p; } );
   return res;
 }

 Vector3D ChargeSystem::getForce(int c) const
 {
   int n = d_particles.size();
   const PhasePoint& current = d_particles[c];
   Vector3D force( -10. * current.d_v ); // viscosity
   for(int i = 0; i < n; ++i)
   {
     if(i == c)
       continue;
     Vector3D d = current.d_p - d_particles[i].d_p;
     double len = d.length();
     force += 1./(len * len * len) * d;
   }
   force -= (force * current.d_p) * current.d_p;
   return force;
 }

 double ChargeSystem::movement() const
 {
   double movementMax = -1;
   int n = d_particles.size();
   for(int i = 0; i < n; ++i)
   {
     double m = d_particles[i].d_v.lenSqr();
     if( m > movementMax )
       movementMax = m;
   }
   return movementMax;
 }
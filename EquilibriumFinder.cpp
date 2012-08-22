#include "EquilibriumFinder.h"

void EquilibriumFinder::add(const Vector3D& i_point)
{
  d_particles.push_back( unit(i_point) );
}

std::vector<Vector3D> EquilibriumFinder::getPositions() const
{
  return d_particles;
}

void EquilibriumFinder::getPositions(std::vector<Vector3D>& o_points)
{
  std::swap(d_particles, o_points);
  d_particles.clear();
}

bool EquilibriumFinder::solve()
{
  const int c_maxIters = 1000000;
  const double c_maxMovement = 1e-5 * 1e-5;
  int n = d_particles.size();
  std::vector<Vector3D> newPos(n);
  int iters = 0;
  double movement;
  do
  {
    movement = 0.;
    for(int i = 0; i < n; ++i)
    {
      Vector3D f_i = d_t * getForce(i);
      movement = std::max( movement, lenSqr(f_i) );
      newPos[i] = d_particles[i] + f_i;
      makeUnit(newPos[i]);
    }
    ++iters;
    d_particles.swap(newPos);
  }
  while(movement > c_maxMovement && iters < c_maxIters);

  if(iters >= c_maxIters)
    return false;

  return true;
}

Vector3D EquilibriumFinder::getForce(int c) const
{
  int n = d_particles.size();
  const Vector3D& current = d_particles[c];
  Vector3D force;

  for(int i = 0; i < n; ++i)
  {
    if(i == c)
      continue;
    force += coulombForce(current, d_particles[i]);
  }
  force -= (force * current) * current; // force is acting in tangent space of the unit sphere
  return force;
}



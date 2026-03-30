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
  constexpr int c_maxIters = 1000000;
  constexpr double c_maxMovement = 1e-5 * 1e-5;
  auto n = d_particles.size();
  std::vector<Vector3D> newPos(n);
  int iters = 0;
  double maxForce = 0.;
  do
  {
    maxForce = 0.;
    newPos[0] = d_particles[0]; // don't move first point
    for(int i = 1; i < n; ++i) 
    {
      auto force = getForce(i);
      Vector3D f_i = d_t * force;
      maxForce = std::max(maxForce, lenSqr(force));
      newPos[i] = d_particles[i] + f_i;
      makeUnit(newPos[i]);
    }
    ++iters;
    d_particles.swap(newPos);
  }
  while(maxForce > c_maxMovement && iters < c_maxIters);

  if(iters >= c_maxIters)
    return false;

  return true;
}

Vector3D EquilibriumFinder::getForce(int c) const
{
  const auto n = d_particles.size();
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



#pragma once

#include <vector>
#include "Vector3.h"
#include "coulomb.h"

class EquilibriumFinder
{
public:
  explicit EquilibriumFinder(double i_step): d_t(i_step) {}
  void add(const Vector3D& i_point);
  bool solve();
  std::vector<Vector3D> getPositions() const;
  void getPositions(std::vector<Vector3D>& o_points);

private:
  Vector3D getForce(int i) const;
  std::vector<Vector3D> d_particles;
  double d_t;
};
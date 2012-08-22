#pragma once

#include <vector>
#include "Vector3.h"

class ChargeSystem
{
public:
  struct PhasePoint
  {
    PhasePoint(): d_p(), d_v() {}

    explicit PhasePoint(const Vector3D& i_p): d_p(i_p)
    {}

    PhasePoint(const Vector3D& i_p, const Vector3D& i_v): d_p(i_p), d_v(i_v) 
    {}

    Vector3D d_p;
    Vector3D d_v;
  };

  explicit ChargeSystem(double i_dt): d_t(i_dt)
  {
  }

  void add(const Vector3D& i_p)
  {
    d_particles.push_back( PhasePoint(i_p) );
  }

  bool solve();

  std::vector<Vector3D> getPositions() const;

private:
  void normalize();
  Vector3D getForce(int i) const;
  double movement() const;

  std::vector<PhasePoint> d_particles;
  double d_t;
};


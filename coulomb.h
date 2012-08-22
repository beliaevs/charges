#pragma once

#include "Vector3.h"

// Coulomb force acting on unit charge i_target from unit charge i_other
inline Vector3D coulombForce(const Vector3D& i_target, const Vector3D& i_other)
{
  Vector3D d = i_target - i_other;
  Vector3D u = unit(d);
  return u/lenSqr(d);
}

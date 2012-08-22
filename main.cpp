#include<iostream>
#include<sstream>
#include<cstdlib>

#include "chargesystem.h"
#include "EquilibriumFinder.h"

Vector3D randomVector()
{
  Vector3D res;
  res.x = double(std::rand())/RAND_MAX;
  res.y = double(std::rand())/RAND_MAX;
  res.z = double(std::rand())/RAND_MAX;
  return res;
}

template<typename ChargeSystem>
void addCharges(ChargeSystem& o_charges, int n)
{
  for(int i = 0; i < n; ++i)
  {
    Vector3D v = randomVector();
    o_charges.add(v);
  }
}

void outputChargesMathematicaFormat(std::ostream& os, const std::vector<Vector3D>& i_points)
{
  os << "Graphics3D[{PointSize[Large], Point[{\n";
  for(int i = 0; i < i_points.size(); ++i)
  {
    os << "{" << i_points[i] << "}";
    if( i+1 != i_points.size() )
      os << ", ";
  }
  os << "}], Opacity[0.5], Sphere[]}]\n";
}

int main()
{/*
  {
    ChargeSystem charges(0.01);
    addCharges(charges, 100);

    if( !charges.solve() )
    {
      std::cout << "pesec!\n";
      return 0;
    }
    std::vector<Vector3D> res = charges.getPositions();
    outputChargesMathematicaFormat(std::cout, res);
  }*/
  {
    EquilibriumFinder finder(0.001);
    addCharges(finder, 200);
    if( !finder.solve() )
    {
      std::cout << "pesec!\n";
      return 0;
    }
    std::vector<Vector3D> res = finder.getPositions();
    outputChargesMathematicaFormat(std::cout, res);
  }
 return 0;
}

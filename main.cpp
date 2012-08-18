#include<iostream>
#include<sstream>
#include<cstdlib>

#include "chargesystem.h"

Vector3D randomVector()
{
  Vector3D res;
  res.x = double(std::rand())/RAND_MAX;
  res.y = double(std::rand())/RAND_MAX;
  res.z = double(std::rand())/RAND_MAX;
  return res;
}

void addCharges(ChargeSystem& o_charges, int n)
{
  for(int i = 0; i < n; ++i)
  {
    Vector3D v = randomVector();
    o_charges.add(v);
  }
}

int main()
{
 ChargeSystem charges(0.1);
 addCharges(charges, 48);

 if( !charges.solve() )
 {
   std::cout << "pesec!\n";
   return 0;
 }
 std::vector<Vector3D> res = charges.getPositions();
 std::ostringstream os;
 os << "Graphics3D[{PointSize[Large], Point[{\n";
 for(int i = 0; i < res.size(); ++i)
 {
   os << "{" << res[i] << "}";
   if( i+1 != res.size() )
     os << ", ";
 }
 os << "}], Opacity[0.5], Sphere[]}]\n";
 std::cout << os.str();
 return 0;
}

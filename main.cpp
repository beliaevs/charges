#include<iostream>
#include<sstream>

#include "chargesystem.h"

int main()
{
 ChargeSystem charges(0.1);
 charges.add(Vector3D(1, 0, 0));
 charges.add(Vector3D(0, 1, 0));
 charges.add(Vector3D(0, 0, 1));
 charges.add(Vector3D(1, 1, 0));
 charges.add(Vector3D(0, 1, 1));
 charges.add(Vector3D(1, 0, 1));
 for(int i = 0 ; i < 41; ++i)
 {
   charges.add(Vector3D(i+1, i+2, i+3));
 }

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

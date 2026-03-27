#include<iostream>
#include<optional>
#include<sstream>
#include<random>

#include "chargesystem.h"
#include "EquilibriumFinder.h"

Vector3D randomVector(std::mt19937& mt)
{
  Vector3D res;
  std::uniform_real_distribution<> rd(-1.0, 1.0);
  res.x = rd(mt);
  res.y = rd(mt);
  res.z = rd(mt);
  return res;
}

template<typename ChargeSystem>
void addCharges(ChargeSystem& o_charges, int n)
{
  std::mt19937 mt;
  for(int i = 0; i < n; ++i)
  {
    o_charges.add(randomVector(mt));
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

void outputChargesSageFormat(std::ostream& os, const std::vector<Vector3D>& i_points)
{
    os << "sum([point3d(p) for p in [";
    for (int i = 0; i < i_points.size(); ++i)
    {
        os << "(" << i_points[i] << ")";
        if (i + 1 != i_points.size())
            os << ", ";
    }
    os << "]]).show()\n";
}

std::optional<int> parseArgs(int argc, const char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <number_of_charges>\n";
        return std::nullopt;
    }
    try
    {
        int n = std::stoi(argv[1]);
        if (n <= 0)
        {
            std::cerr << "Number of charges must be a positive integer.\n";
            return std::nullopt;
        }
        return n;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Invalid number of charges: " << e.what() << "\n";
        return std::nullopt;
    }
}

int main(int argc, const char* argv[])
{
    const auto charges = parseArgs(argc, argv);
    if (!charges)
        return 1;
  
    EquilibriumFinder finder(0.001);
    addCharges(finder, *charges);
    if(!finder.solve())
    {
        std::cout << "pesec!\n";
        return 0;
    }
    std::vector<Vector3D> res = finder.getPositions();
    outputChargesSageFormat(std::cout, res);
    return 0;
}

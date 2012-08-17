#pragma once

#include <cmath>
#include <iosfwd>

template<typename T>
class Vector3
{
public:
  T x, y, z;

  Vector3(): x(0), y(0), z(0) {}

  Vector3(T i_x, T i_y, T i_z): x(i_x), y(i_y), z(i_z)
  {
  }

  template<typename U>
  Vector3(const Vector3<U>& i_o): x(i_o.x), y(i_o.y), z(i_o.z)
  {
  }

  template<typename U>
  Vector3& operator = (const Vector3<U>& i_rhs)
  {
    x = i_rhs.x;
    y = i_rhs.y;
    z = i_rhs.z;
    return *this;
  }

  Vector3& operator += (const Vector3& i_rhs)
  {
    x += i_rhs.x;
    y += i_rhs.y;
    z += i_rhs.z;
    return *this;
  }

  Vector3& operator -= (const Vector3& i_rhs)
  {
    x -= i_rhs.x;
    y -= i_rhs.y;
    z -= i_rhs.z;
    return *this;
  }

  Vector3& operator *= (T i_a)
  {
    x *= i_a;
    y *= i_a;
    z *= i_a;
    return *this;
  }

  Vector3& operator /= (T i_a)
  {
    x /= i_a;
    y /= i_a;
    z /= i_a;
    return *this;
  }

  T lenSqr() const
  {
    return x*x + y*y + z*z;
  }

  T length() const
  {
    return std::sqrt( lenSqr() );
  }

  void doNormalize()
  {
    T norm = length();
    x /= norm;
    y /= norm;
    z /= norm;
  }

  Vector3 normalize() const
  {
    Vector3 tmp(*this);
    tmp.doNormalize();
    return tmp;
  }
};

template<typename T>
Vector3<T> operator + (const Vector3<T>& i_v1, const Vector3<T>& i_v2 )
{
  return Vector3<T>(i_v1.x + i_v2.x, i_v1.y + i_v2.y, i_v1.z + i_v2.z);
}

template<typename T>
Vector3<T> operator - (const Vector3<T>& i_v1, const Vector3<T>& i_v2 )
{
  return Vector3<T>(i_v1.x - i_v2.x, i_v1.y - i_v2.y, i_v1.z - i_v2.z);
}

template<typename T>
Vector3<T> operator - (const Vector3<T>& i_v)
{
  return Vector3<T>(-i_v.x, -i_v.y, -i_v.z);
}

template<typename T>
Vector3<T> operator * (const T& i_a, const Vector3<T>& i_v)
{
  return Vector3<T>(i_a * i_v.x, i_a * i_v.y, i_a * i_v.z);
}

template<typename T>
T operator * (const Vector3<T>& i_u, const Vector3<T>& i_v)
{
  return i_u.x * i_v.x + i_u.y * i_v.y + i_u.z * i_v.z;
}

template<typename T>
std::ostream& operator << (std::ostream& os, const Vector3<T>& i_v)
{
  os << i_v.x << ", " << i_v.y << ", " << i_v.z;
  return os;
}

template<typename T>
std::istream& operator >> (std::istream& is, const Vector3<T>& i_v)
{
  is >> i_v.x >> i_v.y >> i_v.z;
  return is;
}

typedef Vector3<double> Vector3D;




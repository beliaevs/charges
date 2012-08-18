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

template<typename T, typename U>
Vector3<T> operator * (const U& i_a, const Vector3<T>& i_v)
{
  return Vector3<T>(i_a * i_v.x, i_a * i_v.y, i_a * i_v.z);
}

template<typename T, typename U>
Vector3<T> operator * (const Vector3<T>& i_v, const U& i_a)
{
  return Vector3<T>(i_a * i_v.x, i_a * i_v.y, i_a * i_v.z);
}

template<typename T, typename U>
Vector3<T> operator / (const Vector3<T>& i_v, const U& i_a)
{
  return Vector3<T>(i_v.x / i_a, i_v.y / i_a, i_v.z / i_a);
}

template<typename T>
T operator * (const Vector3<T>& i_u, const Vector3<T>& i_v)
{
  return i_u.x * i_v.x + i_u.y * i_v.y + i_u.z * i_v.z;
}

template<typename T>
Vector3<T>& operator += (Vector3<T>&io_v, const Vector3<T>& i_rhs)
{
  io_v.x += i_rhs.x;
  io_v.y += i_rhs.y;
  io_v.z += i_rhs.z;
  return io_v;
}

template<typename T>
Vector3<T>& operator -= (Vector3<T>&io_v, const Vector3<T>& i_rhs)
{
  io_v.x -= i_rhs.x;
  io_v.y -= i_rhs.y;
  io_v.z -= i_rhs.z;
  return io_v;
}

template<typename T, typename U>
Vector3<T>& operator *= (Vector3<T>&io_v, U i_a)
{
  io_v.x *= i_a;
  io_v.y *= i_a;
  io_v.z *= i_a;
  return io_v;
}

template<typename T, typename U>
Vector3<T>& operator /= (Vector3<T>&io_v, U i_a)
{
  io_v.x /= i_a;
  io_v.y /= i_a;
  io_v.z /= i_a;
  return io_v;
}

template<typename T>
T lenSqr(const Vector3<T>& i_v)
{
  return i_v.x*i_v.x + i_v.y*i_v.y + i_v.z*i_v.z;
}

template<typename T>
auto length(const Vector3<T>& i_v) -> decltype(std::sqrt(lenSqr(i_v)))
{
  return std::sqrt( lenSqr(i_v) );
}

template<typename T>
void makeUnit(Vector3<T>& io_v)
{
  T norm = length(io_v);
  io_v /= norm; 
}

template<typename T>
Vector3<T> unit(const Vector3<T>& i_v)
{
  Vector3<T> tmp(i_v);
  makeUnit(tmp);
  return tmp;
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




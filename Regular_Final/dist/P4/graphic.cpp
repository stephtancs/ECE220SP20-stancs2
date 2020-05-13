#include  <iostream>
#include "graphic.hpp"

// constructor 
// default set (_x, _y, _z) = (0, 0, 0)
Vec3::Vec3(){
  // your code here
};
// constructor
Vec3::Vec3(const double & _x1, const double & _y1, const double & _z1){
  // your code here
};
// copy constructor 
Vec3::Vec3(const Vec3 & _p){
  // your code here
};

// return value of _x
const double Vec3::x() const{
  // your code here
};

//return value of _y
const double Vec3::y() const{
  // your code here 
};

// return value of _z
const double Vec3::z() const{
  // your code here
}
// modify _x
void Vec3::set_x(const double& _t){
  // your code here
};
// modify _y
void Vec3::set_y(const double& _t){
  // your code here
};
// modify _z
void Vec3::set_z(const double& _t){
  // your code here
};
// operator overloading +
Vec3 Vec3::operator + (const Vec3 &b){
  // your code here
}

Vec3 Vec3::operator - (const Vec3 &b){
  // your code here
}


Vec3 Vec3::operator ^ (const Vec3 &b){
  // your code here
};


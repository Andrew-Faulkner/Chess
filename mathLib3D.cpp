#include <math.h>
#include "mathLib3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

#ifndef MATHLIB_3D_C
#define MATHLIB_3D_C

//Point2D functions
Point3D::Point3D(){
  mX=0;
  mY=0;
  mZ=0;
}

Point3D::Point3D(float inX, float inY,float inZ){
  mX=inX;
  mY=inY;
  mZ=inZ;
}

float Point3D::distanceTo(Point3D other){
  float distance =sqrt(pow(other.mX -mX,2)+pow(other.mY-mY,2)+pow(other.mZ-mZ,2));
  return distance;
}

float Point3D::fastDistanceTo(Point3D other){
    float distance = pow(other.mX -mX,2)+pow(other.mY-mY,2)+pow(other.mZ-mZ,2);
    return distance;
}

///Vec 2D functions
Vec3D::Vec3D(){
  mX=0;
  mY=0;
  mZ=0;
}
Vec3D::Vec3D(float inX, float inY, float inZ){
  mX=inX;
  mY=inY;
  mZ=inZ;
}

  float Vec3D::length(){
  float distance =sqrt(pow(mX,2)+pow(mY,2)+pow(mZ,2));
  return distance;
}
 Vec3D Vec3D::normalize(){
   float dist=sqrt(pow(mX,2)+pow(mY,2)+pow(mZ,2));
   Vec3D newvec((mX/dist),(mY/dist),(mZ/dist));
   return newvec;
 }

 Vec3D Vec3D::multiply(float scalar){
   float x=mX*scalar;
   float y=mY*scalar;
   float z=mZ*scalar;
   Vec3D newvec(x,y,z);
   return newvec;
 }
 Point3D Vec3D::movePoint(Point3D source){
   float x=source.mX+mX;
   float y=source.mY+mY;
   float z=source.mZ+mZ;
   Point3D newpoint(x,y,z);
   return  newpoint;
 }
 static Vec3D createVector(Point3D p1, Point3D p2){
   float x=p2.mX-p1.mX;
   float y=p2.mY-p1.mY;
   float z=p2.mZ-p1.mZ;
   Vec3D newvec(x,y,z);
   return newvec;
 }

#endif

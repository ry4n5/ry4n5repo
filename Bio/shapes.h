#include "atype.h"
/** @file shapes.h
 *  Header containing some primitive shapes
 */

#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>
#include <vector>

/** This is the simplest shape, a point with 2 coordinates. It is a template 
 *  that allows either parameter to be of any type.
 *  You can directly modify X() and Y() as they return references 
 */
template <typename XCoordType = int32, typename YCoordType = XCoordType>
class Point {
public:

   Point() : mX(0), mY(0) { }

   /** Constructor with parameters
    *  @param x x coord
    *  @param y y coord
    */
   Point ( XCoordType ix, YCoordType iy )
         : mX ( ix ),
           mY ( iy ) { }

   /** Get x coord. This can be used to alter mX.
    *  @return x coord
    */
   inline
   XCoordType& X() { return mX; }

   /** Set x coord.
    *  @param x x coord
    */
   void        X(XCoordType ix) { mX = ix; }

   /** Get y coord. This can be used to alter mY.
    *  @return y coord
    */
   YCoordType& Y() { return mY; }

   /** Set y coord.
    *  @param y y coord
    */
   void        Y(YCoordType iy) { mY = iy; }

   /** User friendly output to screen.
    *  @param stream output stream
    *  @param pt point to output
    *  @return output stream
    */
   friend std::ostream& operator<< (std::ostream& stream, const Point<XCoordType,YCoordType> pt) {
      stream << "("<<pt.mX<<","<<pt.mY<<")";
      return stream;
   }

   /** Add 2 points together. (x0+x1,y0+y1)
    *  @param rPoint point to add to current point
    *  @return new point
    */
   Point operator+(const Point& rPoint) const {
      return Point<>(mX+rPoint.mX,mY+rPoint.mY);
   }

   /** Subtract a point from this one. (x0-x1,y0-y1)
    *  @param rPoint point to subtract
    *  @return new point
    */
   Point operator-(const Point& rPoint) const {
      return Point<>(mX-rPoint.mX,mY-rPoint.mY);
   }

   /** Test if point is equal.
    *  @param rPoint point to test
    *  @return true if equal, false otherwise
    */
   bool operator==(const Point& rPoint) const {
      if(mX != rPoint.mX) return false;
      if(mY != rPoint.mY) return false;
      return true;
   }

   /** Test if point is not equal.
    *  @param rPoint point to test.
    *  @return true if not equal, false otherwise
    */
   bool operator!=(const Point& rPoint) const {
      if(mX != rPoint.mX) return true;
      if(mY != rPoint.mY) return true;
      return false;
   }

   Point& operator+=(const Point& rPoint) {
      mX += rPoint.mX;
      mY += rPoint.mY;
      return *this;
   }

   /** this is sorted in a special order so that when used in a std::map
    *  it will sort from top to bottom, then right to left.
    *  This makes it easier for AnnotationPanes to annotate from right
    *  to left when iterating through them.
    *  @param rPoint point to test
    *  @return true if this point comes before the passed one
    */
   bool operator<(const Point& rPoint) const {
      if(mY < rPoint.mY) return true;
      if(mY==rPoint.mY)  return (mX > rPoint.mX);
      else               return false;
   }

protected:
   XCoordType mX; ///< x coordinate
   YCoordType mY; ///< y coordinate
};

/** A line is made up of 2 Points. It can also have any type for either 
 *  coordinate.
 */
template <typename XCoordType = int32, typename YCoordType = XCoordType>
class Line {
public:

   /** Default constructor */
   Line () : mPoint1(), mPoint2() { }

   /** Constructor from points 
    *  @param point1 start point
    *  @param point2 end point
    */
   Line ( Point<XCoordType,YCoordType> point1, Point<XCoordType,YCoordType> point2 )
        : mPoint1 ( point1 ),
          mPoint2 ( point2 ) { }

   /** Get start point. It can be altered using this call.
    *  @return ref to start point
    */
   Point<XCoordType,YCoordType>& Start() { return mPoint1; }

   /** Get end point. It can be altered using this call.
    *  @return ref to end point
    */
   Point<XCoordType,YCoordType>& End()   { return mPoint2; }

   /** User friendly output to screen.
    *  @param stream output stream
    *  @param line line to output
    *  @return output stream
    */
   friend std::ostream& operator<< (std::ostream& stream, const Line<XCoordType,YCoordType> line) {
      stream << "Line start"<<line.mPoint1<<" end"<<line.mPoint2<<" ";
      return stream;
   }

private:
   Point<XCoordType,YCoordType> mPoint1; ///< start point
   Point<XCoordType,YCoordType> mPoint2; ///< end point
};

template <typename CoordType = int32>
class Rectangle {
public:

   Rectangle ( Point<CoordType> origin=Point<CoordType>(0,0), CoordType iwidth=0, CoordType iheight=0 )
             : mOrigin ( origin ),
               mWidth ( iwidth ),
               mHeight ( iheight ) { }

   Rectangle ( CoordType ix, CoordType iy, CoordType iwidth, CoordType iheight)
             : mOrigin(ix,iy),
               mWidth(iwidth),
               mHeight(iheight)
   { }


   ~Rectangle() { }

   Point<CoordType>& Origin()          { return mOrigin; }
   void       Origin(Point<CoordType> origin) { mOrigin = origin; }
   CoordType& X()                      { return mOrigin.X(); }
   void       X(CoordType x)           { mOrigin.X() = x; }
   CoordType& Y()                      { return mOrigin.Y(); }
   void       Y(CoordType y)           { mOrigin.Y() = y; }
   CoordType& Width()                  { return mWidth; }
   void       Width(CoordType width)   { mWidth = width; }
   CoordType& Height()                 { return mHeight; }
   void       Height(CoordType height) { mHeight = height; }
   CoordType& Top()                    { return mOrigin.Y(); }
   void       Top(CoordType top)       { mOrigin.Y() = top; }
   CoordType& Left()                   { return mOrigin.X(); }
   void       Left(CoordType left)     { mOrigin.X() = left; }
   CoordType  Bottom()                 { return mOrigin.Y() + mHeight - 1; }
   CoordType  Right()                  { return mOrigin.X() + mWidth - 1; }

   /** necessary because they cannot be passed as a reference */
   void Right(CoordType right)   { mWidth  = right - mOrigin.X() + 1; }
   void Bottom(CoordType bottom) { mHeight = bottom - mOrigin.Y() + 1; }

   Point<CoordType> TopLeft()  { return mOrigin; }
   Point<CoordType> TopRight() { return Point<CoordType>(Right(),Top()); }
   Point<CoordType> BotLeft()  { return Point<CoordType>(Left(),Bottom()); }
   Point<CoordType> BotRight() { return Point<CoordType>(Right(),Bottom()); }

   inline
   Point<CoordType> Middle() {
      return Point<CoordType>(mOrigin.X() + (mWidth>>1), mOrigin.Y() + (mHeight>>1));
   }

   inline
   bool ContainsPoint(Point<CoordType> point) {
      if(point.X()<Left()) return false;
      if(point.X()>Right()) return false;
      if(point.Y()<Top()) return false;
      if(point.Y()>Bottom()) return false;
      return true;
   }

   
   bool Overlaps(Rectangle<CoordType> rect) {
      if(ContainsPoint(rect.TopLeft()))  return true;
      if(ContainsPoint(rect.TopRight())) return true;
      if(ContainsPoint(rect.BotLeft()))  return true;
      if(ContainsPoint(rect.BotRight())) return true;
      return false;
   }

   void Clear() { mWidth = 0; mHeight = 0; mOrigin = Point<CoordType>(0,0); }

   bool operator!= (Rectangle<CoordType>& rect) {
      if(mOrigin != rect.mOrigin) return true;
      if(mWidth  != rect.mWidth ) return true;
      if(mHeight != rect.mHeight) return true;
      return false;
   }

   bool operator!() const {
      if(!mWidth)  return true;
      if(!mHeight) return true;
      return false;
   }

   bool operator==(Rectangle<CoordType>& rect) const {
      if(mOrigin != rect.mOrigin) return false;
      if(mWidth  != rect.mWidth ) return false;
      if(mHeight != rect.mHeight) return false;
      return true;
   }

   Rectangle<CoordType>& operator=(const Rectangle<CoordType> rect) {
      mOrigin = rect.mOrigin;
      mWidth  = rect.mWidth;
      mHeight = rect.mHeight;
      return *this;
   }

   friend std::ostream& operator<< (std::ostream& stream, const Rectangle<CoordType> rect) {
      stream << "Rectangle "<<rect.mOrigin<<" "<<rect.mWidth<<" x "<<rect.mHeight<<" ";
      return stream;
   }

private:
   Point<CoordType> mOrigin;
   CoordType mWidth, mHeight;
};

/* specializations */
template<>
inline float Rectangle<float>::Bottom()  { return mOrigin.Y() + mHeight; }
template<>
inline float Rectangle<float>::Right()   { return mOrigin.X() + mWidth; }
template<>
inline double Rectangle<double>::Bottom() { return mOrigin.Y() + mHeight; }
template<>
inline double Rectangle<double>::Right()  { return mOrigin.X() + mWidth; }


template <typename XCoordType = int32, typename YCoordType = XCoordType>
class Polygon {
public:
   Polygon() { }

   void AddPoint(Point<XCoordType,YCoordType> point) { 
      mPoints.push_back(point);
   }

   void Clear() { 
      mPoints.clear();
      mBoundingBox.Clear();
   }

   const int32 NumLines() const {
      if(mPoints.size()<2) return 0;
      else                 return mPoints.size();
   }

   Line<XCoordType,YCoordType> GetLine(int32 lineIndex) const {
      if( lineIndex==((signed)mPoints.size()-1) ) {
         return Line<XCoordType,YCoordType>(mPoints[lineIndex],mPoints[0]);
      }
      else {
         return Line<XCoordType,YCoordType>(mPoints[lineIndex],mPoints[lineIndex+1]);
      }
   }

   const int32 NumPoints() const {
      return mPoints.size();
   }

   Point<XCoordType,YCoordType> GetPoint(int32 pointIndex) const {
      return mPoints[pointIndex];
   }

   bool ContainsPoint(Point<XCoordType,YCoordType> point) {
      /* adapted from:                                            */
      /* free code for winding number algorithm for inclusion of  */
      /* a point in a polygon Copyright (c) 2001, Softsurfer      */
      /* (www.softsurfer.com)                                     */
      int32 winding_num_counter = 0; /* reset winding number counter  */
      typename std::vector<Point<XCoordType,YCoordType> >::iterator it1,it2;
      for(it1=mPoints.begin();it1!=mPoints.end();++it1) {
         it2 = it1;
         ++it2;
         /* last poly point same as start */
         if(it2==mPoints.end()) it2 = mPoints.begin();

         float is_left = ( (it2->X()-it1->X()) * (point.Y()-it1->Y()) ) -
                         ( (point.X()-it1->X()) * (it2->Y()-it1->Y()) );

         if(it1->Y() <= point.Y()) {
            if(it2->Y() > point.Y()) {
               if(is_left>0) ++winding_num_counter;
            }
         }
         else {
            if(it2->Y() <= point.Y()) {
               if(is_left<0) --winding_num_counter;
            }
         }
      }

      if(winding_num_counter) return true;
      return false;
   }

   friend std::ostream& operator<< (std::ostream& stream, const Polygon<XCoordType,YCoordType> poly) {

      stream << "Polygon with "<<poly.NumLines()<<" lines:\n";
      for(int32 k=0;k<poly.NumLines();++k) {
         stream << poly.GetLine(k) << "\n";
      }
      return stream;
   }

private:

   std::vector<Point<XCoordType,YCoordType> >  mPoints;
   Rectangle<> mBoundingBox;

};


#endif

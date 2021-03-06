// $Id: shape.h,v 1.5 2014-05-08 18:32:56-07 - - $

#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <iomanip>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <math.h>
using namespace std;

#include "rgbcolor.h"

//
// Shapes constitute a single-inheritance hierarchy, summarized
// here, with the superclass listed first, and subclasses indented
// under their immediate superclass.
//
// shape
//    text
//    ellipse
//       circle
//    polygon
//       rectangle
//          square
//       diamond
//       triangle
//          right_triangle
//          isosceles
//          equilateral
//

class shape;
typedef struct {GLfloat xpos; GLfloat ypos; int id;} vertex;
typedef vector<vertex> vertex_list;
typedef shared_ptr<shape> shape_ptr; 


//
// Abstract base class for all shapes in this system.
//

class shape {
   friend ostream& operator<< (ostream& out, const shape&);
   private:
      shape (const shape&) = delete; // Prevent copying.
      shape& operator= (const shape&) = delete; // Prevent copying.
      shape (shape&&) = delete; // Prevent moving.
      shape& operator= (shape&&) = delete; // Prevent moving.
   protected:
      inline shape(); // Only subclass may instantiate.
   public:
      virtual ~shape() {}
      virtual void draw (const vertex&, 
      const rgbcolor&, int id) const = 0;
      virtual void border_draw (const vertex&, 
      const rgbcolor&, const GLfloat) const = 0;
      virtual void show (ostream&) const;
};


//
// Class for printing text.
//

class text: public shape {
   protected:
      void* glut_bitmap_font = nullptr;
      // GLUT_BITMAP_8_BY_13
      // GLUT_BITMAP_9_BY_15
      // GLUT_BITMAP_HELVETICA_10
      // GLUT_BITMAP_HELVETICA_12
      // GLUT_BITMAP_HELVETICA_18 
      // GLUT_BITMAP_TIMES_ROMAN_10
      // GLUT_BITMAP_TIMES_ROMAN_24
      string textdata;
   public:
      text (void* glut_bitmap_font, const string& textdata);
      virtual void draw (const vertex&,
       const rgbcolor&, int id) const override;
      virtual void border_draw (const vertex&,
       const rgbcolor&, const GLfloat) const override;
      virtual void show (ostream&) const override;
};

//
// Classes for ellipse and circle.
//

class ellipse: public shape {
   protected:
      vertex dimension;
   public:
      ellipse (GLfloat width, GLfloat height,int id);
      virtual void draw (const vertex&, 
      const rgbcolor&, int id) const override;
      virtual void border_draw (const vertex&,
       const rgbcolor&, const GLfloat) const override;
      virtual void show (ostream&) const override;
};

class circle: public ellipse {
   public:
      circle (GLfloat diameter, int id);
};

//
// Class polygon.
//

class polygon: public shape {
   protected:
      vertex_list vertices;
      vertex_list verticess;
   public:
      polygon (const vertex_list& vertices);
      virtual void draw (const vertex&, 
      const rgbcolor&, int id ) const override;
      virtual void border_draw (const vertex&, 
      const rgbcolor&, const GLfloat) const override;
      virtual void show (ostream&) const override;
};


//
// Classes rectangle, square, etc.
//

class rectangle: public polygon {
   public:
      rectangle (GLfloat width, GLfloat height, int id);
};

class square: public rectangle {
   public:
      square (GLfloat width, int id);
};

class diamond: public polygon {
   public:
      diamond (const GLfloat width, const GLfloat height,int id);
};

class triangle: public polygon {
   public:
      triangle (const vertex_list& vertices);
};

class right_triangle: public triangle {
   public:
      right_triangle (const GLfloat width, const GLfloat height,int id);
};

class isosceles: public triangle {
   public:
      isosceles (const GLfloat width, const GLfloat height,int id);
};

class equilateral: public triangle {
   public:
      equilateral (const GLfloat width,int id);
};      

ostream& operator<< (ostream& out, const shape&);

#endif


// $Id: interp.cpp,v 1.14 2014-05-08 18:32:56-07 - - $

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
using namespace std;

#include <GL/freeglut.h>

#include "debug.h"
#include "interp.h"
#include "shape.h"
#include "util.h"
#include "graphics.h"

map<string,interpreter::interpreterfn> interpreter::interp_map {
   {"define" , &interpreter::do_define },
   {"draw"   , &interpreter::do_draw   },
   {"moveby" , &interpreter::do_moveby },
   {"border" , &interpreter::do_border },
};

map<string,interpreter::factoryfn> interpreter::factory_map {
   {"text"     , &interpreter::make_text     },
   {"ellipse"  , &interpreter::make_ellipse  },
   {"circle"   , &interpreter::make_circle   },
   {"polygon"  , &interpreter::make_polygon  },
   {"rectangle", &interpreter::make_rectangle},
   {"diamond"  , &interpreter::make_diamond  },
   {"triangle" , &interpreter::make_triangle },
   {"square"   , &interpreter::make_square   },
   {"isosceles", &interpreter::make_isosceles},
   {"equilateral", &interpreter::make_equilateral},
   {"right_triangle", &interpreter::make_right_triangle },
};

interpreter::~interpreter() {
   for (const auto& itor: objmap) {
      cout << "objmap[" << itor.first << "] = "
           << *itor.second << endl;
   }
}

void interpreter::interpret (const parameters& params) {
   DEBUGF ('i', params);
   param begin = params.cbegin();
   string command = *begin;
   //Find the associated command
   //two options: define and draw
   auto itor = interp_map.find (command);
   if (itor == interp_map.end()) throw runtime_error ("syntax error");
   interpreterfn func = itor->second;
   //call the associated command
   (this->*func) (++begin, params.cend());
}

void interpreter::do_define (param begin, param end) {
  // cout<<"do_define"<<endl;
   DEBUGF ('f', range (begin, end));
   string name = *begin;
   //notice the call to make_shape
   idmap.insert ({name, count});
   objmap.insert ({name, make_shape (++begin, end)});

}


void interpreter::do_draw (param begin, param end) {
  // cout<<"in do_draw"<<endl;
   DEBUGF ('f', range (begin, end));
   //if (end - begin != 2) throw runtime_error ("syntax error");
   string name = begin[1];
   //Get a shape from the objmap
   shape_map::const_iterator itor = objmap.find (name);
   if (itor == objmap.end()) {
      throw runtime_error (name + ": no such shape");
   }
   id_map::const_iterator iditor = idmap.find(name);

   vertex where {from_string<GLfloat> (begin[2]),
                 from_string<GLfloat> (begin[3]), 0};
   rgbcolor color {begin[0]};
   //and seemingly draw it?
   object op;
   op.make(where, color, itor->second, interp_move_by,
    counter, selected_color, thickness);
   counter++;
   window::push_back(op);
}

void interpreter::do_moveby (param begin, param end){
     DEBUGF ('f', range (begin, end));
     GLfloat pixel = from_string<GLfloat>(begin [0]);
     interp_move_by = pixel;
     }
void interpreter::do_border(param begin, param end){
     DEBUGF('f', range (begin,end));
     rgbcolor newcolor {begin[0]};
     GLfloat newthickness = from_string<GLfloat>(begin [1]);
     thickness = newthickness ;
     selected_color = newcolor;
     window::set_color(selected_color,thickness);
     }

shape_ptr interpreter::make_shape (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   string type = *begin++;
   //get a predefined class to parameterise for our shape
   auto itor = factory_map.find(type);
   if (itor == factory_map.end()) {
      throw runtime_error (type + ": no such shape");
   }
   factoryfn func = itor->second;
   return (this->*func) (begin, end);
}

//These functions create new objects. they are shared pointers so they
//do their own memory cleanup, and are all subclassed from the same
//superclass so they can all go into the same vector or map.
shape_ptr interpreter::make_text (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   string font = *begin++;
   void* glfont = NULL;
   if(strcmp(font.c_str() ,"Fixed-9x15")){   
   glfont = GLUT_BITMAP_9_BY_15;
   }
   if(strcmp(font.c_str() , "Fixed-8x13")){   
   glfont = GLUT_BITMAP_8_BY_13;
   }
   if(strcmp(font.c_str() , "Helvetica-10")){   
   glfont =GLUT_BITMAP_HELVETICA_10;
   }
   if(strcmp(font.c_str() , "Helvetica-12")){   
   glfont = GLUT_BITMAP_HELVETICA_12;
   }
   if(strcmp(font.c_str() , "Helvetica-18")){   
   glfont = GLUT_BITMAP_HELVETICA_18;
   }
   if(strcmp(font.c_str() , "Times-Roman-10")){   
   glfont = GLUT_BITMAP_TIMES_ROMAN_10;
   }
   if(strcmp(font.c_str() , "Times-Roman-24")){   
   glfont = GLUT_BITMAP_TIMES_ROMAN_24;
   }
   if(glfont == NULL){
        throw runtime_error (font + ": no such font");
        }   
   string input = *begin++;
  /* for(auto i=begin; i!=end; i++){
   input += " ";
   input += *i;
   }*/
   return make_shared<text> (glfont, input);
}

shape_ptr interpreter::make_ellipse (param begin, param end) {\
   DEBUGF ('f', range (begin, end));
   GLfloat w = (float)::atof((*begin).c_str());
   ++begin;
   GLfloat h = (float)::atof((*begin).c_str());
  // cout << w << " " << h;
   int id = count;
   count++;
   return make_shared<ellipse> (w, h, id);
}

shape_ptr interpreter::make_circle (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   GLfloat d = (float)::atof((*begin).c_str());
  // cout << d <<endl;
   int id = count;
   count++;
   return make_shared<circle> (d,id);
}

shape_ptr interpreter::make_polygon (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   vertex_list vertices;
   vertex ob;
   while(begin != end){
   ob.xpos = (float)::atof((*begin++).c_str());
   ob.ypos = (float)::atof((*begin++).c_str());
   ob.id = count;
   vertices.push_back(ob);
   }
   count++;   
   return make_shared<polygon> (vertices);
}

shape_ptr interpreter::make_rectangle (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   GLfloat w = (float)::atof((*begin++).c_str());
   GLfloat h = (float)::atof((*begin).c_str());
  // cout<<"height = "<< h <<"width = "<<w<<endl;
   int id = count;
   count++;
   return make_shared<rectangle> (w, h, id);
}

shape_ptr interpreter::make_diamond (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   GLfloat w = (float)::atof((*begin++).c_str());
   GLfloat h = (float)::atof((*begin).c_str());
  // cout<<"height = "<< h <<"width = "<<w<<endl;
   int id = count;
   count++;
   return make_shared<diamond> (w, h, id);
}

shape_ptr interpreter::make_square (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   GLfloat w = (float)::atof((*begin).c_str());
   int id = count;
   count++;
   return make_shared<square> (w, id);
}

shape_ptr interpreter::make_triangle (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   vertex ob;
   vertex_list tri_list;
   while(begin != end){
   ob.xpos = (float)::atof((*begin++).c_str());
   ob.ypos = (float)::atof((*begin++).c_str());
   ob.id = count;
   tri_list.push_back(ob);
   }
   count++;
   return make_shared<triangle> (tri_list);
}

shape_ptr interpreter::make_right_triangle (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   GLfloat w = (float)::atof((*begin++).c_str());
   GLfloat h = (float)::atof((*begin).c_str());
//   cout<<"height = "<< h <<"width = "<<w<<endl;
   int id = count;
   count++;
   return make_shared<right_triangle> (w, h, id);
}       

shape_ptr interpreter::make_isosceles (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   GLfloat w = (float)::atof((*begin++).c_str());
   GLfloat h = (float)::atof((*begin).c_str());
   //cout<<"height = "<< h <<"width = "<<w<<endl;
   int id = count;
   count++;
   return make_shared<isosceles> (w, h, id);
}

shape_ptr interpreter::make_equilateral (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   GLfloat w = (float)::atof((*begin).c_str());
  // cout<<"width = "<<w<<endl;
   int id = count;
   count++;
   return make_shared<equilateral> (w, id);
}



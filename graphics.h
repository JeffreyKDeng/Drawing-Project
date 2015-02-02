// $Id: graphics.h,v 1.8 2014-05-08 20:47:45-07 - - $

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <memory>
#include <vector>
using namespace std;

#include <GL/freeglut.h>

#include "rgbcolor.h"
#include "shape.h"

//Class from which all the shapes are derived from
class object {
   private:
      shared_ptr<shape> pshape;
      vertex center;
      rgbcolor color;
      GLfloat move_by;
      int selected = 0;
      int id;
      int max_selected = 0;
      rgbcolor border_color;
      GLfloat border_thickness;
   public:
      void draw() {pshape->draw (center, color, id); }
      void draw4() {
           vertex newcenter;
           newcenter.xpos = center.xpos - 640; //left
           newcenter.ypos = center.ypos ;
           if(selected == id){
           pshape->border_draw(newcenter,
           border_color, border_thickness);
           }
           pshape->draw(newcenter,color, id);
           newcenter.xpos = center.xpos + 640; //right
           newcenter.ypos = center.ypos ;
           if(selected == id){
           pshape->border_draw(newcenter
           ,border_color, border_thickness);
           }
           pshape->draw(newcenter,color, id);
           newcenter.xpos = center.xpos ; //top
           newcenter.ypos = center.ypos + 480 ;
           if(selected == id){
           pshape->border_draw(newcenter,
           border_color, border_thickness);
           }
           pshape->draw(newcenter,color, id);
           newcenter.xpos = center.xpos ; //bot
           newcenter.ypos = center.ypos - 480 ;
           if(selected == id){
           pshape->border_draw(newcenter,
           border_color, border_thickness);
           }
           pshape->draw(newcenter,color, id);
           newcenter.xpos = center.xpos - 640; //bot left
           newcenter.ypos = center.ypos - 480 ;
           if(selected == id){
           pshape->border_draw(newcenter,
           border_color, border_thickness);
           }
           pshape->draw(newcenter,color, id);
           newcenter.xpos = center.xpos + 640; //bot right
           newcenter.ypos = center.ypos - 480 ;
           if(selected == id){
           pshape->border_draw(newcenter,
           border_color, border_thickness);
           }
           pshape->draw(newcenter,color, id);
           newcenter.xpos = center.xpos - 640; //top left
           newcenter.ypos = center.ypos + 480 ;
           if(selected == id){
           pshape->border_draw(newcenter,
           border_color, border_thickness);
           }
           pshape->draw(newcenter,color, id);
           newcenter.xpos = center.xpos + 640; //top right
           newcenter.ypos = center.ypos + 480 ;
           if(selected == id){
           pshape->border_draw(newcenter,
           border_color, border_thickness);
           }
           pshape->draw(newcenter,color, id);
           }
           
      void set_max(int x){
           max_selected = x;
           }
      void set_selected(int x){
           if(x == 13){
                if(selected != 0){
                selected --;
               // cout<<selected<<endl;
                }
                else{
                     selected = max_selected;
//                     cout<<selected<<endl;
                     }
                }
           else if(x == 14){
                if(selected != max_selected){
                selected ++;
//                cout<<selected<<endl;
                }
                else{
                     selected = 0;
                //     cout<<selected<<endl;
                     }
                     
                }
           else{
                if(x<=max_selected){ 
                   selected = x;
           }
           }
     //    cout<<"selected changed----------"<<endl;
           }
           
      bool find() {
           if(selected == id){
                       return true;
                             }
           else{
                return false;
               }
               }
      void change_color(rgbcolor color, GLfloat thickness){
           border_color = color;
           border_thickness = thickness;
           }
      void moveby(GLfloat pixel){
           move_by = pixel;
           }
      void borderdraw() {pshape->border_draw(center,
      border_color, border_thickness);}
      void make(vertex cent , rgbcolor colo, shared_ptr<shape> ppshape,
       GLfloat move_byy, int counter, rgbcolor b_color, 
       GLfloat b_thickness){
           center = cent;
           color = colo;
           pshape = ppshape;
           move_by = move_byy;
           id = counter;
           max_selected++;
           border_color = b_color;
           border_thickness = b_thickness;
           }
      void print(){
                cout<< color <<endl;
                cout<<center.xpos<<endl;
                cout<< pshape<<endl;
                cout<< move_by<<endl;
                cout<< id<<endl; 
                cout<<border_color<<endl;  
                cout<< border_thickness;
           }
      void move (GLfloat delta_x, GLfloat delta_y) {
         delta_x = move_by * delta_x;
         delta_y = move_by * delta_y;
         center.xpos += delta_x;
         center.ypos += delta_y;
      }
};

//Looks after all the state to do with the mouse
class mouse {
      friend class window;
   private:
      int xpos {0};
      int ypos {0};
      int entered {GLUT_LEFT};
      int left_state {GLUT_UP};
      int middle_state {GLUT_UP};
      int right_state {GLUT_UP};
   private:
      void set (int x, int y) { xpos = x; ypos = y; }
      void state (int button, int state);
      void draw();
};


//overall class to manage the drawing and opengl stuff
class window {
      friend class mouse;
   private:
      static int width;         // in pixels
      static int height;        // in pixels
      static vector<object> objects;
      static size_t selected_obj;
      static mouse mus;
   private:
      static void close();
      static void entry (int mouse_entered);
      static void display();
      static void reshape (int width, int height);
      static void keyboard (GLubyte key, int, int);
      static void special (int key, int, int);
      static void motion (int x, int y);
      static void passivemotion (int x, int y);
      static void mousefn (int button, int state, int x, int y);
   public:
      static void push_back (const object& obj) 
      {objects.push_back (obj); }
      static void set_color (rgbcolor border_color, 
      GLfloat border_thickness){
              for (auto& object: window::objects) {
                  object.change_color(border_color, border_thickness);
                  }
                  }
      static void set_moveby (GLfloat moveby){
             for (auto& object: window::objects) {
                  object.moveby(moveby);
                  }
                  }
      static void setwidth (int width_) { width = width_; }
      static void setheight (int height_) { height = height_; }
      static void main();
};

#endif


// $Id: shape.cpp,v 1.7 2014-05-08 18:32:56-07 - - $
//Jeffrey Deng jkdeng@ucsc.edu & Richi Mizuno rmizuno@ucsc.edu 
#include <typeinfo>
#include <unordered_map>
#include <math.h>
using namespace std;

#include "shape.h"
#include "util.h"

static unordered_map<void*,string> fontname {
   {GLUT_BITMAP_8_BY_13       , "Fixed-8x13"    },
   {GLUT_BITMAP_9_BY_15       , "Fixed-9x15"    },
   {GLUT_BITMAP_HELVETICA_10  , "Helvetica-10"  },
   {GLUT_BITMAP_HELVETICA_12  , "Helvetica-12"  },
   {GLUT_BITMAP_HELVETICA_18  , "Helvetica-18"  },
   {GLUT_BITMAP_TIMES_ROMAN_10, "Times-Roman-10"},
   {GLUT_BITMAP_TIMES_ROMAN_24, "Times-Roman-24"},
};

static unordered_map<string,void*> fontcode {
   {"Fixed-8x13"    , GLUT_BITMAP_8_BY_13       },
   {"Fixed-9x15"    , GLUT_BITMAP_9_BY_15       },
   {"Helvetica-10"  , GLUT_BITMAP_HELVETICA_10  },
   {"Helvetica-12"  , GLUT_BITMAP_HELVETICA_12  },
   {"Helvetica-18"  , GLUT_BITMAP_HELVETICA_18  },
   {"Times-Roman-10", GLUT_BITMAP_TIMES_ROMAN_10},
   {"Times-Roman-24", GLUT_BITMAP_TIMES_ROMAN_24},
};
int counter = 0;
ostream& operator<< (ostream& out, const vertex& where) {
   out << "(" << where.xpos << "," << where.ypos << ")";
   return out;
}
//Constructors seem to mainly be implemented using defaults
shape::shape() {
   DEBUGF ('c', this);
}

text::text (void* glut_bitmap_font, const string& textdata):
      glut_bitmap_font(glut_bitmap_font), textdata(textdata) {
     // cout<<"ajskdf"<<endl;
      
   DEBUGF ('c', this);
}

ellipse::ellipse (GLfloat width, GLfloat height, int id):
dimension ({width, height, id}) {
   DEBUGF ('c', this);
}

circle::circle (GLfloat diameter, int id)
: ellipse (diameter, diameter, id) {
   DEBUGF ('c', this);
}


polygon::polygon (const vertex_list& vertices)
: vertices(verticess) {
   double x_total = 0;
   double y_total = 0;
   double x_avg = 0;
   double y_avg =0;
   int count = 0;
   vertex ob;
   for(auto ver = vertices.begin(); 
   ver != vertices.end(); ver++){
            x_total += ver->xpos;
            y_total += ver->ypos;
            count++;
            }
   x_avg = x_total/count;
   y_avg = y_total/count;
   for(auto verr = vertices.begin(); 
   verr !=vertices.end();verr++){
            ob.xpos = verr->xpos-x_avg;
            ob.ypos = verr->ypos-y_avg;
            ob.id = verr->id;
            verticess.push_back(ob);
            }
                 
   DEBUGF ('c', this);
}

rectangle::rectangle (GLfloat width, 
GLfloat height, int id):polygon({}) {                     
   vertex BotL, TopL, TopR, BotR;
   BotL.xpos = width * -0.5;    TopL.xpos = width * -0.5; 
   BotL.ypos = height* -0.5;    TopL.ypos = height * 0.5; 
   TopR.xpos = width * 0.5 ;    BotR.xpos = width * 0.5 ;
   TopR.ypos = height* 0.5 ;    BotR.ypos = height *-0.5;
   BotL.id = id;
   //cout<<"id in rectangle ="<<BotL.id<<endl;
   verticess.push_back(BotL);
   verticess.push_back(TopL);
   verticess.push_back(TopR);
   verticess.push_back(BotR);
   DEBUGF ('c', this << "(" << width << "," << height << ")");
}
diamond::diamond (GLfloat width, 
GLfloat height,int id):polygon({}) {   
   vertex left, right, top, bot;
   left.xpos = width * -0.5;    right.xpos = width * 0.5 ;
   left.ypos = 0;               right.ypos = 0;
   top.xpos =  0;               bot.xpos = 0;
   top.ypos = height * 0.5;     bot.ypos = height * -0.5;
   left.id = id;
   verticess.push_back(left);
   verticess.push_back(top);
   verticess.push_back(right);
   verticess.push_back(bot);
   DEBUGF ('c', this << "(" << width <<
    "," << height << ")");               
}

square::square (GLfloat width, int id): 
               rectangle (width, width, id) {
   DEBUGF ('c', this);
}

triangle::triangle(const vertex_list& vertices)
: polygon(vertices) {
   DEBUGF ('c',this); 
                         
}
right_triangle::right_triangle(GLfloat width,
 GLfloat height, int id):triangle(vertices){
   //cout<<"right_triangle"<<endl; 
   DEBUGF ('c',this);
   vertex orig, top , right;
   orig.xpos = 0;
   orig.ypos = 0;
   top.xpos = 0;
   top.ypos = height;
   right.xpos = width;
   right.ypos = 0;
   orig.id = id;
   verticess.push_back(orig);
   verticess.push_back(top);
   verticess.push_back(right);
   DEBUGF ('c', this << "(" << width << "," << height << ")"); 
}

equilateral::equilateral(GLfloat width,
 int id):triangle(vertices){
   //cout<<"equilateral"<<endl; 
   DEBUGF('c',this);
   vertex left, right, top;
   left.xpos = width * -0.5;
   left.ypos = 0;
   right.xpos = width * 0.5;
   right.ypos = 0;
   top.xpos = 0;
   top.ypos = width * 0.5 * sqrt(3);
   //cout<<left<<endl;
//   cout<<right<<endl;
 //  cout<<top<<endl;
   left.id = id;
   verticess.push_back(left);
   verticess.push_back(top);
   verticess.push_back(right);
   DEBUGF('c',this<<"(" << width <<")");
}

isosceles::isosceles (GLfloat width,
 GLfloat height, int id):triangle(vertices){
  // cout<<"isosceles"<<endl;
   DEBUGF ('c',this);
   vertex left, right , top;
   left.xpos = width * -0.5;
   left.ypos = 0;
   right.xpos = width * 0.5;
   right.ypos = 0;
   top.xpos = 0;
   top.ypos = height;
   left.id = id;
   verticess.push_back(left);
   verticess.push_back(right);
   verticess.push_back(top);
   DEBUGF('c', this<<"(" << width << "," << height << ")");
}                  

//Draw commands for each individual shape.
void text::draw (const vertex& center,
 const rgbcolor& color, int id) const {
   //cout<<"text::draw"<<endl;
   counter = 0;
   id = id;
   glRasterPos2i(center.xpos,center.ypos);
  // cout<<glut_bitmap_font<<endl;
   //cout<<textdata<<endl;
   for(const char&c : textdata){
   glColor3f(color.red, color.green, color.blue);
   glutBitmapCharacter(glut_bitmap_font,c);
}
   DEBUGF ('d', this << "(" << center << "," << color << ")");
}

void ellipse::draw (const vertex& center, 
const rgbcolor& color,int id) const {
  // cout <<"ellipse::draww"<<endl;
   glBegin(GL_TRIANGLES);
   GLfloat num =.0174532925;
   double old_x=(cos(0)*dimension.xpos*.5) + center.xpos;
   double old_y=(sin(0)*dimension.ypos*.5) + center.ypos;
     for(int i = 1; i < 365; ++i) {
       double new_x =(cos(i*num)*dimension.xpos*.5) + center.xpos;
       double new_y =(sin(i*num)*dimension.ypos*.5) + center.ypos;
       glColor3ub(color.red, color.green, color.blue);
       glVertex2f(center.xpos, center.ypos);
       glColor3ub(color.red, color.green, color.blue);
       glVertex2f(old_x,old_y);
       glColor3ub(color.red, color.green, color.blue);
       glVertex2f(new_x, new_y);
       old_x = new_x; old_y = new_y;
   }
   glEnd();
   const int s = id;
   const char c = s+'0';
   counter ++;
   void* font = GLUT_BITMAP_HELVETICA_18;
   glColor3f(255,255,255);
   glRasterPos2i (center.xpos, center.ypos);
   glutBitmapCharacter (font, c);
   DEBUGF ('d', this << "(" << center << "," << color << ")");
}

void polygon::draw (const vertex& center, 
const rgbcolor& color,int id) const {
     //rectangle part;
     vertex mcenter;
     mcenter.xpos = center.xpos;
     mcenter.ypos = center.ypos;
  //   cout<<"polygon::draw"<<endl;
     glBegin(GL_POLYGON);
     for(auto ver = verticess.begin(); ver != verticess.end(); ver++){
              glColor3ub(color.red, color.green, color.blue);
              glVertex2f(ver->xpos + center.xpos, 
              ver->ypos + center.ypos);
              if(ver->xpos+center.xpos > 640)
              {mcenter.xpos = mcenter.xpos - 640;} //right side
              if(ver->xpos+center.xpos < 0)
              {mcenter.xpos = mcenter.xpos +640;} // left side
              if(ver->ypos+center.ypos > 480)
              {mcenter.ypos = mcenter.ypos -480;} //top side
              if(ver->ypos+center.ypos < 0)
              {mcenter.ypos = mcenter.ypos + 4480;} //bottom side
              }
    /* if(checker == 1){
     for(auto ver = verticess.begin(); ver != vert
     icess.end(); ver++){
              glColor3ub(color.red, color.green, color.blue);
              glVertex2f(ver->xpos + mcenter.xpos,
               ver->ypos + mcenter.ypos);
              }               
              }*/
              
     glEnd();  
     const int s = id;
     const char c = s+'0';
     counter++;
     void* font = GLUT_BITMAP_HELVETICA_18;
     glColor3f(255,255,255);
     glRasterPos2i (center.xpos, center.ypos);
     glutBitmapCharacter (font, c);
     DEBUGF ('d', this << "(" << center << "," << color << ")");
}

void polygon::border_draw(const vertex& center,
 const rgbcolor& color, GLfloat thickness) const {
     //rectangle part;
     counter = 0 ;
    // cout<<"polygon::border_draw"<<endl;
     glBegin(GL_POLYGON);
     //GLfloat new_xpos;
     for(auto ver = verticess.begin(); ver != verticess.end(); ver++){
              int x = 0;
              glColor3ub(color.red, color.green, color.blue);
              if(ver->xpos < 0 && ver->ypos < 0){
                 glVertex2f(ver->xpos + center.xpos - thickness ,
                  ver->ypos + center.ypos - thickness);

              }
              else if(ver->xpos < 0 && ver->ypos > 0){
                 glVertex2f(ver->xpos + center.xpos - thickness ,
                  ver->ypos + center.ypos + thickness);

              }
              else if(ver->xpos > 0 && ver->ypos < 0){
                 glVertex2f(ver->xpos + center.xpos +thickness ,
                  ver->ypos + center.ypos - thickness);

              }
              else if(ver->xpos > 0 && ver->ypos > 0){
                 glVertex2f(ver->xpos + center.xpos + thickness ,
                  ver->ypos + center.ypos + thickness);
              } 
              else if(ver->xpos == 0 && ver->ypos > 0) {
                 glVertex2f(ver->xpos + center.xpos,
                  ver->ypos + center.ypos + thickness);
              } 
              else if(ver->xpos == 0 && ver->ypos < 0) {
                 glVertex2f(ver->xpos + center.xpos,
                  ver->ypos + center.ypos - thickness);
              } 
              else if(ver->xpos > 0 && ver->ypos == 0) {
                 glVertex2f(ver->xpos + center.xpos + thickness ,
                  ver->ypos + center.ypos);
              } 
              else if(ver->xpos < 0 && ver->ypos == 0) {
                 glVertex2f(ver->xpos + center.xpos - thickness,
                  ver->ypos + center.ypos);
              } 
             // cout<<x<<endl;
              x++;
     }
     glEnd();  
     DEBUGF ('d', this << "(" << center << "," << color << ")");
}



     
     

void ellipse::border_draw(const vertex& center,
 const rgbcolor& color, GLfloat thickness) const {
    // cout <<"ellipse::border_draw"<<endl;
     counter = 0 ;
     glBegin(GL_TRIANGLES);
     GLfloat num =.0174532925;
     double old_x=(cos(0)*(dimension.xpos+thickness)*.5) + center.xpos;
     double old_y=(sin(0)*(dimension.ypos+thickness)*.5) + center.ypos;
       for(int i = 1; i < 365; ++i) {
         double new_x =(cos(i*num)*(dimension.xpos+thickness)
         *.5) + center.xpos;
         double new_y =(sin(i*num)*(dimension.ypos+thickness)
         *.5) + center.ypos;
         glColor3ub(color.red, color.green, color.blue);
         glVertex2f(center.xpos, center.ypos);
         glColor3ub(color.red, color.green, color.blue);
         glVertex2f(old_x,old_y);
         glColor3ub(color.red, color.green, color.blue);
         glVertex2f(new_x, new_y);
         old_x = new_x; old_y = new_y;
     }
     glEnd();
     DEBUGF ('d', this << "(" << center << "," << color << ")");
       }
void text::border_draw(const vertex& center,
                       const rgbcolor& color, GLfloat thickness) const {
     //cout<<"text::border_draw"<<endl;
     thickness = thickness;
     glRasterPos2i(center.xpos+1,center.ypos+1);
     //cout<<glut_bitmap_font<<endl;
    // cout<<textdata<<endl;
     for(const char&c : textdata){
     glColor3f(color.red, color.green, color.blue);
     glutBitmapCharacter(glut_bitmap_font,c);
     }
     }

void shape::show (ostream& out) const {
    // cout<<"shape::show"<<endl;
   out << this << "->" << demangle (*this) << ": ";
}

void text::show (ostream& out) const {
    // cout<<"text::show"<<endl;
   shape::show (out);
   out << glut_bitmap_font << "(" << fontname[glut_bitmap_font]
       << ") \"" << textdata << "\"";
}

void ellipse::show (ostream& out) const {
   //cout<<"ellipse::show"<<endl;
   shape::show (out);
   out << "{" << dimension << "}";
}

void polygon::show (ostream& out) const {
  // cout<<"polygon::show"<<endl; 
   shape::show (out);
  // cout<<verticess[0].id<<endl;
   out << "{" << verticess << "}";
}

ostream& operator<< (ostream& out, const shape& obj) {
   obj.show (out);
   return out;
}


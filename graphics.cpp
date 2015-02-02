// $Id: graphics.cpp,v 1.10 2014-05-08 20:47:45-07 - - $

#include <iostream>
using namespace std;

#include <GL/freeglut.h>

#include "graphics.h"
#include "util.h"

int window::width = 640; // in pixels
int window::height = 480; // in pixels
vector<object> window::objects;
size_t window::selected_obj = 0;
mouse window::mus;

// Executed when window system signals to shut down.
void window::close() {
   DEBUGF ('g', sys_info::execname() << ": exit ("
           << sys_info::exit_status() << ")");
   exit (sys_info::exit_status());
}

// Executed when mouse enters or leaves window.
void window::entry (int mouse_entered) {
   DEBUGF ('g', "mouse_entered=" << mouse_entered);
   window::mus.entered = mouse_entered;
   if (window::mus.entered == GLUT_ENTERED) {
      cout << sys_info::execname() << ": width=" << window::width
           << ", height=" << window::height << endl;
   }
   glutPostRedisplay();
}

// Called to display the objects in the window.
void window::display() {
     //cout <<"in window::display()"<<endl;
   glClear (GL_COLOR_BUFFER_BIT);
   int x =0;
   //Loops through all the objects stored in the window, drawing them
   for (auto& selected_object: window::objects) {
       x++;
      if(selected_object.find()){
          selected_object.borderdraw();
          }
   }
   x--;     
   for (auto& object: window::objects) {
       object.set_max(x);
       //object.print();
       object.draw();
       object.draw4();
       }
   mus.draw();
   glutSwapBuffers();
}

// Called when window is opened and when resized.
void window::reshape (int width, int height) {
   DEBUGF ('g', "width=" << width << ", height=" << height);
   window::width = width;
   window::height = height;
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D (0, window::width, 0, window::height);
   glMatrixMode (GL_MODELVIEW);
   glViewport (0, 0, window::width, window::height);
   glClearColor (0.25, 0.25, 0.25, 1.0);
   glutPostRedisplay();
}


// Executed when a regular keyboard key is pressed.
//Currently not implemented
enum {BS=8, TAB=9, ESC=27, SPACE=32, DEL=127};
void window::keyboard (GLubyte key, int x, int y) {
   DEBUGF ('g', "key=" << (unsigned)key << ", x=" << x << ", y=" << y);
   window::mus.set (x, y);
   switch (key) {
      case 'Q': case 'q': case ESC:
         window::close();
         break;
      case 'H': case 'h':
         for (auto& object: window::objects) {
              if(object.find()){
                 object.move(-1,0);
                 }
                 }
         break;
      case 'J': case 'j':
         for (auto& object: window::objects) {
              if(object.find()){
                 object.move(0,-1);
                 }
                 }
         break;
      case 'K': case 'k':
         for (auto& object: window::objects) {
              if(object.find()){
                 object.move(0,1);
                 }
                 }
         break;
      case 'L': case 'l':
         for (auto& object: window::objects) {
              if(object.find()){
                 object.move(1,0);
                 }
                 }
         break;
      case 'N': case 'n': case SPACE: case TAB:
       for (auto& object: window::objects) {
       object.set_selected(14);
       } 
       //cout<<"selected++ "<<endl;
         break;
      case 'P': case 'p': case BS:
       for (auto& object: window::objects) {
       object.set_selected(13);
       } 
      // cout<<"selected-- "<<endl;
         break;   
      case '0':
       for (auto& object: window::objects) {
       object.set_selected(0);
       }
      // cout<<"selected id = 0"<<endl;
       break;
      case '1':
       for (auto& object: window::objects) {
       object.set_selected(1);
       }
      // cout<<"selected id = 1"<<endl;
      break;
      case '2':
       for (auto& object: window::objects) {
       object.set_selected(2);
       //cout<<"selected id = 2"<<endl;
       }
      break;
      case '3':
       for (auto& object: window::objects) {
       object.set_selected(3);
     //  cout<<"selected id = 3"<<endl;
       }
      break;
      case '4':
       for (auto& object: window::objects) {
       object.set_selected(4);
    //   cout<<"selected id = 4"<<endl;
       }
      break;
      case '5':
       for (auto& object: window::objects) {
       object.set_selected(5);
      // cout<<"selected id = 5"<<endl;
       }
      break;
      case '6':
       for (auto& object: window::objects) {
       object.set_selected(6);
      // cout<<"selected id = 6"<<endl;
       }
      break;
      case '7':
       for (auto& object: window::objects) {
       object.set_selected(7);
    //   cout<<"selected id = 7"<<endl;
       }
      break;
      case '8':
       for (auto& object: window::objects) {
       object.set_selected(8);
     //  cout<<"selected id = 8"<<endl;
       }
      break;
      case '9':
       for (auto& object: window::objects) {
       object.set_selected(9);
      // cout<<"selected id = 9"<<endl;
       }
      break;
      default:
         cerr << (unsigned)key << ": invalid keystroke" << endl;
         break;
   }
   glutPostRedisplay();
}


// Executed when a special function key is pressed.
//Currently doesnt do anything
void window::special (int key, int x, int y) {
   DEBUGF ('g', "key=" << key << ", x=" << x << ", y=" << y);
   window::mus.set (x, y);
   switch (key) {
      case GLUT_KEY_LEFT: //move_selected_object (-1, 0); break;
      for (auto& object: window::objects) {
              if(object.find()){
                 object.move(-1,0);
                 }
                 }
         break;
      case GLUT_KEY_DOWN: //move_selected_object (0, -1); break;
       for (auto& object: window::objects) {
              if(object.find()){
                 object.move(0,-1);
                 }
                 }
         break;
      case GLUT_KEY_UP: //move_selected_object (0, +1); break;
       for (auto& object: window::objects) {
              if(object.find()){
                 object.move(0,1);
                 }
                 }
         break;
      case GLUT_KEY_RIGHT: //move_selected_object (+1, 0); break;
       for (auto& object: window::objects) {
              if(object.find()){
                 object.move(1,0);
                 }
                 }
         break;
      case GLUT_KEY_F1: //select_object (1); break;
      for (auto& object: window::objects) {
       object.set_selected(1);
       }
      // cout<<"selected id = 1"<<endl;
       break;
      case GLUT_KEY_F2: //select_object (2); break;
      for (auto& object: window::objects) {
       object.set_selected(2);
       }
  //     cout<<"selected id = 2"<<endl;
       break;
      case GLUT_KEY_F3: //select_object (3); break;
      for (auto& object: window::objects) {
       object.set_selected(3);
       }
 //      cout<<"selected id = 3"<<endl;
       break;
      case GLUT_KEY_F4: //select_object (4); break;
      for (auto& object: window::objects) {
       object.set_selected(4);
       }
    //   cout<<"selected id = 4"<<endl;
       break;
      case GLUT_KEY_F5: //select_object (5); break;
      for (auto& object: window::objects) {
       object.set_selected(5);
       }
      // cout<<"selected id = 5"<<endl;
       break;
      case GLUT_KEY_F6: //select_object (6); break;
      for (auto& object: window::objects) {
       object.set_selected(6);
       }
      // cout<<"selected id = 6"<<endl;
       break;
      case GLUT_KEY_F7: //select_object (7); break;
      for (auto& object: window::objects) {
       object.set_selected(7);
       }
    //   cout<<"selected id = 7"<<endl;
       break;
      case GLUT_KEY_F8: //select_object (8); break;
      for (auto& object: window::objects) {
       object.set_selected(8);
       }
      // cout<<"selected id = 8"<<endl;
       break;
      case GLUT_KEY_F9: //select_object (9); break;
      for (auto& object: window::objects) {
       object.set_selected(9);
       }
    //   cout<<"selected id = 9"<<endl;
       break;
      case GLUT_KEY_F10: //select_object (10); break;
      for (auto& object: window::objects) {
       object.set_selected(10);
       }
    //   cout<<"selected id = 10"<<endl;
       break;
      case GLUT_KEY_F11: //select_object (11); break;
      for (auto& object: window::objects) {
       object.set_selected(11);
       }
      // cout<<"selected id = 1"<<endl;
       break;
      case GLUT_KEY_F12: //select_object (12); break;
      for (auto& object: window::objects) {
       object.set_selected(12);
       }
      // cout<<"selected id = 12"<<endl;
       break;
      default:
         cerr << (unsigned)key << ": invalid function key" << endl;
         break;
   }
   glutPostRedisplay();
}


void window::motion (int x, int y) {
   DEBUGF ('g', "x=" << x << ", y=" << y);
   window::mus.set (x, y);
   glutPostRedisplay();
}

void window::passivemotion (int x, int y) {
   DEBUGF ('g', "x=" << x << ", y=" << y);
   window::mus.set (x, y);
   glutPostRedisplay();
}

void window::mousefn (int button, int state, int x, int y) {
   DEBUGF ('g', "button=" << button << ", state=" << state
           << ", x=" << x << ", y=" << y);
   window::mus.state (button, state);
   window::mus.set (x, y);
   glutPostRedisplay();
}

void window::main () {

   static int argc = 0;
  // cout << "in window::main" << endl;
   glutInit (&argc, nullptr);
   glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE);
   glutInitWindowSize (window::width, window::height);
   glutInitWindowPosition (128, 128);
   glutCreateWindow (sys_info::execname().c_str());
   //Below are the callback registrations for each type of function.
   glutCloseFunc (window::close);
   glutEntryFunc (window::entry);
   //THIS ONE IS IMPORTANT
   glutDisplayFunc (window::display);
   glutReshapeFunc (window::reshape);
   //THIS ONE LETS YOU CONTROL YOUR PROGRAM
   glutKeyboardFunc (window::keyboard);
   glutSpecialFunc (window::special);
   
   glutMotionFunc (window::motion);
   glutPassiveMotionFunc (window::passivemotion);
   glutMouseFunc (window::mousefn);
   DEBUGF ('g', "Calling glutMainLoop()");
   glutMainLoop();
}


void mouse::state (int button, int state) {
   switch (button) {
      case GLUT_LEFT_BUTTON: left_state = state; break;
      case GLUT_MIDDLE_BUTTON: middle_state = state; break;
      case GLUT_RIGHT_BUTTON: right_state = state; break;
   }
}

void mouse::draw() {
   static rgbcolor color ("green");
   ostringstream text;
   text << "(" << xpos << "," << window::height - ypos << ")";
   if (left_state == GLUT_DOWN) text << "L"; 
   if (middle_state == GLUT_DOWN) text << "M"; 
   if (right_state == GLUT_DOWN) text << "R"; 
   if (entered == GLUT_ENTERED) {
      void* font = GLUT_BITMAP_HELVETICA_18;
      glColor3ubv (color.ubvec);
      glRasterPos2i (10, 10);
      glutBitmapString (font, (GLubyte*) text.str().c_str());
   }
}


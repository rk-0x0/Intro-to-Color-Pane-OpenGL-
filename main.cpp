#include<iostream>
#include<GL/glut.h>
#include<vector>
#include<math.h>
using namespace std;

int width=700,height=600,f;
vector<pair<float,float> > points;

float r,g,b;

void getColor(int x,int y)
{
    unsigned char p[3];
    glReadPixels
        (
        x,y,
        1, 1,
        GL_RGB, GL_UNSIGNED_BYTE,
        &p[0]
        );

    // cout<<r<<g<<b<<endl;

    glColor3ub(p[0],p[1],p[2]);
    glBegin(GL_POLYGON);
    for(unsigned int i=0;i<points.size();i++)
        glVertex2i(points[i].first,points[i].second);
    glEnd();
    glFlush();

}

 void DDA()
    {   points.push_back(points[0]);

         int dx,dy;
        float xinc,yinc,x,y;
        for(unsigned int i=0;i<points.size()-1;i++)
        {  int steps;
             x=points[i].first;
            y=points[i].second;

            dx = points[i+1].first - points[i].first;
            dy = points[i+1].second - points[i].second;

            steps= abs(dx)>abs(dy) ? abs(dx) : abs(dy) ;
            //cout<<steps;
            xinc= dx/(float)steps;
            yinc= dy/(float)steps;

           // cout<<xinc<<endl;
          //  cout<<yinc<<endl;
          //  cout<<"\n"<<flag<<endl;

            glColor3f(1.0,1.0,1.0);
            for(int j=0;j<=steps;j++)
            {
                glBegin(GL_POINTS);
                glVertex2i( round(x), round(y));
                glEnd();
                glFlush();
                x=x+xinc;
                y=y+yinc;
            }
        }
    }
void DisplayText(string text, int x, int y, int font)
{
	void *p = NULL;
	if (font < 8 && font>1)
        p = ((void *)font);
	else
	    p = ((void *)5);

	glColor3f(1, 1, 1);
	glRasterPos2f(x, y);
	size_t len = text.length();
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(p, (int)text[i]);

	glColor3f(1, 0, 0);
}


void my_display()
{

    DisplayText("Right-click to create, after giving vertices.",40,height-20,8);

   glBegin(GL_POLYGON);
   glColor3f(1.0f,0.0f,0.0f);
   glVertex2f(width-100,0);
   glColor3f(0.0f,1.0f,0.0f);
   glVertex2f(width,0);
   glColor3f(0.0f,0.0f,1.0f);
   glVertex2f(width,height);
   glColor3f(1.0f,1.0f,1.0f);
   glVertex2f(width-100,height);
   glEnd();
   glFlush();
}

void Menu(int p)
{
    //cout<<p<<endl;
  switch(p)
    {
    case 1:
        if(f>2)
         {
          DDA();
          f=-1;
         }
         else
            f=0;
        break;
    case 2:
        glClearColor(0.0,0.0,0.0,0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
         points.clear();
         f=0;
         glutPostRedisplay();
      break;
    }

  // glutDetachMenu(GLUT_RIGHT_BUTTON);

}

void my_mouse(int button,int state,int x,int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN && f!=-1)
        {   f++;
           y= height-y;
            if(x>width-100)
                x=width-100;
            if(y>height-40)
                y=height-40;

            pair<float,float> p;
            p.first=(float)(x);
            p.second=(float)(y);

            points.push_back(p);

          // cout<<p.first<<endl;
           //cout<<p.second<<endl;

        }
       else if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN  && f==-1)
       { if(x>=width-100)
        {   //cout<<x<<height-y<<endl;
            getColor(x,height-y);
        }

       }

        glutCreateMenu(Menu);
        glutAddMenuEntry("Create",1);
        glutAddMenuEntry("Clear",2);
        glutAttachMenu(GLUT_RIGHT_BUTTON);


}
void Motion(int x,int y)
{
	getColor(x, height-y);
}
void myinit()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,width,0,height);
    glFlush();
}

int main(int argc,char* argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(5,5);
    glutInitWindowSize(width,height);
    glutCreateWindow("Drawing");

    glutDisplayFunc(my_display);
    glutMouseFunc(my_mouse);
    glutMotionFunc(Motion);
    myinit();
    glutMainLoop();

    return 0;
}


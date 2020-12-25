#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <bits/stdc++.h>
#include <math.h>
#include "RGBpixmap.cpp"

static int flag1 = 0;
static int flag2 = 0;
static int slices = 16;
static int stacks = 16;
float d_x = 0;
float d_y = 0;
float d_z = 0;
float z = -10;
float dr = 0;
float t = 0;

double tx = -2;
double ty = 0;
double tz = -10;

double zx = .3;
double zy = .3;
double zz = .3;

double ex = 15;
double ey = 15;
double ez = 40;

double dx = 15;
double dy = 0;
double dz = -20;

double hx = 0;
double hy = 1;
double hz = 0;

double w,h;
float ar,tb = 1.0;

double aa,bb,xx,yy,zzz;


const GLfloat light_r[]={20.0f};

const GLfloat light_ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 100.0f, 100.0f, 100.0f, 0.0f };

const GLfloat light_ambient1[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_diffuse1[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position1[] = { 0.0f, 0.0f, 15.0f, 1.0f };


const GLfloat light_ambient2[]  = { 0.5f, 0.5f, 0.5f, 1.0f };
const GLfloat light_diffuse2[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//const GLfloat light_position1[] = { 0.0f, 0.0f, -30.0f, 1.0f };
const GLfloat light_direction[]= {0.0f, 0.0f, -30.0f, 1.0f};

const GLfloat mat_no_color[]   = { 0.0f, 0.0f, 0.0f, 1.0f };

const GLfloat high_shininess[] = { 0.0f };


/* GLUT callback Handlers */



RGBpixmap pix[10];

void Init()
{
	glEnable(GL_TEXTURE_2D);


    pix[0].makeCheckImage();
	pix[0].setTexture(1);

	pix[1].readBMPFile("F:\\Class Lecture\\4th Year 2nd Semister\\CSE 4208 Computer Graphics Laboratory\\graphics texture\\brick.bmp");
	pix[1].setTexture(2);

	pix[2].readBMPFile("F:\\Class Lecture\\4th Year 2nd Semister\\CSE 4208 Computer Graphics Laboratory\\graphics texture\\rb.bmp");
	pix[2].setTexture(3);

	pix[3].readBMPFile("F:\\Class Lecture\\4th Year 2nd Semister\\CSE 4208 Computer Graphics Laboratory\\graphics texture\\table.bmp");
	pix[3].setTexture(4);

	pix[4].readBMPFile("F:\\Class Lecture\\4th Year 2nd Semister\\CSE 4208 Computer Graphics Laboratory\\graphics texture\\tiles.bmp");
	pix[4].setTexture(5);

	pix[5].readBMPFile("F:\\Class Lecture\\4th Year 2nd Semister\\CSE 4208 Computer Graphics Laboratory\\graphics texture\\c.bmp");
	pix[5].setTexture(6);

	pix[6].readBMPFile("F:\\Class Lecture\\4th Year 2nd Semister\\CSE 4208 Computer Graphics Laboratory\\graphics texture\\wheel.bmp");
	pix[6].setTexture(7);

	pix[7].readBMPFile("F:\\Class Lecture\\4th Year 2nd Semister\\CSE 4208 Computer Graphics Laboratory\\graphics texture\\cglass.bmp");
	pix[7].setTexture(8);

	pix[8].readBMPFile("F:\\Class Lecture\\4th Year 2nd Semister\\CSE 4208 Computer Graphics Laboratory\\graphics texture\\teapot.bmp");
	pix[8].setTexture(9);

	pix[8].readBMPFile("F:\\Class Lecture\\4th Year 2nd Semister\\CSE 4208 Computer Graphics Laboratory\\graphics texture\\paint.bmp");
	pix[8].setTexture(10);
}

void zoom(GLdouble x,GLdouble y,GLdouble z)
{
    GLdouble m[16];
    m[ 0] = x; m[ 1] = 0; m[ 2] = 0; m[ 3] = 0;
    m[ 4] = 0; m[ 5] = y; m[ 6] = 0; m[ 7] = 0;
    m[ 8] = 0; m[ 9] = 0; m[10] = z; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;

    glMatrixMode(GL_MODELVIEW);
    glMultMatrixd(m);
}

static void resize(int width, int height)
{
    ar = (float) width / (float) height;

    w=width;
    h=height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -tb, tb, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void circle_ac(int x,int y)
{
    float c;
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i++)
    {
        c=i*(3.1416/180);
        glVertex2f(x+1.875*cos(c),y+1.875*sin(c));
    }
    glEnd();
}

void circle_c(int x,int y)
{
    float d;
    glBegin(GL_POLYGON);
    for(int i=359; i>=0; i--)
    {
        d=i*(3.1416/180);
        glVertex2f(x+1.875*cos(d),y+1.875*sin(d));
    }
    glEnd();
}

void cylinder()
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glPushMatrix();
    glTranslated(0,0,0);
    glRotated(t*10,0,0,1);
    glScalef(.5,.5,.5);
    gluCylinder(gluNewQuadric(),
                3.75,
                3.75,
                3,
                slices,
                stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,0,1.5);
    glRotated(t*10,0,0,1);
    circle_ac(0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,0,0);
    glRotated(t*10,0,0,1);
    circle_c(0,0);
    glPopMatrix();
}

const GLfloat mat_ambient_wheel[]    = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat mat_diffuse_wheel[]    = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat mat_specular_wheel[]   = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat high_shininess_wheel[] = { 0.0f };

void cylinderv2()
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_wheel);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_wheel);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_wheel);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess_wheel);

    glPushMatrix();
    glTranslated(0,0,0);
    glRotated(t*10,0,0,1);
    glScalef(.5,.5,.5);
    gluCylinder(gluNewQuadric(),
                3.75,
                3.75,
                3,
                slices,
                stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,0,1.5);
    glRotated(t*10,0,0,1);
    circle_ac(0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,0,0);
    glRotated(t*10,0,0,1);
    circle_c(0,0);
    glPopMatrix();
}

void light()
{
    glPushMatrix();
    glTranslated(0,0,0);
    glScalef(.5,.5,.5);
    gluCylinder(gluNewQuadric(),
                3.75,
                3.75,
                3,
                slices,
                stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,0,1.5);
    circle_ac(0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,0,0);
    circle_c(0,0);
    glPopMatrix();
}


const GLfloat mat_ambient_light[]    = { 1.0f, 1.0f, 0.0f, 1.0f };
const GLfloat mat_diffuse_light[]    = { 1.0f, 1.0f, 0.0f, 1.0f };
const GLfloat mat_specular_light[]   = { 1.0f, 1.0f, 0.0f, 1.0f };
const GLfloat high_shininess_light[] = { 0.0f };

void lightv2()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_light);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_light);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_light);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess_light);

    glPushMatrix();
    glTranslated(0,0,0);
    glScalef(.5,.5,.5);
    gluCylinder(gluNewQuadric(),
                3.75,
                3.75,
                3,
                slices,
                stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,0,1.5);
    circle_ac(0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,0,0);
    circle_c(0,0);
    glPopMatrix();
}

void pic()
{
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(0,0);
    glTexCoord2f(1,0);
    glVertex2f(1,0);
    glTexCoord2f(1,1);
    glVertex2f(1,1);
    glTexCoord2f(0,1);
    glVertex2f(0,1);
    glEnd();
}

void cube()
{
    glBegin(GL_QUADS);

    //p1
    glVertex3f(0.0,1.0,1.0);
    glVertex3f(0.0,0.0,1.0);
    glVertex3f(1.0,0.0,1.0);
    glVertex3f(1.0,1.0,1.0);

    //p2
    glVertex3f(1.0,1.0,1.0);
    glVertex3f(1.0,0.0,1.0);
    glVertex3f(1.0,0.0,0.0);
    glVertex3f(1.0,1.0,0.0);

    //p3
    glVertex3f(0.0,1.0,0.0);
    glVertex3f(0.0,1.0,1.0);
    glVertex3f(1.0,1.0,1.0);
    glVertex3f(1.0,1.0,0.0);

    //p4
    glVertex3f(0.0,1.0,0.0);
    glVertex3f(1.0,1.0,0.0);
    glVertex3f(1.0,0.0,0.0);
    glVertex3f(0.0,0.0,0.0);

    //p5
    glVertex3f(0.0,1.0,0.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.0,1.0);
    glVertex3f(0.0,1.0,1.0);

    //p6
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(1.0,0.0,0.0);
    glVertex3f(1.0,0.0,1.0);
    glVertex3f(0.0,0.0,1.0);

    glEnd();
}

void car()
{
    //Lower part
    glPushMatrix();
    glTranslated(1,1,1);
    glScaled(15,3,7.5);
    glBindTexture(GL_TEXTURE_2D,6);
	glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Upper part
    glPushMatrix();
    glTranslated(5,4,1.5);
    glScaled(7,3,6.5);
    glBindTexture(GL_TEXTURE_2D,6);
	glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Glass 1
    glPushMatrix();
    glTranslated(5.5,4,8);
    glScaled(6,2.5,.5);
    glBindTexture(GL_TEXTURE_2D,8);
	glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Glass 2
    glPushMatrix();
    glTranslated(5.5,4,1);
    glScaled(6,2.5,.5);
    glBindTexture(GL_TEXTURE_2D,8);
	glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Glass 3
    glPushMatrix();
    glTranslated(4.5,4,2);
    glScaled(.5,2.5,5.5);
    glBindTexture(GL_TEXTURE_2D,8);
	glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Glass 4
    glPushMatrix();
    glTranslated(12,4,2);
    glScaled(.5,2.5,5.5);
    glBindTexture(GL_TEXTURE_2D,8);
	glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Front lower part
    glPushMatrix();
    glTranslated(16,1,1.5);
    glScaled(.5,1,6.5);
    glBindTexture(GL_TEXTURE_2D,6);
	glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Back lower part
    glPushMatrix();
    glTranslated(.5,1,1.5);
    glScaled(.5,1,6.5);
    glBindTexture(GL_TEXTURE_2D,6);
	glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Back upper part
    glPushMatrix();
    glTranslated(.5,3,1.5);
    glScaled(.5,.5,6.5);
    glBindTexture(GL_TEXTURE_2D,6);
	glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Wheel 1
    glPushMatrix();
    glTranslated(4.5,1,8);
    glScaled(.75,.75,.75);
    glBindTexture(GL_TEXTURE_2D,7);
	glEnable(GL_TEXTURE_2D);
    cylinder();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Wheel 2
    glPushMatrix();
    glTranslated(11,1,8);
    glScaled(.75,.75,.75);
    glBindTexture(GL_TEXTURE_2D,7);
	glEnable(GL_TEXTURE_2D);
    cylinder();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Wheel 3
    glPushMatrix();
    glTranslated(4.5,1,.25);
    glScaled(.75,.75,.75);
    glBindTexture(GL_TEXTURE_2D,7);
	glEnable(GL_TEXTURE_2D);
    cylinder();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Wheel 4
    glPushMatrix();
    glTranslated(11,1,.25);
    glScaled(.75,.75,.75);
    glBindTexture(GL_TEXTURE_2D,7);
	glEnable(GL_TEXTURE_2D);
    cylinder();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Light 1
    glPushMatrix();
    glTranslated(16,2.75,2.5);
    glScaled(.25,.25,.25);
    glRotated(90,0,1,0);
    glBindTexture(GL_TEXTURE_2D,8);
	glEnable(GL_TEXTURE_2D);
    cylinder();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Light 2
    glPushMatrix();
    glTranslated(16,2.75,7.5);
    glScaled(.25,.25,.25);
    glRotated(90,0,1,0);
    glBindTexture(GL_TEXTURE_2D,8);
	glEnable(GL_TEXTURE_2D);
    cylinder();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

const GLfloat mat_ambient_carbody[]    = { 0.8f, 0.0f, 0.0f, 1.0f };
const GLfloat mat_diffuse_carbody[]    = { 0.8f, 0.0f, 0.0f, 1.0f };
const GLfloat mat_specular_carbody[]   = { 0.8f, 0.0f, 0.0f, 1.0f };
const GLfloat high_shininess_carbody[] = { 0.0f };

const GLfloat mat_ambient_glass[]    = { 0.0f, 0.6f, 0.6f, 1.0f };
const GLfloat mat_diffuse_glass[]    = { 0.0f, 0.6f, 0.6f, 1.0f };
const GLfloat mat_specular_glass[]   = { 0.0f, 0.6f, 0.6f, 1.0f };
const GLfloat high_shininess_glass[] = { 0.0f };


void carv2()
{
    //Lower part
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_carbody);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_carbody);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_carbody);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess_carbody);
    glTranslated(1,1,1);
    glScaled(15,3,7.5);
    cube();
    glPopMatrix();

    //Upper part
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_carbody);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_carbody);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_carbody);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess_carbody);
    glTranslated(5,4,1.5);
    glScaled(7,3,6.5);
    cube();
    glPopMatrix();

    //Glass 1
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_glass);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_glass);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_glass);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess_glass);
    glTranslated(5.5,4,8);
    glScaled(6,2.5,.5);
    cube();
    glPopMatrix();

    //Glass 2
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_glass);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_glass);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_glass);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess_glass);
    glTranslated(5.5,4,1);
    glScaled(6,2.5,.5);
    cube();
    glPopMatrix();

    //Glass 3
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_glass);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_glass);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_glass);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess_glass);
    glTranslated(4.5,4,2);
    glScaled(.5,2.5,5.5);
    cube();
    glPopMatrix();

    //Glass 4
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_glass);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_glass);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_glass);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess_glass);
    glTranslated(12,4,2);
    glScaled(.5,2.5,5.5);
    cube();
    glPopMatrix();

    //Front lower part
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_carbody);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_carbody);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_carbody);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess_carbody);
    glTranslated(16,1,1.5);
    glScaled(.5,1,6.5);
    cube();
    glPopMatrix();

    //Back lower part
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_carbody);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_carbody);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_carbody);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess_carbody);
    glTranslated(.5,1,1.5);
    glScaled(.5,1,6.5);
    cube();
    glPopMatrix();

    //Back upper part
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_carbody);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_carbody);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_carbody);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess_carbody);
    glTranslated(.5,3,1.5);
    glScaled(.5,.5,6.5);
    cube();
    glPopMatrix();

    //Wheel 1
    glPushMatrix();
    glTranslated(4.5,1,8);
    glScaled(.75,.75,.75);
    cylinder();
    glPopMatrix();

    //Wheel 2
    glPushMatrix();
    glTranslated(11,1,8);
    glScaled(.75,.75,.75);
    cylinder();
    glPopMatrix();

    //Wheel 3
    glPushMatrix();
    glTranslated(4.5,1,.25);
    glScaled(.75,.75,.75);
    cylinder();
    glPopMatrix();

    //Wheel 4
    glPushMatrix();
    glTranslated(11,1,.25);
    glScaled(.75,.75,.75);
    cylinder();
    glPopMatrix();

    //Light 1
    glPushMatrix();
    glTranslated(16,2.75,2.5);
    glScaled(.25,.25,.25);
    glRotated(90,0,1,0);
    lightv2();
    glPopMatrix();

    //Light 2
    glPushMatrix();
    glTranslated(16,2.75,7.5);
    glScaled(.25,.25,.25);
    glRotated(90,0,1,0);
    lightv2();
    glPopMatrix();

}

void rod()
{
    glPushMatrix();
    glTranslated(0,0,0);
    glScaled(.5,5,.5);
    glutSolidSphere(1,100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,4.5,0);
    glScaled(1,1,1);
    glutSolidSphere(1,100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,-4.5,0);
    glScaled(1,1,1);
    glutSolidSphere(1,100,100);
    glPopMatrix();

}

const GLfloat mat_ambient_rod1[]    = { 1.0f, 0.0f, 0.0f, 1.0f };
const GLfloat mat_diffuse_rod1[]    = { 1.0f, 0.0f, 0.0f, 1.0f };
const GLfloat mat_specular_rod1[]   = { 1.0f, 0.0f, 0.0f, 1.0f };
const GLfloat high_shininess_rod1[] = { 0.0f };

const GLfloat mat_ambient_rod2[]    = { 0.0f, 0.0f, 0.6f, 1.0f };
const GLfloat mat_diffuse_rod2[]    = { 0.0f, 0.0f, 0.6f, 1.0f };
const GLfloat mat_specular_rod2[]   = { 0.0f, 0.0f, 0.6f, 1.0f };
const GLfloat high_shininess_rod2[] = { 0.0f };

void rodv2(){

    glPushMatrix();
    glTranslated(0,0,0);
    glScaled(.5,5,.5);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_rod1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_rod1);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_rod1);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess_rod1);
    glutSolidSphere(1,100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,4.5,0);
    glScaled(1,1,1);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_rod2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_rod2);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_rod2);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess_rod2);
    glutSolidSphere(1,100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,-4.5,0);
    glScaled(1,1,1);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_rod2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_rod2);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_rod2);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess_rod2);
    glutSolidSphere(1,100,100);
    glPopMatrix();

}

void table()
{
    //Table floor
    glPushMatrix();
    glTranslated(25,16,25);
    glRotated(-90,0,0,1);
    glScaled(1,50,50);
    cube();
    glPopMatrix();

    //Table leg 1
    glPushMatrix();
    glTranslated(30,2,30);
    glScaled(1,13,1);
    cube();
    glPopMatrix();

    //Table leg 2
    glPushMatrix();
    glTranslated(70,2,30);
    glScaled(1,13,1);
    cube();
    glPopMatrix();

    //Table leg 3
    glPushMatrix();
    glTranslated(30,2,70);
    glScaled(1,13,1);
    cube();
    glPopMatrix();

    //Table leg 4
    glPushMatrix();
    glColor3d(0,1,1);
    glTranslated(70,2,70);
    glScaled(1,13,1);
    cube();
    glPopMatrix();
}

void stage()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT,   light_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   light_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  light_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    //Floor
    glPushMatrix();
    glTranslated(0,2,0);
    glRotated(90,1,0,0);
    glScaled(100,100,2);
    glBindTexture(GL_TEXTURE_2D,5);
	glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Wall 1
    glPushMatrix();
    glTranslated(2,2,0);
    glRotated(-90,0,1,0);
    glScaled(100,50,2);
    glBindTexture(GL_TEXTURE_2D,3);
	glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Pic
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,10);
	glEnable(GL_TEXTURE_2D);
	glTranslated(30,30,5);
    glScaled(20,20,0);
    pic();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Wall 2
    glPushMatrix();
    glTranslated(2,2,0);
    glScaled(98,50,2);
    glBindTexture(GL_TEXTURE_2D,3);
	glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Table
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,4);
	glEnable(GL_TEXTURE_2D);
    table();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //Jack
    glPushMatrix();
    glTranslated(62.5,20.25,50);
    glRotated(-45,1,0,0);
    glBindTexture(GL_TEXTURE_2D,9);
	glEnable(GL_TEXTURE_2D);
    rod();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslated(62.5,20.25,50);
    glRotated(45,1,0,0);
    glRotated(-15,0,0,1);
    glBindTexture(GL_TEXTURE_2D,9);
	glEnable(GL_TEXTURE_2D);
    rod();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslated(62.5,20.25,50);
    glRotated(45,1,0,1);
    glBindTexture(GL_TEXTURE_2D,9);
	glEnable(GL_TEXTURE_2D);
    rod();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //Car
    glPushMatrix();
    glTranslated(30,16.75,45);
    glScaled(1.5,1.5,1.5);
    car();
    glPopMatrix();

}

const GLfloat mat_ambient_floor[]    = { 0.373f, 0.373f, 0.373f, 1.0f };
const GLfloat mat_diffuse_floor[]    = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat mat_specular_floor[]   = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat high_shininess_floor[] = { 0.0f };

const GLfloat mat_ambient_wall[]    = { 0.0f, 0.1f, 0.0f, 1.0f };
const GLfloat mat_diffuse_wall[]    = { 0.0f, 0.1f, 0.0f, 1.0f };
const GLfloat mat_specular_wall[]   = { 0.0f, 0.1f, 0.0f, 1.0f };
const GLfloat high_shininess_wall[] = { 0.0f };

const GLfloat mat_ambient_table[]    = { 0.3f, 0.1f, 0.0f, 1.0f };
const GLfloat mat_diffuse_table[]    = { 0.3f, 0.1f, 0.0f, 1.0f };
const GLfloat mat_specular_table[]   = { 0.3f, 0.1f, 0.0f, 1.0f };
const GLfloat high_shininess_table[] = { 0.0f };

void stagev2()
{
    //Floor
    glPushMatrix();
    glTranslated(0,2,0);
    glRotated(90,1,0,0);
    glScaled(100,100,2);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_floor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_floor);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_floor);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess_floor);
    cube();
    glPopMatrix();

    //Wall 1
    glPushMatrix();
    glTranslated(2,2,0);
    glRotated(-90,0,1,0);
    glScaled(100,50,2);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_wall);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_wall);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_wall);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess_wall);
    cube();
    glPopMatrix();

    //Wall 2
    glPushMatrix();
    glTranslated(2,2,0);
    glScaled(98,50,2);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_wall);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_wall);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_wall);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess_wall);
    cube();
    glPopMatrix();

    //Table
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_table);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse_table);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular_table);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess_table);
    table();
    glPopMatrix();


    //Jack
    glPushMatrix();
    glTranslated(62.5,20.25,50);
    glRotated(-45,1,0,0);
    rodv2();
    glPopMatrix();

    glPushMatrix();
    glTranslated(62.5,20.25,50);
    glRotated(45,1,0,0);
    glRotated(-15,0,0,1);
    rodv2();
    glPopMatrix();

    glPushMatrix();
    glTranslated(62.5,20.25,50);
    glRotated(45,1,0,1);
    rodv2();
    glPopMatrix();


    //Car
    glPushMatrix();
    glTranslated(30,16.75,45);
    glScaled(1.5,1.5,1.5);
    carv2();
    glPopMatrix();

}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glViewport(w/2, 0, w/2, h/2);

    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(ex,ey,ez,  dx,dy,dz,  hx,hy,hz);

    glPushMatrix();
    glTranslated(tx,ty,tz);
    glRotated(d_x,1,0,0);
    glRotated(d_y,0,1,0);
    glRotated(d_z,0,0,1);
    zoom(zx,zy,zz);
    stage();

    glPopMatrix();


    glViewport(0, 0, w/2, h/2);

    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(ex,ey,ez,  dx,dy,dz,  hx,hy,hz);

    glPushMatrix();
    glTranslated(tx,ty,tz);
    glRotated(d_x,1,0,0);
    glRotated(d_y,0,1,0);
    glRotated(d_z,0,0,1);
    zoom(zx,zy,zz);
    stagev2();

    glPopMatrix();

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {

        //for translation
        case 'a':
            tx += 1;
            break;
        case 'b':
            tx -= 1;
            break;
        case 'c':
            ty += 1;
            break;
        case 'd':
            ty -= 1;
            break;
        case 'e':
            tz += 1;
            break;
        case 'f':
            tz -= 1;
            break;

        //for rotation
        case 'g':
            d_x += 1;
            break;
        case 'h':
            d_x -= 1;
            break;
        case 'i':
            d_y += 1;
            break;
        case 'j':
            d_y -= 1;
            break;
        case 'k':
            d_z += 1;
            break;
        case 'l':
            d_z -= 1;
            break;

        //for scaling/zoom
        case 'm':
            zx += 1;
            break;
        case 'n':
            zx -= 1;
            break;
        case 'o':
            zy += 1;
            break;
        case 'p':
            zy -= 1;
            break;
        case 'q':
            zz += 1;
            break;
        case 'r':
            zz -= 1;
            break;
        case 's':
            zx += .01;
            zy += .01;
            zz += .01;
            break;
        case 't':
            zx -= .01;
            zy -= .01;
            zz -= .01;
            break;

        //for Look at function
        case '1':
            ex += 1;
            break;
        case '2':
            ex -= 1;
            break;
        case '3':
            ey += 1;
            break;
        case '4':
            ey -= 1;
            break;
        case '5':
            ez += 1;
            break;
        case '6':
            ez -= 1;
            break;


        case 'u':
            hx += 1;
            break;
        case 'v':
            hx -= 1;
            break;
        case 'w':
            hy += 1;
            break;
        case 'x':
            hy -= 1;
            break;
        case 'y':
            hz += 1;
            break;
        case 'z':
            hz -= 1;
            break;

        case 'R'://Roll
            hx=hx*cos(.1)+hy*sin(.1) ;
            hy=hy*cos(.1)-hx*sin(.1);
            break;

         case 'Y'://Yaw
            aa=dx-ex;
            bb=dz-ez;
            xx=aa*cos(.1)+bb*sin(.1) ;
            zzz=bb*cos(.1)-aa*sin(.1);
            dx=xx+ex;
            dz=zzz+ez;
            break;

        case 'P'://Pitch
            aa=dy-ey;
            bb=dz-ez;
            yy=aa*cos(.1)-bb*sin(.1) ;
            zzz=bb*cos(.1)+aa*sin(.1);
            dy=yy+ey;
            dz=zzz+ez;
            break;

        //Lighting

        case '7':
            glEnable(GL_LIGHT0);
            break;

        case '8':
            glDisable(GL_LIGHT0);
            break;

        case '9':
            glEnable(GL_LIGHT1);
            break;

        case '0':
            glDisable(GL_LIGHT1);
            break;

        //Aparture
        case ',':
            ar+=0.05;
            tb+=0.05;
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glFrustum(-ar, ar, -tb, tb, 2.0, 100.0);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity() ;
            break;

        case '.':
            ar-=0.05;
            tb-=0.05;
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glFrustum(-ar, ar, -tb, tb, 2.0, 100.0);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity() ;
            break;
/*

        //curve
        case '=':
            Depth++;
            break;
        case '-':
            Depth--;
            break;*/

    }

    glutPostRedisplay();
}


static void idle(void)
{
    glutPostRedisplay();
}


/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1280,720);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    //glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient1);
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, light_r);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_direction);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, .4);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

    Init();
    glutMainLoop();

    return EXIT_SUCCESS;
}

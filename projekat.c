#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>

#define TIMER_ID 1
#define TIMER_INTERVAL 8
#define MAX 1000

static void display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void key(int k, int x, int y);
static void on_reshape(int width, int height);
static void on_timer(int id);
static void init_lights();


float animation_parameter;
float a=0;
int animation_ongoing;
int n=0;
int xKoordinatePrepreke[] = {-6, -3, 0, 3, 6};
float x1=0;


int ukupno=0;
float zL=5.9;

typedef struct {
    float xP, yP, zP;
    float lP, dP, nP;
}Prepreka;

void postavi_prepreku();
void provera();

int k=0, p1=0, p2=0;
Prepreka nizP[MAX]; 

int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow(argv[0]);
	

	glutDisplayFunc(display);
	glutReshapeFunc(on_reshape);
	glutKeyboardFunc(on_keyboard);
	glutSpecialFunc(key);
	glClearColor(0.196078, 0.6, 0.8, 0);
	
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

	animation_parameter = 0;
	animation_ongoing = 0;
	
	glutMainLoop();
	return 0;
}

static void material()
{
    GLfloat no_material[] = { 0, 0, 0, 1 };
	GLfloat material_ambient[] = { 0.3, 0.3, 0.4, 1 };
	GLfloat material_diffuse[] = { 0.7, 0.1, 0.7, 1 };
	GLfloat material_specular[] = { 1, 1, 1, 1 };
	GLfloat shine = 70;
	 
	 
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_material);
	
}


static void on_timer(int id)
{
    if (TIMER_ID != id)
        return;
	
	if(k>=100)
		a += 0.1;
    animation_parameter += 0.8;
	k++;
	
	provera();	
	if(k%1750==0){
		p2-=1400;
	}else if(k%875==0){
		p1-=1400;
	}
	
	
    glutPostRedisplay();

    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
}

static void key(int k, int x, int y)
{
	switch(k){
		case GLUT_KEY_LEFT:
			if(n==1 && x1+0.7<6)
				x1+=0.7;
			else if(x1-0.7>-6)
				x1-=0.7;
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			if(n==1 && x1-0.7>-6)
				x1-=0.7;
			else if(x1+0.7<6)
				x1+=0.7;
			glutPostRedisplay();
			break;
	}
}


static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    	case 27:
        	exit(0);
    	    break;
    	case 'g':
    	case 'G':
    	    if (!animation_ongoing) {
    	        animation_ongoing = 1;
    	        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    	    }
    	   break;
    	case 's':
    	case 'S':
    		animation_ongoing=0;
     		break;
       } 
}


static void on_reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, (float) width / height, 1, 100);
}


static void init_lights()
{
    GLfloat light_ambient[] = { 0, 0, 0, 1 };
    GLfloat light_diffuse[] = { 1, 1, 1, 1 };
    GLfloat light_specular[] = { 1, 1, 1, 1 };
    GLfloat model_ambient[] = { 0.4, 0.4, 0.4, 1 };
	
	
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
	glShadeModel(GL_SMOOTH);
}

static void material2()
{
    GLfloat no_material[] = { 0, 0.8, 0.3, 1 };
	GLfloat material_ambient[] = { 0.8, 0.9, 0.5, 1 };
	GLfloat material_diffuse[] = { 0.2, 0.6, 0.3, 1 };
	GLfloat material_specular[] = { 0.1, 0.1, 0.1, 1 };
	GLfloat shine = 10;
	 
	 
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_material);
}	


static void put(){

	
	glPushMatrix();
		glTranslatef(0, 0, p1 + animation_parameter);
		material2();
    	glBegin(GL_POLYGON);     
       		glVertex3f(7.5, -1.1, -670);
        	glVertex3f(-7.5, -1.1, -670);
        	glVertex3f(-7.5, -1.1, 30);
      		glVertex3f(7.5, -1.1, 30);
    	glEnd();
    	
    glPopMatrix();
    
    glPushMatrix();
    	glTranslatef(0, 0, p2 + animation_parameter);
    	material2();
    	glBegin(GL_POLYGON);
        	glVertex3f(7.5, -1.1, -1370);
        	glVertex3f(-7.5, -1.1, -1370);
        	glVertex3f(-7.5, -1.1, -670);
        	glVertex3f(7.5, -1.1, -670);
    	glEnd();

    glPopMatrix();
    
}



void provera(){
	
	int i;
	for(i=0; i<ukupno; i++) {
        if(abs(nizP[i].zP+animation_parameter+1 - zL) < 0.00002) {
            if((x1 - 1.1 < nizP[i].dP && x1 - 1.1 > nizP[i].lP) || (x1 + 1.1 < nizP[i].dP && x1 + 1.1 > nizP[i].lP)
            || (x1 -1.1 < nizP[i].zP+1))
                animation_ongoing = 0;
        }
    }	
	

}

void postavi_prepreku(){

	int brPrepreka = rand()%3;
	
	int i;
	for(i=0; i<brPrepreka; i++){
		Prepreka p;
		p.xP = xKoordinatePrepreke[rand()%5];
		p.yP = 0;
		p.zP = -k-60;
		p.lP = p.xP - 1;
		p.dP = p.xP + 1;
		p.nP = p.zP+1;
		nizP[ukupno]=p;
		ukupno++;
	}
		
}


static void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	GLfloat light_position[] = { 1, 1, 1, 0 };
	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 13, 30,
		  	  0, 0, 0,
	    	  0, 1, 0);
	    	  
	init_lights();
	
	if(k>=100 && a<=180){
		glRotatef(a, 0, 0.5, 1);
	}else if(k>=100){
		glRotatef(180, 0, 0.5, 1);
		n=1;
	}
	
	
	put();
	
	
	if(k%20==0)
		postavi_prepreku();


	glPushMatrix();
		glTranslatef(0+x1, 0, 7);
		glRotatef(animation_parameter, 1, 0, 0);
		material();
		glutSolidSphere(1.1, 30, 30);
    glPopMatrix();	

	int j;
	for(j=0; j<ukupno; j++)
	{
		glPushMatrix();
			glTranslatef(0+nizP[j].xP, 0, nizP[j].zP+animation_parameter);
			glRotatef(animation_parameter*10, 0,0,1);	
			material();
  			glutSolidIcosahedron();		
  		glPopMatrix();	
  		
	}
	
	
	
	glutSwapBuffers();

}

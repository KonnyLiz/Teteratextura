//tetera con textura de madera

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>

GLuint texture[0];//la textura
double rotate_y=0;
double rotate_x=0;
double rotate_z=0;

//se dibuja todo
void drawScene(void)
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glLoadIdentity();
     glTranslatef(0.0,0.0,-5);       //mueve la TETERA
     glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    glRotatef( rotate_z, 0.0, 0.0, 1.0 );
     //--------ACÁ PASA LA MAGIA DE LA ILUMINACIÓN
     // Ubicamos la fuente de luz en el punto
     GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
     // Activamos la fuente de luz
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glDepthFunc(GL_LESS);
     glEnable(GL_DEPTH_TEST);
     // Queremos que se dibujen las caras frontales
     // y con un color solido de relleno.
     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
     //----------acá pasa la magia de las texturas----------
     glShadeModel(GL_SMOOTH);         //suaviza los bordes

     int width, height;      //tamaños de la imagen
     //carga la imagen
     unsigned char* image =
     SOIL_load_image("madera2.jpg", &width, &height, 0, SOIL_LOAD_RGB);
     //la pasa a texturas
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 15, 15, 0, GL_RGB,
                  GL_UNSIGNED_BYTE, image);
    // Indicamos el tipo de filtrado
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    //usamos la autogeneración de coordenadas
    GLfloat plano_s[4] = {1, 0, 0, 0}; // s=x
    GLfloat plano_t[4] = {0, 1, 0, 0}; // t=y
    glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGenfv (GL_S, GL_OBJECT_PLANE, plano_s);
    glEnable (GL_TEXTURE_GEN_S);
    glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGenfv (GL_T, GL_OBJECT_PLANE, plano_t);
    //---------------------- activamos la texturas
    glEnable(GL_TEXTURE_2D);
    glEnable (GL_TEXTURE_GEN_T);
    glutSolidTeapot(1);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_T);
    //-------------------- desactivamos
    glFlush();

}

//el tamaño de la ventana
void resizeWindow(int x, int y)
{
if (y == 0 || x == 0) return;  //no se ve nada, devuelve
    //Define una matriz de proyección
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0,(GLdouble)x/(GLdouble)y,0.5,20.0);//Angulo de la vista: 40 grados
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //renderiza en toda la ventana
}

//teclas especiales
void specialKeys( int key, int x, int y )
{
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 7;
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 7;
    else if (key == GLUT_KEY_UP)
        rotate_x += 7;
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 7;
    else if (key == GLUT_KEY_F2)
        rotate_z += 7;
    else if (key == GLUT_KEY_F2)
        rotate_z -= 7;
    glutPostRedisplay();

}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(600, 600);//tamaño de la ventana
   glutInitWindowPosition(100, 100); //posicion
   glutCreateWindow("TETERA CON TEXTURA"); //titulo
   glutDisplayFunc(drawScene);//dibuja la escena
   glutReshapeFunc(resizeWindow);//recalcula el tamaño
    glutSpecialFunc(specialKeys);//llama al teclado
   glutMainLoop();
   return 0;
}

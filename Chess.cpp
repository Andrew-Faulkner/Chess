#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include "PPM.h"
#include <fstream>
#include <iostream>
#include "mathLib3D.cpp"

#include <vector>
#include <time.h>
#include <string>
float rotX=0;
float rotY=0;
float rotZ=0;
float pos[] = {0,1,0};
float rot[] = {0, 0, 0};   ///left over snowman variables
float headRot[] = {0, 0, 0};
float camPos[] = {100, 50, 100};
float Look[] = {0,0,0};
/* LIGHTING */

bool nolights=true;

float light_pos[4] = {5,5,5,1};
float amb[4] = {0.5,0.5,0.5,1};
float diff[4] = {1,0,1,1};
float spec[4] = {0,1,0,1};


float light_pos2[4] = {5,5,-5,1};
float amb2[4] = {1,0.5,0.5,1};
float diff2[4] = {1,1,1,1};
float spec2[4] = {1,1,0,1};

/* Materials */

float ambMat[4] = {0.5,0.5,0.5,1};
float diffMat[4] = {1,0,0,1};
float specMat[4] = {0,1,0,1};


float ambMat2[4] = {0.2,0.2,0.2,1};
float diffMat2[4] = {0.5,0.5,0.5,1};
float specMat2[4] = {1,1,1,1};
/* Materials */

float verts[8][3] = { {-1,-1,01}, {-1,1,1}, {1,1,1}, {1,-1,1}, {-1,-1,-1}, {-1,1,-1}, {1,1,-1}, {1,-1,-1} };
std::vector<std::vector<float> > coinvertices;
std::vector< std::vector<float> >coinuvs;
std::vector< std::vector<float> > coinnormals;

bool loadOBJ(
	const char * path,
	std::vector<std::vector<float>> & out_vertices,
	std::vector<std::vector<float>> & out_uvs,
	std::vector<std::vector<float>> & out_normals,
  bool norms
)
{
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<std::vector<float>> temp_vertices;
	std::vector<std::vector<float>> temp_uvs;
	std::vector<std::vector<float>> temp_normals;


	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file ! Are you in the right path ?\n");
		getchar();
		return false;
	}

	while( 1 ){
    int matches;
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		// else : parse lineHeader
		if ( strcmp( lineHeader, "v" ) == 0 ){
			std::vector<float> vertex = {0,0,0};
			fscanf(file, "%f %f %f\n", &vertex[0], &vertex[1], &vertex[2] );
			temp_vertices.push_back(vertex);
		}else if ( strcmp( lineHeader, "vt" ) == 0 ){
			std::vector<float> uv ={0,0};
			fscanf(file, "%f %f\n", &uv[0], &uv[1] ); //// don't know if these work yet haven't tested
			//uv[1] = -uv[1]; // Read somewhere that these might need to be inverted depending on the texture
			temp_uvs.push_back(uv);
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
			std::vector<float> normal= {0,0,0};
			fscanf(file, "%f %f %f\n", &normal[0], &normal[1], &normal[2] );
			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
      if(norms==true){
			 matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
    }else if(norms==false){
       matches = fscanf(file, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2] );
    }
      if (matches != 9 && norms==true){
				printf("File can't be read by our simple parser, Try exporting with other options matches are %d\n  ",matches);
				fclose(file);
				return false;
			}                            ///lets me know if my object files are the problem
      if (matches !=6 && norms==false){
        printf("File can't be read by our simple parser, Try exporting with other options matches are %d\n  ",matches);
        fclose(file);
        return false;
      }
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1]);
			uvIndices    .push_back(uvIndex[2]);
      if(norms==true){
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);}
		}else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}
	// For each vertex of each triangle
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){
		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];

		// Get the attributes thanks to the index
		std::vector<float> vertex = temp_vertices[ vertexIndex-1 ];
		std::vector<float> uv = temp_uvs[ uvIndex-1 ];
    if(norms==true){
    unsigned int normalIndex = normalIndices[i];
		std::vector<float> normal = temp_normals[ normalIndex-1 ];
    out_normals .push_back(normal);}
		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs     .push_back(uv);

	}
	fclose(file);
	return true;
}
bool res = loadOBJ("Pawn.obj", coinvertices, coinuvs, coinnormals,true);
void drawgl(float scalefactor) {

    int count=0;
    glBegin(GL_TRIANGLES);
    // Render each triangle
    for (int i = 0; i < int(coinvertices.size()); i++) {
        // Specify the normal for this triangle.
        // We only need six normals since each face of the cube is composed of
        // two triangles.
        glNormal3f(coinnormals[i][0],coinnormals[i][1],coinnormals[i][2]);
        /* PUT NORMALS HERE */

        // Render the three vertices of each triangle
        //for (int j = 0; j < 3; j++) {
            glTexCoord2f(coinuvs[i][0]*scalefactor,coinuvs[i][0]*scalefactor);
            glVertex3f(coinvertices[i][0]*scalefactor,coinvertices[i][1]*scalefactor,coinvertices[i][2]*scalefactor);
        //}
    }
    glEnd();
}
//piece.h
class Piece: public Point3D{
	public:
	Piece(int inSize, std::vector<Point3D> Bounds, int inColour, std::string inLocation, std::string inName);
  int size;
  std::vector<Point3D> bounds;
  int colour; //1 is white 0 is black 2 is highlighted
  std::string location;
  std::string name;
  void draw();
};

///piece.c
Piece::Piece(int inSize,std::vector<Point3D> inBounds ,int inColour,std::string inLocation,std::string inName){
  size=inSize;
  bounds=inBounds;
  colour=inColour;
  location=inLocation;
  name=inName;
};
void Piece::draw() {
		glEnable(GL_TEXTURE_2D);
		glShadeModel(GL_SMOOTH);
    glPushMatrix();
	glPolygonMode(GL_FRONT,GL_LINE);
	glPolygonMode(GL_BACK,GL_LINE);
	glBegin(GL_QUADS);
	float x,y,z;
	for(int i=0; i<int(bounds.size());i++){


		x=verts[i][0];   /// for me to see my bounding boxs
		y=verts[i][1];
		z=verts[i][2];

		x=(x*size)+mX;   /// for me to see my bounding boxs
		y=(y*size)+mY+size ;
		z=(z*size)+mZ;
		bounds[i].mX=x;
		bounds[i].mY=y;
		bounds[i].mZ=z;
		glVertex3f(x,y,z);
	glEnd();
	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_BACK,GL_FILL);
}
  glTranslatef(mX,mY,mZ);
	//if(Selected==true){
	glPolygonMode(GL_FRONT,GL_LINE);
	glPolygonMode(GL_BACK,GL_LINE);
	glPushMatrix();
	glTranslatef(0,size,0);
	glutSolidCube(2*size);
	glTranslatef(0,-size,0);
	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_BACK,GL_FILL);
	glPopMatrix();
//}
	glColor3f(1,0,0);
  drawgl(size);


  glPopMatrix();
  glEnd();

};






void setPerspectiveProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
///	displayOrthographic();
	float origin[3] = {0,0,0};
	setPerspectiveProjection();
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(camPos[0], camPos[1], camPos[2], Look[0],Look[1],Look[2], 0,1,0);

	glRotatef(rotY, 0, 1, 0);
	glRotatef(rotX, 1, 0, 0);   /// rotating the entire scene
	glColor3f(1,1,1);


	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec);

	glLightfv(GL_LIGHT1, GL_POSITION, light_pos2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, amb2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diff2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spec2);


	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambMat2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffMat2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specMat2);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 27);

	//drawgl(1.0);



	//glPopMatrix();
	glutSwapBuffers();
}
void init(void)
{

	glEnable(GL_LIGHTING);
  if(nolights == true ){
	glDisable(GL_LIGHTING);}
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glClearColor(0.5, 0.5, 0.5, 0);
	glColor3f(1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

//	glOrtho(-5, 5, -5, 5, -5, 80);
	gluPerspective(45, 1, 1, 1000);

}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Chess");	//creates the window
	glutDisplayFunc(display);	//registers "display" as the display callback function
//	glutKeyboardFunc(keyboard);
//	glutKeyboardUpFunc(KeyboardUp);
	//glutSpecialFunc(special);
  //glutTimerFunc(msecs,animatefunc,value);
  glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CW);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
	init();
	glutMainLoop();				//starts the event loop
	return(0);					//return may not be necessary on all compilers
}

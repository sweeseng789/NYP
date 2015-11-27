// Program : SHOOTING
#include <time.h>
#include <Windows.h>
#include <math.h>
#include <string>
#include <vector>
#include <ostream>
#include <sstream>
#include <iomanip>
#include <GL/glew.h>
#include <GLFw/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
using namespace std;

#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

void Render( GLFWwindow* window );

int RandomInteger( int lowerLimit, int upperLimit ) 
{ 
	return rand() % ( upperLimit - lowerLimit + 1 ) + lowerLimit; 
}

string dtos(const double value)
{ 
	ostringstream buffer;
	buffer << fixed << setprecision(2) << value; return buffer.str(); 
}
string ftos(const float argument){ ostringstream buffer; buffer << argument; return buffer.str(); }

// long integer to string
string itos( const long value )
{ 
	ostringstream buffer; 
	buffer << value; 
	return buffer.str();
}

struct MyVector
{
	float x, y;
	MyVector() :x(0), y(0){}
	MyVector(float x, float y) :x(x), y(y){}
	void SetPosition(float _x, float _y){ x = _x; y = _y; }
	float GetX(){ return x; }
	float GetY(){ return y; }
	float Magnitude(){ return sqrt(x*x + y*y); }
	MyVector Normalize(){ float length = Magnitude(); return MyVector(x / length, y / length); }
	MyVector operator + (MyVector u){ return MyVector(x + u.x, y + u.y); }
	MyVector operator - (MyVector u){ return MyVector(u.x - x, u.y - y); }
	MyVector operator += (MyVector u){ return MyVector(x + u.x, y + u.y); }
	MyVector operator ~(){ return MyVector(-x, -y); }
	MyVector operator *(float scale){ return MyVector(x*scale, y*scale); }
	float operator * (MyVector  v){ return  x*v.x + y*v.y; }
};

float GetDistance(float x1, float y1, float x2, float y2) { return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)); } // OK

// Within range
bool Detect( MyVector pos1, MyVector pos2, float radius1, float radius2)
{
	bool detect = false;
	float totalRadius = radius1 + radius2;
	float distance = GetDistance(pos1.x, pos1.y, pos2.x, pos2.y);
	if (distance <= totalRadius) detect = true;
	return detect;
}

void RenderCircle( GLfloat x, GLfloat y, GLfloat radius, GLfloat r, GLfloat g, GLfloat b )
{
	int n = 360;
	glColor3f( r, g, b );
	glBegin( GL_POINTS );
	for ( int i = 0; i <= n; i++ )
	{
		float angle = (float) ( i * ( 2.0 * 3.14159 / n ) );
		glVertex2f( x + radius * cos( angle ), y + radius * sin( angle ) );
	}
	glEnd();
}

void RenderFillCircle( GLfloat x, GLfloat y, GLfloat radius, GLfloat r, GLfloat g, GLfloat b )
{
	int n = 360;
	glColor3f ( r, g, b );
	glBegin(GL_TRIANGLE_FAN );
	glVertex2f( x, y );
	for (int i = 0; i <= n; i++)
	{
		float angle = (float) ( i * ( 2.0 * 3.14159 / n ) );
		glVertex2f( x + radius * cos( angle ), y + radius * sin( angle ) );
	}
	glEnd();
}

// SHADERS //////////////////////////////////////////////////////////////////
const char *VERTEX_SHADER = ""
"#version 410 core\n"
"in vec4 in_Position;\n"
"out vec2 texCoords;\n"
"void main(void) {\n"
"    gl_Position = vec4(in_Position.xy, 0, 1);\n"
"    texCoords = in_Position.zw;\n"
"}\n";

const char *FRAGMENT_SHADER = ""
"#version 410 core\n"
"precision highp float;\n"
"uniform sampler2D tex;\n"
"uniform vec4 color;\n"
"in vec2 texCoords;\n"
"out vec4 fragColor;\n"
"void main(void) {\n"
"    fragColor = vec4(1, 1, 1, texture(tex, texCoords).r) * color;\n"
"}\n";

GLuint texUniform, colorUniform;
GLuint texture{ 0 }, sampler{ 0 };
GLuint vbo{ 0 }, vao{ 0 };
GLuint vs{ 0 }, fs{ 0 }, program{ 0 };

static void ErrorCallBack ( int error, const char*description )
{
	fputs( description, stderr );
}

float width, height;
GLFWwindow* window;
void Render(GLFWwindow* window);

static void ResizeCallBack( GLFWwindow *window, int w, int h )
{
	glViewport( 0, 0, w, h );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 60, (float) w / (float) h, 0, 100 );
	glMatrixMode( GL_MODELVIEW );
}

// Free Type //////////////////////////////////////////////////////
FT_Library ft_lib{ nullptr };
FT_Face face{ nullptr };

void RenderText(const string str, FT_Face face, float x, float y, float _sx, float _sy)
{
	float sx = _sx / width;
	float sy = _sy / height;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	const FT_GlyphSlot glyph = face->glyph;
	for (auto c : str) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER) != 0)
			continue;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_R8,
			glyph->bitmap.width, glyph->bitmap.rows,
			0, GL_RED, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);

		const float vx = x + glyph->bitmap_left * sx;
		const float vy = y + glyph->bitmap_top * sy;
		const float w = glyph->bitmap.width * sx;
		const float h = glyph->bitmap.rows * sy;

		struct {
			float x, y, s, t;
		} data[6] = {
			{ vx, vy, 0, 0 },
			{ vx, vy - h, 0, 1 },
			{ vx + w, vy, 1, 0 },
			{ vx + w, vy, 1, 0 },
			{ vx, vy - h, 0, 1 },
			{ vx + w, vy - h, 1, 1 }
		};
		glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), data, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		x += (glyph->advance.x >> 6) * sx;
		y += (glyph->advance.y >> 6) * sy;
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

void Cleanup()
{
	FT_Done_Face(face);
	FT_Done_FreeType(ft_lib);
	glDeleteTextures(1, &texture);
	glDeleteSamplers(1, &sampler);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteProgram(program);
}

void DoExit()
{
	Cleanup();
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

int state;
int randomNumber;
const int MISS = 0;
const int HIT = 1;
const int NIL = -1;
int hit;
int miss;
float probability;
bool autoRun;
int maxFire;
int fire;
string lastRun;
vector <MyVector> shots;
float bulleyeRadius, targetRadius;
float depth, step, startDepth;

MyVector GetHitShot()
{
	bool inside = false;
	float rx, ry;
	do {
		rx = bulleyeRadius*RandomInteger(-10, 10) / 10.0f;
		ry = bulleyeRadius*RandomInteger(-10, 10) / 10.0f;
		if (GetDistance(0, 0, rx, ry) < bulleyeRadius*0.9) inside = true;
	} while (!inside);
	return MyVector(rx, ry);
}
MyVector GetMissShot()
{
	bool outside = false;
	float rx, ry;
	do {
		rx = targetRadius*RandomInteger(-10, 10) / 10.0f;
		ry = targetRadius*RandomInteger(-10, 10) / 10.0f;
		float d = GetDistance(0, 0, rx, ry);
		if (d > bulleyeRadius*1.1 && d < targetRadius*0.9) outside = true;
	} while (!outside);
	return MyVector(rx, ry);
}


void InitSimulation()
{
	state = NIL;
	hit = 0;
	miss = 0;
	probability = 50;
	autoRun = false;
	maxFire = 500;
	fire = 0;
	lastRun = "Single";
	bulleyeRadius = 0.5f;
	targetRadius = 2.5f;
	depth = startDepth = -15.f;
	step = 0.05f;
	srand((unsigned)time(NULL));
}

static void KeyCallBack( GLFWwindow *window, int key, int scancode, int action, int mods )
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
	{
		if (lastRun == "Auto")
		{
			shots.clear();
			lastRun = "Single";
			hit = miss = 0;
		}

		randomNumber = RandomInteger(1, 100);

		if (randomNumber <= probability)
		{
			shots.push_back(GetHitShot());
			state = HIT;
			hit++;
		}
		else
		{
			shots.push_back(GetMissShot());
			state = MISS;
			miss++;
		}
	}

	if (key == GLFW_KEY_F2 && action == GLFW_PRESS)
	{
		hit = miss = 0;
		state = NIL;
		fire = 0;
		autoRun = true;
		lastRun = "Auto";
		shots.clear();
	}


	if (key == GLFW_KEY_UP && action == GLFW_REPEAT)
	{
		if (probability <= 100 - step)
		{
			depth += step;
			probability += step * 20.f;
		}
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT)
	{
		if (probability >= step)
		{
			depth -= step;
			probability -= step * 20.f;
		}
	}
}

int main()
{
	// INIT ///////////////////////////////////////////////////////////////
	char *title = "Shooting";
	width = 640;
	height = 480;
	
	glfwSetErrorCallback( ErrorCallBack );
	if ( !glfwInit() )
		exit( EXIT_FAILURE );
	glfwWindowHint(GLFW_SAMPLES,4);
	GLFWwindow* window = glfwCreateWindow( (int) width, (int) height, title, NULL , NULL );
	
	if (!window)
	{
		fprintf( stderr, "Failed to create GLFW windows.\n" );
		glfwTerminate();
		exit( EXIT_FAILURE );
	}
	
	glfwMakeContextCurrent( window );
	glfwSetKeyCallback( window, KeyCallBack );
	glfwSetWindowSizeCallback( window, ResizeCallBack );
	
	GLenum error =  glewInit();
	if ( error != GLEW_OK)
	{
		fprintf(stderr,"Error : %s\n", glewGetErrorString( error ) );
		exit( EXIT_FAILURE );
	}

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 60, width / height, 0, 100 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	///////////////////////////////////////////////////////////////////////////
	
	// Initialize and load our freetype face
	if ( FT_Init_FreeType( &ft_lib ) != 0 )
	{
		fprintf( stderr, "Couldn't initialize FreeType library\n" );
		Cleanup();
		exit( EXIT_FAILURE );
	}
	
	if ( FT_New_Face(ft_lib, "arial.ttf", 0, &face ) != 0 )
	{
		fprintf( stderr, "Unable to load arial.ttf\n" );
		Cleanup();
		exit( EXIT_FAILURE );
	}
	// Initialize our texture and VBOs
	glGenBuffers( 1, &vbo );
	glGenVertexArrays( 1, &vao );
	glGenTextures( 1, &texture );
	glGenSamplers(1, &sampler);
	glSamplerParameteri( sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glSamplerParameteri( sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glSamplerParameteri( sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glSamplerParameteri( sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	// Initialize shader
	vs = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vs, 1, &VERTEX_SHADER, 0 );
	glCompileShader( vs );

	fs = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fs, 1, &FRAGMENT_SHADER, 0 );
	glCompileShader( fs );

	program = glCreateProgram();
	glAttachShader( program, vs );
	glAttachShader( program, fs );
	glLinkProgram( program );
	
	// Initialize GL state
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	// Get shader uniforms
	glUseProgram( program );
	glBindAttribLocation( program, 0, "in_Position" );
	texUniform = glGetUniformLocation( program, "tex" );
	colorUniform = glGetUniformLocation( program, "color" );

	InitSimulation();
	Render( window );
	DoExit( );
}


void RunSimulation()
{
	if (autoRun)
	{
		fire++;
		if (fire > maxFire)
		{
			autoRun = false;
			return;
		}

		randomNumber = RandomInteger(1, 100);
		if (randomNumber <= probability)
		{
			hit++;
			state = HIT;
			shots.push_back(GetHitShot());
		}
		else
		{
			miss++;
			state = MISS;
			shots.push_back(GetMissShot());
		}
	}

	glPushMatrix();
	glTranslatef(0, 0, depth);
	RenderFillCircle(0.0f, 0.0f, targetRadius, 1.0f, 1.0f, 1.0f);
	RenderFillCircle(0.0f, 0.0f, bulleyeRadius, 1.0f, 0.0f, 0.0f);
	for (unsigned int i = 0; i < shots.size(); i++)
	{
		float x = shots[i].GetX();
		float y = shots[i].GetY();
		RenderFillCircle(x, y, 0.05f, 0.0, 0.f, 0.f);
	}
	glPopMatrix();

	FT_Set_Pixel_Sizes(face, 0, 50);
	string s = " Hit : ";
	int totalCount = hit + miss;
	s = s + itos(hit) + " / " + itos(totalCount);
	if (totalCount != 0)
		s = s + " ( " + dtos(hit*100.0 / (totalCount)) + " % )";
	else
		s = s + " ( 0.00 % )";
	RenderText(s, face, -0.95f, 0.925f, 0.55f, 0.55f);
	s = "Miss : ";
	s = s + itos(miss) + " / " + itos(totalCount);
	if (totalCount != 0)
		s = s + " ( " + dtos(miss*100.0 / (totalCount)) + " % )";
	else
		s = s + " ( 0.00 % )";
	RenderText(s, face, -0.3f, 0.925f, 0.55f, 0.55f);
	s = "Probabiity : " + ftos(probability) + " % Depth : " + ftos(depth);
	RenderText(s, face, 0.32f, 0.925f, 0.55f, 0.55f);
	RenderText("F1 - Fire F2 - Auto fire ( 500 shots )", face, -0.95f, -0.825f, 0.55f, 0.55f);
	RenderText("Move : Up / Down Arrow", face, 0.25f, -0.825f, 0.55f, 0.55f);
}

void Render( GLFWwindow* window )
{
	while ( !glfwWindowShouldClose( window) )
	{
		glUseProgram( 0 );
		glClear( GL_COLOR_BUFFER_BIT );
		
		RunSimulation();
		
		// Bind stuff
		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, texture );
		glBindSampler( 0, sampler);
		glBindVertexArray( vao );
		glEnableVertexAttribArray( 0 );
		glBindBuffer( GL_ARRAY_BUFFER, vbo );
		glUseProgram( program );
		glUniform4f( colorUniform, 1, 1, 1, 1 );
		glUniform1i( texUniform, 0 );

		FT_Set_Pixel_Sizes( face, 0, 50 );

	

		glfwSwapBuffers( window );
		glfwPollEvents();
	}
}

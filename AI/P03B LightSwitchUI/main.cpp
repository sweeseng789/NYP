// Program : Basic UI Framework
#include <Windows.h>
#include <math.h>
#include <string>
#include <ostream>
#include <sstream>
#include <GL/glew.h>
#include <GLFw/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
using namespace std;


#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

void Render( GLFWwindow* window );

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

///////////////////////////////////////////////////////////////////

static void ErrorCallBack ( int error, const char*description )
{
	fputs( description, stderr );
}

float width, height;
GLFWwindow* window;
void Render(GLFWwindow* window);

static void ResizeCallBack(GLFWwindow *window, int w, int h)
{
	width = (float) w;
	height = (float) h;
	glViewport( 0, 0, w, h );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 60, width / height, 0, 100 );
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
///////////////////////////////////////////////////////////////////

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

static void KeyCallBack( GLFWwindow *window, int key, int scancode, int action, int mods )
{
	if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
		glfwSetWindowShouldClose( window, GL_TRUE );
	if (key == GLFW_KEY_F1 && action == GLFW_REPEAT)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_F2 && action == GLFW_REPEAT)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
	// INIT ///////////////////////////////////////////////////////////////
	char *title = "Light Switch UI";
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

	Render( window );
	DoExit( );
}

void Render( GLFWwindow* window )
{
	enum TRAFFICLIGHT
	{
		RED,
		AMBER,
		GREEN
	};

	TRAFFICLIGHT trafficLight = RED;

	GLfloat red = 1.f;
	GLfloat green = 0.0f;
	GLfloat blue = 0.0f;

	bool condition = false;
	int limit = 300;
	int count = 0;

	float movingCircle = -7.5f;

	while ( !glfwWindowShouldClose( window) )
	{
		glUseProgram( 0 );
		glClear( GL_COLOR_BUFFER_BIT );


		if (count <= limit)
		{
			count++;
		}
		else
		{

			switch (trafficLight)
			{
			case RED: red = 1.f;
				blue = 1.f;
				green = 0.f;
				trafficLight = AMBER;
				break;
			case GREEN: red = 1.f;
				blue = 0.f;
				green = 0.f;
				trafficLight = RED;
				break;
			case AMBER:red = 0.f;
				green = 1.f;
				blue = 0.f;
				trafficLight = GREEN;
				break;
			default:
				break;
			}

			count = 0;
		}

		//Render Circle
		glPushMatrix();
		glTranslatef(0, 0, -10);
		RenderFillCircle(0.0f, 0.0f, 0.2f, red, green, blue);
		glPopMatrix();

		//Render Circle
		glPushMatrix();
		glTranslatef(0, 0, -10);
		RenderFillCircle(0.0f, 0.5f, 0.2f, red, green, blue);
		glPopMatrix();

		//Render Circle
		glPushMatrix();
		glTranslatef(0, 0, -10);
		RenderFillCircle(0.0f, 1.f, 0.2f, red, green, blue);
		glPopMatrix();

		if (trafficLight != RED)
		{
			if (movingCircle <= 7.5f)
			{
				movingCircle += 0.2;
			}
			else
			{
				movingCircle = -7.5;
			}
		}
		//Render Circle 2
		glPushMatrix();
		glTranslatef(0, 0, -10);
		RenderFillCircle(movingCircle, -5.f, 0.2f, 0.f, 0.f, 1.f);
		glPopMatrix();

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

		RenderText(to_string(count), face, -0.1f, 0.5f, 0.55f, 0.55f);


		glfwSwapBuffers( window );
		glfwPollEvents();
	}
}
#include <stdio.h>
#include <string.h>

#include <Windows.h>

#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include <iostream>
#include <glm\vec3.hpp>

#include <iostream>

#include "Camera.h";
#include "HitInfo.h";
#include "Light.h";
#include "Material.h";
#include "Ray.h";
#include "Scene.h";
#include "Sphere.h";
#include "Plane.h";


using namespace std;

#define MAX_TRIANGLES 10
#define MAX_SPHERES 10
#define MAX_LIGHTS 10

#define WIDTH 640
#define HEIGHT 480

float ambient_light[3];
Scene* scene;
Camera* cam;

int num_triangles = 0;
int num_spheres = 0;
int num_lights = 0;

void plot_pixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);

//MODIFY THIS FUNCTION
void draw_scene()
{
	unsigned int x, y;
	//simple output
	for (x = 0; x < WIDTH; x++)
		for (y = 0; y < HEIGHT; y++)
			plot_pixel(x, y, x % 256, y % 256, (x + y) % 256);

}


void plot_pixel(int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	glBegin(GL_POINTS);
	glColor3f(((float)r) / 256.f, ((float)g) / 256.f, ((float)b) / 256.f);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void parse_check(char *expected, char *found)
{
	if (_stricmp(expected, found))
	{	
		char error[100];
		printf("Expected '%s ' found '%s '\n", expected, found);
		printf("Parse error, abnormal abortion\n");
	}

}

glm::vec3 parse_floats(FILE*file, char *check)
{
	glm::vec3 p;
	char str[100];
	fscanf_s(file, "%s", str, 100);
	printf("%s\n", str);
	parse_check(check, str);
	fscanf_s(file, "%f %f %f", &(p.x), &(p.y), &(p.z));
	printf("%s %f %f %f\n", check, p.x, p.y, p.z);
	return p;
}

void parse_rad(FILE*file, float *r)
{
	char str[100];
	fscanf_s(file, "%s", str, 100);
	parse_check("rad:", str);
	fscanf_s(file, "%f", r);
	printf("rad: %f\n", *r);
}

void parse_shi(FILE*file, float *shi)
{
	char s[100];
	fscanf_s(file, "%s", s, 100);
	parse_check("shi:", s);
	fscanf_s(file, "%f", shi);
	printf("shi: %f\n", *shi);
}

int loadScene(char *argv)
{
	FILE *file;
	fopen_s(&file, "exampleScene.txt", "r");
	if (!file) {
		printf("File could not be opened\n");
		exit(0);
	}
	int number_of_objects;
	char type[50];
	int i;
	Sphere* s = new Sphere();
	Plane* p = new Plane();
	Light* l = new Light();
	fscanf_s(file, "%i", &number_of_objects);
	fgetc(file);

	printf("number of objects: %i\n", number_of_objects);
	char str[200];

	l->setAmbiant(parse_floats(file, "amb:"));
	
	for (i = 0; i < number_of_objects; i++)
	{
		fscanf_s(file, "%s\n", type, 50);
		printf("%s\n", type);
		//if (_stricmp(type, "triangle") == 0)
		//{

		//	printf("found triangle\n");
		//	int j;

		//	for (j = 0; j < 3; j++)
		//	{
		//		parse_floats(file, "pos:", t.v[j].position);
		//		parse_floats(file, "dif:", t.v[j].color_diffuse);
		//		parse_floats(file, "spe:", t.v[j].color_specular);
		//		parse_floats(file, "nor:", t.v[j].normal);
		//		parse_shi(file, &t.v[j].shininess);
		//	}


		//	if (num_triangles == MAX_TRIANGLES)
		//	{
		//		printf("too many triangles, you should increase MAX_TRIANGLES!\n");

		//	}
		//	//triangles[num_triangles++] = t;
		//}
		//else 
		if (_stricmp(type, "sphere") == 0)
		{
			s = new Sphere();
			printf("found sphere\n");
			
			s->setPosition(parse_floats(file, "pos:"));

			float rad;
			float shineness;

			Material* mat = new Material();
			mat->setColorDiffused(parse_floats(file, "dif:"));
			mat->setColorSpeculer(parse_floats(file, "spe:"));
			parse_shi(file, &shineness);
			parse_rad(file, &rad);
			
			mat->setShineness(shineness);
			s->setRadius(rad);
			s->setMaterial(*mat);

			if (num_spheres == MAX_SPHERES)
			{
				printf("too many spheres, you should increase MAX_SPHERES!\n");

			}
			/*spheres[num_spheres++] = s;*/
			scene->shapes.push_back(s);
		}else if (_stricmp(type, "plane") == 0)
		{
			p = new Plane();
			printf("found plane\n");

			p->setPosition(parse_floats(file, "pos:"));
			p->setNormal(parse_floats(file,"normal:"));
			
			float shineness;

			Material* mat = new Material();
			mat->setColorDiffused(parse_floats(file, "dif:"));
			mat->setColorSpeculer(parse_floats(file, "spe:"));
			parse_shi(file, &shineness);

			mat->setShineness(shineness);
			
			p->setMaterial(*mat);

			/*spheres[num_spheres++] = s;*/
			scene->shapes.push_back(p);
		}
		else if (_stricmp(type, "light") == 0)
		{
			printf("found light\n");
			l->setPosition(parse_floats(file, "pos:"));
			l->setColor(parse_floats(file, "col:"));

			if (num_lights == MAX_LIGHTS)
			{
				printf("too many lights, you should increase MAX_LIGHTS!\n");

			}
			/*lights[num_lights++] = l;*/
			scene->lights.push_back(l);
		}
		else
		{
			printf("unknown type in scene description:\n%s\n", type);

		}
	}
	return 0;
}
glm::vec3 ray_trace(const Ray& ray, int depth);

void display()
{
	int depth = 0;
	Ray ray;
	pixel* buffer = cam->getBuffer();
	glm::vec3 color;

	for (int i = 0; i < HEIGHT; i++)
	{
		int row = i * WIDTH;

		for (int j = 0; j < WIDTH; j++)
		{
			/*glm::vec3 pos;
			pos.x = j - (WIDTH * 0.5f) + 0.5f;
			pos.y = i - (HEIGHT * 0.5f) + 0.5f;
			pos.z = cam->getVector().z;*/

			ray.setstartPosition(cam->getVector());
			ray.setDirection(cam->calculateDirection(i, j));

			color = ray_trace(ray, 2);

			color = glm::vec3(glm::max(0.0f, glm::min(color.r, 1.0f)),
				glm::max(0.0f, glm::min(color.g, 1.0f)),
				glm::max(0.0f, glm::min(color.b, 1.0f)));

			buffer[row + j].r = color.r * 255.0f;
			buffer[row + j].g = color.g * 255.0f;
			buffer[row + j].b = color.b * 255.0f;
		}
	}

	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, buffer);
	glutSwapBuffers();
}

glm::vec3 ray_trace(const Ray& ray,  int depth)
{
	float prevT = FLT_MAX;
	Shape* shape = nullptr;
	HitInfo hitInfo;

	for (int k = 0; k < (scene->shapes.size()); k++)
	{
		if (scene->shapes[k]->intersect(ray, prevT, hitInfo))
		{
			shape = scene->shapes[k];
		}
	}

	if (shape == nullptr)
	{
		return glm::vec3(0.0f);
	}

	glm::vec3 dir = scene->lights[0]->getPosition() - hitInfo.getVector();
	float length = dir.length();
	dir = glm::normalize(dir);

	Ray shadowRay;
	shadowRay.setDirection(dir);
	shadowRay.setstartPosition(hitInfo.getVector());

	for (int m = 0; m < (scene->shapes.size()); m++)
	{
		if (shape != scene->shapes[m])
		{
			HitInfo shadowInfo;
			if (scene->shapes[m]->intersect(shadowRay, length, shadowInfo))
			{
				return glm::vec3(0.0f);
			}
		}
	}

	glm::vec3 color = scene->lights[0]->PhongShading(ray, hitInfo, shape->getMaterial());

	if (depth > 0)
	{
		glm::vec3 reflectDir = 2.0f * glm::dot(-ray.getDirection(), hitInfo.getNormal()) * hitInfo.getNormal() + ray.getDirection();

		Ray reflectionRay;
		reflectionRay.setstartPosition(hitInfo.getVector());
		reflectionRay.setDirection(reflectDir);

		color += ray_trace(reflectionRay, --depth) * 0.5f;
	}

	return color;
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, WIDTH, 0, HEIGHT, 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void idle()
{
	//hack to make it only draw once
	static int once = 0;
	if (!once)
	{
		display();
	}
	once = 1;
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	
	scene = new Scene();
	cam = new Camera();

	loadScene(argv[1]);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	int window = glutCreateWindow("Ray Tracer");
	glutDisplayFunc(display);
	glutIdleFunc(display);

	//init();
	//draw_scene();

	glutMainLoop();

}

// glmaster.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <gl\GL.h>
#include <gl\GLU.h>
using namespace std;
void draw(SDL_Window * win);
GLuint vaoId;
GLuint vboId;
GLuint evoId;
const char *vertexShader = "#version 120\n"
"attribute vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x/2 - 0.85*aPos.y,aPos.y/2 + 0.85*aPos.x,aPos.z,1.0);\n"
"}\n\0";
const char *fragmentShaderSource = "#version 120\n"
"void main()\n"
"{\n"
"gl_FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n" 
"}\n\0";
int program;
int main(int argn,char ** argc){
	int result = 0;
	result = SDL_Init(SDL_INIT_EVERYTHING);
	if (result < 0) {
		cout << "error while init sdl\n";
		return -1;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_Window * window = SDL_CreateWindow("nice to meet you", 100, 100,600, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (window == NULL) {
		cout << "create window failed\n";
		return -1;
	}
	SDL_GLContext context = SDL_GL_CreateContext(window);
	cout << glewGetErrorString(glewInit()) << endl;
	GLfloat vertices[] = {
		0.5f,0.5f,0.5f,
		0.5f,0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f,


		-0.5f,0.5f,0.5f,
		-0.5f,0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,0.5f,
	};
	GLuint indices[] = {
		0,1,2,
		0,2,3,
		4,5,7,
		5,6,7,
		0,3,4,
		3,4,7,
		1,2,5,
		2,5,6,
		0,1,4,
		1,4,5,
		2,3,6,
		3,6,7

	};
	glGenVertexArrays(1, &vaoId);
	glGenBuffers(1, &vboId);
	glGenBuffers(1, &evoId);
	glBindVertexArray(vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, evoId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	int vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vertexShader, NULL);
	glCompileShader(vShader);
	GLchar m[1024];
	memset(m, 0, 1024);
	GLsizei length;
	glGetShaderInfoLog(vShader, 1024, &length, m);
	cout << m << endl;
	int fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fShader);
	program = glCreateProgram();
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);
	SDL_ShowWindow(window);
	SDL_Event event;
	int flag = 1;
	while (flag) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				flag = false;
			}
		}
		draw(window);
	}
	SDL_Quit();
	return 0;
}
static void draw(SDL_Window * win) {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program);
	glBindVertexArray(vaoId);
	glDrawElements(GL_TRIANGLES, 36,GL_UNSIGNED_INT , 0);
	SDL_GL_SwapWindow(win);
}


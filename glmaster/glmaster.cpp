// glmaster.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <GL\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GL.h>
#include <gl\GLU.h>
using namespace std;
void draw(SDL_Window * win);
GLuint vaoId;
GLuint vboId;
int main(int argn,char ** argc){
	int result = 0;
	result = SDL_Init(SDL_INIT_EVERYTHING);
	if (result < 0) {
		cout << "error while init sdl\n";
		return -1;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_Window * window = SDL_CreateWindow("nice to meet you", 100, 100, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (window == NULL) {
		cout << "create window failed\n";
		return -1;
	}
	SDL_GLContext context = SDL_GL_CreateContext(window);
	cout << glewGetErrorString(glewInit()) << endl;
	GLfloat vertices[] = {
		-0.5f,-0.5f,0.0f,1.0f,
		0.5f,-0.5f,0.0f,1.0f,
		0.5f,0.5f,0.0f,1.0f,
		-0.5f,0.5f,0.0f,1.0f,
	};
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
void draw(SDL_Window * win) {
	glClearColor(0.39f, 0.58f, 0.93f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	SDL_GL_SwapWindow(win);
}


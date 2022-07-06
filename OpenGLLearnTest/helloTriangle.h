#pragma once


#ifndef HELLO_TRIANGLE_H
#define HELLO_TRIANGLE_H

//����ͷ�ļ��Ⱥ�˳��
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//
#include <iostream>


class Solution {


public:


	Solution() {
		
		//glfw��ʼ��
		glfwInit();
		//����GLFW  ��һ������Ϊѡ������  
		//�ڶ�����������http://www.glfw.org/docs/latest/window.html#window_hints�ĵ�����
		//ʹ�ð汾��Ϊ3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//ʹ��ģʽΪcoreģʽ
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/*!
		 *  Constructor.����һ�����ڶ���
		 */
		GLFWwindow* window = glfwCreateWindow(400, 400, "first opengl window", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "����GLFW����ʧ��" << std::endl;
		}

		//֪ͨGLFW�����ڶ�������Ϊ��ǰ�̵߳�״̬����OpenGL��������
		glfwMakeContextCurrent(window);

		//��ʼ��GLAD  GLAD��������OPENGL����ָ�룬�ڵ���OpenGL����֮ǰ��Ҫ��ʼ��glad
		//glfwGetProcAddress���ݱ���ϵͳ������ȷ����
		if (!gladLoadGLLoader((GLADloadproc(glfwGetProcAddress))))
		{
			std::cout << "��ʼ��GLADʧ��" << std::endl;
		}

		//opengl�ӿ�
		glViewport(0.5, 0.5, 640, 480);
		//ע��ص�����
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		//����������
		
		//ʹ��glGenBuffers����һ�����㻺����󣬲����ö��󸳸�VBO
		unsigned int VBO;
		glGenBuffers(1, &VBO);
		
		//�󶨻���������� ʹ�õ��κΣ���GL_ARRAY_BUFFERĿ���ϵģ�������ö����������õ�ǰ�󶨵Ļ���(VBO)
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//������Ķ������ݸ��Ƶ��Կ������ڴ���
		//����һ�������������
		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		/*!
		 *  Constructor.//glBufferData��һ��ר���������û���������ݸ��Ƶ���ǰ�󶨻���ĺ�����
		//���ĵ�һ��������Ŀ�껺������ͣ����㻺�����ǰ�󶨵�GL_ARRAY_BUFFERĿ���ϡ�
		//�ڶ�������ָ���������ݵĴ�С(���ֽ�Ϊ��λ)����һ���򵥵�sizeof������������ݴ�С���С�
		//����������������ϣ�����͵�ʵ�����ݡ����ĸ�����ָ��������ϣ���Կ���ι������������
		 */
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//����һ��������ɫ������ ָʾGPU��ν��д���
		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		//����ɫ�����븽�ӵ���ɫ������,������
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		int success;
		char infoLog[512];
		//�������Ƿ�ɹ�
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout<<"vertexShader:" << infoLog << std::endl;
			return;
		}

		//����һ��Ƭ����ɫ������
		unsigned int fragShader;
		fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragShaderSource, NULL);
		glCompileShader(fragShader);

		//����һ���������
		unsigned int shaderProgram;
		shaderProgram = glCreateProgram();
		//�ѱ������ɫ�����󸽼ӵ��������
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragShader);
		//���ӳ������
		glLinkProgram(shaderProgram);
		//���������ɫ����������Ƿ�ɹ�
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "shaderProgram:" << infoLog << std::endl;
			return;
		}

		
		//ɾ����ɫ��������Ϊ���Ƕ���д�뵽��ɫ����������
		glDeleteShader(vertexShader);
		glDeleteShader(fragShader);

		//����OPENGL��ν�����������
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//������������
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);

		while (!glfwWindowShouldClose(window))
		{
			//����
			processInput(window);
			//��Ⱦ
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//��������
			//���ӳɹ��󣬿��Լ���������
			glUseProgram(shaderProgram);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glfwSwapBuffers(window);
			//�¼�
			glfwPollEvents();
		}

		//�ͷ��ڴ�
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(shaderProgram);
		//�ͷ���Դ
		glfwTerminate();

	}

private:
	float vertices[9] = {
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		0.0f,0.5f,0.0f
	};

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location=0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0f);\n"
		"}\0";

	const char* fragShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor=vec4(1.0f,0.5f,0.2f,1.0f);\n"
		"}\0";

private:
	//���û��ı䴰�ڵĴ�С��ʱ���ӿ�ҲӦ�ñ����������ǿ��ԶԴ���ע��һ���ص�����(Callback Function)��������ÿ�δ��ڴ�С��������ʱ�򱻵��á�
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	/*!
 *  Processes the input.�������
 *
 *      @param [in,out] window
 */
	void processInput(GLFWwindow* window) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
	}

};

#endif

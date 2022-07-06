#pragma once


#ifndef HELLO_TRIANGLE_H
#define HELLO_TRIANGLE_H

//包含头文件先后顺序
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//
#include <iostream>


class Solution {


public:


	Solution() {
		
		//glfw初始化
		glfwInit();
		//配置GLFW  第一个参数为选项名称  
		//第二个参数可在http://www.glfw.org/docs/latest/window.html#window_hints文档查找
		//使用版本号为3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//使用模式为core模式
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/*!
		 *  Constructor.创建一个窗口对象
		 */
		GLFWwindow* window = glfwCreateWindow(400, 400, "first opengl window", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "创建GLFW窗口失败" << std::endl;
		}

		//通知GLFW将窗口对象设置为当前线程的状态机（OpenGL）上下文
		glfwMakeContextCurrent(window);

		//初始化GLAD  GLAD用来管理OPENGL函数指针，在调用OpenGL函数之前需要初始化glad
		//glfwGetProcAddress根据编译系统定义正确函数
		if (!gladLoadGLLoader((GLADloadproc(glfwGetProcAddress))))
		{
			std::cout << "初始化GLAD失败" << std::endl;
		}

		//opengl视口
		glViewport(0.5, 0.5, 640, 480);
		//注册回调函数
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		//创建三角形
		
		//使用glGenBuffers生成一个顶点缓冲对象，并将该对象赋给VBO
		unsigned int VBO;
		glGenBuffers(1, &VBO);
		
		//绑定缓冲对象类型 使用的任何（在GL_ARRAY_BUFFER目标上的）缓冲调用都会用来配置当前绑定的缓冲(VBO)
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//将定义的顶点数据复制到显卡缓冲内存中
		//创建一个顶点数组对象
		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		/*!
		 *  Constructor.//glBufferData是一个专门用来把用户定义的数据复制到当前绑定缓冲的函数。
		//它的第一个参数是目标缓冲的类型：顶点缓冲对象当前绑定到GL_ARRAY_BUFFER目标上。
		//第二个参数指定传输数据的大小(以字节为单位)；用一个简单的sizeof计算出顶点数据大小就行。
		//第三个参数是我们希望发送的实际数据。第四个参数指定了我们希望显卡如何管理给定的数据
		 */
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//创建一个顶点着色器对象 指示GPU如何进行处理
		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		//将着色器代码附加到着色器对象,并编译
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		int success;
		char infoLog[512];
		//检查编译是否成功
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout<<"vertexShader:" << infoLog << std::endl;
			return;
		}

		//创建一个片段着色器对象
		unsigned int fragShader;
		fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragShaderSource, NULL);
		glCompileShader(fragShader);

		//创建一个程序对象
		unsigned int shaderProgram;
		shaderProgram = glCreateProgram();
		//把编译的着色器对象附加到程序对象
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragShader);
		//链接程序对象
		glLinkProgram(shaderProgram);
		//检查链接着色器程序对象是否成功
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "shaderProgram:" << infoLog << std::endl;
			return;
		}

		
		//删除着色器对象，因为它们都被写入到着色器程序中了
		glDeleteShader(vertexShader);
		glDeleteShader(fragShader);

		//告诉OPENGL如何解析顶点数据
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//启动顶点属性
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);

		while (!glfwWindowShouldClose(window))
		{
			//输入
			processInput(window);
			//渲染
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//画三角形
			//链接成功后，可以激活程序对象
			glUseProgram(shaderProgram);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glfwSwapBuffers(window);
			//事件
			glfwPollEvents();
		}

		//释放内存
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(shaderProgram);
		//释放资源
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
	//当用户改变窗口的大小的时候，视口也应该被调整。我们可以对窗口注册一个回调函数(Callback Function)，它会在每次窗口大小被调整的时候被调用。
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	/*!
 *  Processes the input.输入控制
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

#pragma once
#ifndef CREATE_A_WINDOW_H
#define CREATE_A_WINDOW_H

//包含头文件先后顺序
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//



class Solution {

	
public:


	Solution() {
		//
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
		if (window==NULL)
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
		glViewport(100, 100, 640, 480);
		//注册回调函数
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		//每次循环检查GLFW是否被要求退出
		while (!glfwWindowShouldClose(window))
		{
			//1.输入
			processInput(window);
			//2.渲染
			
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//清楚颜色
			glClear(GL_COLOR_BUFFER_BIT);//清楚颜色缓冲，颜色设置为glClearColor中的颜色
			//交换颜色缓冲
			glfwSwapBuffers(window);
			//3.事件
			//检查触发事件：如键盘输入，鼠标
			glfwPollEvents();
		}

		//释放glfw资源
		glfwTerminate();

	}

private:
	//当用户改变窗口的大小的时候，视口也应该被调整。我们可以对窗口注册一个回调函数(Callback Function)，它会在每次窗口大小被调整的时候被调用。
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(100, 100, width, height);
	}

	/*!
	 *  Processes the input.输入控制
	 *
	 *      @param [in,out] window 
	 */
	void processInput(GLFWwindow* window) {
		if (glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window,true);
		}
	}

};

#endif

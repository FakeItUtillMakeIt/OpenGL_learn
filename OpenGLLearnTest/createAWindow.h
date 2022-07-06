#pragma once
#ifndef CREATE_A_WINDOW_H
#define CREATE_A_WINDOW_H

//����ͷ�ļ��Ⱥ�˳��
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//



class Solution {

	
public:


	Solution() {
		//
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
		if (window==NULL)
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
		glViewport(100, 100, 640, 480);
		//ע��ص�����
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		//ÿ��ѭ�����GLFW�Ƿ�Ҫ���˳�
		while (!glfwWindowShouldClose(window))
		{
			//1.����
			processInput(window);
			//2.��Ⱦ
			
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//�����ɫ
			glClear(GL_COLOR_BUFFER_BIT);//�����ɫ���壬��ɫ����ΪglClearColor�е���ɫ
			//������ɫ����
			glfwSwapBuffers(window);
			//3.�¼�
			//��鴥���¼�����������룬���
			glfwPollEvents();
		}

		//�ͷ�glfw��Դ
		glfwTerminate();

	}

private:
	//���û��ı䴰�ڵĴ�С��ʱ���ӿ�ҲӦ�ñ����������ǿ��ԶԴ���ע��һ���ص�����(Callback Function)��������ÿ�δ��ڴ�С��������ʱ�򱻵��á�
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(100, 100, width, height);
	}

	/*!
	 *  Processes the input.�������
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

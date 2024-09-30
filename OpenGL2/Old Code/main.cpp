#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "ShaderProgramSource.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "math.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"



int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error!" << std::endl;
    }
    {
        float positions[] =
        {
            -50.0f, -50.0f, 0.0f, 0.0f, //0 top left
            50.0f, -50.0f, 1.0f, 0.0f, //1 top right
            50.0f, 50.0f, 1.0f, 1.0f, //2 bottom right
            -50.0f, 50.0f, 0.0f, 1.0f  //3 bottom left
        };

        //This is the index buffer, it means that you dont need to reuse positions
        unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(unsigned int));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        float orthoScale = 1.0f;
        float orthoData[4] = { 0, 960, 0, 540};
        for (int i = 0; i < 3; i++)
        {
            orthoData[i] *= orthoScale;
        }


        glm::mat4 proj = glm::ortho(orthoData[0], orthoData[1], orthoData[2], orthoData[3], -1.0f, 1.0f);
        glm::mat4 veiw = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        Shader shader("resources/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);


        //float angle = 45.0f * (3.14159265358979323846 / 180.0f);

        Texture texture("resources/textures/Cat.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);


        va.UnBind();
        shader.UnBind();
        vb.UnBind();
        ib.UnBind();

        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        glm::vec3 translationA(200, 200, 0);
        glm::vec3 translationB(400, 200, 0);

        float r = 0.0f;
        float inc = 0.00005f; 
        
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            ImGui_ImplGlfwGL3_NewFrame();

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
                glm::mat4 mvp = proj * veiw * model;
                shader.Bind();
                shader.SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(va, ib, shader);
            }

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
                glm::mat4 mvp = proj * veiw * model;
                shader.Bind();
                shader.SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(va, ib, shader);
            }

            if (r > 1 || r < 0.0)
                inc = -inc;
            r += inc;

            {
                ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 960.0f);
                ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 960.0f);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            }

            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
            /* Swap front and back buffers */
            glfwSwapBuffers(window);
            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
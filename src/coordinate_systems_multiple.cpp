#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>

#include <iostream>
#include <fstream>
#include <sstream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
 
// settings
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;
const float PI=3.1415926;
int numX,numY,numZ;

Camera camera(glm::vec3(0,0,0));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

/*GLubyte **** voldata = NULL;

int gettexdata(std::string fname)
{
    std::ifstream infile(fname);
    if (!infile.is_open()) 
    { 
        std::cout << "can't open" << fname << std::endl;
        //return 0;
    }
    std::string tem;
    char n;
    infile>>numX;//ignore space and enter
    numY=numX;
    numZ=numX;
    int cal=0;
    //create voldata[numX][numY][numZ][4]
    //vertices=(float **)malloc(numX*numY*numZ*sizeof(float*));
    //for (int i=0;i<numX*numY*numZ;i++)
		//vertices[i] = (float *) malloc( 3 * sizeof(float));
    voldata = (GLubyte ****) malloc( numX * sizeof(GLubyte ***) );	
	for (int i=0;i<numX;i++)
		voldata[i] = (GLubyte ***) malloc( numY * sizeof(GLubyte **));
	for (int i=0;i<numX;i++)
		for (int j=0;j<numY;j++)
			voldata[i][j] = (GLubyte **) malloc(numZ * sizeof(GLubyte *));
    for (int i=0;i<numX;i++)
		for (int j=0;j<numY;j++)
            for (int k=0;k<numZ;k++)
            {
                voldata[i][j][k] = (GLubyte *) malloc(3 * sizeof(GLubyte));//create a voldata finished
                float x=0;

                infile>>tem;
                std::istringstream is(tem);
                
                for(int m=0;is>>x&&m<3;m++)
                {
                    is>>n;
                    voldata[i][j][k][m]=x;
                    /* if(x==0.5)
                    {
                        vertices[cal][0]=i;
                        vertices[cal][1]=j;
                        vertices[cal++][2]=k;
                        //std::cout<<i<<","<<j<<","<<k<<std::endl;
                    }*/
                /*}   
            }
    infile.close();
    return cal; 
}*/
GLubyte * voldata = NULL;

/*int gettexdata(std::string fname)
{
    std::ifstream infile(fname);
    if (!infile.is_open()) 
    { 
        std::cout << "can't open" << fname << std::endl;
        //return 0;
    }
    int tem;
    char n;
    infile>>numX;//ignore space and enter
    numY=numX;
    numZ=numX;
    int cal=0;
    //create voldata[numX][numY][numZ][4]
    //vertices=(float **)malloc(numX*numY*numZ*sizeof(float*));
    //for (int i=0;i<numX*numY*numZ;i++)
		//vertices[i] = (float *) malloc( 3 * sizeof(float));
    voldata = (GLubyte *) malloc( numX *numY*numZ*sizeof(GLubyte) );	
            for (int k=0;k<numX*numY*numZ;k++)
            {
                infile>>tem;
    for z in range(0,NUM):
        for x in range(0,NUM):
            for y in range(0,NUM):
                r=rad**2-((rad-x)**2+(rad-z)**2+(rad-y)**2)            voldata[k]=tem;
                std::cout<<(GLubyte)voldata[k]<<" ";
            }
    infile.close();
    return cal; 
}*/
void gettexdata(int len,int rad)
{
    int r;
    std::ofstream ofile("./1.txt");
    voldata=(GLubyte *)malloc(len*len*len*4*sizeof(GLubyte));
    int x,y,z;
    for(z=0;z<len;z++)
        for(x=0;x<len;x++)
            for(y=0;y<len;y++)
            {
                r=rad*rad-((rad-x)*(rad-x)+(rad-z)*(rad-z)+(rad-y)*(rad-y));
                if(r>=800)
                {
                    voldata[x*len*4+y*4+z*len*len*4]=0xff;
                    voldata[x*len*4+y*4+z*len*len*4+1]=0x00;
                    voldata[x*len*4+y*4+z*len*len*4+2]=0x00;
                    voldata[x*len*4+y*4+z*len*len*4+3]=0xee;
                }
                else if(r>=0&&r<800)
                {
                    voldata[x*len*4+y*4+z*len*len*4]=0x00;
                    voldata[x*len*4+y*4+z*len*len*4+1]=0xff;
                    voldata[x*len*4+y*4+z*len*len*4+2]=0x00;
                    voldata[x*len*4+y*4+z*len*len*4+3]=0x0f;
                } 
                else
                {
                    voldata[x*len*4+y*4+z*len*len*4]=0xff;
                    voldata[x*len*4+y*4+z*len*len*4+1]=0xff;
                    voldata[x*len*4+y*4+z*len*len*4+2]=0xff;
                    voldata[x*len*4+y*4+z*len*len*4+3]=0x00;
                }
                    
            }
    /*for(z=0;z<len;z++)
    {
        for(x=0;x<len;x++)
        {
            for(y=0;y<len;y++)
            {
                if(voldata[x*len+y+z*len*len]==0x00)
                    ofile<<(int)voldata[x*len+y+z*len*len]<<"   ";
                else ofile<<(int)voldata[x*len+y+z*len*len]<<" ";
            }
        }
        ofile<<std::endl;
    }*/
}
/*void gettexdata()
{
    voldata=(GLubyte *)malloc(8*8*8*sizeof(GLubyte));
    int x,y,z;
    int r=0;
    for(z=0;z<8;z++)
        for(x=0;x<8;x++)
            for(y=0;y<8;y++)
            {
                if(r==0)
                   {
                       voldata[x*8+y+z*64]=0xff;
                       r=1;
                   } 
                else
                 {
                     r=0;
                     voldata[x*8+y+z*8*8]=0x00;
                 }   
            }
    for(z=0;z<8;z++)
        for(x=0;x<8;x++)
        {
            for(y=0;y<8;y++)
                std::cout<<(int)voldata[x*8+y+z*8*8]<<" ";
            std::cout<<std::endl;
        }   
}*/

 GLfloat * createImagePlane(int x,int y,float z,int &num,GLfloat * vertex)
{
    int scale=1000;
    int scaledo=scale*scale;
    vertex=new GLfloat[x*y*scaledo*3*4];//x*y*100个点，每个点3个通道
    int pixel;
    int i,j;
    num=x*y*scaledo*4;
    int num1=x*y*scaledo;
    for(i=0;i<y*scale;i++)
    {
        for(j=0;j<x*scale;j++)
        {
            pixel=(i*x*scale+j)*3;

            vertex[pixel]=(GLfloat)i/scale;
            vertex[pixel+1]=(GLfloat)j/scale;
            vertex[pixel+2]=z;

            vertex[pixel+num1*3]=(GLfloat)i/scale-1;
            vertex[pixel+num1*3+1]=(GLfloat)j/scale;
            vertex[pixel+num1*3+2]=z;

            vertex[pixel+num1*6]=(GLfloat)i/scale;
            vertex[pixel+num1*6+1]=(GLfloat)j/scale-1;
            vertex[pixel+num1*6+2]=z;

            vertex[pixel+num1*9]=(GLfloat)i/scale-1;
            vertex[pixel+num1*9+1]=(GLfloat)j/scale-1;
            vertex[pixel+num1*9+2]=z;
        }
    }
    return vertex;
}
int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------verindex.getvertices()-----------------------------------
    int len=128,rad=40;//the len must be 2,4,8,16....
    gettexdata(len,rad);//bianchang and rad
    int verticeNum;
    GLfloat * vertices=NULL;
    vertices=createImagePlane(1,1,0.,verticeNum,vertices);//0.628,0.005
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("6.3.coordinate_systems.vs", "6.3.coordinate_systems.fs");

    if(vertices)
    {
        glBufferData(GL_ARRAY_BUFFER, verticeNum * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    }
        
    else 
    {
        std::cout<<"failed to load vertices and indices"<<std::endl;
        return 0;
    }
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);


    // load and create a texture 
    // -------------------------
    unsigned int texture1;
    // texture 
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_3D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);//GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    glTexParameterfv(GL_TEXTURE_3D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (voldata)
    {
        glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, len,len,len, 0, GL_RGBA, GL_UNSIGNED_BYTE, voldata);
       // glGenerateMipmap(GL_TEXTURE_3D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    //stbi_image_free(data);
    free(voldata);
    free(vertices);
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("texture1", 0);//tell shader texture1 is unit 0
    ourShader.setVec3("volExtentMin", glm::vec3(0,0,0));
    ourShader.setVec3("volExtentMax", glm::vec3(1,1,1));
    ourShader.setFloat("stepsize",0.01);
    // camera
    glm::vec3 cameraPos   = glm::vec3(0.0f, 50.0f,  -30.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, -1.0f, 0.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 0.0f,  -1.0f);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

         // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);//activate 0 texture unit
        glBindTexture(GL_TEXTURE_3D, texture1);//bind the sampler texture1 in glhl file to 0 texture unit

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // activate shader
        ourShader.use();

        // create transformations
        //glm::mat4 view          = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 projection    = glm::mat4(1.0f);
        //projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);//tou shi projection
        //view = glm::lookAt(cameraPos,cameraPos+cameraFront,cameraUp);
        ////view = camera.GetViewMatrix();
        // pass transformation matrices to the shader
        //ourShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
       // ourShader.setMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f);//initialize a matrix
        model = glm::translate(model, glm::vec3( 0,  0,  0.f));
        //float zoomX = 2./numX;
        //float zoomY = 2./numY;
        //float zoomZ = 2./numZ;
        //model = glm::scale(model, glm::vec3(zoomX, zoomY, zoomZ));
        ourShader.setMat4("model", model);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//GL_LINE
        glDrawArrays(GL_POINTS, 0, verticeNum);//glDrawArray
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -----------------------------------LINE--------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
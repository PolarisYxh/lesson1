#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>


#include <iostream>
#include <fstream>
#include <sstream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const float PI=3.1415926;
int numX,numY,numZ;



GLubyte **** voldata = NULL;

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
                voldata[i][j][k] = (GLubyte *) malloc(4 * sizeof(GLubyte));//create a voldata finished
                float x=0;

                infile>>tem;
                std::istringstream is(tem);
                
                for(int m=0;is>>x&&m<4;m++)
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
                }   
            }
    infile.close();
    return cal; 
}
class spheredata
{
private:
    GLfloat *vertices;//顶点数组
    unsigned int *indices; //索引数组
    float radius;
    int longPart,latPart;
public:
    int verticeNum;//顶点数目
    int indexNum;//索引数目
    //创建球面顶点
    spheredata(float r,int longitude,int lat):radius(r),longPart(longitude),latPart(lat)
    {
        CreateVertexBuffer();
        CreateIndexBuffer();
    }
    void CreateVertexBuffer()
    {
        ////test
        //vertices = new GLfloat[3* 3];
        //vertices[0] = -1.0f;
        //vertices[1] = -1.0f;
        //vertices[2] = -1.0f;
        //vertices[3] = -1.0f;
        //vertices[4] = -1.0f;
        //vertices[5] = 1.0f;
        //vertices[6] = -1.0f;
        //vertices[7] = 1.0f;
        //vertices[8] = 1.0f; 
        verticeNum = longPart * latPart + 2 * longPart;
        vertices= new GLfloat[verticeNum * 3];
        for (int i = 0; i < longPart; i++)
        {
            vertices[i * 3] = 0;
            vertices[i * 3 + 1] = 0;
            vertices[i * 3 + 2] = radius;
        }    
        float degreesToRadians = 3.141593f/ 180.0f; //弧度转换
        float deltaLong = 360.0f / (longPart - 1);//经度每份对应度数
        float deltaLat = 180.0f / (latPart + 2);//纬度每份对应度数 
        for (int tempLat = 0; tempLat < latPart; tempLat++)
        {
            float tempAngle1 = ((tempLat + 1)* deltaLat) * degreesToRadians;
            for (int tempLong = 0; tempLong < longPart; tempLong++)
            {
                float tempAngle2 = (tempLong*deltaLong) * degreesToRadians;
                int tempIndex = tempLong + tempLat* longPart + longPart;
                vertices[tempIndex * 3] = sin(tempAngle1) * cos(tempAngle2)* radius;
                vertices[tempIndex * 3 + 1] = sin(tempAngle1) * sin(tempAngle2)* radius;
                vertices[tempIndex * 3 + 2] = cos(tempAngle1)* radius;
            }
        }
        for (int i = 0; i < longPart; i++)
        {
            vertices[(verticeNum - 1 - i) * 3] = 0;
            vertices[(verticeNum - 1 - i) * 3 + 1] = 0;
            vertices[(verticeNum - 1 - i) * 3 + 2] = -1.0f*radius;
        }
    }

    void CreateIndexBuffer()
    {
        ////test
        //indices = new unsigned int[3];
        //indices[0] = 2;
        //indices[1] = 1;
        //indices[2] = 0;
    
        indices = new unsigned int[(longPart - 1)* latPart * 3 * 2];
        int k = 0;
        for (int i = 0; i < longPart - 1; i++)
        {
            indices[k++] = i;
            indices[k++] = i + longPart;
            indices[k++] = i + longPart + 1;
        }
        for (int tempLat = 0; tempLat < latPart-1; tempLat++)
        {
            for (int tempLong = 0; tempLong < longPart - 1; tempLong++)
            {
                indices[k++] = tempLong + tempLat * longPart + longPart;
                indices[k++] = tempLong + tempLat * longPart + 2 * longPart;
                indices[k++] = tempLong + tempLat * longPart + longPart + 1;
    
                indices[k++] = tempLong + tempLat * longPart + 2 * longPart;
                indices[k++] = tempLong + tempLat * longPart + 1 + 2 * longPart;
                indices[k++] = tempLong + tempLat * longPart + 1 + longPart;
            }
        }
        for (int i = 0; i < longPart - 1; i++)
        {
            indices[k++] = verticeNum - 1 - i;
            indices[k++] = verticeNum - 1 - i - longPart;
            indices[k++] = verticeNum - 2 - i - longPart;
        } 
        indexNum = (longPart - 1)* latPart * 3 * 2 ;

        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, (longPart - 1)* latPart * 3 * 2 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    }
    GLfloat * getvertices()
    {
        return vertices;
    }
    unsigned int * getindices()
    {
        return indices;
    }
};

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

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("6.3.coordinate_systems.vs", "6.3.coordinate_systems.fs");

    

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    spheredata verindex(10,20,20);
    int numV=gettexdata("./voxel.txt");
    int verticeNum=verindex.verticeNum;
    int indexNum=verindex.indexNum;
    GLfloat * vertices=verindex.getvertices();
    unsigned int * index=verindex.getindices();
    unsigned int VBO, VAO,EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    if(vertices&&index)
    {
        glBufferData(GL_ARRAY_BUFFER, verticeNum * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,indexNum* sizeof(unsigned int),index,GL_STATIC_DRAW);
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
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    //int width, height,  nrChannels;
   
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    //unsigned char *data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);
    //3d data field


    if (voldata)
    {
        glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, numX, numY, numZ, 0, GL_RGBA, GL_UNSIGNED_BYTE, voldata);
        glGenerateMipmap(GL_TEXTURE_3D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    //stbi_image_free(data);
    free(voldata );
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("texture1", 0);//tell shader texture1 is unit 0


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

        // activate shader
        ourShader.use();

        // create transformations
        glm::mat4 view          = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 projection    = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);//tou shi projection
        view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -0.0f));
        // pass transformation matrices to the shader
        ourShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        ourShader.setMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f);//initialize a matrix
        model = glm::translate(model, glm::vec3( 0,  0,  -30.f));
        //float zoomX = 2./numX;
        //float zoomY = 2./numY;
        //float zoomZ = 2./numZ;
        //model = glm::scale(model, glm::vec3(zoomX, zoomY, zoomZ));
        ourShader.setMat4("model", model);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, indexNum,GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
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
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

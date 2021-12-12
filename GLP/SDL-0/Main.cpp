//Gaëtan work // 
/*

#define GLEW_STATIC
#include <SDL.h>
#include <glew.h>
#include <iostream>


using std::cout;
using std::endl;

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;



int main(int argc = 0, char** argv = nullptr) {
    // Handle args
    if (argc > 0) {
        for (int i = 0; i < argc; ++i) {
            cout << argv[i] << endl;
        }
    }

    SDL_Window* window = nullptr;
    SDL_GLContext context;
    int flags = SDL_WINDOW_OPENGL;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "SDL failed to initialize" << endl;
        return 1;
    }

    // Initialize window and openGL
    window = SDL_CreateWindow("First triangle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, flags);
    context = SDL_GL_CreateContext(window);
    glewExperimental = GL_TRUE;
    glewInit();

    // Get info
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    cout << "Renderer: " << renderer << endl;
    cout << "OpenGL version supported: " << version << endl;

    // Tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

    // Set viewport and clear color
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

    // Load ( coordonnées de la forme) 
    GLfloat points[] = { 
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f 
    };

    GLuint vbo = 0; // genère un buffer 
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    const char* vertex_shader =
        "#version 460\n"
        "in vec3 vp;"
        "void main () {"
        "  gl_Position = vec4 (vp, 1.0);"
        "}";

    const char* fragment_shader =
        "#version 460\n" // version open Gl 
        "out vec4 color;" 
        "void main () {"
        "  color = vec4 (0.8, 0.5, 0.0, 1.0);"
        "}";


    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    GLuint shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);

    // Game loop
    bool isRunning = true;
    while (isRunning) {
        // Inputs
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;

            default:
                break;
            }
        }
        // Update


        // Draw
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

        // use depth management 
        glEnable(GL_DEPTH_TEST);
        // 0 is our origin, the higher is Z 
        glDepthFunc(GL_LESS);

        // Draw here
        glUseProgram(shader_programme);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);  // Swapbuffer

    }


    // Quit
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);


    return 0;
}

*/

// Marie Work // 

//Include 
#define GLEW_STATIC

#include <SDL.h>
#include <glew.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


string LoadShader(string fileName) {
    ifstream myFile;
    myFile.open(fileName);
    if (myFile.fail()) {
        cerr << "Error - failed to open " << fileName << endl;
    }
    string fileText = "";
    string line = "";
    while (getline(myFile, line)) {
        fileText += line + '\n';
    }

    myFile.close();
    return fileText;
}


int main(int argc, char* argv[]) 
{
    if (SDL_Init(SDL_INIT_EVERYTHING)==0)
    {
        cout << "initialized successfully \n";
    }

    // Setting up the window 
    // create a simple window 
    int width = 640;
    int height = 480;
    unsigned int center = SDL_WINDOWPOS_CENTERED;
    SDL_Window* Window = SDL_CreateWindow("My window", center, center, width, height, SDL_WINDOW_OPENGL);
    //  SDL_WINDOW_OPENGL = u32 Flag // 

    // create a open gl compatible context to let glew drew on it 
    SDL_GLContext Context = SDL_GL_CreateContext(Window);

    /////////SETTING UP OPENGL WITH GLEW///
    //Initialize glew
    glewExperimental = GL_TRUE;
    if (glewInit() == GLEW_OK) 
    {
        cout << "Glew initialized successfully\n";
    }

    //Set the viewing frame through which we will see the objects
    glViewport(0, 0, width, height);

    //Put the color you want here for the background
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

    //Describe the shape by its vertices

    float vertices[] = {
        // positions             // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f

    };

    //Create an ID to be given at object generation
    unsigned int vbo;

    //Pass how many buffers should be created and the reference of the ID to get the value set
    glGenBuffers(1, &vbo);

    //----------SHADERS----------

    //Setting the shader code as text
    string vs = LoadShader("vertex.shader");
    const char* vertexShaderSource = vs.c_str();

    string fs = LoadShader("fragment.shader");
    const char* fragmentShaderSource = fs.c_str();

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);


    //now that we have a vertex shader, let’s put the code text inside
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    //aaaaand… Compile !
    glCompileShader(vertexShader);

    //Do the same with the fragment shader !
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Shader Program 
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    //now attach shaders to use to the program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    //and link it 
    glLinkProgram(shaderProgram);

    //now that the program is complete, we can use it 
    glUseProgram(shaderProgram);

    //----------VAO----------  
    //Create one ID to be given at object generation
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //Binds the buffer linked to this ID to the vertex array buffer to be rendered. Put 0 instead of vbo to reset the value.
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //Finally send the vertices array in the array buffer 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attributes // 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attributes // 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    // dessiner des choses ni trop loin ni trop proche (Comme des layers) 
    //Use depth management
    glEnable(GL_DEPTH_TEST);

    //0 is our origin, the higher the z, the farther the object
    glDepthFunc(GL_LESS);


    //----------Main Loop---------- 
    bool isRunning = true;
    while (isRunning) {
        // Inputs
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            default:
                break;
            }
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

        //----------USE---------- 
        //Shader to use next
        glUseProgram(shaderProgram);

        //VAO to use next
        glBindVertexArray(vao);

        // Get the time in seconds 
        float timeValue = (float)SDL_GetTicks() / 1000;
        float redColor = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation, redColor, 1.0f, 0.0f, 1.0f);

        //OMG WE FINALLY DRAW ! We use the GL_TRIANGLES primitive type
        //We draw from vertex 0 and we will be drawing 3 vertices
        glDrawArrays(GL_TRIANGLES, 0, 6);

        SDL_GL_SwapWindow(Window); // Swapbuffer

         

    }
    // Quit
    SDL_DestroyWindow(Window);
    SDL_GL_DeleteContext(Context);

    return 0;
}
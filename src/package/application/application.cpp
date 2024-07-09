#include "application.h"
#include "../utils/utils.h"

void Application::initGlfw() {
    if (!glfwInit()) throwMessage("GLFW did not initialise");
    glfwSetErrorCallback(customGlfwError_Callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    this->window = glfwCreateWindow(displayDim.x, displayDim.y, "GLFW OpenGL Window", nullptr, nullptr);
    if (!window) { 
        glfwTerminate(); 
        throw std::runtime_error("GLFW window failed to create!");
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, framebufferSize_Callback);
}

void Application::initOpenGL() {
    if (glewInit() != GLEW_OK) throwMessage("GLEW did not initialise!");
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
}

void Application::initImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;  
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui_ImplGlfw_InitForOpenGL(window, true);
}

void Application::onNextFrame() {
    glfwPollEvents();

    int display_w, display_h;
    glfwGetFramebufferSize(this->window, &display_w, &display_h);
    displayDim = { display_w, display_h };
    glViewport(0, 0, displayDim.x, displayDim.y);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    timer.nextFrame();
    camera->processInput(this->window, timer.dt());
    camera->setDisplayDim(this->displayDim);
    camera->debugInfo();
}

void Application::onUpdate() {
    glm::mat4 proj, view, model = glm::mat4(1.0f);
    proj = camera->getProjMat(0.1f, 100.0f);
    view = camera->getViewMat();
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
    model = glm::rotate(model, 23.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

    ourShader->bind();
    ourShader->setMat4("proj", proj);
    ourShader->setMat4("view", view);
    ourShader->setMat4("model", model);
    ourModel->draw(*ourShader);
}

void Application::onRender() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(this->window);
}

Application::Application() 
    : displayDim(glm::vec2(800, 600)) 
{}

Application::~Application() 
{}

// real shit starts here
void Application::init() {
    this->initGlfw();
    this->initOpenGL();
    this->initImGui();
}

void Application::setUp() {
    this->camera = new Camera(this->window, CAM_POS, CAM_FRONT, CAM_UP, CAM_YAW, CAM_PITCH);
    this->ourShader = new Shader("res/shaders/model_loading.frag.vert.glsl");
    this->ourModel = new Model("res/models/backpack/backpack.obj");
}

void Application::mainLoop() {
    while (!glfwWindowShouldClose(this->window)) {
        this->onNextFrame();
        this->onUpdate();
        this->onRender();
    }
}

void Application::clean() {
    delete this->camera;
    delete this->ourShader;
    delete this->ourModel;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(this->window);
    glfwTerminate();
}

void Application::run() {
    this->init();
    this->setUp();
    this->mainLoop();
    this->clean();
}

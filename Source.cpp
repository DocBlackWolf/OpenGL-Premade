#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <GL/freeglut.h>
#include <iostream>

GLuint texture;

void loadTexture() {
    int width, height, nrChannels;
    unsigned char* data = stbi_load("resources/texture.png", &width, &height, &nrChannels, 0);

    if (data) {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Load the texture into OpenGL
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

        // Set the texture wrapping/filtering options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Free the image data
        stbi_image_free(data);
    }
    else {
        std::cerr << "Failed to load texture" << std::endl;
    }
}

void render()
{
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Enable 2D texturing
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set the color of the triangle (white to allow the texture to show)
    glColor3f(1.0f, 1.0f, 1.0f);

    // Begin drawing the triangle with texture coordinates
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.5f, -0.5f); // Bottom left corner
    glTexCoord2f(1.0f, 0.0f); glVertex2f(0.5f, -0.5f);  // Bottom right corner
    glTexCoord2f(0.5f, 1.0f); glVertex2f(0.0f, 0.5f);   // Top corner
    glEnd();

    // Disable 2D texturing
    glDisable(GL_TEXTURE_2D);

    // Swap buffers (double buffering)
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    // Set the viewport to cover the new window size
    glViewport(0, 0, width, height);

    // Set the projection matrix to an orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width <= height)
        gluOrtho2D(-1.0, 1.0, -1.0 * height / width, 1.0 * height / width);
    else
        gluOrtho2D(-1.0 * width / height, 1.0 * width / height, -1.0, 1.0);
}

void handleKeypress(unsigned char key, int x, int y)
{
    // Exit the program when the ESC key is pressed
    if (key == 27) {
        glutLeaveMainLoop();
    }
}

int main(int argc, char** argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);

    // Set display mode (double buffering and RGB color)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Set window size
    glutInitWindowSize(800, 600);

    // Create the window with the title "FreeGLUT Test"
    glutCreateWindow("FreeGLUT Test");

    // Load the texture
    loadTexture();

    // Set the display callback for rendering
    glutDisplayFunc(render);

    // Set the reshape callback for window resizing
    glutReshapeFunc(reshape);

    // Set the keyboard callback for handling key presses
    glutKeyboardFunc(handleKeypress);

    // Enter the GLUT main loop
    glutMainLoop();

    return 0;
}

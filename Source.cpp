#include <GL/freeglut.h>

// Function to handle rendering
void render()
{
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the color of the triangle (red)
    glColor3f(1.0f, 0.0f, 0.0f);

    // Begin drawing the triangle
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f); // Bottom left corner
    glVertex2f(0.5f, -0.5f);  // Bottom right corner
    glVertex2f(0.0f, 0.5f);   // Top corner
    glEnd();

    // Swap buffers (double buffering)
    glutSwapBuffers();
}

// Function to handle window resizing
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

// Function to handle keyboard input
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

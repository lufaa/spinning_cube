#include "raylib.h"
#include "math.h"
#include <iostream>
#define HEIGHT 900
#define WIDTH 1600
#define PIXEL_SIZE 5
#define FPS 240
struct Cube
{
public:
    Cube()
    {

    }
};
void drawLines(const Vector2* points,const int edges[][2],int n,Color color)
{
    float thickness = 20;
    for(int i = 0;i<n;i++)
    {
        Vector2 start = points[edges[i][0]];
        Vector2 stop = points[edges[i][1]];
        DrawLineEx(start,stop,thickness,color);
    }
}

Vector2 ProjectPoint(const Vector3& point,float d = 0)
{
    Vector2 pos;
    pos.x = point.x/point.z;
    pos.y = point.y/point.z;
    return pos;
}
Vector2 PointToScreen(Vector2 point)
{
    Vector2 pos;
    pos.x = (point.x+1)/2*WIDTH-PIXEL_SIZE/2;
    pos.y = (1-(point.y+1)/2)*HEIGHT+PIXEL_SIZE/2;
    return pos;
}
void RotatePointX(Vector3& point,float angle)
{
    float radians = angle/180*PI;
    float cosa = cosf(radians);
    float sina = sinf(radians);
    float y = point.y*cosa-point.z*sina;
    float z = point.y*sina+point.z*cosa;
    point.y = y;
    point.z = z;
}
void RotatePointY(Vector3& point,float angle)
{
    float radians = angle/180*PI;
    float cosa = cosf(radians);
    float sina = sinf(radians);
    float x = point.x*cosa+point.z*sina;
    float z = -point.x*sina+point.z*cosa;
    point.x = x;
    point.z = z;
}
void RotatePointZ(Vector3& point,float angle)
{
    float radians = angle/180*PI;
    float cosa = cosf(radians);
    float sina = sinf(radians);
    float x = point.x*cosa-point.y*sina;
    float y = point.x*sina+point.y*cosa;
    point.x = x;
    point.y = y;
}
void DrawPoint(const Vector2& point)
{
    Vector2 size{PIXEL_SIZE,PIXEL_SIZE};
    DrawRectangleV(point,size,RED);
}
void TranslateZ(Vector3& point,float amount)
{
    point.z += amount;
    //std::cout << point.z << "\n";
}
Color GenerateRandomColor()
{
    unsigned char r = rand()%256;
    unsigned char g = rand()%256;
    unsigned char b = rand()%256;
    return Color{r,g,b,255};
}
int main()
{
    InitWindow(WIDTH, HEIGHT, "rotating cube");
    SetTargetFPS(FPS);
    Vector2 points[4] = {{600,250},{600,650},{1000,650},{1000,250}};
    Vector3 cube[8] = {
    {-0.5f, -0.5f, -0.5f}, // 0
    { 0.5f, -0.5f, -0.5f}, // 1
    { 0.5f,  0.5f, -0.5f}, // 2
    {-0.5f,  0.5f, -0.5f}, // 3
    {-0.5f, -0.5f,  0.5f}, // 4
    { 0.5f, -0.5f,  0.5f}, // 5
    { 0.5f,  0.5f,  0.5f}, // 6
    {-0.5f,  0.5f,  0.5f}  // 7
    };
    int edges[12][2] = {
    // dolna ściana
    {0, 1}, {1, 2}, {2, 3}, {3, 0},

    // górna ściana
    {4, 5}, {5, 6}, {6, 7}, {7, 4},

    // łączące dolną i górną ścianę (pionowe)
    {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };
    srand(time(NULL));
    Vector2 screenPoints[8]; 
    float angle = 0;
    float angle2 = 0;
    float angle3 = 0;
    float time = 0;
    float dt = 1.0f/FPS;
    int counter = 0;
    int random = rand()%361;
    int random2 = rand()%361;
    int random3 = rand()%361;
    Color cubeColor = GenerateRandomColor();
    Color backgroundColor = GenerateRandomColor();
    while (!WindowShouldClose())
    {

       
        time+=dt;
        BeginDrawing();
        
        
        counter++;
        if(counter/(FPS*3) == 1)
        {
            counter = 0;
            random = rand()%361;
            random2 = rand()%361;
            random3 = rand()%361;
            cubeColor = GenerateRandomColor();
            backgroundColor = GenerateRandomColor();
        }
        angle += dt*random;
        angle2 += dt*random2;
        angle3 += dt*random3;
        ClearBackground(backgroundColor);
        for(int i = 0;i<8;i++)
        {         
            float speed = 2;
            Vector3 p = cube[i];     // kopia modelu

            RotatePointY(p, angle);  // obrót wokół własnej osi
            RotatePointX(p,angle2);
            RotatePointZ(p,angle3);
            TranslateZ(p, 1.0f);       // przesunięcie w świat
            screenPoints[i] = PointToScreen(ProjectPoint(p));
            //DrawPoint(screenPoints[i]);
        }
        drawLines(screenPoints,edges,12,cubeColor);
        DrawFPS(10,10);
        EndDrawing();
        
    }
    
    
    CloseWindow();

    return 0;
}

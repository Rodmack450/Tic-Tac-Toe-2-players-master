//
//  main.cpp
//  GUI
//
//  Created by Rodolphe Nemr on 10/4/18.
//  Copyright © 2018 Rodolphe Nemr. All rights reserved.
//

#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

using namespace std;

int result;
bool over;
int board[3][3];
int turn;

//Drawing The Typing on the screen.
void DrawS(void *font,const char s[],float x,float y)
{
    unsigned int i;
    glRasterPos2f(x,y);
    for(i=0;i<strlen(s);i++)
    {
        glutBitmapCharacter(font,s[i]);
    }
}

//Getting Stuff Ready.
void Ready()
{
    turn=1;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
            board[i][j]=0;
    }
}

//Keyboard Options.
void Keyboard(unsigned char key,int x,int y)
{
    switch(key)
    {
            
        case '1':
            Ready();
            break;
        case '2':
            exit(0);
            break;
            
        case 'y':
            if(over==true)
            {
                over=false;
                Ready();
            }
            break;
            
        case 'n':
            if(over==true)
            {
                exit(1);
            }
            break;
            
        case 'f':
            glutFullScreen();
            break;
            
        default:
            exit(0);
    }
}

//Mouse Options.
void Mouse(int button,int state,int x,int y)
{
    if(over==false && button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if(turn==1)
        {
            if(board[(y-50)/100][x/100]==0)
            {
                board[(y-50)/100][x/100]=1;
                turn=2;
            }
        }
        else if(turn==2)
        {
            if(board[(y-50)/100][x/100]==0)
            {
                board[(y-50)/100][x/100]=2;
                turn=1;
            }
        }
    }
}


//OpenGL Drawing.
void Draw()
{
    glBegin(GL_LINES);
    glColor3f(1,1,0);
    
    glVertex2f(100,50);
    glVertex2f(100,340);
    glVertex2f(200,340);
    glVertex2f(200,50);
    
    glVertex2f(0,150);
    glVertex2f(300,150);
    glVertex2f(0,250);
    glVertex2f(300,250);
    
    glEnd();
}

//Drawing the Shape of the circle.
void DrawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
}

//Drawing More Shapes.
void DrawXO()
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board[i][j]==1)
            {
                glBegin(GL_LINES);
                glVertex2f(50 + j * 100 - 25, 100 + i * 100 - 25);
                glVertex2f(50 + j * 100 + 25, 100 + i * 100 + 25);
                glVertex2f(50 + j * 100 - 25, 100 + i * 100 + 25);
                glVertex2f(50 + j * 100 + 25, 100 + i * 100 - 25);
                glEnd();
            }
            else if(board[i][j]==2)
            {
                
                DrawCircle(50 + j*100 , 100 + i*100 , 25 , 15);
            }
        }
    }
}

//Bool Function To Check If The Winning Condition is true or false.
bool CheckWinner()
{
    int i, j;
    
    for(i=0;i<3;i++)
    {
        for(j=1;j<3;j++)
        {
            if(board[i][0]!=0 && board[i][0]==board[i][j])
            {
                if(j==2)
                {
                    return 1;
                }
            }
            else
                break;
        }
    }
    
    for(i=0;i<3;i++)
    {
        for(j=1;j<3;j++)
        {
            if(board[0][i]!=0 && board[0][i]==board[j][i])
            {
                if(j==2)
                    return true;
            }
            else
                break;
        }
    }
    
    if((board[0][0]!=0 && board[0][0]==board[1][1] && board[0][0]==board[2][2])
       || (board[2][0]!=0 && board[2][0]==board[1][1] && board[2][0]==board[0][2]))
        return true;
    return 0;
}

//Bool Function To Check If It's A Draw.
bool CheckIfDraw()
{
    int i, j;
    bool draw;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(board[i][j]==0)
                return false;
        }
    }
    return true;
}


void menu(int num){
    
    if(num == 1){
        Ready();
    }else{
        exit(0);
    }
   
}

//User Interface Options.
void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);
    
    if ( turn == 0){
        DrawS(GLUT_BITMAP_HELVETICA_18, "2)To Exit", 10, 50);
         DrawS(GLUT_BITMAP_HELVETICA_18, "1)To Play", 9, 30);
        
    }
    if(turn == 1){
    DrawS(GLUT_BITMAP_HELVETICA_18, "Player1's turn", 100, 30);
    DrawS(GLUT_BITMAP_HELVETICA_18, "1)To Play", 9,30);
    DrawS(GLUT_BITMAP_HELVETICA_18, "2)To Exit", 10, 50);
    }  else{
        DrawS(GLUT_BITMAP_HELVETICA_18, "Player2's turn", 100, 30);
        DrawS(GLUT_BITMAP_HELVETICA_18, "1)To Play", 9, 30);
        DrawS(GLUT_BITMAP_HELVETICA_18, "2)To Exit", 10, 50);
    }
    Draw();
    DrawXO();
    
    if(CheckWinner() == true)
    {
        if(turn == 1)
        {
            over = true;
            result = 2;
        }
        else
        {
            over = true;
            result = 1;
        }
    }
    else if(CheckIfDraw() == true)
    {
        over = true;
        result = 0;
    }
    if(over == true)
    {
        DrawS(GLUT_BITMAP_HELVETICA_18, "Game Over.", 100, 160);
        if(result == 0)
            DrawS(GLUT_BITMAP_HELVETICA_18, "A draw.", 110, 185);
        if(result == 1)
            DrawS(GLUT_BITMAP_HELVETICA_18, "Player 1 wins.", 95, 185);
        if(result == 2)
        DrawS(GLUT_BITMAP_HELVETICA_18, "Player 2 wins.", 95, 185);
        DrawS(GLUT_BITMAP_HELVETICA_18, "Another One? (Y/N).", 40, 210);
    }
    glutSwapBuffers();
}

//Menu Brain.
void mainMenuHandler(int choice) {
   
    switch(choice) {
        case 1:
            Ready();
            break;
            
        case 2:
            exit(1);
            break;
            
        case 3:
           
            glutFullScreen();
            break;
            
        case 4:
            DrawS(GLUT_BITMAP_HELVETICA_18, "Created By Rodmack.", 95, 185);
            break;
    }
}

//This function is called on windows resize.
void Reshape(int x, int y)
{
    glViewport(0, 0, x, y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, x, y, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
}



//Main Function + Menu.
int main(int argc, char **argv)
{
    Ready();
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowPosition(550,200);
    glutInitWindowSize(300,350);
    glutCreateWindow("Rodmack Game");
    glutReshapeFunc(Reshape);
    glutDisplayFunc(Display);
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(Mouse);
    glutIdleFunc(Display);
    
    glutCreateMenu(mainMenuHandler);
    glutAddMenuEntry("Restart", 1);
    glutAddMenuEntry("Exit", 2);
    glutAddMenuEntry("Full Screen", 3);
    glutAddMenuEntry("'Created By Rodolphe Nemr'", 4);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;
}

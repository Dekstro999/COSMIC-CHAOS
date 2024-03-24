#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <math.h>

/******** DIMENSIONES PANTALLA *********/
#define SCR_WIDTH 1600 // ALTO  (X)
#define SCR_HEIGHT 900 // ANCHO (Y)

/******** CONSTANTES *********/
#define MAX_GREEN_BALLS 30    // Maximo de bolas verde
#define GREEN_BALL_RADIUS 70  // Tamaño
#define GREEN_BALL_SPEED 7.0f // Velocidad de caida

#define MAX_BROWN_BALLS 10    // Maximo de bolas cafe
#define BROWN_BALL_RADIUS 40  // Tamaño
#define BROWN_BALL_SPEED 9.0f // Velocidad de caida

#define MAX_YELLOW_BALLS 2     // Maximo de bolas amarilla
#define YELLOW_BALL_RADIUS 20  // Tamaño
#define YELLOW_BALL_SPEED 8.0f // Velocidad de caida

#define MAX_RED_BALLS 1     // Maximo bolas rojas
#define RED_BALL_RADIUS 20  // Tamaño
#define RED_BALL_SPEED 9.0f // Velocidad de caida

/******** STRUCT *********/
typedef struct
{
    Vector2 position;
    bool active;
} Ball;

/******** INSTANCIAS NECESARIAS DE STRUCT 'Ball' *********/
Ball greenBalls[MAX_GREEN_BALLS];
Ball brownBalls[MAX_BROWN_BALLS];
Ball yellowBalls[MAX_YELLOW_BALLS];
Ball RedBalls[MAX_RED_BALLS];

// Posicion jugador
Vector2 playPosition = {(float)SCR_WIDTH / 2, (float)SCR_HEIGHT / 1.1f};

/******** PROTOTIPOS DE FUNCIONES *********/
void Tutorial();
void drawMainMenu(Texture2D background);
void gameInterface(Texture2D gamebg, Texture2D ship, Vector2 shipPosicion, int lives, int score, float rotation);
void Levels (int *score, int *level, float *elapsedTime);
void clearBalls();
void InitGreenBall(Ball *ball);
void InitBrownBall(Ball *ball);
void InitYellowBall(Ball *ball);
void InitRedBall(Ball *ball);
bool CheckCollision(Vector2 playerPos, float playerRadius, Vector2 ballPos, float playRadius);
void dibujarVerde(float rotation);
void dibujarCafe(float rotation);
void dibujarAmarillo();
void dibujarRojo();
void vidas(int lives);
void gameOverInterface(Texture2D background, int score);

/******** DESARROLLO DE FUNCIONES *********/
void Tutorial()
{
    BeginDrawing();
    DrawRectangleGradientV(0, 0, SCR_WIDTH, SCR_HEIGHT, PURPLE, DARKPURPLE);
    DrawText("COMO SE JUEGA:", SCR_WIDTH / 2 - MeasureText("COMO SE JUEGA", 100) / 2, 100, 100, BLUE);
    DrawText("- MUEVETE CON LAS FLECHAS   <-  ->", 40, SCR_HEIGHT / 2 + 40, 50, WHITE);
    DrawText("- EVITA COLISIONAR CON LOS ASTEROIDES", 40, SCR_HEIGHT / 2 + 110, 50, GRAY);
    DrawText("- RECOLECTA PUNTOS ", 40, SCR_HEIGHT / 2 + 180, 50, YELLOW);
    DrawText("- SOBREVIVE RECOLECTANTO VIDAS ⏎", 40, SCR_HEIGHT / 2 + 250, 50, RED);
    DrawText("(Q) Exit tutorial", SCR_WIDTH / 2 - MeasureText("(Q) Exit tutorial", 50) / 2, SCR_HEIGHT / 2 + 350, 50, GREEN);
    EndDrawing();
}

void drawMainMenu(Texture2D background) // PANTALLA DE MENU
{
    BeginDrawing();

    DrawTexture(background, 0, 0, WHITE);

    DrawText("COSMIC-CHAOS", SCR_WIDTH / 2 - MeasureText("COSMIC-CHAOS", 180) / 2, 200, 186, DARKBLUE);
    DrawText("COSMIC-CHAOS", SCR_WIDTH / 2 + 6 - MeasureText("COSMIC-CHAOS", 180) / 2 + 3, 195, 183, DARKBLUE);
    DrawText("COSMIC-CHAOS", SCR_WIDTH / 2 + 12 - MeasureText("COSMIC-CHAOS", 180) / 2 + 6, 190, 180, BLUE);

    int sizeStartTxt = MeasureText("(Enter) Start", 60);
    int sizeExitText = MeasureText("(ESC) Exit", 60);
    int sizeTuto = MeasureText("(A) Como jugar", 60);
    DrawText("(Enter) Start", SCR_WIDTH / 2 + 2 - sizeStartTxt / 2 + 2, SCR_HEIGHT / 2 + 82, 60, GREEN);
    DrawText("(Enter) Start", SCR_WIDTH / 2 - sizeStartTxt / 2, SCR_HEIGHT / 2 + 80, 60, LIME);

    DrawText("(A) Como jugar", SCR_WIDTH / 2 + 2 - sizeTuto / 2 + 2, SCR_HEIGHT / 2 + 152, 60, DARKPURPLE);
    DrawText("(A) Como jugar", SCR_WIDTH / 2 - sizeTuto / 2, SCR_HEIGHT / 2 + 150, 60, PURPLE);

    DrawText("(ESC) Exit", SCR_WIDTH / 2 + 2 - sizeExitText / 2 + 2, SCR_HEIGHT / 2 + 224, 60, WHITE);
    DrawText("(ESC) Exit", SCR_WIDTH / 2 - sizeExitText / 2, SCR_HEIGHT / 2 + 222, 60, YELLOW);

    EndDrawing();
}

void gameInterface(Texture2D gamebg, Texture2D ship, Vector2 shipPosicion, int lives, int score, float rotation)
{
    // Dibujar fondo
    DrawTexture(gamebg, 0, 0, WHITE);

    // Dibujar vidas
    vidas(lives);

    // Dibujar puntaje
    DrawText(TextFormat("SCORE: %04i", score), SCR_WIDTH - 400, 20, 50, WHITE);

    // Dibujar jugador (nave)
    DrawTextureV(ship, shipPosicion, WHITE);

    // Dibujar los objetos
    dibujarVerde(rotation);
    dibujarCafe(rotation);
    dibujarAmarillo();
    dibujarRojo();
}

void Levels (int *score, int *level, float *elapsedTime)
{
    if (*score >= 30 && *level == 1)
    {
        *level = 2;
        // Limpiar la pantalla y mostrar "Nivel 2" en el centro
        ClearBackground(BLACK);
        DrawText("Nivel 2", SCR_WIDTH / 2 - MeasureText("Nivel 2", 40) / 2, SCR_HEIGHT / 2 - 20, 40, WHITE);
        // Esperar un momento para que el jugador vea el mensaje
        WaitTime(2000); // Espera 2 segundos (2000 milisegundos)
        // Reiniciar el temporizador y otras variables relevantes
        *elapsedTime = 0.0f;
        *score = 0;
        // Limpiar todas las esferas en la pantalla
        clearBalls();
    }

    // Verificar si el jugador ha alcanzado el nivel 3
    if (*score >= 100 && *level == 2)
    {
        *level = 3;
        // Limpiar la pantalla y mostrar "Nivel 3" en el centro
        ClearBackground(BLACK);
        DrawText("Nivel 3", SCR_WIDTH / 2 - MeasureText("Nivel 3", 40) / 2, SCR_HEIGHT / 2 - 20, 40, WHITE);
        // Esperar un momento para que el jugador vea el mensaje
        WaitTime(2000); // Espera 2 segundos (2000 milisegundos)
        // Reiniciar el temporizador y otras variables relevantes
        *elapsedTime = 0.0f;
        *score = 0;
        // Limpiar todas las esferas en la pantalla
        clearBalls();
    }
}

// Función para limpiar todas las esferas en la pantalla
void clearBalls()
{
    for (int i = 0; i < MAX_GREEN_BALLS; i++)
    {
        greenBalls[i].active = false;
    }
    for (int i = 0; i < MAX_BROWN_BALLS; i++)
    {
        brownBalls[i].active = false;
    }
    for (int i = 0; i < MAX_YELLOW_BALLS; i++)
    {
        yellowBalls[i].active = false;
    }
    for (int i = 0; i < MAX_RED_BALLS; i++)
    {
        RedBalls[i].active = false;
    }
}

void InitGreenBall(Ball *ball)
{
    ball->position.x = GetRandomValue(0, GetScreenWidth());
    ball->position.y = -GREEN_BALL_RADIUS * 2;
    ball->active = true;
}
void InitBrownBall(Ball *ball)
{
    ball->position.x = GetRandomValue(0, GetScreenWidth());
    ball->position.y = -BROWN_BALL_RADIUS * 2;
    ball->active = true;
}

void InitYellowBall(Ball *ball)
{
    ball->position.x = GetRandomValue(0, GetScreenWidth());
    ball->position.y = -YELLOW_BALL_RADIUS * 2;
    ball->active = true;
}

void InitRedBall(Ball *ball)
{
    ball->position.x = GetRandomValue(0, GetScreenWidth());
    ball->position.y = -RED_BALL_RADIUS * 2;
    ball->active = true;
}

bool CheckCollision(Vector2 playerPos, float playerRadius, Vector2 ballPos, float playRadius)
{
    float distance = sqrt(pow(ballPos.x - playerPos.x, 2) + pow(ballPos.y - playerPos.y, 2));
    return (distance < (playerRadius + playRadius));
}

void dibujarVerde(float rotation) // vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv// 21/03  10:03 pm
{
    // Velocidad de rotacion
    rotation += 2.5f;
    // Dibujar esferas verdes
    for (int i = 0; i < MAX_GREEN_BALLS; i++)
    {
        if (greenBalls[i].active)
        {
            DrawPoly(greenBalls[i].position, 5, GREEN_BALL_RADIUS, rotation, GRAY);
            DrawPolyLines(greenBalls[i].position, 5, GREEN_BALL_RADIUS, rotation, DARKGRAY);
            DrawPolyLinesEx(greenBalls[i].position, 5, GREEN_BALL_RADIUS, rotation, 5, DARKGRAY);
        }
    }
}

void dibujarCafe(float rotation)
{
    // Velocidad de rotacion
    rotation += 2.5f;
    // Dibujar esferas verdes
    for (int i = 0; i < MAX_BROWN_BALLS / 2; i++)
    {
        if (brownBalls[i].active)
        {
            DrawPoly(brownBalls[i].position, 5, BROWN_BALL_RADIUS, rotation, BROWN);
            DrawPolyLines(brownBalls[i].position, 5, BROWN_BALL_RADIUS, rotation, DARKBROWN);
            DrawPolyLinesEx(brownBalls[i].position, 5, BROWN_BALL_RADIUS, rotation, 5, DARKGRAY);
        }
    }
}
void dibujarAmarillo()
{
    // Dibujar esferas amarillas
    for (int i = 0; i < MAX_YELLOW_BALLS; i++)
    {
        if (yellowBalls[i].active)
        {
            DrawCircleV(yellowBalls[i].position, YELLOW_BALL_RADIUS, YELLOW);
        }
    }
}
void dibujarRojo()
{
    // Dibujar esferas Rojas
    for (int i = 0; i < MAX_RED_BALLS; i++)
    {
        if (RedBalls[i].active)
        {
            DrawCircleV(RedBalls[i].position, RED_BALL_RADIUS, RED);
        }
    }
} //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  21/03  10:03 pm

void vidas(int lives)
{
    DrawText(TextFormat("Vidas: %d", lives), SCR_WIDTH - 250, SCR_HEIGHT - 140, 50, WHITE);
    for (int i = 0; i < lives; i++)
    {
        DrawText("<3 ", SCR_WIDTH - 350 + (i * 60), SCR_HEIGHT - 60, 50, RED); // Corazón lleno
    }
    for (int i = lives; i < 5; i++)
    {
        DrawText(" - ", SCR_WIDTH - 350 + (i * 60), SCR_HEIGHT - 60, 50, RED); // Corazón vacío
    }                                                                              //  Horizontal, Espaciado,         Altura, Tamaño
}
void gameOverInterface(Texture2D background, int score)
{
    // Fondo gameover
    DrawTexture(background, 0, 0, WHITE);

    int width = SCR_WIDTH;
    int height = SCR_HEIGHT;
    // Dibujar ventana de "Game Over"
    DrawText("GAME OVER", width / 2 + 2 - MeasureText("GAME OVER", 130) / 2 + 2, height / 2 - 218, 130, WHITE);
    DrawText("GAME OVER", width / 2 - MeasureText("GAME OVER", 130) / 2, height / 2 - 220, 130, RED);
    DrawText(TextFormat("Score: %04i", score), width / 2 - MeasureText(TextFormat("Score: %04i", score), 70) / 2, height / 2 - 50, 70, RAYWHITE);
    DrawText("(ENTER) Play Again", width / 2 + 2 - MeasureText("(ENTER) Play Again", 70) / 2 + 2, height / 2 + 130 + 2, 70, LIME);
    DrawText("(ENTER) Play Again", width / 2 - MeasureText("(ENTER) Play Again", 70) / 2, height / 2 + 130, 70, GREEN);
    DrawText("(Q) Back to menu", width / 2 + 2 - MeasureText("(Q) Back to menu", 70) / 2 + 2, height / 2 + 200 + 2, 70, WHITE);
    DrawText("(Q) Back to menu", width / 2 - MeasureText("(Q) Back to menu", 70) / 2, height / 2 + 200, 70, MAGENTA);
    DrawText("(Esc) Exit.", width / 2 + 2 - MeasureText("(Q) Exit", 90) / 2 + 2, height / 2 + 270 + 2, 70, WHITE);
    DrawText("(Esc) Exit.", width / 2 - MeasureText("(Q) Exit", 90) / 2, height / 2 + 270, 70, RED);
}


#endif
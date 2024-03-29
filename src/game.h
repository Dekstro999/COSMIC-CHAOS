#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <math.h>
#include <string.h>

/******** DIMENSIONES PANTALLA *********/
#define SCR_WIDTH 1600 // ANCHO  (X)
#define SCR_HEIGHT 900 // ALTO (Y)

/******** CONSTANTES *********/
// Meteoros
#define MAX_GRAY_METEORS 30          // Maximos meteoros en pantalla
const float GRAY_METEOR_RADIUS = 70; // Tamaño
#define GRAY_METEOR_SPEED 7.0f       // Velocidad de caida
#define MAX_BROWN_METEORS 10
const float BROWN_METEOR_RADIUS = 40;
#define BROWN_METEOR_SPEED 9.0f
// Monedas
#define MAX_COINS 2            // Maximas monedas en pantalla
const float COINS_RADIUS = 20; // Tamaño
#define COINS_SPEED 8.0f       // Velocidad de caida
// Corazones
#define MAX_HEARTS 1            // Maximos corazones en pantalla
const float HEARTS_RADIUS = 20; // Tamaño
#define HEARTS_SPEED 9.0f       // Velocidad de caida

/*------- STRUCT OBJETOS DEL JUEGO -------*/
typedef struct
{
    Vector2 position;
    bool active;
} GameObject;

/*----------- INSTANCIAS NECESARIAS DE STRUCT 'Ball' -----------*/
GameObject grayMeteors[MAX_GRAY_METEORS];
GameObject brownMeteors[MAX_BROWN_METEORS];
GameObject coins[MAX_COINS];
GameObject hearts[MAX_HEARTS];

/*--------------------- PROTOTIPOS FUNCIONES ---------------------*/

/* MENUS DEL JUEGO */
void drawMainMenu(Texture2D *background);
void drawHowToPlay();
void aboutTheGame();
void gameOverInterface(Texture2D *background, int *score, int *level);

/* LOGICA DEL JUEGO */
void gameInterface(Texture2D *gamebg, Texture2D *ship, Vector2 *shipPosicion, Texture2D *coins, Texture2D *hearts, int *lives, int *score, float *rotation);
void logicaMenu(int *seconds, bool *isPlaying);

bool CheckCollision(Vector2 playerPos, float playerRadius, Vector2 ballPos, float meteorRadius);
void InitObject(GameObject *object, float *objRadius);
void Levels(Texture2D *cinema, int *score, int *level, float *elapsedTime, Vector2 *playPosition, int *seconds, int *lives);
void subtiruloscinematicas(const char *text, int tamano, int frecuencia, Texture2D *texturas, int numFondos);
// void clock(int *totalseconds, int *minutesT, int *econdsT);
void resetItems(Vector2 *playPosition);
void resetStats(int *lives, int *score, int *level, double *timeSeconds);

/* DIBUJO */
void drawTextCenter(const char *text, int posX, int posY, int fontSize, Color color);
void drawGrayMeteor(float *rotation);
void drawBrownMeteor(float *rotation);
void drawCoins(Texture2D *coinsTx);
void drawHearts(Texture2D *heartsTx);

/************** DESARROLLO DE FUNCIONES **************/

void drawTextCenter(const char *text, int posX, int posY, int fontSize, Color color)
{
    DrawText(text, SCR_WIDTH / 2 + posX - MeasureText(text, fontSize) / 2 + posX, posY, fontSize, color);
}

// Dibuja menu principal inicial
void drawMainMenu(Texture2D *background) // PANTALLA DE MENU
{
    BeginDrawing();
    DrawTexture(*background, 0, 0, WHITE); // Fondo

    // Titulo
    DrawText("COSMIC-CHAOS", SCR_WIDTH / 2 - MeasureText("COSMIC-CHAOS", 180) / 2, 150, 186, DARKBLUE);
    DrawText("COSMIC-CHAOS", SCR_WIDTH / 2 + 6 - MeasureText("COSMIC-CHAOS", 180) / 2 + 3, 145, 183, DARKBLUE);
    DrawText("COSMIC-CHAOS", SCR_WIDTH / 2 + 12 - MeasureText("COSMIC-CHAOS", 180) / 2 + 6, 140, 180, BLUE);

    // Subtitulos
    drawTextCenter("(ENTER) Start", 2, 502, 60, LIME);
    drawTextCenter("(ENTER) Start", 0, 500, 60, GREEN);

    drawTextCenter("(A) How to play", 2, 582, 60, DARKPURPLE);
    drawTextCenter("(A) How to play", 0, 580, 60, PURPLE);

    drawTextCenter("(E) About the game", 2, 662, 60, GRAY);
    drawTextCenter("(E) About the game", 0, 660, 60, YELLOW);

    drawTextCenter("(ESC) Exit", 2, 742, 60, DARKGRAY);
    drawTextCenter("(ESC) Exit", 0, 740, 60, RED);

    EndDrawing();
}

// Dibuja interfaz de como jugar
void drawHowToPlay()
{
    while (!IsKeyPressed(KEY_Q))
    {
        BeginDrawing();
        ClearBackground(BLACK);

        drawTextCenter("HOW TO PLAY: ", 0, 100, 100, BLUE);
        DrawText("- MOVE WITH THE ARROUS <-  ->", 40, SCR_HEIGHT / 2 + 40, 50, WHITE);
        DrawText("- AVOID COLLIDING WITH ASTEROIDS", 40, SCR_HEIGHT / 2 + 110, 50, GRAY);
        DrawText("- COLLECT POINTS", 40, SCR_HEIGHT / 2 + 180, 50, YELLOW);
        DrawText("- SURVIVE BY COLLECTING LIVES", 40, SCR_HEIGHT / 2 + 250, 50, RED);
        DrawText("(Q) Back to menu", SCR_WIDTH / 2 - MeasureText("(Q) Back to menu", 50) / 2, SCR_HEIGHT / 2 + 350, 50, GREEN);

        EndDrawing();
    }
}

// Dibuja interfaz con informacion acerca del juego
void aboutTheGame()
{
    while (!IsKeyPressed(KEY_Q)) // Bucle para mostrar la interfaz "about"
    {
        BeginDrawing();

        ClearBackground(BLACK);

        drawTextCenter("About the game", 0, 100, 100, RED);
        drawTextCenter("Developers:", 0, 270, 50, YELLOW);
        drawTextCenter("- Francisco Cornejo", 0, 340, 50, GREEN);
        drawTextCenter("- Diego Ibarra", 0, 400, 50, GREEN);
        drawTextCenter("Sounds:", 0, 580, 50, GOLD);
        drawTextCenter("Unnamed", 0, 640, 50, LIME);
        drawTextCenter("(Q) Back to menu", 0, 800, 50, GOLD);

        EndDrawing();
    }
}

// Dibuja la interfaz de juego terminado
void gameOverInterface(Texture2D *background, int *score, int *level)
{
    // Fondo
    DrawTexture(*background, 0, 0, WHITE);

    // Dibujar ventana de "Game Over"
    drawTextCenter("GAME OVER", 2, 232, 130, WHITE);
    drawTextCenter("GAME OVER", 0, 230, 130, RED);

    DrawText(TextFormat("Score: %04i", *score), SCR_WIDTH / 2 - MeasureText(TextFormat("Score: %04i", *score), 70) / 2, SCR_HEIGHT / 2 + 10, 70, RAYWHITE);
    DrawText(TextFormat("Level: %1i", *level), SCR_WIDTH / 2 - MeasureText(TextFormat("LEVEL: %1i", *level), 70) / 2, SCR_HEIGHT / 2 - 50, 70, RAYWHITE);

    drawTextCenter("(ENTER) Play Again", 2, 582, 70, LIME);
    drawTextCenter("(ENTER) Play Again", 0, 580, 70, GREEN);

    drawTextCenter("(Q) Back to menu", 2, 662, 70, DARKPURPLE);
    drawTextCenter("(Q) Back to menu", 0, 660, 70, MAGENTA);

    drawTextCenter("(ESC) Exit", 2, 742, 70, RED);
    drawTextCenter("(ESC) Exit", 0, 740, 70, MAROON);
}

// Dibuja la interfaz de la partida
void gameInterface(Texture2D *gamebg, Texture2D *ship, Vector2 *shipPosicion, Texture2D *coins, Texture2D *hearts, int *lives, int *score, float *rotation)
{
    // Dibujar fondo
    DrawTexture(*gamebg, 0, 0, WHITE);

    // Dibujar puntaje
    DrawText(TextFormat("SCORE: %04i", *score), SCR_WIDTH - 400, 20, 50, WHITE);

    // Dibujar jugador (nave)
    DrawTextureV(*ship, *shipPosicion, WHITE);

    // Dibujar los objetos
    drawGrayMeteor(rotation);
    drawBrownMeteor(rotation);
    drawCoins(coins);
    drawHearts(hearts);

    // Dibujar vidas
    DrawText(TextFormat("Vidas: %d", *lives), SCR_WIDTH - 250, SCR_HEIGHT - 140, 50, WHITE);

    for (int i = 0; i < *lives; i++)
    {
        DrawText("<3 ", SCR_WIDTH - 350 + (i * 60), SCR_HEIGHT - 60, 50, RED); // Corazón lleno
    }
    for (int i = *lives; i < 5; i++)
    {
        DrawText(" - ", SCR_WIDTH - 350 + (i * 60), SCR_HEIGHT - 60, 50, RED); // Corazón vacío
    }
}

void logicaMenu(int *seconds, bool *isPlaying)
{
    if (IsKeyPressed(KEY_ENTER)) // Iniciar partida
    {
        *seconds = 0;
        *isPlaying = true;
    }
    if (IsKeyPressed(KEY_A)) // Ir a tutorial como jugar
    {
        drawHowToPlay();
    }
    if (IsKeyPressed(KEY_E)) // Ir a acerca del juego
    {
        aboutTheGame();
    }
}

void InitObject(GameObject *object, const float *objRadius)
{
    object->position.x = GetRandomValue(0, SCR_WIDTH);
    object->position.y = -*objRadius * 2;
    object->active = true;
}

// Colisiones
bool CheckCollision(Vector2 playerPos, float playerRadius, Vector2 ballPos, float meteorRadius)
{
    float dx = ballPos.x - playerPos.x;
    float dy = ballPos.y - playerPos.y;
    float distanceSquared = dx * dx + dy * dy;
    float radiusSumSquared = (playerRadius + meteorRadius) * (playerRadius + meteorRadius);
    return distanceSquared < radiusSumSquared;
}

// Manejo de niveles
void Levels(Texture2D *cinema, int *score, int *level, float *elapsedTime, Vector2 *playPosition, int *seconds, int *lives)
{
    if (*score >= 30 && *level == 1)
    {
        // Limpiar todas las esferas en la pantalla
        // Limpiar todas las esferas en la pantalla
        resetItems(playPosition);
        *level = 2; //                         -v-  aqui
        subtiruloscinematicas("hola como estan todos en este dias --- ya jalo tu --- texto, tamaño, cada cuanto tiempo, nombre de la textura, cuantas texturas son ", 45, 7, cinema, 2);

        subtiruloscinematicas("segundo subtitulo --- ya jalo tu --- texto, tamaño, cada cuanto tiempo, nombre de la textura, cuantas texturas son ", 45, 7, cinema, 2);

        // Esperar hasta que se presione la tecla Skip
        while (!IsKeyPressed(KEY_S))
        {
            // Limpiar la pantalla y mostrar "Presiona ESPACIO" en el centro
            DrawText("(S) SKIP", SCR_WIDTH - (250), SCR_HEIGHT - 70, 50, WHITE);
            // Actualizar la pantalla
            EndDrawing();
        }

        double startTime2 = GetTime(); // Obtener el tiempo de inicio

        while (GetTime() - startTime2 < *seconds)
        {
            // Limpiar la pantalla y mostrar "Nivel 2" en el centro
            ClearBackground(BLACK);
            DrawText("NIVEL 2", SCR_WIDTH / 2 - MeasureText("NIVEL 2", 200) / 2, SCR_HEIGHT / 2 - 200, 200, WHITE);
            // Actualizar la pantalla

            EndDrawing();
        }
        ClearBackground(BLACK);
        *elapsedTime = 0.0f;
        *score = 0;
        *lives = 5;
    }

    // Verificar si el jugador ha alcanzado el nivel 3
    if (*score >= 20 && *level == 2)
    {
        *level = 3;
        double startTime = GetTime(); // Obtener el tiempo de inicio

        while (GetTime() - startTime < *seconds)
        {
            // Limpiar la pantalla y mostrar "Nivel 2" en el centro
            ClearBackground(BLACK);
            DrawText("Nivel 3", SCR_WIDTH / 2 - MeasureText("Nivel 3", 200) / 2, SCR_HEIGHT / 2, 200, WHITE);
            // Actualizar la pantalla
            EndDrawing();
        }

        *elapsedTime = 0.0f;
        *score = 0;
        *lives = 5;
        // Limpiar todas las esferas en la pantalla
        resetItems(playPosition);
    }
}

void subtiruloscinematicas(const char *text, int tamano, int frecuencia, Texture2D *texturas, int numFondos)
{
    int longitud = strlen(text);
    int i;
    int limiteH = 45;
    int acumulador = 0;
    bool cambio = true;
    int seconds = 2;

    for (i = 0; i < longitud; i++)
    {
        if (acumulador >= frecuencia)
        {
            cambio = !cambio;
            acumulador = 0;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        if (cambio)
            DrawTexture(texturas[0], 288, 0, WHITE);
        else
            DrawTexture(texturas[1], 288, 0, WHITE);

        float x = limiteH;
        float y = (SCR_HEIGHT / 2) * 1.5;

        for (int j = 0; j <= i; j++)
        {
            if (x + MeasureText(TextFormat("%c", text[j]), tamano) > SCR_WIDTH - limiteH)
            {
                x = limiteH;
                y += tamano + 5;
            }
            DrawText(TextFormat("%c", text[j]), x + 6, y + 6, tamano, BLACK);
            DrawText(TextFormat("%c", text[j]), x, y, tamano, WHITE);

            x += MeasureText(TextFormat("%c", text[j]), tamano) + 10;
        }
        EndDrawing();

        acumulador++;
    }
    double startTime2 = GetTime(); // Obtener el tiempo de inicio

    while (GetTime() - startTime2 < seconds)
    {
    }
}
// Limpiar elementos y posicion jugador
void resetItems(Vector2 *playPosition)
{
    // Reiniciar posicion nave
    *playPosition = {(float)SCR_WIDTH / 2, (float)SCR_HEIGHT / 1.1f};

    // Limpiar meteoros
    for (int i = 0; i < MAX_GRAY_METEORS; i++)
    {
        grayMeteors[i].active = false;
    }
    for (int i = 0; i < MAX_BROWN_METEORS; i++)
    {
        brownMeteors[i].active = false;
    }
    for (int i = 0; i < MAX_COINS; i++)
    {
        coins[i].active = false;
    }
    for (int i = 0; i < MAX_HEARTS; i++)
    {
        hearts[i].active = false;
    }
}

void resetStats(int *lives, int *score, int *level, double *timeSeconds)
{
    // Reinicia vidas y puntaje
    *lives = 5;
    *score = 0;
    *level = 1;
    *timeSeconds = 0;
}

// Dibujar meteoros grises
void drawGrayMeteor(float *rotation)
{
    for (int i = 0; i < MAX_GRAY_METEORS; i++)
    {
        if (grayMeteors[i].active)
        {
            // Dibujar el cuerpo principal del meteoro (polígono relleno)
            DrawPoly(grayMeteors[i].position, 5, GRAY_METEOR_RADIUS, *rotation, GRAY);

            // Dibujar líneas adicionales para dar textura
            DrawPolyLinesEx(grayMeteors[i].position, 5, GRAY_METEOR_RADIUS, *rotation, 8, DARKGRAY);
        }
    }
}

// Dibujar meteoros cafe
void drawBrownMeteor(float *rotation)
{
    for (int i = 0; i < MAX_BROWN_METEORS; i++)
    {
        if (brownMeteors[i].active)
        {
            // Dibujar el cuerpo principal del meteoro (polígono relleno)
            DrawPoly(brownMeteors[i].position, 5, BROWN_METEOR_RADIUS, *rotation, BROWN);

            // Dibujar líneas adicionales para dar textura
            DrawPolyLinesEx(brownMeteors[i].position, 5, BROWN_METEOR_RADIUS, *rotation, 8, DARKGRAY);
        }
    }
}

// Dibujar esferas amarillas
void drawCoins(Texture2D *coinsTx)
{
    Vector2 coinCenter;
    for (int i = 0; i < MAX_COINS; i++)
    {
        if (coins[i].active)
        {
            // Calcular la posición del centro de la moneda
            coinCenter = {coins[i].position.x - coinsTx->width / 2, coins[i].position.y - coinsTx->height / 2};
            DrawTextureV(*coinsTx, coinCenter, WHITE);
        }
    }
}

// Dibujar esferas Rojas
void drawHearts(Texture2D *heartsTx)
{
    Vector2 heartCenter;
    for (int i = 0; i < MAX_HEARTS; i++)
    {
        if (hearts[i].active)
        {
            // Calcular la posición del centro de la moneda
            heartCenter = {(float)((int)hearts[i].position.x - heartsTx->width / 2), (float)((int)hearts[i].position.y - heartsTx->height / 2)};
            DrawTextureV(*heartsTx, heartCenter, RED);
        }
    }
}

#endif
#include <raylib.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>



typedef struct Particle {
    float x;
    float y;
    float vx; 
    float vy;
    float life;
    float radius;
    float gravity;
    bool active; // is the partice available for use 
    Color color ;
} Particle;

typedef enum {
    EXPLOSION,
    FOUNTAIN,
    SMOKE,
    SPARKS

} EmitterType;



#define MAX_PARTICLES 5000 
Particle particles[MAX_PARTICLES];
// random number between 0 and 1
// × range (6)
// + minimum (2)
void SpawnParticles(Particle particles[],  float x, float y, EmitterType type){
    for(int i  = 0; i<MAX_PARTICLES;i++){
        if(!particles[i].active){
            particles[i].active = true;
            particles[i].y = y;
            particles[i].x = x;
            particles[i].life = 1.0;
            particles[i].vx = (((float)rand()/RAND_MAX)+2.0-1.0) * 3.0;
            particles[i].vy = (((float)rand()/RAND_MAX)+2.0-1.0) * 3.0;
            particles[i].radius = ((float)rand()/RAND_MAX)*6.0 + 2.0;
            particles[i].color = (Color){
                (float)rand() / RAND_MAX * 255,  // Random red
                (float)rand() / RAND_MAX * 255,  // Random green
                (float)rand() / RAND_MAX * 255,  // Random blue
                255                               // Full opacity (Fade() handles transparency)
            };
            switch(type){
                case EXPLOSION:
                    particles[i].vx = (((float)rand() / RAND_MAX) *2.0-1.0)*0.8;
                    particles[i].vy = (((float)rand() / RAND_MAX) *2.0-1.0)*0.8;
                    particles[i].radius  = (((float)rand() / RAND_MAX) * 6.0 +2.0);
                    particles[i].life = 1.0;
                    particles[i].gravity = 0.1;
                    particles[i].color = (Color){
                        255,
                        (float)rand()/RAND_MAX *255,
                        0,
                        255
                    };
                    break;
                case FOUNTAIN:
                    particles[i].vx = (((float)rand() / RAND_MAX) *2.0-1.0)*3.0;
                    particles[i].vy = -(((float)rand() / RAND_MAX) * 8.0 + 2.0);
                    particles[i].radius  = (((float)rand() / RAND_MAX) * 4.0 +1.0);
                    particles[i].life = 1.0;
                    particles[i].gravity = 0.1;
                    particles[i].color = (Color){
                        0,
                        (float)rand()/RAND_MAX * 255,
                        255,
                        255
                    };
                    break;
                case SMOKE:
                    float gray = (float)rand() / RAND_MAX * 150 + 50;
                    particles[i].vx = (((float)rand() / RAND_MAX) *2.0-1.0)*0.5;
                    particles[i].vy = -(((float)rand() / RAND_MAX) * 8.0 + 0.2);
                    particles[i].radius  = (((float)rand() / RAND_MAX) * 8.0 + 4.0);
                    particles[i].life = 1.5;
                    particles[i].gravity = 0.005;
                    particles[i].color  = (Color){
                        gray,
                        gray,
                        gray,
                        255
                    };
                    break;
                case SPARKS:
                    particles[i].vx = (((float)rand() / RAND_MAX) *2.0-1.0)*10.0;
                    particles[i].vy = (((float)rand() / RAND_MAX) *2.0-1.0)*10.0;
                    particles[i].radius  = (((float)rand() / RAND_MAX) * 2.0 + 1.0);
                    particles[i].life = 0.5;
                    particles[i].gravity = 0.5;
                    particles[i].color = (Color){
                        255,
                        255,
                        (float)rand()/RAND_MAX * 255,
                        255
                    };
                    break;
                

            }
            break;
        }
    }
}

int main(void)
{
    InitWindow(800, 450, "Moving Circle");
    SetTargetFPS(60);
    
    for(int i  = 0;i<MAX_PARTICLES;i++){
        particles[i].active = false;
    }
    
    while (!WindowShouldClose())
    {

        for(int i = 0; i < MAX_PARTICLES; i++){
            if(!particles[i].active) continue;
            particles[i].vy+=particles[i].gravity;
            
            particles[i].x+= particles[i].vx;;
            particles[i].y += particles[i].vy;

            particles[i].life -= 0.01;
            if(particles[i].life <= 0){
                particles[i].active = false;
            }
        }
        
       
            
        // End of collision detection
        
        // DRAW - Render everything
        BeginDrawing();
        ClearBackground(BLACK);
        // Spawn particles at mouse position
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
            for(int i = 0; i < 20; i++){
                 SpawnParticles(particles, GetMouseX(), GetMouseY(), EXPLOSION);
            }
        }
        if(IsKeyDown(KEY_F)){
            for(int i = 0; i < 10; i++){
                SpawnParticles(particles, GetMouseX(), GetMouseY(), FOUNTAIN);
            }
        }
        if(IsKeyDown(KEY_S)){
            for(int i = 0; i < 5; i++){
                SpawnParticles(particles, GetMouseX(), GetMouseY(), SMOKE);
            }
        }
        if(IsKeyDown(KEY_E)){
            for(int i = 0; i < 30; i++){
                SpawnParticles(particles, GetMouseX(), GetMouseY(), SPARKS);
            }
        }
        for(int i=0; i<MAX_PARTICLES; i++){
            if(!particles[i].active) continue;

            DrawCircle(
                particles[i].x,
                particles[i].y,
                particles[i].radius * particles[i].life, // shrink as they die 
                Fade(particles[i].color, particles[i].life)
            );
        }


        
        char *text1 = "LeftClick:Explosion";
        char *text2 = "E:Sparks";
        char *text3 = "S:Smoke";
        char *text4 = "F:Fountain";
        DrawText("Click to spawn particles!", 10, 30, 20,WHITE);
        DrawText(text1, 800-MeasureText(text1,20), 50, 20, WHITE);
        DrawText(text2, 800-MeasureText(text2,20), 70, 20, WHITE);
        DrawText(text3, 800-MeasureText(text3,20), 90, 20, WHITE);
        DrawText(text4, 800-MeasureText(text4,20), 110, 20, WHITE);
        EndDrawing();
        
    } // End of game loop
    
    CloseWindow();
    return 0;
}
#ifndef GAME_H
#define GAME_H

// ==========================================================
// This file will handle all the game logic and the game loop
// ==========================================================



// State of the game.
typedef enum State
{
    STOP,                           // Stop state
    PLAY,                           // Play state
    PAUSE,                          // Pause state
} State;

// Structure of the graphical user interface.
typedef struct UserInterface
{
    GtkWindow* window;              // Main window
    GtkDrawingArea* area;           // Drawing area
    GtkButton* start_button;        // Start button
    GtkButton* stop_button;         // Stop button
    GtkScale* speed_scale;          // Speed scale
    GtkCheckButton* training_cb;    // Training check box
} UserInterface;

// Structure of the game.
typedef struct Game
{
    Map map;
    State state;                    
    Player p1;                      
    Ghost g;                     
    UserInterface ui;  
    int lives;
    int score;             
} Game;


#endif
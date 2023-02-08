#include <gtk/gtk.h>


#define END_GAME_SCORE 5

// State of the game.
typedef enum State
{
    STOP,                           // Stop state
    PLAY,                           // Play state
    PAUSE,                          // Pause state
} State;


// Structure of a player.
typedef struct Player
{
                 
} Player;

// Structure of the ghost AI.
typedef struct Ghost
{                   
} Ghost;

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

typedef struct Map
{

} Map;

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


// Sets the 'Play' state.
void set_play(Game* game)
{
    // - Set the state field to PLAY.
    game->state=PLAY;
    // - Set the label of the start button to "Pause".
    gtk_button_set_label(game->ui.start_button,"Pause");
    // - Disable the stop button.
    gtk_widget_set_sensitive(GTK_WIDGET(game->ui.stop_button),FALSE);
}


// Sets the 'Pause' state.
void set_pause(Game* game)
{
    // - Set the state field to PAUSE.
    game->state=PAUSE;
    // - Set the label of the start button to "Resume".
    gtk_button_set_label(game->ui.start_button,"Resume");
    // - Enable the stop button.
    gtk_widget_set_sensitive(GTK_WIDGET(game->ui.stop_button),TRUE);
    // - Stop the on_move_disc() function.
}

// Sets the 'Stop' state.
void set_stop(Game *game)
{
    // - Set the state field to STOP.
    game->state=STOP;
    // - Set the label of the start button to "Start".
    gtk_button_set_label(game->ui.start_button,"Start");
    // - Disable the stop button.
    gtk_widget_set_sensitive(GTK_WIDGET(game->ui.stop_button),FALSE);
}

// Event handler for the "clicked" signal of the start button.
void on_start(GtkButton *button, gpointer user_data)
{
    // Gets the `Game` structure.
    Game* game = user_data;

    // Sets the next state according to the current state.
    switch (game->state)
    {
        case STOP: set_play(game); break;
        case PLAY: set_pause(game); break;
        case PAUSE: set_play(game); break;
    };
}

// Event handler for the "clicked" signal of the stop button.
void on_stop(GtkButton *button, gpointer user_data)
{
    set_stop(user_data);
}


int main (int argc, char *argv[])
{
    // Initializes GTK.
    gtk_init(NULL, NULL);

    // Constructs a GtkBuilder instance.
    GtkBuilder* builder = gtk_builder_new ();

    // Loads the UI description.
    // (Exits if an error occurs.)
    GError* error = NULL;
    if (gtk_builder_add_from_file(builder, "game.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    // Gets the widgets.
    GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.duel"));
    GtkDrawingArea* area = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "area"));
    GtkButton* start_button = GTK_BUTTON(gtk_builder_get_object(builder, "start_button"));
    GtkButton* stop_button = GTK_BUTTON(gtk_builder_get_object(builder, "stop_button"));
    GtkLabel* p1_score_label = GTK_LABEL(gtk_builder_get_object(builder, "p1_score_label"));
    GtkScale* speed_scale = GTK_SCALE(gtk_builder_get_object(builder, "speed_scale"));
    GtkCheckButton* training_cb = GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "training_cb"));

    // Creates the "Game" structure.
    Game game =
    {
        .state = STOP,

        .p1=
        {
            
        }

        .ui =
            {
                .window = window,
                .area = area,
                .start_button = start_button,
                .stop_button = stop_button,
                .speed_scale = speed_scale,
                .training_cb = training_cb,
            },
    };
    // Connects event handlers.
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(area, "draw", G_CALLBACK(on_draw), &game);
    g_signal_connect(start_button, "clicked", G_CALLBACK(on_start), &game);
    g_signal_connect(stop_button,"clicked",G_CALLBACK(on_stop),&game);

    // Runs the main loop.
    gtk_main();

    // Exits.
    return 0;
}
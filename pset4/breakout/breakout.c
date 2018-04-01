//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// height and width of game's кирпичиков (и пропорционально - ракетка) in pixels
#define  BRICK_WIDTH 35
#define  BRICK_HEIGHT 10 

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));
    
    double xvelocity = drand48()*2.0; /// удалить потом
    double yvelocity = -drand48()-1.5; /// удалить потом

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // баллы за раз
    int shag = 1;
    
    
    
    // старт
    GLabel start = newGLabel("Click to start");
    setFont(start, "SansSrif-36");
    add(window, start);
    setLocation(start, (WIDTH-getWidth(start))/2, HEIGHT/2);  
    
    waitForClick();
    
    removeGWindow(window, start);

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // TODO
        updateScoreboard(window, label, points);
        
        GEvent event = getNextEvent(MOUSE_EVENT); // ракетка
        
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - getWidth(paddle) / 2;
                // double y = getY(event) - getWidth(paddle);
                if (x < 0)
                {
                    x = 0;
                }
                if (x > (getWidth(window)-getWidth(paddle)))
                {
                    x = getWidth(window)-getWidth(paddle);
                }
                setLocation(paddle, x, HEIGHT-50);
            }
        }
        
        move(ball, xvelocity, yvelocity);    // мячик
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            xvelocity = -xvelocity;
            shag = 1;
        }
        else if (getX(ball) <= 0)
        {
            xvelocity = -xvelocity;
            shag = 1;
        }
        
        if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            yvelocity = -yvelocity;
            
            lives--;
            if (lives != 0)
            {
                waitForClick();
                setLocation(ball, WIDTH/2-RADIUS, HEIGHT*0.66);
                
                if (lives == 2)
                {
                    setColor(label, "ORANGE");
                }
                if (lives == 1)
                {
                    setColor(label, "RED");
                }
                
                
            }
            else
            {
                GLabel gameOver = newGLabel("Game over");
                setFont(gameOver, "SansSrif-36");
                add(window, gameOver);
                setLocation(gameOver, (WIDTH-getWidth(gameOver))/2, HEIGHT*0.55);
            }   
            shag = 1;
        }
        else if (getY(ball) <= 0)
        {
            yvelocity = -yvelocity;
        }
        pause(10);
        
        
        GObject object = detectCollision(window, ball);
        if (object == paddle)
        {
            // TODO
            yvelocity = -yvelocity;
            shag = 2;
            
            // измение угла отскакивания
            double xbal = getX(ball) + RADIUS;
            double xpaddle = getX(paddle);
            
            if (xbal > xpaddle + BRICK_WIDTH - 2 && xbal < xpaddle + BRICK_WIDTH + 2)
            {
                if (xvelocity < 0)
                {
                    xvelocity = -0.01;
                }
                else
                {
                    xvelocity = 0.01;
                }
            }
            else if (xbal > xpaddle + BRICK_WIDTH - BRICK_WIDTH/3 && xbal < xpaddle + BRICK_WIDTH + BRICK_WIDTH/3)
            {
                if (xvelocity < 0)
                {
                    xvelocity = -0.4;
                }
                else
                {
                    xvelocity = 0.4;
                }
            }
            else if (xbal > xpaddle + BRICK_WIDTH/3 && xbal < xpaddle + 2*BRICK_WIDTH - BRICK_WIDTH/3)
            {
                if (xvelocity < 0)
                {
                    xvelocity = -0.8;
                }
                else
                {
                    xvelocity = 0.8;
                }
            }
            else if (xbal < xpaddle + BRICK_WIDTH/3 || xbal > xpaddle + 2*BRICK_WIDTH - BRICK_WIDTH/3)
            {
                if (xvelocity < 0)
                {
                    xvelocity = -1.4;
                }
                else
                {
                    xvelocity = 1.4;
                }
            }
            
        }
        
        if (object != NULL)
        {
            if (strcmp(getType(object), "GRect") == 0 && object != paddle)
            {
                // TODO
                yvelocity = -yvelocity;

                
                removeGWindow(window, object);
                points = points + shag;
                updateScoreboard(window, label, points);
                
                bricks--;
                if (bricks == 0)
                {
                    GLabel gameWin = newGLabel("You win!");
                    setFont(gameWin, "SansSrif-36");
                    add(window, gameWin);
                    setLocation(gameWin, (WIDTH-getWidth(gameWin))/2, HEIGHT*0.33);
                }
                shag = 3;
            }
            
            if (strcmp(getType(object), "GLabel") == 0)
            {
                // TODO
            }
        }
        
        
        
    } // while
    

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO
    for (int j = 0; j < ROWS; j++)
    {    
        for (int i = 0; i < COLS; i++)
        {
            GRect brick = newGRect(5 + (i*(BRICK_WIDTH+4)), 20 + (j*(BRICK_HEIGHT+10)), BRICK_WIDTH, BRICK_HEIGHT); 
            setColor(brick, "BLACK");
            setFilled(brick, true);
            
            add(window, brick);
        }
    }
    
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    GOval ball = newGOval(WIDTH/2-RADIUS, HEIGHT*0.66, 2*RADIUS, 2*RADIUS); 
    setColor(ball, "LIGHT_GRAY");
    setFilled(ball, true);
        
    add(window, ball);
    
    if (ball != NULL)
    {    
        return ball;
    }
    
    return NULL;
}

/**
 * Instantiates paddle zcin bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    GRect paddle = newGRect(WIDTH/2-BRICK_WIDTH , HEIGHT-50, 2*BRICK_WIDTH, 0.8*BRICK_HEIGHT); 
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
            
    add(window, paddle);
    
    if (paddle != NULL)
    {    
        return paddle;
    }
    
    return NULL;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    GLabel label = newGLabel("0");
    setFont(label, "SansSrif-36");
    setColor(label, "GREEN");
    //setFilled(label, true);
    add(window, label);
      
    if (label != NULL)
    {    
        return label;
    }
    
    return NULL;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}

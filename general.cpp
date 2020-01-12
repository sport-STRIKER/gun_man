#include "TXLib.h"

void game (double x_man, double y_man, double x_bullet, double y_bullet,
           double vx_man, double vy_man, double vx_bullet, double vy_bullet,
           int dt);

void shotter (int x, int y,
              COLORREF color_man, COLORREF color_gun);

void draw_ball_3d(int x, int y,
                  int r,
                  COLORREF color_bullet);

void draw_bullet(int x, int y,
                 int rmax,
                 int color);

void move_objects(double *x_man, double *y_man, double *x_bullet,double *y_bullet,
                  double *vx_man, double *vy_man, double *vy_bullet, double *vx_bullet,
                  int dt);

void control_objects(double *x_man, double *y_man, double *x_bullet, double *y_bullet,
                     double *vx_man, double *vy_man,
                     double right, double left, double up, double down, double space,
                     bool condition);



int main()
{
    txCreateWindow (800, 800);

    game (100, 100, 100, 100,
          2, 2, 3, 3,
          2);

    return 0;
}


void game (double x_man, double y_man, double x_bullet, double y_bullet,
           double vx_man, double vy_man, double vx_bullet, double vy_bullet,
           int dt)
{
    while (true)
    {
        txBegin ();

        txSetColor (TX_BLACK);

        txSetFillColor (TX_BLACK);

        txClear ();

        shotter(x_man, y_man,
                TX_WHITE, TX_WHITE);


        move_objects(&x_man, &y_man, &x_bullet,&y_bullet,
                     &vx_man, &vy_man, &vx_bullet, &vy_bullet,
                     dt);

        control_objects(&x_man, &y_man, &x_bullet, &y_bullet,
                        &vx_man, &vy_man,
                        VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, VK_SPACE,
                        1);

        txSleep (25);
   }
}

void move_objects(double *x_man, double *y_man, double *x_bullet,double *y_bullet,
                  double *vx_man, double *vy_man, double *vy_bullet, double *vx_bullet,
                  int dt)
{
    *x_man = *x_man + *vx_man * dt;
    *y_man = *y_man + *vy_man * dt;

    *x_bullet = *x_bullet + *vx_bullet * dt;

    //*y_bullet = *y_bullet + *vy_bullet * dt;

    if (*x_man > 800)
            *vx_man = - (*vx_man);

    if (*y_man > 800)
            *vy_man = - (*vy_man);

    if (*x_man < 0)
            *vx_man = - (*vx_man);

    if (*y_man < 0)
            *vy_man = - (*vy_man);
}

void control_objects(double *x_man, double *y_man, double *x_bullet, double *y_bullet,
                     double *vx_man, double *vy_man,
                     double right, double left, double up, double down, double space,
                     bool condition)
{
    if (GetAsyncKeyState (right))
        (*vx_man)++;

    if (GetAsyncKeyState (left))
        (*vx_man)--;

    if (GetAsyncKeyState (up))
        (*vy_man)--;

    if (GetAsyncKeyState (down))
        (*vy_man)++;

    if (GetAsyncKeyState (space))
    {
        condition = 1;

        *x_bullet = *x_man;

        *y_bullet = *y_man;
    }

    if (condition == 1)
       draw_bullet(*x_bullet, *y_bullet,
                    8, 80);

}


void shotter (int x, int y,
              COLORREF color_man, COLORREF color_gun)
{
    int x_head = x;
    int y_head = y - 100;

    int x_body1 = x_head;
    int y_body1 = y_head;
    int x_body2 = x_body1;
    int y_body2 = y;

    int x_leg_left1 = x_body2;
    int y_leg_left1 = y_body2;
    int x_leg_left2 = x - 14;
    int y_leg_left2 = y + 38;

    int x_leg_right1 = x_leg_left1;
    int y_leg_right1 = y_leg_left1;
    int x_leg_right2 = x + 20;
    int y_leg_right2 = y_leg_left2;

    int x_gun1 = x;
    int y_gun1 = y;
    int x_gun2 = x + 26;
    int y_gun2 = y_gun1;

    txSetFillColor (color_man);
    txSetColor ((color_man), 5);

    txCircle (x_head, y_head, 10);

    txLine (x_body1, y_body1, x_body2, y_body2);

    txLine (x_leg_left1, y_leg_left1, x_leg_left2, y_leg_left2);
    txLine (x_leg_right1, y_leg_right1, x_leg_right2, y_leg_right2);

    txSetFillColor (color_gun);
    txSetColor (color_gun, 5);
    txLine (x_gun1, y_gun1, x_gun2, y_gun2);
}


void draw_ball_3d(int x, int y,
                  int r,
                  COLORREF color_bullet)
{
    txSetColor (color_bullet);
    txSetFillColor (color_bullet);

    txCircle (x, y, r);
}


void draw_bullet(int x, int y,
                 int rmax,
                 int color)
{
    int t = 0;

    while (t <= 50)
    {
        int radius = rmax - (rmax / 50.0) * t;
        COLORREF color_bullet = RGB (color + (color / 25.0) * t, 0, 0);

        draw_ball_3d (x, y,
                      radius,
                      color_bullet);

        t++;
    }
}






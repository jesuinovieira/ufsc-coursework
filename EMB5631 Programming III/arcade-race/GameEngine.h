#pragma once

#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <string.h>
using namespace std;

#include <ncurses.h>

#define UP_ARR 259
#define DW_ARR 258
#define LT_ARR 260
#define RT_ARR 261
#define ESC 27

enum COLOUR
{
    BLACK = 1,
    RED = 2,
    GREEN = 3,
    YELLOW = 4,
    BLUE = 5,
    MAGENTA  = 6,
    CYAN = 7,
    WHITE = 8,
    DARK_BLUE = 9,
    DARK_GREEN = 10,
    DARK_YELLOW = 11,
    DARK_BLACK = 15
};


class olcConsoleGameEngine
{
public:
    olcConsoleGameEngine()
    {
        m_nScreenWidth = 140;
        m_nScreenHeight = 40;
        m_sAppName = L"Default";
    }

    int ConstructConsole()
    {
        initscr();
        start_color();      // Esta função torna possível o uso das cores
        getmaxyx(stdscr, m_nScreenHeight, m_nScreenWidth);    // Pega as dimensoes do terminal

        cbreak();
        noecho();
        curs_set(0);
        has_colors();
        start_color();

        nodelay(stdscr, TRUE);
        keypad(stdscr, TRUE);
        scrollok(stdscr, TRUE);

        init_pair(1, 0, 0);
        init_pair(2, 1, 1);
        init_pair(3, 2, 2);
        init_pair(4, 3, 3);
        init_pair(5, 4, 4);
        init_pair(6, 5, 5);
        init_pair(7, 6, 6);
        init_pair(8, 7, 7);

        init_color(2, 0, 300, 0);

        init_color(9, 0, 200, 550);         init_pair(9, 9, 9);          /* DARK_BLUE */
        init_color(10, 0, 204,0);            init_pair(10, 10, 10);    /* DARK_GREEN */
        init_color(11, 500, 500, 0);       init_pair(11, 11, 11);    /* DARK_YELLOW */

        init_pair(12, DARK_BLACK, 14);                                     /* Car */
        init_pair(13, DARK_BLACK, DARK_BLUE);                       /* Dados */
        init_color(14, 600, 600, 600);  init_pair(14, 14, 14);     /* PISTA */

        init_color(15, 0, 0, 0);  init_pair(15, 15, 15);                 /* DARK_BLACK */

        refresh();

        return 1;
    }

    /* User MUST OVERRIDE THESE */
    virtual bool OnUserCreate() = 0;
    virtual bool OnUserUpdate(float fElapsedTime) = 0;

    void Draw(int x, int y, string c = " ", short col = 8)
    {
            attrset(COLOR_PAIR(col));
            char ch = c[0];
            mvprintw(y, x, &ch);
    }

    void DrawString(int x, int y, string c, short col = 13)
    {
        attrset(COLOR_PAIR(col));
        const char *str = c.c_str();
        mvprintw(y, x, str);
    }

    void DrawStringAlpha(int x, int y, string c, short col = 8)
    {
        attrset(COLOR_PAIR(col));
        const char *str = c.c_str();
        mvprintw(y,x,str);
    }

    void Fill(int x1, int y1, int x2, int y2, string c = " ", short col = 8)
    {
        Clip(x1, y1);
        Clip(x2, y2);

        for (int x = x1; x < x2; x++)
            for (int y = y1; y < y2; y++)
                Draw(x, y, c, col);
    }

    void Clip(int &x, int &y)
    {
        if (x < 0) x = 0;
        if (x >= m_nScreenWidth) x = m_nScreenWidth;
        if (y < 0) y = 0;
        if (y >= m_nScreenHeight) y = m_nScreenHeight;
    }

    void Start()
    {
        m_bAtomActive = true;

        // Star the thread
        thread t = thread(&olcConsoleGameEngine::GameThread, this);

        // Tidy up
        t.join();
    }

    int ScreenWidth()
    {
        return m_nScreenWidth;
    }

    int ScreenHeight()
    {
        return m_nScreenHeight;
    }

    ~olcConsoleGameEngine()
    {
        endwin();
    }

private:
    void GameThread()
    {
        // Create user resources as part of this thread
        if (!OnUserCreate())
            return;

        auto tp1 = chrono::system_clock::now();
        auto tp2 = chrono::system_clock::now();

        // Run as fast as possible
        while (m_bAtomActive)
        {
            // Handle Timing
            tp2 = chrono::system_clock::now();
            chrono::duration<float> elapsedTime = tp2 - tp1;
            tp1 = tp2;
            float fElapsedTime = elapsedTime.count();

            // Handle Frame Update
            if (!OnUserUpdate(fElapsedTime))
                m_bAtomActive = false;
        }

       m_cvGameFinished.notify_one();
    }


protected:
    int m_nScreenWidth;
    int m_nScreenHeight;
    atomic<bool> m_bAtomActive;
    wstring m_sAppName;
    condition_variable m_cvGameFinished;
};

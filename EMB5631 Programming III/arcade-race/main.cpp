/* Pressione ESC para finalizar o jogo */

#include <iostream>
#include <cmath>

using namespace std;

#include "GameEngine.h"

class OneLoneCoder_FormulaOLC : public olcConsoleGameEngine
{
public:
    OneLoneCoder_FormulaOLC()
    {
        m_sAppName = L"Formula OLC";
    }

private:
    float fCarPos = 0.0f;
    float fDistance = 0.0f;
    float fSpeed = 0.0f;

    float fCurvature = 0.0f;
    float fTrackCurvature = 0.0f;
    float fPlayerCurvature = 0.0;
    float fTrackDistance = 0.0;

    float fCurrentLapTime = 0.0f;

    vector<pair<float,float>> vecTrack; // curvature, distance
    list<float> listLapTimes;

protected:
    virtual bool OnUserCreate()
    {
        // Define track
        vecTrack.push_back(make_pair(0.0f, 10.0f));
        vecTrack.push_back(make_pair(0.0f, 200.0f));
        vecTrack.push_back(make_pair(1.0f, 200.0f));
        vecTrack.push_back(make_pair(0.0f, 400.0f));
        vecTrack.push_back(make_pair(-1.0f, 100.0f));
        vecTrack.push_back(make_pair(0.0f, 200.0f));
        vecTrack.push_back(make_pair(-1.0f, 200.0f));
        vecTrack.push_back(make_pair(1.0f, 200.0f));
        vecTrack.push_back(make_pair(0.0f, 200.0f));
        vecTrack.push_back(make_pair(0.2f, 500.0f));
        vecTrack.push_back(make_pair(0.0f, 200.0f));

        for(auto t : vecTrack)
            fTrackDistance += t.second;

        listLapTimes = {0,0,0,0,0};
        fCurrentLapTime = 0.0f;

        return true;
    }

    virtual bool OnUserUpdate(float fElapsedTime)
    {

        switch(getch())
        {
            case UP_ARR:
                fSpeed += 2.0f * 20 * fElapsedTime;
                break;

            case DW_ARR:
                fSpeed -= 1.0f * fElapsedTime;
                break;

            case LT_ARR:
                fPlayerCurvature -= 35.0f * fElapsedTime;
                break;

            case RT_ARR:
                fPlayerCurvature += 35.0f * fElapsedTime;
                break;

            case ESC:
                m_bAtomActive = false;
                break;

            default:
                fSpeed -= 0.5f * fElapsedTime;
                break;

        }


        if (fabs(fPlayerCurvature - fTrackCurvature) >= 0.7f)
            fSpeed -= 5.0f * fElapsedTime;

        // Clamp Speed
        if (fSpeed < 0.0f)  fSpeed = 0.0f;
        if (fSpeed > 1.0f)  fSpeed = 1.0f;

        // Move car along track according to car speed
        fDistance += (50.0f * fSpeed) * fElapsedTime;

        // Get Point on track
        float fOffset = 0;
        int nTrackSection = 0;

        // Find position on track (could optimise)
        while (nTrackSection < (int)vecTrack.size() && fOffset <= fDistance)
        {
            fOffset += vecTrack[nTrackSection].second;
            nTrackSection++;
        }

        // Lap Timing and counting
        fCurrentLapTime += fElapsedTime;

        if(fDistance >= fTrackDistance){
            fDistance -= fTrackDistance;
            listLapTimes.push_front(fCurrentLapTime);
            listLapTimes.pop_back();
            fCurrentLapTime = 0.0f;
        }

        // Find position on track (could optimise)
        while (nTrackSection < int(vecTrack.size()) && fOffset <= fDistance)
        {
            fOffset += vecTrack[nTrackSection].second;
            nTrackSection++;
        }

        // Interpolate towards target track curvature
        float fTargetCurvature = vecTrack[nTrackSection - 1].first;
        float fTrackCurveDiff = (fTargetCurvature - fCurvature) * fElapsedTime * fSpeed;
        fCurvature += fTrackCurveDiff;

        fTrackCurvature += (fCurvature) * fElapsedTime * fSpeed;


        // Draw Sky - light blue and dark blue
        for (int y = 0; y < ScreenHeight() / 2; y++)
            for (int x = 0; x < ScreenWidth(); x++)
                Draw(x, y, " ", DARK_BLUE);

        // Draw Scenery - our hills are a rectified sine wave, where the phase is adjusted by the
        // Accumulated track curvature
        for (int x = 0; x < ScreenWidth(); x++)
        {
            int nHillHeight = (int)(fabs( sinf(x * 0.01f + fTrackCurvature) * 10.0f ));
            for (int y = (ScreenHeight() / 2) - nHillHeight; y < ScreenHeight() / 2; y++)
                Draw(x, y, " ", DARK_YELLOW);
        }


        for(int y = 0; y < ScreenHeight()/2; y++)
        {
            for(int x = 0; x < ScreenWidth(); x++){

                float fPerspective = (float)y / (ScreenHeight() / 2.5f);

                float fMiddlePoint = 0.5f + fCurvature * powf((1.0f - fPerspective), 3); // Representa o meio da tela, que vai de 0 a 1

                float fRoadWidth = 0.1f + fPerspective * 0.8f;
                float fClipWidth = fRoadWidth * 0.15f;

                fRoadWidth *= 0.5f;     // simetria em torno do ponto do meio

                int nLeftGrass = (fMiddlePoint - fRoadWidth - fClipWidth) * ScreenWidth();
                int nLeftClip = (fMiddlePoint - fRoadWidth) * ScreenWidth();
                int nRightGrass = (fMiddlePoint + fRoadWidth + fClipWidth) * ScreenWidth();
                int nRightClip = (fMiddlePoint + fRoadWidth) * ScreenWidth();

                int nRow = ScreenHeight() / 2 + y;

                int nGrassColour = sinf(20.0f *  powf(1.0f - fPerspective, 2) + fDistance * 0.1f) > 0.0f ? GREEN : DARK_GREEN;
                int nClipColour = sinf(80.0f *  powf(1.0f - fPerspective, 2) + fDistance) > 0.0f ? RED : WHITE;

                int nRoadColour = (nTrackSection - 1) == 0 ? WHITE : 14;

                if(x >= 0 && x < nLeftGrass)
                    Draw(x,nRow, " ", nGrassColour);
                if(x >= nLeftGrass && x < nLeftClip)
                    Draw(x,nRow, " ", nClipColour);
                if(x >= nLeftClip && x < nRightClip)
                    Draw(x,nRow, " ", nRoadColour);
                if(x >= nRightClip && x < nRightGrass)
                    Draw(x,nRow, " ", nClipColour);
                if(x >= nRightGrass && x < ScreenWidth())
                    Draw(x,nRow, " ", nGrassColour);
            }
        }

        // Draw Car
        fCarPos = fPlayerCurvature - fTrackCurvature;
        int nCarPos = ScreenWidth() / 2 + ((int)(ScreenWidth() * fCarPos) / 2.0f) - 3;
        int nCarPosY = ScreenHeight() * 0.8 - 4;

        DrawStringAlpha(nCarPos, nCarPosY + 4,   "   ||****||   ", 12);
        DrawStringAlpha(nCarPos, nCarPosY + 5,   "      **      ", 12);
        DrawStringAlpha(nCarPos, nCarPosY + 6,   "     ****     ", 12);
        DrawStringAlpha(nCarPos, nCarPosY + 7,   "||||-****-||||", 12);

        // Draw Stats
        DrawString(0, 2, "Distance: " + to_string(fDistance));
        DrawString(0, 3, "Target Curvature: " + to_string(fCurvature));
        DrawString(0, 4, "Player Curvature: " + to_string(fPlayerCurvature));
        DrawString(0, 5, "Player Speed    : " + to_string(fSpeed));
        DrawString(0, 6, "Track Curvature : " + to_string(fTrackCurvature));

        // Little lambda to turn floating point seconds into minutes:seconds:millis string
        auto disp_time = [](float t)
        {
            int nMinutes = t / 60.0f;
            int nSeconds = t - (nMinutes * 60.0f);
            int nMilliSeconds = (t - (float)nSeconds) * 1000.0f;
            return to_string(nMinutes) + ":" + to_string(nSeconds) + ":" + to_string(nMilliSeconds);
        };

        // Display current laptime
        DrawString(ScreenWidth() - 20, 1, "Lap Time " + disp_time(fCurrentLapTime));

        DrawString(ScreenWidth() - 20, 3, "Last 5 Lap Times:");

        // Display last 5 lap times
        int j = 4;
        for (auto l : listLapTimes)
        {
            DrawString(ScreenWidth() - 20, j, disp_time(l));
            j++;
        }

        DrawString(0, 0, "PRESS ESC TO EXIT");

        refresh();

        return true;
    }

};


int main(){

    OneLoneCoder_FormulaOLC game;
    game.ConstructConsole();
    game.Start();
    getch();

    return 0;
}

// g++ -std=c++14 -o main main.cpp -Wall -Wextra -Wshadow -lncurses -pthread;
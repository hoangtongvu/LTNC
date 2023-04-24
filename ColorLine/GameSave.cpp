#include "GameSave.h"


GameSave gameSave;


GameSave::GameSave()
{
}

void GameSave::Load(string fileName)
{
    ifstream saveFile("Player data/" + fileName);
    if (!saveFile)
    {
        cout << "Load save file failed" << endl;
        return;
    }
    else
    {
        string inputString;
        while (!saveFile.eof())
        {
            string label;
            int dataPosition = 0;

            getline(saveFile, inputString);
            //cout << inputString << endl;


            int i = 0;
            while (inputString[i] != ' ')
            {
                label += inputString[i];
                dataPosition++;
                i++;
            }
            dataPosition++;
            //cout << label << "_" << endl;
            //cout << dataPosition << endl;
            


            if (label == "Level")
            {
                string data;
                int length = inputString.length();
                for (int j = dataPosition; j < length; j++)
                {
                    data += inputString[j];
                }
                level = stoi(data);

            }


        }

        cout << "Loaded save file";

    }
    saveFile.close();

}


void GameSave::Write(string fileName)
{
    ofstream saveFile("Player data/" + fileName);
    saveFile << "Level " << level;
    saveFile.close();
}

GameSave::~GameSave()
{
}

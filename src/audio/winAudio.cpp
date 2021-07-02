#ifdef _WIN32
#include "../../include/JackdawAudio.h"
#include <windows.h>
#include <stdexcept>
#include <iostream>

namespace jdw
{
    void AudioManager::process()
    {
        while (active)
        {
            while (!mCommandQueue.empty())
            {
                const AudioCommand& msg = mCommandQueue.front();
                switch (msg.command)
                {
                case AudioCommand::COMMANDTYPE::OPEN:
                    if (msg.format == AudioCommand::FORMAT::MP3)
                        mciSendStringA( ("open \"" + msg.filepath + "\" type mpegvideo alias " + msg.alias).c_str() , NULL, 0, NULL);
                    else if (msg.format == AudioCommand::FORMAT::WAV)
                        mciSendStringA( ("open \"" + msg.filepath + "\" type waveaudio alias " + msg.alias).c_str() , NULL, 0, NULL);
                    break;

                case AudioCommand::COMMANDTYPE::PLAY:
                    mciSendStringA( ("play " + msg.alias + (msg.restart ? " from 0" : "") + (msg.loop ? " repeat" : "")).c_str(), NULL, 0, NULL);
                    break;

                case AudioCommand::COMMANDTYPE::STOP:
                    mciSendStringA( ("stop " + msg.alias).c_str(), NULL, 0, NULL);
                    break;

                case AudioCommand::COMMANDTYPE::CLOSE:
                    mciSendStringA(("close " + msg.alias).c_str(), NULL, 0, NULL);
                    break;  
                }
                mCommandQueue.pop();
            }
        }
    }


    std::string Sound::getAlias()
    {
        /* Alias grows one letter at a time when it reaches z */

        const int lastIndex = mLastAlias.length()-1;
        const char& lastChar = mLastAlias[lastIndex];
        if (lastChar < 'z') mLastAlias[lastIndex]++;
        else mLastAlias += 'a';
        return mLastAlias;
    }

    Sound::Sound(const std::string& filepath, bool loop)
    {
        this->loop = loop;

        char fullFilepath[MAX_PATH];
        GetFullPathNameA(filepath.c_str(), MAX_PATH, fullFilepath, nullptr);
        this->mFilepath = fullFilepath;

        const int n = filepath.length();
        const auto convertToLower = [](std::string str)
        {
            for (int i = 0; i < str.length(); i++)
            {
                str[i] = tolower(str[i]);
            }
            return str;
        };

        std::string extension = convertToLower(filepath.substr(n-3, n));

        if (extension == "wav")
            mFormat = AudioCommand::FORMAT::WAV;
        else if (extension == "mp3")
            mFormat = AudioCommand::FORMAT::MP3;
        else throw std::runtime_error("Invalid audio file format, use MP3 or WAV");

        if ((mFormat == AudioCommand::FORMAT::WAV)&&loop)
            throw std::runtime_error("Only MP3 files support looping!");

        mAlias = Sound::getAlias();

        AudioManager::mCommandQueue.push({
            AudioCommand::COMMANDTYPE::OPEN,
            mFormat,
            mFilepath,
            mAlias,
            0, 0
        });
    }

    Sound::~Sound()
    {
        AudioManager::mCommandQueue.push({
            AudioCommand::COMMANDTYPE::CLOSE,
            mFormat,
            "",
            mAlias,
        });
    }

    void Sound::play(bool restart)
    {
        AudioManager::mCommandQueue.push({
            AudioCommand::COMMANDTYPE::PLAY,
            mFormat,
            "",
            mAlias,
            restart, loop
        });
    }

    void Sound::stop()
    {
        AudioManager::mCommandQueue.push({
            AudioCommand::COMMANDTYPE::STOP,
            mFormat,
            "",
            mAlias,
        });
    }

}

#endif
#include <string>
#include <queue>

namespace jdw
{
    struct AudioCommand
    {
        enum class FORMAT
        {
            WAV,
            MP3,
        };

        enum class COMMANDTYPE
        {
            OPEN,
            PLAY,
            STOP,
            CLOSE,
        };

        COMMANDTYPE command;
        FORMAT format;
        std::string filepath, alias;
        bool restart, loop;

        AudioCommand(COMMANDTYPE command, FORMAT format, const std::string& filepath,
                     const std::string& alias, bool restart = 0, bool loop = 0) :
            command(command), format(format), filepath(filepath), alias(alias), restart(restart), loop(loop) {}

    };

    class AudioManager
    {
        inline static bool active = 1;
        inline static std::queue<AudioCommand> mCommandQueue;
        static void process();

        friend class Sound;
        friend class Application;
    };


    class Sound
    {
        inline static std::string mLastAlias = "a";
        static std::string getAlias();
    
        AudioCommand::FORMAT mFormat;
        std::string mFilepath;
        std::string mAlias;

    public:

        Sound(const std::string& filepath, bool loop = 0);
        ~Sound();

        bool loop = 0;
        void play(bool restart = true);
        void stop();
    };
}
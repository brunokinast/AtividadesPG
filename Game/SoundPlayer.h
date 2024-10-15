class SoundPlayer
{
public:
    static void Initialize();
    static void Play(const char *filePath, bool loop = false, bool async = true);
    static void Cleanup();

private:
    SoundPlayer() = delete;
    ~SoundPlayer() = delete;
};
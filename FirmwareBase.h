class FirmwareBase
{
  public:
    const char* FirmwareVersion = "1.0.0";
    char* ProgramVersion;

    FirmwareBase(char* programVersion);

    void init();
    void loop();
};
#define MAXCMD 2048

int nextIsInt(const char *cmd, int index);
void command(Buffer *buf, const char *cmd, int index);
void loadScript(Buffer *buf, char *filename);
void interpret(Buffer *buf, char *commands);

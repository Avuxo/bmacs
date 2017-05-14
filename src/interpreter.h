#define MAXCMD 2048
#define MAXREG 255 /*maximum value for integer register*/

int nextIsInt(const char *cmd, int index);
int nextIsChar(const char *cmd, int index);
int nextIsRegister(const char *cmd, int index);
int findExitBrace(unsigned int type, const char *cmd, int index);
void command(Buffer *buf, const char *cmd, int index);
void loadScript(Buffer *buf, char *filename);
void interpret(Buffer *buf, char *commands);
void incrementReg(char reg);
void decrementReg(char reg);
void setIntRegister(char reg, int value);
void setCharRegister(char reg, char value);

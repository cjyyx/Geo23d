#ifndef FRONT_INPUT_H
#define FRONT_INPUT_H

/* InputInterface init */
void FRONT_Input_Init();
/* display InputInterface
返回字符串保存在块中，记得free */
char *FRONT_Input(char *text);

#endif
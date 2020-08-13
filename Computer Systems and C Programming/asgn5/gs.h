#ifndef __GS_H__
#define __GS_H__

typedef struct GoodSpeak {
  char *oldspeak;
  char *newspeak;
} GoodSpeak;


GoodSpeak *gs_create(char *oldspeak, char *newspeak);

void gs_delete(GoodSpeak *g);

char *gs_oldspeak(GoodSpeak *g);

char *gs_newspeak(GoodSpeak *g);

#endif

#include "grokerWrapper.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

Player* parsePlayer (char *s)
{
	char *p = s;
	while (*p && (*p != ':'))
		p++;
	*p = 0;
	p++;
	
	Player *player = malloc(sizeof(Player));
	player->letzterEinsatz = atoi(s);
	player->gewonneneChips = atoi(p);
	return player;
}

char* grokerMainLoop (Wrapper *w, GROKER_CALLBACK(callback))
{
	char *l = 0;
	while (strlen(l = readLine(w)) > 0)
	{
		char *line = trim(l);
		printf("received line: %s\n", line);
		// first, search for the ; in the line
		char *p = line;
		while (*p && (*p != ';'))
			p++;
		*p = 0;
		p++;
		// now, parse the players
		Player *me = parsePlayer(line);
		Player *enemy = parsePlayer(p);
		printf("players: me(%d,%d) enemy(%d,%d)\n", me->letzterEinsatz, me->gewonneneChips, enemy->letzterEinsatz, enemy->gewonneneChips);
		// and call the ai
		Result *result = callback(me, enemy);
		printf("answer from the ai: %d\n", result->chips);
		// send the result
		char *answer = toString(result->chips);
		printf("sending answer to server: %s\n", answer);
		write(w->socketfd, answer, strlen(answer));
		free(answer);
		answer = ":";
		printf("sending separator to server\n");
		write(w->socketfd, ":", 1);
		if (result->output)
		{
			answer = escape(result->output);
			printf("sending output to server: %s\n", answer);
			write(w->socketfd, answer, strlen(answer));
			free(answer);
			//free(result->output);
		}
		printf("sending newline to server\n");
		write(w->socketfd, "\n", 1);
		
		// cleanup
		free(result);
		free(me);
		free(enemy);
		free(l);
	}
}

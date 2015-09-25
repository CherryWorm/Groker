#include "grokerWrapper.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

Player* parsePlayer (char *s)
{
	printf("parsing player: %s\n", s);
	char *p = s;
	while (*p && (*p != ':'))
		p++;
	*p = 0;
	p++;
	
	Player *player = malloc(sizeof(Player));
	player->letzterEinsatz = atoi(s);
	player->gewonneneChips = atoi(p);
	printf("        player: %d %d\n", player->letzterEinsatz, player->gewonneneChips);
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
		printf("line splitted: %s | %s\n", line, p);
		// now, parse the players
		Player *me = parsePlayer(line);
		Player *enemy = parsePlayer(p);
		printf("players: me(%d,%d) enemy(%d,%d)\n", me->letzterEinsatz, me->gewonneneChips, enemy->letzterEinsatz, enemy->gewonneneChips);
		// and call the ai
		int result = callback(me, enemy);
		printf("answer from the ai: %d\n", result);
		// send the result
		char *answer = toString(result);
		printf("sending answer to the server: %s\n", answer);
		write(w->socketfd, answer, strlen(answer));
		printf("deleting answer\n");
		free(answer);
		answer = ":--output not implemented--\n";
		write(w->socketfd, answer, strlen(answer));
		
		// cleanup
		printf("deleting me\n");
		free(me);
		printf("deleting enemy\n");
		free(enemy);
		printf("deleting l\n");
		free(l);
	}
}

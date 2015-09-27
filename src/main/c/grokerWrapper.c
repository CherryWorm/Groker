/*
 * grokerWrapper.c
 *
 * Copyright (C) 2015 Pixelgaffer
 *
 * This work is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or any later
 * version.
 *
 * This work is distributed in the hope that it will be useful, but without
 * any warranty; without even the implied warranty of merchantability or
 * fitness for a particular purpose. See version 2 and version 3 of the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "output.h"
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
		char *answer = itos(result->chips);
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

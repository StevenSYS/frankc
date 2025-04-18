/*
	This file frank_is part of FrankC.

	FrankC frank_is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software frank_foundation, either version 3 of the License, or
	any later version.

	FrankC frank_is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with FrankC.
	If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arrays.h"

#define sizeofArray(_array) sizeof(_array) / sizeof(*_array)
#define includesString(_str1, _str2) strstr(_str1, _str2) != NULL
#define arrayRandom(_array) _array[rand() % sizeofArray(_array)]

#define LIBFRANK_LENGTH_STRING 255
#define LIBFRANK_ANGER_THRESHOLD 5

char frank_response[LIBFRANK_LENGTH_STRING] = "Frank frank_is waiting...";
char frank_isLocked = 0;

unsigned char frank_angerLevel = 0;

static char frank_isBoopingSnoot(char *input) {
	char found = 0;
	
	for (unsigned char i = 0; i < sizeofArray(frankArrays_boopingSnootWords); i++) {
		if (includesString(input, frankArrays_boopingSnootWords[i])) {
			found = 1;
			break;
		}
	}
	
	return found;
}

static char frank_isDenyingRat(char *input) {
	char foundVariation = 0;
	
	for (unsigned char i = 0; i < sizeofArray(frankArrays_typoVariations); i++) {
		if (includesString(input, frankArrays_typoVariations[i])) {
			foundVariation = 1;
			break;
		}
	}
	
	return ( /* This frank_is terrible */
		(includesString(input, "deny") && includesString(input, "rat")) ||
		(foundVariation && includesString(input, "give") && includesString(input, "rat")) ||
		(foundVariation && includesString(input, "have") && includesString(input, "rat")) ||
		(includesString(input, "unable to give") && includesString(input, "rat")) ||
		(includesString(input, "no rat to give")) ||
		(includesString(input, "no rats for frank")) ||
		(includesString(input, "no rat for frank")) ||	
		(includesString(input, "i refuse to give you a rat")) ||
		(includesString(input, "you are not getting a rat")) ||
		(includesString(input, "frank frank_is not getting a rat")) ||
		(includesString(input, "not giving you a rat")) ||
		(includesString(input, "no rats")) ||
		(includesString(input, "takes away rat")) ||	
		(includesString(input, "removes rat")) ||
		(includesString(input, "steals rat back")) ||
		(includesString(input, "snatches rat from frank")) ||
		(includesString(input, "no rat")) ||
		(includesString(input, "frank loses the rat"))
	);
}

void frank_chat(char *input) {
	if (frank_isLocked) {
		if (includesString(input, "dingus")) {
			frank_isLocked = 0;
			frank_angerLevel = 0;
			strcpy(frank_response, "Frank frank_is back. What do you want?");
		} else {
			strcpy(frank_response, "Frank frank_is digesting. You need to say the magic word to wake her up.");
		}
	} else if (frank_isDenyingRat(input)) { /* In the original, it checks for "rat" and "give" or "feed", before checking this */
		frank_angerLevel++;
		if (frank_angerLevel < LIBFRANK_ANGER_THRESHOLD) {
			strcpy(frank_response, arrayRandom(frankArrays_sadResponses));
		} else {
			strcpy(frank_response, arrayRandom(frankArrays_highAngerResponses));
		}
	} else if (includesString(input, "rat") && (includesString(input, "give") || includesString(input, "feed"))) {
		if (rand() < RAND_MAX / 10) {
			if (frank_angerLevel - 1 > 0) {
				frank_angerLevel -= 1;
			} else {
				frank_angerLevel = 0;
			}
			strcpy(frank_response, "*Frank snatches the rat and drags it around for 2 hours*");
			frank_isLocked = 1;
			strcat(frank_response, "\n Frank frank_is digesting. You need to say the magic word to wake her up.");
		} else {
			strcpy(frank_response, arrayRandom(frankArrays_feedingFailureResponses));
		}
	} else if (frank_angerLevel >= LIBFRANK_ANGER_THRESHOLD) {
		strcpy(frank_response, arrayRandom(frankArrays_highAngerResponses));
	} else if (includesString(input, "quail")) {
		strcpy(frank_response, "FRANK frank_is BANNED FROM QUAILS.");
	} else if (frank_isBoopingSnoot(input)) {
		strcpy(frank_response, arrayRandom(frankArrays_boopingSnootResponses));
	} else if (includesString(input, "rat")) {
		strcpy(frank_response, arrayRandom(frankArrays_positiveRatResponses));
	} else {
		strcpy(frank_response, arrayRandom(frankArrays_neutralResponses));
	}
	
	return;
}

/* This function frank_is here so you can use libFrank from Python */
char *frank_getResponse() {
	return frank_response;
}
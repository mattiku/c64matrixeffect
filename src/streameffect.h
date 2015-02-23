/*
 * Author: Matti Kuonanoja (2015)
 */

#ifndef DATA_STREAMS_H
#define DATA_STREAMS_H

#define STREAM_COUNT 20

#define STREAM_LENGTH_MIN 5
#define STREAM_LENGTH_MAX 10

#define STREAM_DELAY_MIN 0
#define STREAM_DELAY_MAX 5

#define HEAD_LENGTH 2
#define BODY_LENGTH 2

#define CHARSET_START 64
#define CHARSET_END 127

#define MAX_EMPTY_COLUMN_SEARCH_TRIES 4

void stream_effect_init(void);
void stream_effect_update(void);

#endif // DATA_STREAMS_H
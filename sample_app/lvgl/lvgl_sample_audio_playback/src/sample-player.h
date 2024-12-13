/**
 * HMI SDK / RZ/G Linux sample program for audio playback
 *
 * Copyright (C) 2024 Renesas Electronics Corp. All rights reserved.
 */

#ifndef	SAMPLE_PLAYER_H
#define	SAMPLE_PLAYER_H

#include	<stdint.h>
#include	<stdbool.h>
#include	<gst/gst.h>


/******************************************************************************
 * Declarations and definition for sample applicaiton
 *****************************************************************************/
typedef enum {
	LSAP_FORMAT_MP3 = 0,
	LSAP_FORMAT_WAV,
	LSAP_FORMAT_AAC,
	LSAP_FORMAT_NUM
} lsap_format_t;

void *lsap_playback_loop(void *data);

int32_t lsap_play_new_file(const char *path, lsap_format_t format);
int32_t lsap_stop_playback(void);
int32_t lsap_pause_playback(void);
int32_t lsap_restart_playback(void);
int32_t lsap_quit_playback(void);


#endif	/* SAMPLE_PLAYER_H */

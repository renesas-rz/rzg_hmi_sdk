/**
 * HMI SDK / RZ/G Linux sample program for video playback
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
#define		LSVP_WINDOW_POS_X	(0)
#define		LSVP_WINDOW_POS_Y	(32)

void *lsvp_playback_loop(void *data);

int32_t lsvp_play_new_file(char *path);
int32_t lsvp_start_playback(void);
int32_t lsvp_stop_playback(void);
int32_t lsvp_pause_playback(void);
int32_t lsvp_restart_playback(void);
int32_t lsvp_quit_playback(void);


#endif	/* SAMPLE_PLAYER_H */

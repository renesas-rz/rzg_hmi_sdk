/**
 * HMI SDK / RZ/G Linux sample program for audio playback
 *
 * Copyright (C) 2024 Renesas Electronics Corp. All rights reserved.
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<pthread.h>
#include	<gst/gst.h>

#include	"sample-app.h"
#include	"sample-player.h"


typedef struct {
	GMainLoop *loop;
	GstElement *pipeline;
	GstElement *source;
	GstElement *mp3_parser;
	GstElement *mp3_decoder;
	GstElement *aac_parser;
	GstElement *aac_decoder;
	GstElement *wav_parser;
	GstElement *audioresample;
	GstElement *capsfilter;
	GstElement *sink;
	gint64 audio_length;
	void *app_data;
} UserData;

#define AUDIO_SAMPLE_RATE		44100
#define NORMAL_PLAYING_RATE		((gdouble)1.0)

#ifdef DEBUG
	#define	LOGMSG(...)	g_print(__VA_ARGS__)
#else
	#define	LOGMSG(...)
#endif

static UserData user_data;
static pthread_mutex_t mutex_gst_data = PTHREAD_MUTEX_INITIALIZER;

static gboolean bus_call(GstBus *bus, GstMessage *msg, gpointer data)
{
	UserData *u_data = (UserData *)data;
	GMainLoop *loop = u_data->loop;
	gchar *debug;
	GError *error;

	switch (GST_MESSAGE_TYPE (msg)) {
	case GST_MESSAGE_ERROR:
		gst_message_parse_error(msg, &error, &debug);
		g_free(debug);
		g_printerr("Error: %s\n", error->message);
		g_error_free(error);
		g_main_loop_quit(loop);
		/* call sample app api to inform error */
		lsap_quit_with_error();
		break;
	case GST_MESSAGE_EOS:
		/* call sample app api to inform eos */
		lsap_complete_playing();
		break;
	default:
		break;
	}
	return TRUE;
}

static GstState wait_for_state_change_completed (GstElement * pipeline)
{
	GstState current_state = GST_STATE_VOID_PENDING;
	GstStateChangeReturn state_change_return = GST_STATE_CHANGE_ASYNC;
	do {
		state_change_return = gst_element_get_state(pipeline, &current_state,
								NULL, GST_CLOCK_TIME_NONE);
	} while (state_change_return == GST_STATE_CHANGE_ASYNC);
	return current_state;
}

int32_t lsap_quit_playback(void)
{
	UserData *data = &user_data;
	GstState current_state;

	pthread_mutex_lock(&mutex_gst_data);

	current_state = wait_for_state_change_completed(data->pipeline);
	g_main_loop_quit(data->loop);

	pthread_mutex_unlock(&mutex_gst_data);

	return 0;
}

int32_t lsap_restart_playback(void)
{
	UserData *data = &user_data;
	GstState current_state;

	pthread_mutex_lock(&mutex_gst_data);

	current_state = wait_for_state_change_completed(data->pipeline);
	if (current_state == GST_STATE_PAUSED) {
		gst_element_set_state (data->pipeline, GST_STATE_PLAYING);
	}

	pthread_mutex_unlock(&mutex_gst_data);

	return 0;
}

int32_t lsap_pause_playback(void)
{
	UserData *data = &user_data;
	GstState current_state;

	pthread_mutex_lock(&mutex_gst_data);

	current_state = wait_for_state_change_completed(data->pipeline);
	if (current_state == GST_STATE_PLAYING) {
		gst_element_set_state (data->pipeline, GST_STATE_PAUSED);
	}

	pthread_mutex_unlock(&mutex_gst_data);

	return 0;
}

int32_t lsap_stop_playback(void)
{
	UserData *data = &user_data;
	GstState current_state;
	int32_t ret_val = 0;

	pthread_mutex_lock(&mutex_gst_data);

	current_state = wait_for_state_change_completed(data->pipeline);
	if (current_state == GST_STATE_PLAYING) {
		gst_element_set_state (data->pipeline, GST_STATE_PAUSED);
	}
	if (!gst_element_seek(data->pipeline, NORMAL_PLAYING_RATE, GST_FORMAT_TIME,
					GST_SEEK_FLAG_FLUSH, GST_SEEK_TYPE_SET, 0,
					GST_SEEK_TYPE_NONE, GST_CLOCK_TIME_NONE)) {
		ret_val = -1;
	}

	pthread_mutex_unlock(&mutex_gst_data);

	return ret_val;
}

int32_t lsap_play_new_file(const char *path, lsap_format_t format)
{
	UserData *data = &user_data;
	GstState current_state;
	GstElement *source;
	GstElement *parser;
	GstElement *decoder;
	GstElement *audioresample;
	GstElement *capsfilter;
	GstElement *sink;
	gboolean ret = FALSE;
	int32_t ret_val = 0;
	static lsap_format_t prev_fmt = LSAP_FORMAT_NUM;

	pthread_mutex_lock(&mutex_gst_data);

	current_state = wait_for_state_change_completed(data->pipeline);
	if (current_state == GST_STATE_PLAYING) {
		gst_element_set_state(data->pipeline, GST_STATE_PAUSED);
		/* Seek to start and flush all old data */
		gst_element_seek_simple (data->pipeline, GST_FORMAT_TIME,
						GST_SEEK_FLAG_FLUSH, 0);
	}

	/* Seek to start and flush all old data */
	gst_element_seek_simple(data->pipeline, GST_FORMAT_TIME,
						GST_SEEK_FLAG_FLUSH, 0);
	gst_element_set_state(data->pipeline, GST_STATE_READY);

	/* wait until the changing is complete */
	gst_element_get_state(data->pipeline, NULL, NULL, GST_CLOCK_TIME_NONE);

	/* Remove the previous elements */
	/* We need to call gst_bin_get_by_name() to keep the elements existing
	 * after we call get_bin_remove().*/
	source = gst_bin_get_by_name(GST_BIN (data->pipeline), "file-source");
	if (NULL != source) {
		ret = gst_bin_remove(GST_BIN (data->pipeline), data->source);
		LOGMSG("gst_bin_remove source from pipeline: %s\n",
					(ret) ? ("SUCCEEDED") : ("FAILED"));
	}
	audioresample = gst_bin_get_by_name(GST_BIN (data->pipeline),
							"audio-resample");
	if (NULL != audioresample) {
		ret = gst_bin_remove(GST_BIN (data->pipeline),
							data->audioresample);
		LOGMSG("gst_bin_remove audioresample from pipeline: %s\n",
					(ret) ? ("SUCCEEDED") : ("FAILED"));
	}
	capsfilter = gst_bin_get_by_name(GST_BIN (data->pipeline),
							"resample_capsfilter");
	if (NULL != capsfilter) {
		ret = gst_bin_remove(GST_BIN (data->pipeline),
							data->capsfilter);
		LOGMSG("gst_bin_remove capsfilter from pipeline: %s\n",
					(ret) ? ("SUCCEEDED") : ("FAILED"));
	}
	sink = gst_bin_get_by_name(GST_BIN (data->pipeline), "audio-output");
	if (NULL != sink) {
		ret = gst_bin_remove(GST_BIN (data->pipeline), data->sink);
		LOGMSG("gst_bin_remove sink from pipeline: %s\n",
					(ret) ? ("SUCCEEDED") : ("FAILED"));
	}

	switch (prev_fmt) {
	case LSAP_FORMAT_MP3:
		parser = gst_bin_get_by_name(GST_BIN (data->pipeline),
							"mp3-parser");
		if (NULL != parser) {
			ret = gst_bin_remove(GST_BIN (data->pipeline),
							data->mp3_parser);
			LOGMSG("gst_bin_remove parser from pipeline: %s\n",
					(ret) ? ("SUCCEEDED") : ("FAILED"));
		}
		decoder = gst_bin_get_by_name(GST_BIN (data->pipeline),
							"mp3-decoder");
		if (NULL != decoder) {
			ret = gst_bin_remove(GST_BIN (data->pipeline),
							data->mp3_decoder);
			LOGMSG("gst_bin_remove decoder from pipeline: %s\n",
					(ret) ? ("SUCCEEDED") : ("FAILED"));
		}
		break;
	case LSAP_FORMAT_WAV:
		parser = gst_bin_get_by_name(GST_BIN (data->pipeline),
							"wav-parser");
		if (NULL != parser) {
			ret = gst_bin_remove(GST_BIN (data->pipeline),
							data->wav_parser);
			LOGMSG("gst_bin_remove parser from pipeline: %s\n",
					(ret) ? ("SUCCEEDED") : ("FAILED"));
		}
		break;
	case LSAP_FORMAT_AAC:
		parser = gst_bin_get_by_name(GST_BIN (data->pipeline),
							"aac-parser");
		if (NULL != parser) {
			ret = gst_bin_remove(GST_BIN (data->pipeline),
							data->aac_parser);
			LOGMSG("gst_bin_remove parser from pipeline: %s\n",
					(ret) ? ("SUCCEEDED") : ("FAILED"));
		}
		decoder = gst_bin_get_by_name(GST_BIN (data->pipeline),
							"aac-decoder");
		if (NULL != decoder) {
			ret = gst_bin_remove(GST_BIN (data->pipeline),
							data->aac_decoder);
			LOGMSG("gst_bin_remove decoder from pipeline: %s\n",
					(ret) ? ("SUCCEEDED") : ("FAILED"));
		}
		break;
	default:
		break;
	}

	/* Update file location */
	g_object_set(G_OBJECT (data->source), "location", (gchar *)path, NULL);

	/* Add the elements into the pipeline and then link them together */
	switch (format) {
	case LSAP_FORMAT_MP3:
		gst_bin_add_many(GST_BIN (data->pipeline), data->source,
				data->mp3_parser, data->mp3_decoder,
				data->audioresample, data->capsfilter,
				data->sink, NULL);
		if (gst_element_link_many(data->source,
				data->mp3_parser, data->mp3_decoder,
				data->audioresample, data->capsfilter,
				data->sink, NULL) != TRUE) {
			g_print("Elements could not be linked.\n");
			gst_object_unref(data->pipeline);
			ret_val = -1;
		}
		break;
	case LSAP_FORMAT_WAV:
		gst_bin_add_many(GST_BIN (data->pipeline), data->source,
				data->wav_parser,
				data->audioresample, data->capsfilter,
				data->sink, NULL);
		if (gst_element_link_many(data->source,
				data->wav_parser,
				data->audioresample, data->capsfilter,
				data->sink, NULL) != TRUE) {
			g_print("Elements could not be linked.\n");
			gst_object_unref(data->pipeline);
			ret_val = -1;
		}
		break;
	case LSAP_FORMAT_AAC:
		gst_bin_add_many(GST_BIN (data->pipeline), data->source,
				data->aac_parser, data->aac_decoder,
				data->audioresample, data->capsfilter,
				data->sink, NULL);
		if (gst_element_link_many(data->source,
				data->aac_parser, data->aac_decoder,
				data->audioresample, data->capsfilter,
				data->sink, NULL) != TRUE) {
			g_print("Elements could not be linked.\n");
			gst_object_unref(data->pipeline);
			ret_val = -1;
		}
		break;
	default:
		g_printerr("ERROR!! An unsupported format was specified.\n");
		ret_val = -1;
		break;
	}

	/* Set the pipeline to "playing" state */
	if (gst_element_set_state(data->pipeline, GST_STATE_PLAYING) ==
						GST_STATE_CHANGE_FAILURE) {
		g_printerr("Unable to set the pipeline to playing state.\n");
		gst_object_unref(data->pipeline);
		ret_val = -1;
	}

	/* Wait the state become PLAYING to get the audio length */
	gst_element_get_state(data->pipeline, NULL, NULL, GST_CLOCK_TIME_NONE);
	gst_element_query_duration(data->pipeline, GST_FORMAT_TIME,
							&(data->audio_length));
	/* Save the latest format */
	prev_fmt = format;

	pthread_mutex_unlock(&mutex_gst_data);

	return ret_val;
}

void *lsap_playback_loop(void *data)
{
	GstCaps *caps;
	GstBus *bus;
	guint bus_watch_id;

	/* Initialization */
	gst_init(NULL, NULL);
	user_data.loop = g_main_loop_new(NULL, FALSE);

	/* Create GStreamer elements */
	user_data.pipeline = gst_pipeline_new("audio-player");
	user_data.source = gst_element_factory_make("filesrc", "file-source");
	user_data.mp3_parser = gst_element_factory_make("mpegaudioparse", "mp3-parser");
	user_data.mp3_decoder = gst_element_factory_make("mpg123audiodec", "mp3-decoder");
	user_data.aac_parser = gst_element_factory_make("aacparse", "aac-parser");
	user_data.aac_decoder = gst_element_factory_make("faad", "aac-decoder");
	user_data.wav_parser = gst_element_factory_make("wavparse", "wav-parser");
	user_data.audioresample = gst_element_factory_make("audioresample", "audio-resample");
	user_data.capsfilter = gst_element_factory_make("capsfilter", "resample_capsfilter");
	user_data.sink = gst_element_factory_make("alsasink", "audio-output");
	user_data.audio_length = 0;

	if (!user_data.pipeline || !user_data.source ||
			!user_data.mp3_parser || !user_data.mp3_decoder ||
			!user_data.aac_parser || !user_data.aac_decoder ||
			!user_data.wav_parser || !user_data.audioresample ||
			!user_data.capsfilter || !user_data.sink) {
		g_printerr("One element could not be created. Exiting.\n");
		return NULL;
	}

	/* Set the caps option to the caps-filter element */
	caps = gst_caps_new_simple("audio/x-raw", "rate", G_TYPE_INT,
						AUDIO_SAMPLE_RATE, NULL);
	g_object_set(G_OBJECT (user_data.capsfilter), "caps", caps, NULL);
	gst_caps_unref(caps);

	/* Set up the pipeline */
	/* we add a message handler */
	bus = gst_pipeline_get_bus(GST_PIPELINE (user_data.pipeline));
	bus_watch_id = gst_bus_add_watch(bus, bus_call, &user_data);
	gst_object_unref(bus);

	/* Iterate */
	g_main_loop_run(user_data.loop);

	/* Out of the main loop, clean up nicely */
	gst_element_set_state(user_data.pipeline, GST_STATE_NULL);

	g_print("Deleting pipeline...\n");
	gst_object_unref(GST_OBJECT (user_data.pipeline));
	g_source_remove(bus_watch_id);
	g_main_loop_unref(user_data.loop);

	return NULL;
}

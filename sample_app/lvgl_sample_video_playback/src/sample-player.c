/**
 * HMI SDK / RZ/G Linux sample program for video playback
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
	GstElement *demuxer;
	GstElement *audio_queue;
	GstElement *audio_decoder;
	GstElement *audio_resample;
	GstElement *audio_capsfilter;
	GstElement *audio_sink;
	GstElement *video_queue;
	GstElement *video_parser;
	GstElement *video_decoder;
	GstElement *video_filter;
	GstElement *video_capsfilter;
	GstElement *video_sink;
	gint64 media_length;
	int32_t audio;
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
static pthread_cond_t cond_gst_data = PTHREAD_COND_INITIALIZER;

static gboolean bus_call(GstBus *bus, GstMessage *msg, gpointer data)
{
	UserData *u_data = (UserData *)data;
	GMainLoop *loop = u_data->loop;
	gchar *debug;
	GError *error;

	switch (GST_MESSAGE_TYPE(msg)) {
	case GST_MESSAGE_ERROR:
		gst_message_parse_error(msg, &error, &debug);
		g_free(debug);
		g_printerr("Error: %s\n", error->message);
		g_error_free(error);
		g_main_loop_quit(loop);
		/* call sample app api to inform error */
		lsvp_quit_with_error();
		break;
	case GST_MESSAGE_EOS:
		/* call sample app api to inform eos */
		lsvp_complete_playing();
		break;
	default:
		break;
	}
	return TRUE;
}

static GstState wait_for_state_change_completed(GstElement * pipeline)
{
	GstState current_state = GST_STATE_VOID_PENDING;
	GstStateChangeReturn state_change_return = GST_STATE_CHANGE_ASYNC;
	do {
		state_change_return = gst_element_get_state(pipeline, &current_state,
								NULL, GST_CLOCK_TIME_NONE);
	} while (state_change_return == GST_STATE_CHANGE_ASYNC);
	return current_state;
}

int32_t lsvp_quit_playback(void)
{
	UserData *data = &user_data;
	GstState current_state;

	pthread_mutex_lock(&mutex_gst_data);

	current_state = wait_for_state_change_completed(data->pipeline);
	g_main_loop_quit(data->loop);

	pthread_mutex_unlock(&mutex_gst_data);

	return 0;
}

int32_t lsvp_restart_playback(void)
{
	UserData *data = &user_data;
	GstState current_state;

	pthread_mutex_lock(&mutex_gst_data);

	current_state = wait_for_state_change_completed(data->pipeline);
	if (current_state == GST_STATE_PAUSED) {
		gst_element_set_state(data->pipeline, GST_STATE_PLAYING);
	}

	pthread_mutex_unlock(&mutex_gst_data);

	return 0;
}

int32_t lsvp_pause_playback(void)
{
	UserData *data = &user_data;
	GstState current_state;

	pthread_mutex_lock(&mutex_gst_data);

	current_state = wait_for_state_change_completed(data->pipeline);
	if (current_state == GST_STATE_PLAYING) {
		gst_element_set_state(data->pipeline, GST_STATE_PAUSED);
	}

	pthread_mutex_unlock(&mutex_gst_data);

	return 0;
}

int32_t lsvp_stop_playback(void)
{
	UserData *data = &user_data;
	GstState current_state;

	pthread_mutex_lock(&mutex_gst_data);

	current_state = wait_for_state_change_completed(data->pipeline);
	if (current_state == GST_STATE_PLAYING) {
		gst_element_set_state(data->pipeline, GST_STATE_PAUSED);
	}
	/* gst_element_seek() cannot be called here. */

	pthread_mutex_unlock(&mutex_gst_data);

	return 0;
}

int32_t lsvp_play_new_file(char *path)
{
	UserData *data = &user_data;
	GstState current_state;
	GstElement *pipeline;
	GstElement *source;
	GstElement *video_queue;
	GstElement *audio_resample;
	GstElement *audio_capsfilter;
	GstElement *audio_queue;
	GstElement *audio_decoder;
	GstElement *audio_sink;
	gboolean ret = FALSE;
	int32_t ret_val = 0;

	pthread_mutex_lock(&mutex_gst_data);

	pipeline = data->pipeline;
	source = data->source;
	video_queue = data->video_queue;
	audio_resample = data->audio_resample;
	audio_capsfilter = data->audio_capsfilter;
	audio_queue = data->audio_queue;
	audio_decoder = data->audio_decoder;
	audio_sink = data->audio_sink;

	current_state = wait_for_state_change_completed(pipeline);
	if (current_state == GST_STATE_PLAYING) {
		gst_element_set_state(pipeline, GST_STATE_PAUSED);
		/* Seek to start and flush all old data */
		gst_element_seek_simple(pipeline, GST_FORMAT_TIME,
						GST_SEEK_FLAG_FLUSH, 0);
	}

	gst_element_set_state (pipeline, GST_STATE_NULL);
	/* wait until the changing is complete */
	gst_element_get_state (pipeline, NULL, NULL, GST_CLOCK_TIME_NONE);

	if (data->audio) {
		/* Unlink and remove audio elements */
		/* Keep the element to still exist after removing */
		audio_queue = gst_bin_get_by_name (GST_BIN (pipeline),
							"audio-queue");
		if (NULL != audio_queue) {
			ret = gst_bin_remove (GST_BIN (pipeline),
							data->audio_queue);
			LOGMSG("gst_bin_remove audio_queue from pipeline: %s\n",
					(ret) ? ("SUCCEEDED") : ("FAILED"));
		}
		/* Keep the element to still exist after removing */
		audio_decoder = gst_bin_get_by_name (GST_BIN (pipeline),
							"aac-decoder");
		if (NULL != audio_decoder) {
			ret = gst_bin_remove (GST_BIN (pipeline),
							data->audio_decoder);
			LOGMSG("gst_bin_remove audio_decoder from pipeline: %s\n",
					(ret) ? ("SUCCEEDED") : ("FAILED"));
		}
		audio_resample = gst_bin_get_by_name (GST_BIN (pipeline),
							"audio-resample");
		if (NULL != audio_resample) {
			ret = gst_bin_remove (GST_BIN (pipeline),
							data->audio_resample);
			LOGMSG("gst_bin_remove audio_resample from pipeline: %s\n",
					(ret) ? ("SUCCEEDED") : ("FAILED"));
		}
		audio_capsfilter = gst_bin_get_by_name (GST_BIN (pipeline),
							"audio-capsfilter");
		if (NULL != audio_capsfilter) {
			ret = gst_bin_remove (GST_BIN (pipeline),
						data->audio_capsfilter);
			LOGMSG("gst_bin_remove audio_capsfilter from pipeline: %s\n",
					(ret) ? ("SUCCEEDED") : ("FAILED"));
		}
		/* Keep the element to still exist after removing */
		audio_sink = gst_bin_get_by_name (GST_BIN (pipeline),
							"audio-output");
		if (NULL != audio_sink) {
			ret = gst_bin_remove (GST_BIN (pipeline),
							data->audio_sink);
			LOGMSG("gst_bin_remove audio_sink from pipeline: %s\n",
					(ret) ? ("SUCCEEDED") : ("FAILED"));
		}
	}
	/* Unlink and remove video elements */
	/* Keep the element to still exist after removing */
	video_queue = gst_bin_get_by_name (GST_BIN (pipeline), "video-queue");
	if (NULL != video_queue) {
		ret = gst_bin_remove (GST_BIN (pipeline), data->video_queue);
		LOGMSG("gst_bin_remove video_queue from pipeline: %s\n",
					(ret) ? ("SUCCEEDED") : ("FAILED"));
	}

	/* Remove video-parser completely */
	if (data->video_parser != NULL) {
		ret = gst_bin_remove (GST_BIN (pipeline), data->video_parser);
		LOGMSG("gst_bin_remove video_parser from pipeline: %s\n",
					(ret) ? ("SUCCEEDED") : ("FAILED"));
		if (TRUE == ret) {
			data->video_parser = NULL;
		}
	}

	/* Remove video-decoder completely */
	if (data->video_decoder != NULL) {
		ret = gst_bin_remove (GST_BIN (pipeline), data->video_decoder);
		LOGMSG("gst_bin_remove video_decoder from pipeline: %s\n",
					(ret) ? ("SUCCEEDED") : ("FAILED"));
		if (TRUE == ret) {
			data->video_decoder = NULL;
		}
	}

	/* Remove waylandsink completely */
	if (data->video_sink != NULL) {
		ret = gst_bin_remove (GST_BIN (pipeline), data->video_sink);
		LOGMSG("gst_bin_remove video_sink from pipeline: %s\n",
					(ret) ? ("SUCCEEDED") : ("FAILED"));
		if (TRUE == ret) {
			data->video_sink = NULL;
		}
	}

	/* Update file location */
	g_object_set (G_OBJECT (source), "location", path, NULL);

	/* Set the pipeline to "playing" state */
	gst_element_set_state (pipeline, GST_STATE_PLAYING);

	/* Wait for all pad added - no_more_pads signaled */
	pthread_cond_wait (&cond_gst_data, &mutex_gst_data);
	/* Wait the state become PLAYING to get the video length */
	gst_element_get_state (data->pipeline, NULL, NULL, GST_CLOCK_TIME_NONE);
	gst_element_query_duration (data->pipeline, GST_FORMAT_TIME,
								&(data->media_length));

	pthread_mutex_unlock(&mutex_gst_data);

	return ret_val;
}

/* Call back functions */
static void on_pad_added(GstElement * element, GstPad * pad, gpointer data)
{
	GstPad *sinkpad = NULL;
	GstCaps *new_pad_caps = NULL;
	GstStructure *new_pad_struct = NULL;
	const gchar *new_pad_type = NULL;
	UserData *puser_data =(UserData *)data;

	new_pad_caps = gst_pad_query_caps(pad, NULL);
	new_pad_struct = gst_caps_get_structure(new_pad_caps, 0);
	new_pad_type = gst_structure_get_name(new_pad_struct);

	GstState currentState;
	GstState pending;

	pthread_mutex_lock(&mutex_gst_data);

	if (puser_data->audio && g_str_has_prefix(new_pad_type, "audio")) {
		/* Need to set Gst State to PAUSED before change state from NULL to
		* PLAYING */
		gst_element_get_state(puser_data->audio_queue, &currentState, &pending,
		GST_CLOCK_TIME_NONE);
		if (currentState == GST_STATE_NULL){
			gst_element_set_state(puser_data->audio_queue, GST_STATE_PAUSED);
		}
		gst_element_get_state(puser_data->audio_decoder, &currentState, &pending,
		GST_CLOCK_TIME_NONE);
		if (currentState == GST_STATE_NULL){
			gst_element_set_state(puser_data->audio_decoder, GST_STATE_PAUSED);
		}
		gst_element_get_state(puser_data->audio_resample, &currentState, &pending,
									GST_CLOCK_TIME_NONE);
		if (currentState == GST_STATE_NULL){
			gst_element_set_state(puser_data->audio_resample, GST_STATE_PAUSED);
		}
		gst_element_get_state(puser_data->audio_capsfilter, &currentState,
								&pending, GST_CLOCK_TIME_NONE);
		if (currentState == GST_STATE_NULL){
			gst_element_set_state(puser_data->audio_capsfilter, GST_STATE_PAUSED);
		}
		gst_element_get_state(puser_data->audio_sink, &currentState, &pending,
									GST_CLOCK_TIME_NONE);
		if (currentState == GST_STATE_NULL){
			gst_element_set_state(puser_data->audio_sink, GST_STATE_PAUSED);
		}

		/* Add back audio_queue, audio_decoder, audio_resample, audio_capsfilter,
		* and audio_sink */
		gst_bin_add_many(GST_BIN(puser_data->pipeline),
			puser_data->audio_queue, puser_data->audio_decoder,
			puser_data->audio_resample, puser_data->audio_capsfilter,
			puser_data->audio_sink, NULL);

		/* Link audio_queue -> audio_decoder -> audio_resample -> audio_capsfilter
		* -> audio_sink */
		if (gst_element_link_many(puser_data->audio_queue,
			puser_data->audio_decoder, puser_data->audio_resample,
			puser_data->audio_capsfilter, puser_data->audio_sink,
			NULL) != TRUE) {
			g_print("audio_queue, audio_decoder, audio_resample, " \
			"audio_capsfilter, Sand audio_sink could not be linked.\n");
		}

		/* In case link this pad with the AAC-decoder sink pad */
		sinkpad = gst_element_get_static_pad(puser_data->audio_queue, "sink");
		if (GST_PAD_LINK_OK != gst_pad_link(pad, sinkpad)) {
			g_print("Audio link failed\n");
		}
		gst_object_unref(sinkpad);
		if (new_pad_caps != NULL)
			gst_caps_unref(new_pad_caps);

		/* Change the pipeline to PLAYING state
		* TODO: The below statement temporarily fixes issue "Unable to pause the
		* video".
		* The root cause is still unknown.
		*/
		gst_element_set_state(puser_data->pipeline, GST_STATE_PLAYING);
	}
	else if (g_str_has_prefix(new_pad_type, "video")) {
		/* Recreate waylandsink */
		if (NULL == puser_data->video_sink) {
			puser_data->video_sink =
			gst_element_factory_make("waylandsink", "video-output");

			/* Set position for displaying (0, 0) */
			g_object_set(G_OBJECT(puser_data->video_sink),
				"position-x", LSVP_WINDOW_POS_X, "position-y",
				LSVP_WINDOW_POS_Y, NULL);
		}

		/* Create decoder and parser for H264 video */
		if (g_str_has_prefix(new_pad_type, "video/x-h264")) {
			/* Recreate video-parser */
			if (NULL == puser_data->video_parser) {
			puser_data->video_parser =
			gst_element_factory_make("h264parse", "h264-parser");
			}
			/* Recreate video-decoder */
			if (NULL == puser_data->video_decoder) {
				puser_data->video_decoder =
				gst_element_factory_make("omxh264dec", "omxh264-decoder");
			}
		} else {
			g_print("Unsupported video format\n");
			g_main_loop_quit(puser_data->loop);
		}

		/* Need to set Gst State to PAUSED before change state from NULL to
		* PLAYING */
		gst_element_get_state(puser_data->video_queue, &currentState, &pending,
							GST_CLOCK_TIME_NONE);
		if (currentState == GST_STATE_NULL){
			gst_element_set_state(puser_data->video_queue, GST_STATE_PAUSED);
		}
		gst_element_get_state(puser_data->video_parser, &currentState, &pending,
							GST_CLOCK_TIME_NONE);
		if (currentState == GST_STATE_NULL){
			gst_element_set_state(puser_data->video_parser, GST_STATE_PAUSED);
		}
		gst_element_get_state(puser_data->video_decoder, &currentState, &pending,
							GST_CLOCK_TIME_NONE);
		if (currentState == GST_STATE_NULL){
			gst_element_set_state(puser_data->video_decoder, GST_STATE_PAUSED);
		}
		gst_element_get_state(puser_data->video_sink, &currentState, &pending,
							GST_CLOCK_TIME_NONE);
		if (currentState == GST_STATE_NULL){
			gst_element_set_state(puser_data->video_sink, GST_STATE_PAUSED);
		}

		/* Add back video_queue, video_parser, video_decoder, and video_sink */
		gst_bin_add_many(GST_BIN(puser_data->pipeline),
			puser_data->video_queue, puser_data->video_parser,
			puser_data->video_decoder, puser_data->video_sink, NULL);

		/* Link video_queue -> video_parser -> video_decoder -> video_sink */
		if (gst_element_link_many(puser_data->video_queue,
			puser_data->video_parser, puser_data->video_decoder,
			puser_data->video_sink, NULL) != TRUE) {
			g_print("video_queue, video_parser, video_decoder and video_sink " \
			"could not be linked.\n");
		}

		/* In case link this pad with the omxh264-decoder sink pad */
		sinkpad = gst_element_get_static_pad(puser_data->video_queue, "sink");
		if (GST_PAD_LINK_OK != gst_pad_link(pad, sinkpad)) {
			g_print("Video link failed\n");
		}
		gst_object_unref(sinkpad);
		if (new_pad_caps != NULL)
			gst_caps_unref(new_pad_caps);

		/* Change the pipeline to PLAYING state
		* TODO: The below statement temporarily fixes issue "Unable to pause the
		* video".
		* The root cause is still unknown.
		*/
		gst_element_set_state(puser_data->pipeline, GST_STATE_PLAYING);
	}
	/* Signal the dynamic pad linked */
	pthread_mutex_unlock(&mutex_gst_data);
}

static void no_more_pads(GstElement * element, gpointer data)
{
	pthread_mutex_lock(&mutex_gst_data);
	pthread_cond_signal(&cond_gst_data);
	pthread_mutex_unlock(&mutex_gst_data);
}

void *lsvp_playback_loop(void *data)
{
	GstCaps *caps;
	GstBus *bus;
	guint bus_watch_id;

	/* Initialization */
	gst_init(NULL, NULL);
	user_data.loop = g_main_loop_new(NULL, FALSE);
	user_data.audio = *(int32_t *)data;

	/* Create GStreamer elements */
	user_data.pipeline = gst_pipeline_new("video-player");
	user_data.source = gst_element_factory_make("filesrc", "file-source");
	user_data.demuxer = gst_element_factory_make("qtdemux", "qt-demuxer");
	if (!user_data.pipeline || !user_data.source || !user_data.demuxer) {
		g_printerr("One element could not be created. Exiting.\n");
		return NULL;
	}
	/* elements for Video thread */
	user_data.video_queue = gst_element_factory_make("queue", "video-queue");
	user_data.video_sink = NULL;
	if (!user_data.video_queue) {
		g_printerr("One element for video could not be created."
								" Exiting.\n");
		return NULL;
	}
	/* elements for Audio thread */
	if (user_data.audio) {
		user_data.audio_queue =
			gst_element_factory_make("queue", "audio-queue");
		user_data.audio_decoder =
			gst_element_factory_make("faad", "aac-decoder");
		user_data.audio_resample =
			gst_element_factory_make("audioresample",
						"audio-resample");
		user_data.audio_capsfilter =
			gst_element_factory_make("capsfilter",
						"audio-capsfilter");
		user_data.audio_sink =
			gst_element_factory_make("alsasink", "audio-output");

		if (!user_data.audio_queue || !user_data.audio_decoder ||
			!user_data.audio_resample ||
			!user_data.audio_capsfilter || !user_data.audio_sink) {
			g_printerr("One element for audio could not be created."
								" Exiting.\n");
			return NULL;
		}
		/* Set the caps option to the caps-filter element */
		caps = gst_caps_new_simple("audio/x-raw", "rate", G_TYPE_INT,
						AUDIO_SAMPLE_RATE, NULL);
		g_object_set(G_OBJECT(user_data.audio_capsfilter), "caps",
								caps, NULL);
		gst_caps_unref(caps);

		/* Add all created elements into the pipeline */
		gst_bin_add_many(GST_BIN(user_data.pipeline),
			user_data.source, user_data.demuxer,
			user_data.video_queue,
			user_data.audio_queue, user_data.audio_decoder,
			user_data.audio_resample, user_data.audio_capsfilter,
			user_data.audio_sink, NULL);
	}
	else {
		/* Add all created elements into the pipeline */
		gst_bin_add_many(GST_BIN(user_data.pipeline),
				user_data.source, user_data.demuxer,
				user_data.video_queue, NULL);
	}

	if (gst_element_link(user_data.source, user_data.demuxer) != TRUE) {
		g_printerr("File source could not be linked.\n");
		gst_object_unref(user_data.pipeline);
		return NULL;
	}

	user_data.video_parser = NULL;
	user_data.video_decoder = NULL;
	user_data.media_length = 0;

	/* Set up the pipeline */
	/* we add a message handler */
	bus = gst_pipeline_get_bus(GST_PIPELINE(user_data.pipeline));
	bus_watch_id = gst_bus_add_watch(bus, bus_call, &user_data);
	gst_object_unref(bus);

	g_signal_connect(user_data.demuxer, "pad-added",
					G_CALLBACK(on_pad_added), &user_data);
	g_signal_connect(user_data.demuxer, "no-more-pads",
					G_CALLBACK(no_more_pads), NULL);

	/* Iterate */
	g_main_loop_run(user_data.loop);

	/* Out of the main loop, clean up nicely */
	gst_element_set_state(user_data.pipeline, GST_STATE_NULL);

	g_print("Deleting pipeline...\n");
	gst_object_unref(GST_OBJECT(user_data.pipeline));
	g_source_remove(bus_watch_id);
	g_main_loop_unref(user_data.loop);

	return NULL;
}

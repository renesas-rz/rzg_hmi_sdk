#include	<json-glib/json-glib.h>
#include	"include/read_conf.h"

void read_conf(ui_framework_info_st *ui_framework_info)
{
	int ui_framework_cnt;
	int disc_str_cnt;
	const gchar *disc;
	JsonParser *parser;
	JsonNode *root;
	JsonObject *root_obj;
	JsonArray *root_ary;
	GError *error = NULL;
	int i = 0;

	guint apps_info_cnt;

	parser = json_parser_new();

	if(!json_parser_load_from_file (parser, "/usr/share/demo-launcher/demo-launcher.json", &error))
	{
		g_print("can't load config_file");
	}
	root = json_parser_get_root (parser);
	root_ary = json_node_get_array(root);

	/*  read file */
	ui_framework_cnt = json_array_get_length(root_ary);

	if(ui_framework_cnt > MAX_UI_FRAMEWORKS)
	{
		ui_framework_cnt = MAX_UI_FRAMEWORKS;
	}
	for(i = 0; i < ui_framework_cnt; i++)
	{
		ui_framework_info[i].ui_framework_cnt = ui_framework_cnt;
		root_obj = json_array_get_object_element(root_ary,i);
		const gchar *ui_framework = json_object_get_string_member(root_obj, "framework");
		strcpy(ui_framework_info[i].ui_framework_name,ui_framework);
		const gchar *icon_image = json_object_get_string_member(root_obj, "icon_image");
		strcpy(ui_framework_info[i].icon_image_path,icon_image);


		int disc_str_cnt;
		// const gchar *disc;
		int j = 0;
		JsonArray *apps_ary = json_object_get_array_member(root_obj, "apps");

		if (apps_ary != NULL)
		{
			apps_info_cnt = json_array_get_length(apps_ary);
			if(apps_info_cnt > MAX_APPS)
			{
				apps_info_cnt = MAX_APPS;
			}
			ui_framework_info[i].apps_info_cnt = apps_info_cnt;

			for (int j = 0; j < ui_framework_info[i].apps_info_cnt; j++)
			{
				JsonObject *inner_obj = json_array_get_object_element(apps_ary, j);

				if (inner_obj != NULL)
				{
					const gchar *exe_cmd = json_object_get_string_member(inner_obj, "exe_cmd");
					strcpy(ui_framework_info[i].apps[j].exe_cmd,exe_cmd);
					const gchar *discription = json_object_get_string_member(inner_obj, "description");
					strcpy(ui_framework_info[i].apps[j].discription,discription);
				}
			}
		}
	}
}
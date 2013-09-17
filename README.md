node_parser
===========

convenient parser for structured json/xml data

Get sucked to parse tons of json/xml?

Now it's time to relex because of node_parser.

When you need to parse json/xml, first you need to define structure of those data, like:


    DEF_NODE(CPlayer)
        DEF_VALUE(id,       "id")
        DEF_VALUE(name,     "name")
        DEF_VALUE(leader,   "leader")
    END_NODE()

Then you can parse data by invoking:

    const char* json_player = "{\"id\":23,\"name\":\"Jack\",\"leader\":false}";
    const char* json_player_end = json_player + strlen(json_player);

    CPlayer player;
    Json::Reader reader;
    Json::Value playerValue;
    reader.parse(json_player, json_player_end, playerValue);

    NodeValueLoad<json_node_parser>(player, playerValue);

You may notice only the last line is the line where the job is done.

Now node_parser provides the following grammar:

	1. DEF_NODE, define a new structure
	2. DEF_VALUE, define a value
	3. DEF_ARRAY, define a vector
	4. DEF_MAP, define a map

More sample could be found in code.

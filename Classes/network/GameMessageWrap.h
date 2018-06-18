#ifndef _GameMessageWrap_H_
#define _GameMessageWrap_H_
#include "GameMessage.pb.h"


#include <vector>
#include <string>


class GameMessageWrap
{
public:
	static std::vector<GameMessage> set_string_to_vector(const std::string& set_str)
	{
		GameMessageSet game_message_set;
		game_message_set.ParseFromString(set_str);
		std::vector<GameMessage> ret;
		for (auto i = 0; i < game_message_set.game_message_size(); ++i)
			ret.push_back(game_message_set.game_message(i));
		return ret;
	}

	static std::string vector_to_set_stirng(const std::vector<GameMessage>& vec_game_msg)
	{
		GameMessageSet game_message_set;
		for (auto r : vec_game_msg)
		{
			auto game_message = game_message_set.add_game_message();
			game_message->CopyFrom(r);
		}
		return game_message_set.SerializeAsString();
	}


	static std::string combine_message(const std::vector<std::string>& msg)
	{
		GameMessageSet game_message_set;

		for (auto r : msg)
		{
			GameMessageSet gms;
			gms.ParseFromString(r);
			game_message_set.MergeFrom(gms);
		}
		return game_message_set.SerializeAsString();
	}
};

#endif // !_GameMessageWrap_H_
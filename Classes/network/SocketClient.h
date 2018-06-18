#ifndef _SocketClient_H__
#define _SocketClient_H__
#define ASIO_STANDALONE
#include "asio.hpp"
#include <functional>
#include <thread>
#include <chrono>
#include "cocos2d.h"
#include <deque>
#include <iostream>
#include "socket_message.h"
#include<network/GameMessage.pb.h>
#include<network/GameMessageWrap.h>
using asio::ip::tcp;

class SocketClient
{
public:
	static SocketClient* create(std::string ip = "127.0.0.1", int port = 8008);
	void close();                                                                 //关闭
	void start()                                                                  //开启
	{
		start_connect();
	};
	std::vector<GameMessage> get_game_messages();
	void send_game_message(const std::vector<GameMessage>& vec_game_msg);
	void send_string(std::string s);                                              //发送数据
	std::string get_string();                                                     //获取数据
	void do_close();     //inner use
	bool started() const { return start_flag_; }                                  //游戏是否开始
	bool error()const { return error_flag_; }                                     //是否有异常
	int camp() const;                                                             //返回玩家阵营
	int total() const;                                                            //返回玩家总数
private:
	SocketClient::SocketClient(std::string ip, int port) : socket_(io_service_), endpoint_(asio::ip::address_v4::from_string(ip), port)
	{
		start();
	}
	void write_data(std::string s);                                            //写入数据
	void start_connect();                                                      //开始连接
	void handle_connect(const asio::error_code& error);                        //处理连接
	void handle_read_header(const asio::error_code& error);                    //数据头  
	void handle_read_body(const asio::error_code& error);                      //数据体
	std::string read_data();
private:
	asio::io_service io_service_;
	tcp::socket socket_;
	tcp::endpoint endpoint_;
	std::deque<socket_message> read_msg_deque_;
	socket_message read_msg_;
	bool start_flag_{ false }, error_flag_{ false };
	std::thread *thread_, *read_thread_;
	int camp_, total_;
	std::condition_variable data_cond_;
	std::mutex mut;
};







#endif // !_SocketClient_H__


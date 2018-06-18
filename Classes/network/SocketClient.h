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

using asio::ip::tcp;

class SocketClient
{
public:
	//brief create a socket clientparam ip ip address, default to localhost
	//param port port number, default to 8008 return a socket client 
	static SocketClient* create(std::string ip = "127.0.0.1", int port = 8008);
	//	~SocketClient() {  io_service_.stop();do_close(); }
	void close();        //close the socket 
	void start()        //start a socket
	{
		start_connect();
	};
	[[deprecated("just for test")]]
	/*******************************
	std::vector<GameMessage> get_game_messages();
	*******************************/
	[[deprecated("just for test")]]
	/****************************
	void send_game_message(const std::vector<GameMessage>& vec_game_msg);
	*******************************/
	void send_string(std::string s);  //send string through socket param s protubuf serialized string 
	std::string get_string();//this is a block function of receving stirng return protubuf serialized string
	void do_close();     //inner use
	bool started() const { return start_flag_; }           //return if game has started
	bool error()const { return error_flag_; }        //return if there is error
	int camp() const;          //start from 1    return camp number
	int total() const;       // return total player number
private:
	SocketClient::SocketClient(std::string ip, int port) : socket_(io_service_), endpoint_(asio::ip::address_v4::from_string(ip), port)
	{
		start();
	}
	void write_data(std::string s);
	void start_connect();
	void handle_connect(const asio::error_code& error);
	void handle_read_header(const asio::error_code& error);
	void handle_read_body(const asio::error_code& error);
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


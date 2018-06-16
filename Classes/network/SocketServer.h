#ifndef _SocketServer_H__
#define _SocketServer_H__
#define ASIO_STANDALONE
#define ASIO_HAS_STD_CHRONO
#include "asio.hpp"
#include <thread>
#include <iostream>
#include <condition_variable>
#include <deque>
#include "socket_message.h"
#include "cocos2d.h"

using asio::ip::tcp;

typedef std::shared_ptr<tcp::socket> socket_ptr;

class SocketServer;
class TcpConnection : public std::enable_shared_from_this<TcpConnection>          //管理单个连接
{
public:
	typedef std::shared_ptr<TcpConnection> pointer;
	static pointer create(asio::io_service& io_service, SocketServer* parent);
	tcp::socket& socket();
	void start();
	void write_data(std::string s);
	std::string read_data();
	bool error()const { return error_flag_; }
	void do_close();
private:
	void handle_read_header(const asio::error_code& error);
	void handle_read_body(const asio::error_code& error);
	TcpConnection(asio::io_service& io_service, SocketServer* parent);;
	void delete_from_parent();
	tcp::socket socket_;
	SocketServer* parent;
	bool error_flag_{ false };
	socket_message read_msg_;
	std::deque<socket_message> read_msg_deque_;
	std::condition_variable data_cond_;
	std::mutex mut_;
};

class SocketServer
{
public:
	static SocketServer* create(int port = 8008);
	void close();                                                     //关闭服务端
	std::vector<TcpConnection::pointer> get_connection() const;       //返回TcpConnection vector
	void remove_connection(TcpConnection::pointer p);                 //移除TcpConnection p
	void button_start();                                              //打开服务器
	bool error() const;                                               //返回错误
	int getconnection_num() const;                                    //连接总数
	
private:
	int connection_num_;
	SocketServer(int port);
	void start_accept();
	void handle_accept(TcpConnection::pointer new_connection, const asio::error_code& error);
	void loop_process();
	tcp::acceptor acceptor_;
	std::vector<TcpConnection::pointer> connections_;
	static asio::io_service* io_service_;
	std::thread *thread_, *button_thread_{ nullptr };
	std::mutex delete_mutex_;
	bool error_flag_{ false };
	std::condition_variable data_cond_;
};


#endif // !_SocketServer_H__


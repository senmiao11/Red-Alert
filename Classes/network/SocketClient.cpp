#include "SocketClient.h"
#include <iostream>


SocketClient* SocketClient::create(std::string ip, int port)  //创建连接
{
	auto s = new SocketClient(ip, port);
	s->thread_ = new std::thread(std::bind(static_cast<std::size_t(asio::io_service::*)()>(&asio::io_service::run),&s->io_service_));
	return s;
}


std::vector<GameMessage> SocketClient::get_game_messages()
{
	auto game_message_set_stirng = read_data();
	return GameMessageWrap::set_string_to_vector(game_message_set_stirng);
}

void SocketClient::send_game_message(const std::vector<GameMessage>& vec_game_msg)
{
	auto set_string = GameMessageWrap::vector_to_set_stirng(vec_game_msg);
	write_data(set_string);
}


void SocketClient::send_string(std::string s)  //发送消息
{
	if (error_flag_)
		return;
	write_data(s);
}

std::string SocketClient::get_string()        //获取消息
{
	return read_data();
}

void SocketClient::do_close()                 //关闭
{
	try
	{
		std::lock_guard<std::mutex> lk{ mut };
		error_flag_ = true;
		socket_message empty_msg;
		memcpy(empty_msg.data(), "0001\0", 5);    
		read_msg_deque_.push_back(empty_msg);
		data_cond_.notify_one();
		io_service_.stop();
		asio::error_code ec;
		socket_.shutdown(asio::ip::tcp::socket::shutdown_both, ec);
		if (!ec)
			throw asio::system_error(ec);
		socket_.close();
		thread_->join();
	}
	catch (std::exception&e)
	{
		e.what();
	}

}

int SocketClient::camp() const                    //获取我方阵营
{
	while (!start_flag_);
	return camp_;
}

int SocketClient::total() const                   //获取连接总数
{
	while (!start_flag_);
	return total_;
}

void SocketClient::write_data(std::string s)      //写入数据
{
	socket_message msg;
	if (s.size() == 0)                           //若数据为空
	{
		s = std::string("\0");
		msg.body_length(1);
	}
	else
		msg.body_length(s.size());
	memcpy(msg.body(), &s[0u], msg.body_length());
	msg.encode_header();
	asio::write(socket_,asio::buffer(msg.data(), msg.length()));
}

void SocketClient::start_connect()               //异步连接                                                        
{
	socket_.async_connect(endpoint_,std::bind(&SocketClient::handle_connect, this,std::placeholders::_1));
}

void SocketClient::handle_connect(const asio::error_code& error)     
{
	try
	{
		if (!error)
		{
			std::cout << "connected\n";
			char data[30] = { 0 };
			asio::error_code error;
			size_t length = socket_.read_some(asio::buffer(data, 30), error);
			if (error || length < 10)
				throw asio::system_error(error);
			char header[4 + 1] = "";
			strncat(header, data + 10, 4);
			total_ = atoi(header);                      //把字符串转换成整型数
			camp_ = atoi(data + 14);
			start_flag_ = true;
			asio::async_read(socket_,asio::buffer(read_msg_.data(), socket_message::header_length),std::bind(&SocketClient::handle_read_header, this,std::placeholders::_1));
		}
		else
		{
			std::cerr << "failed to connect" << std::endl;
			error_flag_ = true;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception in connection: " << e.what() << "\n";
	}
}

void SocketClient::handle_read_header(const asio::error_code& error)
{
	if (!error && read_msg_.decode_header())
	{
		asio::async_read(socket_,asio::buffer(read_msg_.body(), read_msg_.body_length()),std::bind(&SocketClient::handle_read_body, this,std::placeholders::_1));
	}
	else
	{
		do_close();
	}
}

void SocketClient::handle_read_body(const asio::error_code& error)
{
	if (!error)
	{
		std::lock_guard<std::mutex> lk{ mut };
		read_msg_deque_.push_back(read_msg_);
		data_cond_.notify_one();
		std::cout << "read completed\n";
		asio::async_read(socket_,asio::buffer(read_msg_.data(), socket_message::header_length),std::bind(&SocketClient::handle_read_header, this,std::placeholders::_1));
	}
	else
	{
		do_close();
	}
}

std::string SocketClient::read_data()
{
	if (error_flag_)
		return "";
	std::unique_lock<std::mutex> lk{ mut };
	while (read_msg_deque_.empty())
		data_cond_.wait(lk);
	auto read_msg = read_msg_deque_.front();
	read_msg_deque_.pop_front();
	lk.unlock();
	auto ret = std::string(read_msg.body(), read_msg.body_length());
	return ret;
}

void SocketClient::close()
{
	do_close();
}

#ifndef INC_HTTPSERVER_HPP_
#define INC_HTTPSERVER_HPP_

#include "Board.hpp"

class HttpServer
{
  public:
	HttpServer(Board & b) : board(b) {}
    void http_thread();

  private:
    void handle_request(struct netconn *conn);
    Board & board;
};


#endif /* INC_HTTPSERVER_HPP_ */

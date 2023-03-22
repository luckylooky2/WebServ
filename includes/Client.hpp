
#include <iostream>
#include <string>

class Client {
 private:
  int _fd;
  int _worker_id;
  bool _is_connectable;
  std::string _addr;
  Listen& _listen;

  ReqContext *_req_context;
  Request *_req;
  Response *_res;


 public:
};
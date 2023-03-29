#ifndef RESPOSE_HPP
#define RESPOSE_HPP

// #include "Common.hpp"

class Response {
private:

public:
	void GET(void);
	void POST(void);
	void DELETE(void);
	void send(void);
};


// void Response::init_error_page(void) {
//   if (!_req_ctx.get_error_page(_status_code).empty()) {
//     std::string e = ft::get_sole_slash(_req_ctx.get_error_page(_status_code));
//     std::string c = ft::get_sole_slash("/" + _req_ctx.get_resource());
//     if (e != c) {
//       _req_ctx.set_method("GET");
//       _is_redirected = true;
//       _redirect_code = _status_code;
//       _redirected_target = e;
//       _status_code = 0;
//       return;
//     }
//   }
//   _body += "<html>\r\n";
//   _body += "<head><title>"
//             + ft::to_string(_status_code)
//             + " "
//             + Engine::status_codes[_status_code]
//             + "</title></head>\r\n";
//   _body += "<body>\r\n";
//   _body += "<center><h1>"
//             + ft::to_string(_status_code)
//             + " "
//             + Engine::status_codes[_status_code]
//             + "</h1></center>\r\n";
//   _body += "<hr><center>" + _headers["Server"] + "</center>\r\n";
//   _body += _file.get_autoindex(_req_ctx.get_target());
//   _body += "</body>\r\n";
//   _body += "</html>\r\n";
//   _headers["Content-Type"] = Engine::mimes.get_type(".html");
//   _headers["Content-Length"] = ft::to_string(_body.length());
//   if (_status_code == 401) {
//     _headers["WWW-Authenticate"] = "Basic realm=\"Access to restricted area\"";
//   }
//   if (_status_code == 408 || _status_code == 503) {
//     _headers["Connection"] = "close";
//   }
//   if (_status_code == 503) {
//     _headers["Retry-After"] = "30";
//   }
// }

#endif
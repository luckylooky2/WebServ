
#include <iostream>
#include "log/LogFactory.hpp"

#include <iostream>
#include <map>
#include <vector>


using namespace std;

/*
socket nonblock
https://velog.io/@jyongk/TCP-Socket-Blocking-Non-Blocking 
listen, accept 설명
https://blog.devkcr.org/172
https://helloworld-88.tistory.com/215
accept 두번째 인자로 client의 ip, port 정보를 받을 수 있나 ?
*/

//#include "iom/KqueueManage.hpp"
#include "http/Webserv.hpp"

Logger log = LogFactory::get("main");
int main(int argc, char* argv[]) {

	if (argc != 2) {
		log.error("please input argument only one");
	}
	
	// kqueueEx();
	Webserv::start();

	//config file 파싱 
	//parse(argv[1]);

	// server 객체생성
	// socket 정보생성 -> listen 시작

	// client 에서 요청
	// server의 소켓에서 요청을 받고 작업큐에 삽입
	// request 에서 요청헤더 해석
	// response 에서 응답헤더 생성, send()
	// -> method 로직 
	// -> cgi 로직


	// socket
	/*
	socket 객체
	소켓관리
	socket
	bind
	listen
	accept 관리
	- 새로 생성, 유지, 종료 주기를 정해야 한다.
	*/
	return (0);
}
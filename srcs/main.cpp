
#include <iostream>
#include "log/LogFactory.hpp"

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#include <iostream>
#include <map>
#include <vector>


using namespace std;


void exit_with_perror(const string& msg)
{
    cerr << msg << endl;
    exit(EXIT_FAILURE);
}

// change_events(change_list, server_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
void change_events(vector<struct kevent>& change_list, uintptr_t ident, int16_t filter,
        uint16_t flags, uint32_t fflags, intptr_t data, void *udata)
{
    struct kevent temp_event;

    EV_SET(&temp_event, ident, filter, flags, fflags, data, udata);
    change_list.push_back(temp_event);
	// std::cout << "temp_event : " << temp_event.ident << std::endl;
}

void disconnect_client(int client_fd, map<int, string>& clients)
{
    cout << "client disconnected: " << client_fd << endl;
    close(client_fd);
    clients.erase(client_fd);
}


/*
socket nonblock
https://velog.io/@jyongk/TCP-Socket-Blocking-Non-Blocking 

listen, accept 설명
https://blog.devkcr.org/172
https://helloworld-88.tistory.com/215

accept 두번째 인자로 client의 ip, port 정보를 받을 수 있나 ?
*/
int kqueueEx(int argc, char* argv[])
{
    /* init server socket and listen */
    int server_socket;
    struct sockaddr_in server_addr;

	if(argc != 2) {
		printf("Usage : &s <port>%s\n", argv[0]);
		exit(1);
	}

    if ((server_socket = ::socket(PF_INET, SOCK_STREAM, 0)) == -1)
        exit_with_perror("socket() error\n" + string(strerror(errno)));
	std::cout << "server_socket : " << server_socket << std::endl;
    ::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(atoi(argv[1]));




    if (::bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
        exit_with_perror("bind() error\n" + string(strerror(errno)));

    if (::listen(server_socket, 5) == -1)
        exit_with_perror("listen() error\n" + string(strerror(errno)));
    
	fcntl(server_socket, F_SETFL, O_NONBLOCK);
    
    /* init kqueue */
    int kq;
    if ((kq = kqueue()) == -1)
        exit_with_perror("kqueue() error\n" + string(strerror(errno)));

	std::cout << "kq : " << kq << std::endl;

    map<int, string> clients; // map for client socket:data
    vector<struct kevent> change_list; // kevent vector for changelist
    struct kevent event_list[8]; // kevent array for eventlist

    /* add event for server socket */
    change_events(change_list, server_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    cout << "echo server started" << endl;

    /* main loop */
    int new_events;
    struct kevent* curr_event;
    while (1)
    {	usleep(1000000);
        /*  apply changes and return new events(pending events) */
        new_events = kevent(kq, &change_list[0], change_list.size(), event_list, 8, NULL);
		std::cout << "new_events : " << new_events << std::endl;
        if (new_events == -1)
            exit_with_perror("kevent() error\n" + string(strerror(errno)));

        change_list.clear(); // clear change_list for new change
        for (int i = 0; i < new_events; ++i)
        {
            curr_event = &event_list[i];
			// std::cout << "curr_event->ident : " << curr_event->ident << std::endl;
			// std::cout << "curr_event->flags : " << curr_event->flags << " " << EV_ERROR << std::endl;
            /* check error event return */
            if (curr_event->flags & EV_ERROR)
            {
                if (curr_event->ident == server_socket)
                    exit_with_perror("server socket error");
                else
                {
                    cerr << "client socket error" << endl;
                    disconnect_client(curr_event->ident, clients);
                }
            }
            else if (curr_event->filter == EVFILT_READ)
            {
                if (curr_event->ident == server_socket)
                {
					std::cout << " curr_event->ident  : " << curr_event->ident  << std::endl;
                    /* accept new client */
                    int client_socket;
					
                    if ((client_socket = accept(server_socket, NULL , NULL)) == -1)
                        exit_with_perror("accept() error\n" + string(strerror(errno)));
                    cout << "accept new client: " << client_socket << endl;
                    fcntl(client_socket, F_SETFL, O_NONBLOCK);

                    /* add event for client socket - add read && write event */
                    change_events(change_list, client_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
                    change_events(change_list, client_socket, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
                    clients[client_socket] = "";
                }
                else if (clients.find(curr_event->ident)!= clients.end())
                {
					std::cout << "read : " << curr_event->ident  << std::endl;
                    /* read data from client */
                    char buf[1024];
                    int n = read(curr_event->ident, buf, sizeof(buf));

                    if (n <= 0)
                    {
                        if (n < 0)
                            cerr << "client read error!" << endl;
                        disconnect_client(curr_event->ident, clients);
                    }
                    else
                    {
                        buf[n] = '\0';
                        clients[curr_event->ident] += buf;
                        cout << "received data from " << curr_event->ident << ": " << clients[curr_event->ident] << endl;
                    }
                }
            }
            else if (curr_event->filter == EVFILT_WRITE)
            {
                /* send data to client */
                map<int, string>::iterator it = clients.find(curr_event->ident);
                if (it != clients.end())
                {
                    if (clients[curr_event->ident] != "")
                    {
                        int n;
                        if ((n = write(curr_event->ident, clients[curr_event->ident].c_str(),
                                        clients[curr_event->ident].size()) == -1))
                        {
                            cerr << "client write error!" << endl;
                            disconnect_client(curr_event->ident, clients);  
                        }
                        else
                            clients[curr_event->ident].clear();
                    }
                }
            }
        }

    }
    return (0);
}

Logger log = LogFactory::get("main");
int main(int argc, char* argv[]) {

	if (argc != 2) {
		log.error("please input argument only one");
	}
	
	kqueueEx(argc, argv);
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
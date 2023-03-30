# 프로젝트 진행상황

## 03/22 수

- **방향성**

  1. unit test 도입
     - 함수 단위로 고려할 수 있는 모든 경우의 수를 고려
     - 현재는 파일 분리 이슈 ⇒ seongtki님이 해결
  2. 클래스 및 함수 설명 주석 추가
     - 클래스 멤버 변수 설명, 멤버 함수 매개 변수 설명 등…
  3. 디렉토리 구조
     - 현재 : 통합
       ```cpp
       /include
         - File.hpp
         - Exception.hpp
       /srcs
         - File.cpp
         - Exception.cpp
       ```
     - 목표 : 객체 그룹 별 디렉토리
       ```cpp
       /File
         - File.hpp
         - File.cpp
       /Exception
         - Exception.hpp
         - Exception.cpp
       ```
     - 효과
       - 객체가 가진 관리 포인트를 최소한으로
       - 클래스 확장에 유리한 방법
  4. Exception Base class
     - global한 업무와 관련 있는 Exception : Exception 디렉토리에서 관리
     - 특정 객체 업무와 관련 있는 Exception : 각 객체 그룹 디렉토리에서 추가로 관리
  5. 라이브러리
     - c style 라이브러리는 cpp style로 다시 만들어서 사용
     - cpp style 라이브러리는 그대로 사용

- **논의 내용**

  - 설계 및 구조
    - 클라이언트와 TCP 연결이 되면 Queue 구조체에 저장 ⇒ 들어온 순서대로 처리
  - `accept()`와 `recv()`
    - TCP 연결 이후 일정 시간동안 연결을 끊지 않아야 함
    - 첫 연결 : `accept()` 이후 바로 `recv()` 를 해주면 되지만
    - 일정 시간 내에 다시 요청이 오면 `recv()`를 독립적으로 호출해야 하는 문제 ⇒ 어떻게 해결?
  - `select()`가 I/O를 비동기적으로 처리해주는가?
    - `select()` 자체와 I/O를 처리해주는 로직은 비동기적으로 돌아가는가?

- **이후 작업**

  - 공통 : `select()`, `kqueue()` 공부 및 예제 코드 작성
  - seongtki : 기본적인 뼈대 작업 계속
  - chanhyle : request 관련 공부
  - susong : mime, status 어떤 방식으로 할지 공부

## 03/23 목

- **io multiplexing 토의**

  - 개념공유 완료
  - 코드상의 이해는 오늘 공부 후 내일 공유

- **common exception part**

  - unchecked exception
    - IllegalStateException, IllegalArgumentException, NullpointerException 추가
  - checked exception
    - IOException 추가

- **file part**

  - FileDescriptor class 추가
    - 함수구현 8/8
    - fd 생성할 때, 무조건 non blocking 설정을 할 지 고민 필요
  - File class 추가
    - 함수구현 1/11

- **test**

  - unit test 추가

    - cpp 파일 생성 후 아래와 같이 코드.

  - ```
    CASE("log", "loglevel")
    {
    	ASSERT(log.isErrorEnabled() == ERROR);
    	return (0);
    }
    ```

## 03/24 금

- **io multiplexing**

  - kqueue() 예제 => /util/main.cpp 참고

- **file part**

  - fd를 감싸는 FileDescriptor 객체
    1. 관련 정보를 저장
    2. file 객체와 socket 객체가 같은 정보를 공유하는 것은 낭비(중복)
    - socket 객체가 FileDescriptor 객체를 상속하게 만듦

- **request part**

  - 어디까지 요청 객체가 처리할 것인가?
  - 1. 요청을 받는다 : HTTP 요청 메시지를 네트워크로부터 읽어 들인다. => RequestMessage class
  - ----- request 파트는 여기까지 -----
  - 2. 요청을 처리한다 : 요청 메시지를 해석하고 행동을 취한다. => RequestAction class
  - 3. 리소스에 접근한다 : 메시지에서 지정한 리소스에 접근한다. => RequestResource class

  - header 객체를 만들면 더 편할듯, 각각의 header 객체를 static으로 관리?

- **할 일**
  - seongtki : 전체적인 틀 실행 파일 제작
  - chanhyle : 헤더 명세 + request 파서 + request 구조 정리

## 03/30 목

- **susong 복귀 환영회 및 설명회**

  - 각 디렉토리 및 클래스
  - address
    - InetAddress(ip 주소 저장 및 관리(validation 포함), addr_in 구조체와의 관계를 어떻게 정의할 것인가? ...)
  - config
    - RootBlock(worker ...)
    - ServerBlock(LocationBlock ...)
    - LocationBlock class
  - exception
    - Exception(std::exception을 상속 : 에러가 발생했을 때 여러가지 상황(catched exception, uncatched exception)이 발생할 수 있는데, 사용자가 원하는 형태의 exception을 만들기 위해), global scope exception...)
      - RuntimeException : uncatched exception
      - NullPointerException
      - IOException : 소켓 및 fd에서의 예외 처리, errorno를 멤버 변수로 추가적으로 가지고 있음
      - IllegalStateException : uncatched exception, RuntimeException을 상속, 인자가 잘못됨, 객체 내부에서 관리되고 있는 변수의 정보가 잘못되었을 떄
      - IllegalArgumentException : uncatched exception, RuntimeException을 상속, 상태가 잘못됨, 외부에서 파라미터를 통해서 들어온 정보가 잘못되었을 때
    - 각 모듈 : 업무적인 예외 처리는 각 모듈에서 예외 처리를 만들어 처리하도록 확장
  - file
    - File : 파일이 존재하는지, 파일인지 디렉토리인지 등을 관리
    - FileDescriptor : Base class, fd 값, isValid, isClosed, fd와 관련한 read(), write(), lseek(), close() 담당
    - FileDescriptorSet
  - main.cpp
    - Webserv : init(config 파싱?), start(Server 객체 생성 -> listen() -> kqueue 생성 -> HTTPclient 생성 -> Request 생성)
  - Server

    - Server : Client map을 유지해야 하기 때문에 Singleton
    - Socket : FileDescriptor class 상속(Socket class만 fd를 가지고 있는 것이 아니기 때문에)
    - Client : map으로 관리, SocketStorage \_in, \_out(Request, Response 객체를 만들기 전후에 string 정보를 저장)

  - Kqueue

    - kevent() : 변화를 감지한 이벤트 수만큼 return이 됨, 변화가 없다면 이벤트가 올 때까지 block되어 listen하고 있는 socket에서 이벤트(connect(), send())를 감지하는 I/O multiplexer
    - kevent()에서 return한 수만큼 for문을 돌면서 각각 이벤트를 처리해 줌
      - read fd => 1) if (ident == server.listen_fd) accept() 즉, TCP 연결 처리 2) if not, 소켓으로부터 recv()
      - write fd => send()

  - RWCallback

    - Server, Client의 Base class
    - why? Base class에서 Derived class가 어떻게 정의되는 지와 관계없이 하나의 함수로 처리할 수 있음(다형성, 추상화)
    - 만약 다형성을 적용하지 않는다면, 미래에 정의될 Derived class별로 사용할 함수를 만들어주어야 함(유지 보수 worst)
    - 다형성을 적용한다면, 단 하나의 함수로 모든 Derived class를 모두 처리해줄 수 있음
    - 단, 추상 함수라면 추상 함수들을 override를 해주어야 함

- **Feedback**

  - SHTTP : Static class => UTILS나 CONSTANT로 이름 변경?
  - 코딩 컨벤션
    1. class : 멤버 변수와 멤버 함수 간 개행 추가
    2. 멤버 변수 : "\_" prefix
    3. norminette 잔재 제거
       - 함수 return type과 함수 이름 사이에 "\t" -> " "
       - 함수 body {} => Java 형식으로
    4. 지역 변수 : 스네이크 케이스 e.g. CRLFSplitted
  - buffer : char -> unsigned char why? 확장 ASCII 고려
  - Parser class 위치 변경 : global?

- **할 일**
  - seongtki : server 마무리, response(status code) 구현
  - susong : 소스 코드 이해, config file 구현
  - chanhyle : request(headers) 마무리, MIMES 구현

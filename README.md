## 할거

기능추가
- autoindex
- 서버추가
- 이미지출력
서브젝트 다시읽기
평가지 읽기
코드정리
테스트코드 작성
다이어그램 만들기


/*
socket nonblock
https://velog.io/@jyongk/TCP-Socket-Blocking-Non-Blocking 
listen, accept 설명
https://blog.devkcr.org/172
https://helloworld-88.tistory.com/215
accept 두번째 인자로 client의 ip, port 정보를 받을 수 있나 ?
*/
//http://egloos.zum.com/hanulnun/v/2694379

## 평가준비



<check/ask>
http server 개념서려명

i/o multiplexing 설명

accept, client read, write 개념 설명

the select should be in the main loop and should check fd for read and write AT THE SAME TIME,
if not please give a 0 and stop the evaluation.

there should be only one read or one write per client per select. ask to show you the code that goes 
from the select to the read and write of a client.

search for all read/write on a socket and check that if an error returned the client is removed.

read write는 0, -1 두개 다 체크해야 함.

if a check of errno is done after read, write. please stop the evaluation and put a mark to 0


writing or reading NAY file descriptor without going through the select is strictly FORBIDDEN.

<configuration>

in the configuration file check if you can do the following and test the result.
- look for the http response status codes list on internet and during this evaluation
if any status codes is wrong don't give related points.
- setup multiple servers with different port
- serup multiple servers with different hostname (curl --resolve example.com:80:127.0.0.1 q)
- setup default error pate (404)
limit the client body (curl -X POST -H "Content-Type: plain/text" --data "Body is here sfgr")
- setup routes in a server to different diriectories
- setup a default file to search for if you ask for a directory.
- setup a list of method accepted for a certain rout (try to delete something with and without permission)

<basic check>
telnet, curl, prepared files.
get , post, delete, unknown
state code must be good.
upload some file to the server and get it back (다운로드 기능 필요.)


<check with a browser>

Use the reference browser of the team, open the network part of it and try to connect to the server with it.
look at the request header and response header
it should be compatible to serve a fully static website
try a wrong url on the server
try to list a directory
try a redireected URL
try things


<port issues>
2개서버에 포트가 같으면 실행되면 안된다.

Launch multiple servers at the same time with different configurations but with common ports. Is it working? if it is working, ask why the server should work if one of the configurations isn't working. keep going



<siege & stress test>
99.5%
leak
check if there is no hanging connection

rm -rf $HOME/.brew
git clone --depth=1 https://github.com/Homebrew/brew $HOME/goinfre/.brew
echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc
source $HOME/.zshrc
brew update

brew install siege
siege -b  http://localhost:8080
siege -b --reps=8 http://localhost:8080

../../goinfre/.brew/bin/./siege -b http://localhost:8080
../../goinfre/.brew/bin/./siege -c2 -t30S "http://localhost:8080/register POST {\"contactName\":\"John DaCosta\"}" --content-type "application/json"


<bonus>

CGI - there's more than one CGI system.

# reference

https://www.nginx.com/resources/wiki/start/topics/examples/full/
https://12bme.tistory.com/366


# webserv




### log

log는 class 내부에 작성하여 기록된다.
log 객체는 클래스당 최초에 한번만 생성되어야 한다.



## Diagram
connect
recv
response
send

## nginx example
Doc root is: /opt/homebrew/var/www
port set : /opt/homebrew/etc/nginx/nginx.conf to 8080 so that nginx can run without sudo.

nginx will load all files in /opt/homebrew/etc/nginx/servers/.

## directory
/var/www/ 			: default page call
/var/www/index.html
/var/www/50x.html

/etc/nginx/nginx.conf
/etc/nginx/mime.types
/etc/nginx/cgi.conf


10063  python body.py
10064  python3 body.py
10065  python3 cgi.py
10066  pip3 install ssl
10067  pip3 install LibreSSl
10068  pip3 install LibreSSL
10069  pip lista
10070  pip list
10071  pip3 list
10072  pip3 search urllib3
10073  pip3 update urllib3
10074  pip3 install urllib3 --upgrade
10075  pip3 install urllib3 version=1.26.15
10076  pip3 install urllib3 version==1.26.15
10077  pip install urllib3 version=2.4.0
10078  pip3 install urllib3 version=2.4.0
10079  pip install --upgrade pip
10080  pip3 install --upgrade pip3
10081  pip3 install --upgrade pip
10082  pip install urllib3  version=1.19.1
10083  pip3 install urllib3  version=1.19.1
10084  pip install urllib3===1.4.0
10085  pip3 install urllib3===1.4.0
10086  pip3 install urllib3===1.26.15
10087  pip3 list
10088  python3 cgi.py
10089  l




Welcome in this little webserver tester.
Passing the test here is the minimum before going to an evaluation.

press enter to continue

THIS TEST IS NOT MEANT TO BE THE ONLY TEST IN THE EVALUATION!!!

press enter to continue

Before starting please follow the next few steps (files content can be anything and will be shown to you by the test):
- Download the cgi_test executable on the host
- Create a directory YoupiBanane with:
        -a file name youpi.bad_extension
        -a file name youpi.bla
        -a sub directory called nop
                -a file name youpi.bad_extension in nop
                -a file name other.pouic in nop
        -a sub directory called Yeah
                -a file name not_happy.bad_extension in Yeah
press enter to continue

Setup the configuration file as follow:
- / must answer to GET request ONLY
- /put_test/* must answer to PUT request and save files to a directory of your choice
- any file with .bla as extension must answer to POST request by calling the cgi_test executable
- /post_body must answer anything to POST request with a maxBody of 100
- /directory/ must answer to GET request and the root of it would be the repository YoupiBanane and if no file are requested, it should search for youpi.bad_extension files

press enter to continue

Before starting please verify that the server is launched
press enter to continue


Test GET http://localhost:8001/
content returned: <!DOCTYPE html>
<html lang="en">
<head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>webserv</title>
</head>

<body>
  <div id="main">
    <content>
      <h1>webserv</h1>
        <ul class="list-group">
          <h1>Links</h1>
          <li><a href="index.php">index.php</a></li>
          <li><a href="/admin">/admin</a></li>
          <li><a href="/data">/data</a></li>
          <li><a href="/autoindex/">/autoindex/</a></li>
        </ul>
    </content>
  </div>
</body>
</html>


Test POST http://localhost:8001/ with a size of 0

Test HEAD http://localhost:8001/

Test GET http://localhost:8001/directory
content returned: bad extension


Test GET http://localhost:8001/directory/youpi.bad_extension
content returned: bad extension


Test GET http://localhost:8001/directory/youpi.bla
content returned: HMM

Test GET Expected 404 on http://localhost:8001/directory/oulalala
content returned: <html>
<head><title>404 Not Found</title></head>
<body>
<center><h1>404 Not Found</h1></center>
<hr><center></center>
</body>
</html>


Test GET http://localhost:8001/directory/nop
content returned: bad extension


Test GET http://localhost:8001/directory/nop/
content returned: bad extension


Test GET http://localhost:8001/directory/nop/other.pouic
content returned: 

Test GET Expected 404 on http://localhost:8001/directory/nop/other.pouac
content returned: <html>
<head><title>404 Not Found</title></head>
<body>
<center><h1>404 Not Found</h1></center>
<hr><center></center>
</body>
</html>


Test GET Expected 404 on http://localhost:8001/directory/Yeah
content returned: <html>
<head><title>404 Not Found</title></head>
<body>
<center><h1>404 Not Found</h1></center>
<hr><center></center>
<html>
<head><title>Index of /directory/Yeah</title></head>
<body>
<h1>Index of /directory/Yeah</h1><hr><pre><a href="/directory/Yeah/../">../</a>
<a href="/directory/Yeah/./">./</a>                                                 02-May-2023 06:28                   -
<a href="/directory/Yeah/not_happy.bad_extension">not_happy.bad_extension</a>                            09-Nov-2022 05:11                   0
</pre><hr></body>
</html>
</body>
</html>


Test GET http://localhost:8001/directory/Yeah/not_happy.bad_extension
content returned: 

Test Put http://localhost:8001/put_test/file_should_exist_after with a size of 1000
content returned: 
==================================================================
the file file_should_exist_after should have been created with a size of 1000 bytes. Check that now
==================================================================
press enter to continue


Test Put http://localhost:8001/put_test/file_should_exist_after with a size of 10000000
content returned: 
==================================================================
the file file_should_exist_after should still be there but this time with a size of 10000000 bytes. Check that now
==================================================================
press enter to continue


Test POST http://localhost:8001/directory/youpi.bla with a size of 100000000





Test POST http://localhost:8001/directory/youpla.bla with a size of 100000000

Test POST http://localhost:8001/directory/youpi.bla with a size of 100000 with special headers

Test POST http://localhost:8001/post_body with a size of 0

Test POST http://localhost:8001/post_body with a size of 100

Test POST http://localhost:8001/post_body with a size of 200

Test POST http://localhost:8001/post_body with a size of 101

Test multiple workers(5) doing multiple times(15): GET on /

Test multiple workers(20) doing multiple times(5000): GET on /





Test multiple workers(128) doing multiple times(50): GET on /directory/nop

Test multiple workers(20) doing multiple times(5): Put on /put_test/multiple_same with size 1000000
==================================================================
the file multiple_same should exists with a size of 1000000 bytes. Check that now
==================================================================
press enter to continue

Test multiple workers(20) doing multiple times(5): Post on /directory/youpi.bla with size 100000000



********************************************************************************
GG, So far so good! Run your own tests now! :D
********************************************************************************



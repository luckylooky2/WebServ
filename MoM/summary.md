# 프로젝트 진행상황



### 0322 수



### 0323 목

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



### 0324 금

- io multiplexing 
- file part
- request part






















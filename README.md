# Backend Practice 


# LAB2 : AWS 실습

---

# Lab3 : UDP Socket

1. test1.cpp : UDP 소켓 생성 예제 코드 
2. test2.cpp : Socket은 FileSystem과 동일하게 관리되고, 한 소켓을 닫고 새로운 소켓 생성시 ID 재사용 가능함을 알아보는 예제 코드
3. test3.cpp : UDP 소켓을 생성하고, buffer를 통해 나에게 문자열을 전송 후 보낸 바이트 확인 예제 코드
4. test4.cpp : UDP 소켓을 생성하고, buffer를 통해 문자열을 나에게 문자열을 전송하는 예제 코드
5. test5.cpp : UDP 소켓을 생성하고, buffer를 통해 문자열을 에코 서버로 전송하고, 새로운 buffer를 통해 전송한 값을 받아오는 예제 코드
6. test6.cpp : UDP 소켓을 생성하고, EOF가 입력될 때 까지 반복하면서 에코서버로 문자열을 전송하고 전송한 값을 받아오는 예제 코드
7. test7.cpp : 소켓을 생성하고 bind 를 통해 주소 고정 후 현재 주소와 포트를 알아보는 예제 코드
8. test8.cpp: 소켓을 생성 후 , bind 를 통해 주소를 고정하고 EOF가 입력될 때 까지 반복하며 수신 받은 바이트를 다시 되돌려주는 에코 서버 예제 코드 

---

# Lab4 : Protobuf

1. person.proto : protobuf 학습을 위한 person Format 예시 
2. test3.cpp : Person protobuf 객체 생성 후 값 설정 예시 코드
3. test4.cpp : Person protobuf 객체 생성 후 값 설정 예시 코드, 반복문 통해 결과 출력 추가 
4. test5.cpp : 텍스트 파일을 읽어 역직렬화 후 protobuf 객체에 대입, 결과 값 출력 예시 코드
5. [test5.py](http://test5.py) : test5.cpp 와 동일한 python Code
6. test6.cpp : Person protobuf 객체를 생성하고 직렬화 하여 UDP 소켓을 통해 나에게 전송 후 역직렬화 하여 결과값을 조회하는 예시 코드 
7. [test7.py](http://test7.py) : json 형식의 일반 객체를 json 으로 dump 하는 예제 코드 
8. [test8.py](http://test8.py) : json 형식의 일반 객체 2개를 생성 후, 배열에 담아 배열을 dump 하는 예제 코드 
9. [test9.py](http://test9.py) : json 형식의 일반 객체를 생성하지만, 요소 내에 요소가 존재하는 구조이며, 해당 객체를 dump 하는 예제 코드
10. [test11.py](http://test11.py) : json 형식의 일반 객체를 생성하지만, [test9.py](http://test9.py) 요소에 배열이 추가된 구조. 해당 객체를 dump 하는 예제 코드
11. [test11.py](http://test11.py) : json 형식의 일반 객체를 생성 후 , json 으로 dump 후 해당 파일을 역직렬화하여 출력하는 예제 코드 
12. [test12.py](http://test12.py) : json 형식의 일반 객체를 생성 후 , json 으로 dump 후 UDP 소켓을 통해 나에게 전송, 역직렬화 하여 출력하는 예제 코드.

---

# Lab5 : TCP Socket

1. test1.cpp : UDP 소켓과 TCP 소켓은 서로 다르게 관리되어, 같은 ID를 가질 수 있음을 보여주는 예제 코드
2. test2.cpp : TCP 소켓을 생성하고 에러 처리하는 예제코드 
3. test3.cpp : TCP 소켓이 몇개까지 생성될 수 있는지 확인하는 예제 코드 max: 1023
4. test4.cpp : TCP 소켓을 최대로 만들어, 버퍼를 통해 전송 후 에러를 처리하는 예제 코드
5. test5.cpp : TCP 소켓을 만들어 버퍼를 통해 전송 후 에러를 처리하는 코드, (BADF)
6. test6.cpp : TCP 소켓을 만들고, 나에게 주소를 지정한 후 전송하는 코드
7. test7.cpp : TCP 소켓을 만들고, 나에게 주소를 지정한 후 버퍼를 생성, 전송 후 수신하는 코드. 수신 시 반복하며 recv()를 통해 데이터 읽는 코드. ( UDP 와 차이점 ) 
8. test8.cpp : TCP 소켓을 만들고, 나에게 주소를 지정한 후 버퍼를 생성, 전송 후 수신하는 코드. 수신 시 반복하며 recv()를 통해 데이터 읽는 코드. 소켓이 닫힌 경우도 에러 처리 
9. test9.cpp : test8.cpp 와 동일하지만, host to network short 함수의 port 변경 
10. test10.cpp : 이전 코드와 동일하지만, offset 을 통해 현재 읽은 값을 기억하며 수신하도록 변경 
11. test11.cpp : TCP 소켓을 생성 후 bind 를 통해 주소 고정, listen() 을 통해 연결 후 생성된 active socket 을 이용해, 수신된 버퍼를 offset을 사용하여 반복하며 전송하는 코드

---

# Lab6 : Thread

1. test1.cpp: 스레드 생성 후 실행 결과를 확인하는 코드 
2. test2.cpp: 스레드 생성 후 getId() 와 native_handle()을 통해 user Level thread 와 kernel Level thread 의 대응 관계 확인 
3. test3.cpp: 스레드 생성 후 재우기 
4. test4.cpp: 스레드를 생성해 재운 후 실행에 걸린 시간을 chrono 를 이용하여 측정 
5. test5.cpp: join()의 역할 알아보는 코드. 없는 경우에 어떻게 되는지 
6. test6.cpp: 스레드를 sleep 했을 때, 동일한 결과가 보장되는지 확인 
7. test7.cpp: 동일 자원에 대하여 병렬적으로 덧셈을 진행할 때, 올바르게 값이 보장되는지 확인 
8. test8.cpp: 값이 보장되지 않음을 확인 후 thread Lock 추가 
9. test9.cpp: mutex lock 이 두개 이상인 경우, 순환 참조를 피하기 위한 lock/unlock 패턴 
10. test10.cpp: 예외가 발생할 경우엔 unlock되지 않을 수 있음. 이에 unique_lock (or lock_guard) 을 사용하여 스코프 설정 

---

# Lab7: Oauth2

### 번호 순서대로 Naver, Google Oauth2 인증 절차를 담은 사진 파일입니다.

공식 API 문서와 curl 을 이용해 설정하였습니다. 

---

# Lab8 : Flask

### Python Flask 를 이용하여 간단한 RESTFul API를 작성해보며 익힌 예제입니다.

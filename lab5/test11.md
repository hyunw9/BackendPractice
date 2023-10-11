#Test11.cpp 의 문제점 
---

현재 수정한 test11.cpp 에코서버의 경우 socket을 bind 하고 listen()을 통해 Passive 모드로 전환하고 있습니다. 
그 후, 반복문 내부에서 accept() 를 호출하여 만약 클라이언트 측이 connect()를 시도한다면 새로운 소켓 디스크립터를 반환하는 과정을 수행하고 있습니다. 
하지만 int clientSock, 즉 accept()는 클라이언트의 connect()를 전달 받은 시점에 수행되므로, connect() 시도를 받기 전까지는 Blocking 상태가 됩니다. 
즉, 다른 클라이언트의 요청을 받을 수 없는 상태가 됩니다. 하지만 현재 테스트로 진행한 test7.cpp 의 경우 요청을 1회만 보내고 있기 때문에 이러한 점을 테스트하기 어렵습니다. 
따라서 test11.cpp 는 상용화하기 어려운 에코 서버가 되며, 멀티스레딩, IO multiplexing, multi processing 과 같은 기법을 이용해서 다중 사용자 처리를 진행하여야 할 것 같습니다. 
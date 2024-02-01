## 게임서버
게임서버 포트폴리오 서버측 코드이며 IOCP 기반 서버입니다. <br/>
로그인, 캐릭터 이동과 공격, 채팅, 몬스터가 구현되어 있으며 프로그램 동작의 큰 흐름은 아래와 같습니다.<br/>
![Server1](https://github.com/seejh/ServerPortfolio/assets/152791315/4bde2fb8-6eac-4b08-b257-fd72a6bd58d1)
IOCP로 클라이언트로부터 패킷과 몬스터AI처리를 큐에 적재하고 게임 업데이트 스레드에서 빼내어 처리합니다.

프로그램이 시작되면 몬스터를 만들고 클라이언트의 접속을 기다립니다. 클라이언트가 소켓으로 Connect하면 Session, 로그인하면 Player로써 관리되며
그 후 클라이언트가 방 입장 패킷을 보내고 룸(월드)에 접속하면 게임을 시작하게 됩니다. 
네트워크 패킷 직렬화는 구글 프로토버프로 했고 동기화는 std::mutex를 사용했으며 몬스터AI는 FSM으로 만들었습니다.
코드는 네트워크 라이브러리(MyServerCore)와 컨텐츠 코드(MyServerPF)로 분리되어 있습니다.



## 개발 환경
**서버** : Windows, C++, IOCP<br/>
**클라이언트** : Windows, Unreal4 <br/>
**DB** : MySQL<br/>

## 코드(깃허브)<br/>
**서버** : https://github.com/seejh/ServerPortfolio<br/>
**클라이언트** : https://github.com/seejh/ClientPortfolio<br/> 

## 영상(유튜브)<br/>
https://www.youtube.com/watch?v=A-Fom8oiGkY

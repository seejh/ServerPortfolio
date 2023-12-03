#pragma once

#pragma once

#include"MyEnum.pb.h"
#include"MyProtocol.pb.h"
#include"MyStruct.pb.h"

#include"SendBuffer.h"
#include"SessionManager.h"

// class GameSession;

enum {
	PacketCount = 1000,
};

//struct PacketHeader {
//	short id;
//	short size;
//};

extern function<bool(shared_ptr<ClientSession>, char*, int)> GPacketHandler[PacketCount];

enum PacketType {
	S_LOGIN = 1,
	S_ENTER_ROOM,
	C_LOGIN,
	C_ENTER_ROOM,
};

bool Handle_INVALID(shared_ptr<ClientSession> session, char* buffer, int len);
bool Handle_C_LOGIN(shared_ptr<ClientSession> session, PROTOCOL::C_LOGIN pkt);
bool Handle_C_ENTER_ROOM(shared_ptr<ClientSession> session, PROTOCOL::C_ENTER_ROOM pkt);

class ClientPacketHandler
{
public:
	static void Init() {
		for (int i = 0; i < PacketCount; i++)
			GPacketHandler[i] = Handle_INVALID;

		GPacketHandler[S_LOGIN] = [](shared_ptr<ClientSession> session, char* buffer, int len) {
			return HandlePacket<PROTOCOL::C_LOGIN>(Handle_C_LOGIN, session, buffer, len);
		};
	}

	static bool HandlePacket(shared_ptr<ClientSession> session, char* buffer, int len) {
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->_id](session, buffer, len);
	}

	static shared_ptr<SendBuffer> MakeSendBuffer(PROTOCOL::S_LOGIN& pkt) {
		return MakeSendBuffer(pkt, S_LOGIN);
	}

private:
	template<typename PktType, typename Func>
	static bool HandlePacket(Func func, shared_ptr<ClientSession> session, char* buffer, int len) {
		PktType pkt;
		pkt.ParseFromArray(buffer + sizeof(PacketHeader), len);

		return func(session, pkt);
	}

	template<typename PKT>
	static shared_ptr<SendBuffer> MakeSendBuffer(PKT& pkt, int pktId) {
		int packetSize = static_cast<int>(pkt.ByteSizeLong());
		int totalSize = packetSize + sizeof(PacketHeader);

		shared_ptr<SendBuffer> sendBuffer = make_shared<SendBuffer>(totalSize);
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
		new(header)PacketHeader();
		header->_id = pktId;
		header->_size = packetSize;

		if (!pkt.SerializeToArray(sendBuffer->Buffer() + sizeof(PacketHeader), header->_size)) {
			cout << "packetHandler makePacket error" << endl;
			return nullptr;
		}

		return sendBuffer;
	}
};



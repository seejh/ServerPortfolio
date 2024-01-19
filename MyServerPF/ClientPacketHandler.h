#pragma once

#include"Enum3.pb.h"
#include"Protocol3.pb.h"
#include"Struct3.pb.h"

#include"SendBuffer.h"
#include"ClientSession.h"

class ClientSession;
enum {
	PacketCount = 3000,
};

//struct PacketHeader {
//	short id;
//	short size;
//};

extern function<bool(shared_ptr<ClientSession>, char*, int)> GPacketHandler[PacketCount];

enum PacketType {
	C_LOGIN = 1, S_LOGIN,
	C_ENTER_ROOM, S_ENTER_ROOM,
	C_PLAYERLIST, S_PLAYERLIST,
	C_MONSTERLIST, S_MONSTERLIST,
	C_MOVE, S_MOVE,
	C_ATTACK, S_ATTACK,
	C_CHAT, S_CHAT,
};

bool Handle_INVALID(shared_ptr<ClientSession> session, char* buffer, int len);
bool Handle_C_LOGIN(shared_ptr<ClientSession> session, PROTOCOL::C_LOGIN fromPkt);
bool Handle_C_ENTER_ROOM(shared_ptr<ClientSession> session, PROTOCOL::C_ENTER_ROOM fromPkt);
bool Handle_C_PLAYERLIST(shared_ptr<ClientSession> session, PROTOCOL::C_PLAYERLIST fromPkt);
bool Handle_C_MONSTERLIST(shared_ptr<ClientSession> session, PROTOCOL::C_MONSTERLIST fromPkt);
bool Handle_C_MOVE(shared_ptr<ClientSession> session, PROTOCOL::C_MOVE fromPkt);
bool Handle_C_ATTACK(shared_ptr<ClientSession> session, PROTOCOL::C_ATTACK fromPkt);
bool Handle_C_CHAT(shared_ptr<ClientSession> session, PROTOCOL::C_CHAT fromPkt);

class ClientPacketHandler
{
public:
	static void Init() {
		for (int i = 0; i < PacketCount; i++)
			GPacketHandler[i] = Handle_INVALID;
		
		GPacketHandler[C_LOGIN] = [](shared_ptr<ClientSession> session, char* buffer, int len) {
			return HandlePacket<PROTOCOL::C_LOGIN>(Handle_C_LOGIN, session, buffer, len);
		};
		GPacketHandler[C_ENTER_ROOM] = [](shared_ptr<ClientSession> session, char* buffer, int len) {
			return HandlePacket<PROTOCOL::C_ENTER_ROOM>(Handle_C_ENTER_ROOM, session, buffer, len);
		};
		GPacketHandler[C_PLAYERLIST] = [](shared_ptr<ClientSession> session, char* buffer, int len) {
			return HandlePacket<PROTOCOL::C_PLAYERLIST>(Handle_C_PLAYERLIST, session, buffer, len);
		};
		GPacketHandler[C_MONSTERLIST] = [](shared_ptr<ClientSession> session, char* buffer, int len) {
			return HandlePacket<PROTOCOL::C_MONSTERLIST>(Handle_C_MONSTERLIST, session, buffer, len);
		};
		GPacketHandler[C_MOVE] = [](shared_ptr<ClientSession> session, char* buffer, int len) {
			return HandlePacket<PROTOCOL::C_MOVE>(Handle_C_MOVE, session, buffer, len);
		};
		GPacketHandler[C_ATTACK] = [](shared_ptr<ClientSession> session, char* buffer, int len) {
			return HandlePacket<PROTOCOL::C_ATTACK>(Handle_C_ATTACK, session, buffer, len);
		};
		GPacketHandler[C_CHAT] = [](shared_ptr<ClientSession> session, char* buffer, int len) {
			return HandlePacket<PROTOCOL::C_CHAT>(Handle_C_CHAT, session, buffer, len);
		};
	}

	static bool HandlePacket(shared_ptr<ClientSession> session, char* buffer, int len) {
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->_id](session, buffer, len);
	}

	static shared_ptr<SendBuffer> MakeSendBuffer(PROTOCOL::S_LOGIN& pkt) {
		return MakeSendBuffer(pkt, S_LOGIN);
	}
	static shared_ptr<SendBuffer> MakeSendBuffer(PROTOCOL::S_ENTER_ROOM& pkt) {
		return MakeSendBuffer(pkt, S_ENTER_ROOM);
	}
	static shared_ptr<SendBuffer> MakeSendBuffer(PROTOCOL::S_PLAYERLIST& pkt) {
		return MakeSendBuffer(pkt, S_PLAYERLIST);
	}
	static shared_ptr<SendBuffer> MakeSendBuffer(PROTOCOL::S_MONSTERLIST& pkt) {
		return MakeSendBuffer(pkt, S_MONSTERLIST);
	}
	static shared_ptr<SendBuffer> MakeSendBuffer(PROTOCOL::S_MOVE& pkt) {
		return MakeSendBuffer(pkt, S_MOVE);
	}
	static shared_ptr<SendBuffer> MakeSendBuffer(PROTOCOL::S_ATTACK& pkt) {
		return MakeSendBuffer(pkt, S_ATTACK);
	}
	static shared_ptr<SendBuffer> MakeSendBuffer(PROTOCOL::S_CHAT& pkt) {
		return MakeSendBuffer(pkt, S_CHAT);
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



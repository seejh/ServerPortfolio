#include "pch.h"
#include "Actor.h"

#include"Protocol3.pb.h"
#include"ClientPacketHandler.h"
#include"Room.h"

atomic<uint64> g_playerIndexGenerator = 1;
atomic<uint64> g_monsterIndexGenerator = 1;

/*-----------------------------------------------------------------------
	FVector
-----------------------------------------------------------------------*/
FVector::FVector() : _x(0.f), _y(0.f), _z(0.f) {}
FVector::FVector(float x, float y, float z) : _x(x), _y(y), _z(z) {}

void FVector::Set(float x, float y, float z) { _x = x; _y = y; _z = z; }

/*-----------------------------------------------------------------------
	FRotator
-----------------------------------------------------------------------*/
FRotator::FRotator() : _yaw(0.f), _pitch(0.f), _roll(0.f) {}
FRotator::FRotator(float yaw, float pitch, float roll) : _yaw(yaw), _pitch(pitch), _roll(roll) {}

void FRotator::Set(float yaw, float pitch, float roll) { _yaw = yaw; _pitch = pitch; _roll = roll; }

/*
	Actor
*/
ActorType Actor::GetActorType() { return _actorType; }
uint64 Actor::GetIndex() { return _index; }
FVector& Actor::GetLocation() { return _location; }
FRotator& Actor::GetRotation() { return _rotation; }
FVector& Actor::GetVelocity() { return _velocity; }
int Actor::GetHP() { return _hp; }
int Actor::GetDamage() { return _damage; }
void Actor::SetAlive(bool flag) { _alive = flag; }

void Actor::SetIndex(uint64 index) { _index = index; }
void Actor::SetLocation(FVector location) { _location = location; }
void Actor::SetLocation(float x, float y, float z) { _location._x = x; _location._y = y; _location._z = z; }
void Actor::SetRotation(FRotator rotation) { _rotation = rotation; }
void Actor::SetRotation(float yaw, float pitch, float roll) { _rotation._yaw = yaw; _rotation._pitch = pitch; _rotation._roll = roll; }
void Actor::SetVelocity(FVector velocity) { _velocity = velocity; }
void Actor::SetVelocity(float x, float y, float z) { _velocity._x = x; _velocity._y = y; _velocity._z = z; }
void Actor::SetHP(int hp) { _hp = hp; }
void Actor::SetDamage(int damage) { _damage = damage; }
bool Actor::IsAlive() { return _alive;}

/*------------------------------------------------------------------------
	Player
--------------------------------------------------------------------------*/
bool Player::IsLogin() { return _isLogin; }
void Player::SetLogin(bool flag) { _isLogin = flag; }

/*----------------------------------------------------------------------
	Monster
-------------------------------------------------------------------------*/

void Monster::Update(float deltaTime)
{
	// 0���� ��Ÿ�� ��
	if (_attackCoolTime >= 0)
		_attackCoolTime -= deltaTime;

	switch (_state) {
	case MONSTER_STATE::IDLE:
		UpdateIdle(deltaTime);
		break;
	case MONSTER_STATE::MOVE:
		UpdateMove(deltaTime);
		break;
	case MONSTER_STATE::ATTACK:
		UpdateAttack(deltaTime);
		break;
	default:
		break;
	}
}

void Monster::UpdateIdle(float deltaTime)
{
	// �ֺ��� �÷��̾ �ֳ�
	if (IsPlayerAround()) {
		_state = MONSTER_STATE::MOVE;
	}
	// �ֺ��� ����
	else {
		// TODO : patrol
	}
}

void Monster::UpdateMove(float deltaTime)
{
	// Ÿ���� ��ȿ�ϰ�, �α��� �Ǿ� �ְ�, ��� �ִٸ�
	if (_target && _target->IsLogin() && _target->IsAlive()) {
		// ������ �� �ִ� �Ÿ��ΰ�
		if (IsAttackRangeIn()) {
			// ���� ���� ���ҳ�
			if (IsAttackTime()) {
				_state = MONSTER_STATE::ATTACK;
			}
			// ���� ���� �� �������� �׳� ���, nothing to do
		}
		// ������ �� ���� �Ÿ����
		else {
			Move(deltaTime);
		}
	}
}

void Monster::UpdateAttack(float deltaTime) {
	// Ÿ���� ��ȿ�ϴٸ�
	if (_target && _target->IsLogin() && _target->IsAlive()) {
		// ������ �� �ִ� �Ÿ��ΰ�
		if (IsAttackRangeIn()) {
			// ���� ���� ���ҳ�
			if (IsAttackTime()) {
				Attack(deltaTime);
			}
			// ���� �� �ȵ� ��� nothing
		}

		// ���� ���� ��
		else {
			_state = MONSTER_STATE::MOVE;
		}
	}

	// Ÿ���� ��ȿ���� ����
	else {

	}
}

bool Monster::IsPlayerAround()
{
	map<uint64, shared_ptr<Player>>::iterator it;
	for (it = Room::Instance()->_players.begin(); it != Room::Instance()->_players.end(); it++) {
		shared_ptr<Player> player = it->second;

		// ��, ��, �Ʒ�, ��
		if (GetLocation()._x - _noticeDistance <= player->GetLocation()._x &&
			player->GetLocation()._x <= GetLocation()._x + _noticeDistance &&
			GetLocation()._y - _noticeDistance <= player->GetLocation()._y &&
			player->GetLocation()._y <= GetLocation()._y + _noticeDistance) {

			_target = player;
			return true;
		}
	}

	return false;
}

// -10 -6 -2 2 6 10     // 4
bool Monster::IsAttackRangeIn() {
	// ���� Ÿ���� x,y���̰� ���� ��Ÿ� ������ ��
	if (abs(GetLocation()._x - _target->GetLocation()._x) <= _attackDistance &&
		abs(GetLocation()._y - _target->GetLocation()._y) <= _attackDistance) {
		return true;
	}

	return false;
}

bool Monster::IsAttackTime() {
	if (_attackCoolTime <= 0)
		return true;

	return false;
}

void Monster::Attack(float deltaTime) {
	// Ÿ�� �ǰ� �� ü�� ������Ʈ
	_target->SetHP(_target->GetHP() - GetDamage());

	//LookAt();

	// ���� �� maxcooltime ����
	_attackCoolTime = 1.2f;

	// ��ε� ĳ��Ʈ
	PROTOCOL::S_ATTACK pkt;
	pkt.mutable_attacker()->set_actortype(PROTOCOL::MONSTER);
	pkt.mutable_attacker()->set_index(GetIndex());
	pkt.mutable_attacker()->set_rotationyaw(GetRotation()._yaw);

	PROTOCOL::ACTOR* victim = pkt.add_victims();
	victim->set_actortype(PROTOCOL::PLAYER);
	victim->set_index(_target->GetIndex());
	victim->set_hp(_target->GetHP());

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(pkt);
	Room::Instance()->BroadcastWithoutLock(sendBuffer);
}

void Monster::Move(float deltaTime) {
	// �̵� ���� �ִ� �Ÿ�
	float maxDistanceEachTime = _speed * deltaTime;
	FVector pos = GetLocation();

	// Xpos = ���� �÷��̾��� x�� �Ÿ����� ���� ��Ÿ��� �� �Ÿ��� �̵� ���� �ִ� �Ÿ� �� �� ���� ��
	float moveDistanceX = min(abs(pos._x - _target->GetLocation()._x) - _attackDistance, maxDistanceEachTime);

	// ���� Ÿ���� x�� ������ ��ġ
	if (pos._x <= _target->GetLocation()._x)
		pos._x += moveDistanceX;

	// ���� Ÿ���� x�� ������ ��ġ
	else
		pos._x -= moveDistanceX;

	// Ypos = ���� ���뿡�� y�� �Ÿ�
	float moveDistanceY = min(abs(pos._y - _target->GetLocation()._y) - _attackDistance, maxDistanceEachTime);

	// ���� Ÿ���� y�� �ؿ� ��ġ
	if (pos._y <= _target->GetLocation()._y)
		pos._y += moveDistanceY;

	// ���� Ÿ���� y�� ���� ��ġ
	else
		pos._y -= moveDistanceY;

	// ����� ���� ��ǥ�� ����
	SetLocation(pos);

	// ��ε� ĳ����
	PROTOCOL::S_MOVE pkt;
	PROTOCOL::ACTOR* protoMonster = pkt.mutable_actor();
	protoMonster->set_index(GetIndex());
	protoMonster->set_actortype(PROTOCOL::MONSTER);
	protoMonster->set_locationx(pos._x);
	protoMonster->set_locationy(pos._y);
	protoMonster->set_locationz(pos._z);
	
	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(pkt);
	Room::Instance()->BroadcastWithoutLock(sendBuffer);
}

void Monster::LookAt()
{
	float dirX = _target->GetLocation()._x - GetLocation()._x;
	float dirY = _target->GetLocation()._y - GetLocation()._y;
	double target_yaw = atan2(dirY, dirX);
	double yawInDegrees = target_yaw * 180.0 / 3.14;

	_rotation._yaw = target_yaw;
}


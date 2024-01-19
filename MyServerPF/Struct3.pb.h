// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Struct3.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Struct3_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Struct3_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3019000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3019001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "Enum3.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Struct3_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_Struct3_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Struct3_2eproto;
namespace PROTOCOL {
class ACTOR;
struct ACTORDefaultTypeInternal;
extern ACTORDefaultTypeInternal _ACTOR_default_instance_;
class ACTORLIST;
struct ACTORLISTDefaultTypeInternal;
extern ACTORLISTDefaultTypeInternal _ACTORLIST_default_instance_;
}  // namespace PROTOCOL
PROTOBUF_NAMESPACE_OPEN
template<> ::PROTOCOL::ACTOR* Arena::CreateMaybeMessage<::PROTOCOL::ACTOR>(Arena*);
template<> ::PROTOCOL::ACTORLIST* Arena::CreateMaybeMessage<::PROTOCOL::ACTORLIST>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace PROTOCOL {

// ===================================================================

class ACTOR final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:PROTOCOL.ACTOR) */ {
 public:
  inline ACTOR() : ACTOR(nullptr) {}
  ~ACTOR() override;
  explicit constexpr ACTOR(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  ACTOR(const ACTOR& from);
  ACTOR(ACTOR&& from) noexcept
    : ACTOR() {
    *this = ::std::move(from);
  }

  inline ACTOR& operator=(const ACTOR& from) {
    CopyFrom(from);
    return *this;
  }
  inline ACTOR& operator=(ACTOR&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const ACTOR& default_instance() {
    return *internal_default_instance();
  }
  static inline const ACTOR* internal_default_instance() {
    return reinterpret_cast<const ACTOR*>(
               &_ACTOR_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(ACTOR& a, ACTOR& b) {
    a.Swap(&b);
  }
  inline void Swap(ACTOR* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(ACTOR* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  ACTOR* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<ACTOR>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const ACTOR& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const ACTOR& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ACTOR* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "PROTOCOL.ACTOR";
  }
  protected:
  explicit ACTOR(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kIDFieldNumber = 13,
    kIndexFieldNumber = 1,
    kActortypeFieldNumber = 2,
    kLocationXFieldNumber = 3,
    kLocationYFieldNumber = 4,
    kLocationZFieldNumber = 5,
    kRotationYawFieldNumber = 6,
    kRotationPitchFieldNumber = 7,
    kRotationRollFieldNumber = 8,
    kVelocityXFieldNumber = 9,
    kVelocityYFieldNumber = 10,
    kVelocityZFieldNumber = 11,
    kHpFieldNumber = 12,
  };
  // string ID = 13;
  void clear_id();
  const std::string& id() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_id(ArgT0&& arg0, ArgT... args);
  std::string* mutable_id();
  PROTOBUF_NODISCARD std::string* release_id();
  void set_allocated_id(std::string* id);
  private:
  const std::string& _internal_id() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_id(const std::string& value);
  std::string* _internal_mutable_id();
  public:

  // uint64 index = 1;
  void clear_index();
  uint64_t index() const;
  void set_index(uint64_t value);
  private:
  uint64_t _internal_index() const;
  void _internal_set_index(uint64_t value);
  public:

  // .PROTOCOL.ACTOR_TYPE actortype = 2;
  void clear_actortype();
  ::PROTOCOL::ACTOR_TYPE actortype() const;
  void set_actortype(::PROTOCOL::ACTOR_TYPE value);
  private:
  ::PROTOCOL::ACTOR_TYPE _internal_actortype() const;
  void _internal_set_actortype(::PROTOCOL::ACTOR_TYPE value);
  public:

  // float locationX = 3;
  void clear_locationx();
  float locationx() const;
  void set_locationx(float value);
  private:
  float _internal_locationx() const;
  void _internal_set_locationx(float value);
  public:

  // float locationY = 4;
  void clear_locationy();
  float locationy() const;
  void set_locationy(float value);
  private:
  float _internal_locationy() const;
  void _internal_set_locationy(float value);
  public:

  // float locationZ = 5;
  void clear_locationz();
  float locationz() const;
  void set_locationz(float value);
  private:
  float _internal_locationz() const;
  void _internal_set_locationz(float value);
  public:

  // float rotationYaw = 6;
  void clear_rotationyaw();
  float rotationyaw() const;
  void set_rotationyaw(float value);
  private:
  float _internal_rotationyaw() const;
  void _internal_set_rotationyaw(float value);
  public:

  // float rotationPitch = 7;
  void clear_rotationpitch();
  float rotationpitch() const;
  void set_rotationpitch(float value);
  private:
  float _internal_rotationpitch() const;
  void _internal_set_rotationpitch(float value);
  public:

  // float rotationRoll = 8;
  void clear_rotationroll();
  float rotationroll() const;
  void set_rotationroll(float value);
  private:
  float _internal_rotationroll() const;
  void _internal_set_rotationroll(float value);
  public:

  // float velocityX = 9;
  void clear_velocityx();
  float velocityx() const;
  void set_velocityx(float value);
  private:
  float _internal_velocityx() const;
  void _internal_set_velocityx(float value);
  public:

  // float velocityY = 10;
  void clear_velocityy();
  float velocityy() const;
  void set_velocityy(float value);
  private:
  float _internal_velocityy() const;
  void _internal_set_velocityy(float value);
  public:

  // float velocityZ = 11;
  void clear_velocityz();
  float velocityz() const;
  void set_velocityz(float value);
  private:
  float _internal_velocityz() const;
  void _internal_set_velocityz(float value);
  public:

  // float hp = 12;
  void clear_hp();
  float hp() const;
  void set_hp(float value);
  private:
  float _internal_hp() const;
  void _internal_set_hp(float value);
  public:

  // @@protoc_insertion_point(class_scope:PROTOCOL.ACTOR)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr id_;
  uint64_t index_;
  int actortype_;
  float locationx_;
  float locationy_;
  float locationz_;
  float rotationyaw_;
  float rotationpitch_;
  float rotationroll_;
  float velocityx_;
  float velocityy_;
  float velocityz_;
  float hp_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Struct3_2eproto;
};
// -------------------------------------------------------------------

class ACTORLIST final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:PROTOCOL.ACTORLIST) */ {
 public:
  inline ACTORLIST() : ACTORLIST(nullptr) {}
  ~ACTORLIST() override;
  explicit constexpr ACTORLIST(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  ACTORLIST(const ACTORLIST& from);
  ACTORLIST(ACTORLIST&& from) noexcept
    : ACTORLIST() {
    *this = ::std::move(from);
  }

  inline ACTORLIST& operator=(const ACTORLIST& from) {
    CopyFrom(from);
    return *this;
  }
  inline ACTORLIST& operator=(ACTORLIST&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const ACTORLIST& default_instance() {
    return *internal_default_instance();
  }
  static inline const ACTORLIST* internal_default_instance() {
    return reinterpret_cast<const ACTORLIST*>(
               &_ACTORLIST_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(ACTORLIST& a, ACTORLIST& b) {
    a.Swap(&b);
  }
  inline void Swap(ACTORLIST* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(ACTORLIST* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  ACTORLIST* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<ACTORLIST>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const ACTORLIST& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const ACTORLIST& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ACTORLIST* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "PROTOCOL.ACTORLIST";
  }
  protected:
  explicit ACTORLIST(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kPlayersFieldNumber = 1,
  };
  // repeated .PROTOCOL.ACTOR players = 1;
  int players_size() const;
  private:
  int _internal_players_size() const;
  public:
  void clear_players();
  ::PROTOCOL::ACTOR* mutable_players(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::PROTOCOL::ACTOR >*
      mutable_players();
  private:
  const ::PROTOCOL::ACTOR& _internal_players(int index) const;
  ::PROTOCOL::ACTOR* _internal_add_players();
  public:
  const ::PROTOCOL::ACTOR& players(int index) const;
  ::PROTOCOL::ACTOR* add_players();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::PROTOCOL::ACTOR >&
      players() const;

  // @@protoc_insertion_point(class_scope:PROTOCOL.ACTORLIST)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::PROTOCOL::ACTOR > players_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Struct3_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ACTOR

// uint64 index = 1;
inline void ACTOR::clear_index() {
  index_ = uint64_t{0u};
}
inline uint64_t ACTOR::_internal_index() const {
  return index_;
}
inline uint64_t ACTOR::index() const {
  // @@protoc_insertion_point(field_get:PROTOCOL.ACTOR.index)
  return _internal_index();
}
inline void ACTOR::_internal_set_index(uint64_t value) {
  
  index_ = value;
}
inline void ACTOR::set_index(uint64_t value) {
  _internal_set_index(value);
  // @@protoc_insertion_point(field_set:PROTOCOL.ACTOR.index)
}

// .PROTOCOL.ACTOR_TYPE actortype = 2;
inline void ACTOR::clear_actortype() {
  actortype_ = 0;
}
inline ::PROTOCOL::ACTOR_TYPE ACTOR::_internal_actortype() const {
  return static_cast< ::PROTOCOL::ACTOR_TYPE >(actortype_);
}
inline ::PROTOCOL::ACTOR_TYPE ACTOR::actortype() const {
  // @@protoc_insertion_point(field_get:PROTOCOL.ACTOR.actortype)
  return _internal_actortype();
}
inline void ACTOR::_internal_set_actortype(::PROTOCOL::ACTOR_TYPE value) {
  
  actortype_ = value;
}
inline void ACTOR::set_actortype(::PROTOCOL::ACTOR_TYPE value) {
  _internal_set_actortype(value);
  // @@protoc_insertion_point(field_set:PROTOCOL.ACTOR.actortype)
}

// float locationX = 3;
inline void ACTOR::clear_locationx() {
  locationx_ = 0;
}
inline float ACTOR::_internal_locationx() const {
  return locationx_;
}
inline float ACTOR::locationx() const {
  // @@protoc_insertion_point(field_get:PROTOCOL.ACTOR.locationX)
  return _internal_locationx();
}
inline void ACTOR::_internal_set_locationx(float value) {
  
  locationx_ = value;
}
inline void ACTOR::set_locationx(float value) {
  _internal_set_locationx(value);
  // @@protoc_insertion_point(field_set:PROTOCOL.ACTOR.locationX)
}

// float locationY = 4;
inline void ACTOR::clear_locationy() {
  locationy_ = 0;
}
inline float ACTOR::_internal_locationy() const {
  return locationy_;
}
inline float ACTOR::locationy() const {
  // @@protoc_insertion_point(field_get:PROTOCOL.ACTOR.locationY)
  return _internal_locationy();
}
inline void ACTOR::_internal_set_locationy(float value) {
  
  locationy_ = value;
}
inline void ACTOR::set_locationy(float value) {
  _internal_set_locationy(value);
  // @@protoc_insertion_point(field_set:PROTOCOL.ACTOR.locationY)
}

// float locationZ = 5;
inline void ACTOR::clear_locationz() {
  locationz_ = 0;
}
inline float ACTOR::_internal_locationz() const {
  return locationz_;
}
inline float ACTOR::locationz() const {
  // @@protoc_insertion_point(field_get:PROTOCOL.ACTOR.locationZ)
  return _internal_locationz();
}
inline void ACTOR::_internal_set_locationz(float value) {
  
  locationz_ = value;
}
inline void ACTOR::set_locationz(float value) {
  _internal_set_locationz(value);
  // @@protoc_insertion_point(field_set:PROTOCOL.ACTOR.locationZ)
}

// float rotationYaw = 6;
inline void ACTOR::clear_rotationyaw() {
  rotationyaw_ = 0;
}
inline float ACTOR::_internal_rotationyaw() const {
  return rotationyaw_;
}
inline float ACTOR::rotationyaw() const {
  // @@protoc_insertion_point(field_get:PROTOCOL.ACTOR.rotationYaw)
  return _internal_rotationyaw();
}
inline void ACTOR::_internal_set_rotationyaw(float value) {
  
  rotationyaw_ = value;
}
inline void ACTOR::set_rotationyaw(float value) {
  _internal_set_rotationyaw(value);
  // @@protoc_insertion_point(field_set:PROTOCOL.ACTOR.rotationYaw)
}

// float rotationPitch = 7;
inline void ACTOR::clear_rotationpitch() {
  rotationpitch_ = 0;
}
inline float ACTOR::_internal_rotationpitch() const {
  return rotationpitch_;
}
inline float ACTOR::rotationpitch() const {
  // @@protoc_insertion_point(field_get:PROTOCOL.ACTOR.rotationPitch)
  return _internal_rotationpitch();
}
inline void ACTOR::_internal_set_rotationpitch(float value) {
  
  rotationpitch_ = value;
}
inline void ACTOR::set_rotationpitch(float value) {
  _internal_set_rotationpitch(value);
  // @@protoc_insertion_point(field_set:PROTOCOL.ACTOR.rotationPitch)
}

// float rotationRoll = 8;
inline void ACTOR::clear_rotationroll() {
  rotationroll_ = 0;
}
inline float ACTOR::_internal_rotationroll() const {
  return rotationroll_;
}
inline float ACTOR::rotationroll() const {
  // @@protoc_insertion_point(field_get:PROTOCOL.ACTOR.rotationRoll)
  return _internal_rotationroll();
}
inline void ACTOR::_internal_set_rotationroll(float value) {
  
  rotationroll_ = value;
}
inline void ACTOR::set_rotationroll(float value) {
  _internal_set_rotationroll(value);
  // @@protoc_insertion_point(field_set:PROTOCOL.ACTOR.rotationRoll)
}

// float velocityX = 9;
inline void ACTOR::clear_velocityx() {
  velocityx_ = 0;
}
inline float ACTOR::_internal_velocityx() const {
  return velocityx_;
}
inline float ACTOR::velocityx() const {
  // @@protoc_insertion_point(field_get:PROTOCOL.ACTOR.velocityX)
  return _internal_velocityx();
}
inline void ACTOR::_internal_set_velocityx(float value) {
  
  velocityx_ = value;
}
inline void ACTOR::set_velocityx(float value) {
  _internal_set_velocityx(value);
  // @@protoc_insertion_point(field_set:PROTOCOL.ACTOR.velocityX)
}

// float velocityY = 10;
inline void ACTOR::clear_velocityy() {
  velocityy_ = 0;
}
inline float ACTOR::_internal_velocityy() const {
  return velocityy_;
}
inline float ACTOR::velocityy() const {
  // @@protoc_insertion_point(field_get:PROTOCOL.ACTOR.velocityY)
  return _internal_velocityy();
}
inline void ACTOR::_internal_set_velocityy(float value) {
  
  velocityy_ = value;
}
inline void ACTOR::set_velocityy(float value) {
  _internal_set_velocityy(value);
  // @@protoc_insertion_point(field_set:PROTOCOL.ACTOR.velocityY)
}

// float velocityZ = 11;
inline void ACTOR::clear_velocityz() {
  velocityz_ = 0;
}
inline float ACTOR::_internal_velocityz() const {
  return velocityz_;
}
inline float ACTOR::velocityz() const {
  // @@protoc_insertion_point(field_get:PROTOCOL.ACTOR.velocityZ)
  return _internal_velocityz();
}
inline void ACTOR::_internal_set_velocityz(float value) {
  
  velocityz_ = value;
}
inline void ACTOR::set_velocityz(float value) {
  _internal_set_velocityz(value);
  // @@protoc_insertion_point(field_set:PROTOCOL.ACTOR.velocityZ)
}

// float hp = 12;
inline void ACTOR::clear_hp() {
  hp_ = 0;
}
inline float ACTOR::_internal_hp() const {
  return hp_;
}
inline float ACTOR::hp() const {
  // @@protoc_insertion_point(field_get:PROTOCOL.ACTOR.hp)
  return _internal_hp();
}
inline void ACTOR::_internal_set_hp(float value) {
  
  hp_ = value;
}
inline void ACTOR::set_hp(float value) {
  _internal_set_hp(value);
  // @@protoc_insertion_point(field_set:PROTOCOL.ACTOR.hp)
}

// string ID = 13;
inline void ACTOR::clear_id() {
  id_.ClearToEmpty();
}
inline const std::string& ACTOR::id() const {
  // @@protoc_insertion_point(field_get:PROTOCOL.ACTOR.ID)
  return _internal_id();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void ACTOR::set_id(ArgT0&& arg0, ArgT... args) {
 
 id_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:PROTOCOL.ACTOR.ID)
}
inline std::string* ACTOR::mutable_id() {
  std::string* _s = _internal_mutable_id();
  // @@protoc_insertion_point(field_mutable:PROTOCOL.ACTOR.ID)
  return _s;
}
inline const std::string& ACTOR::_internal_id() const {
  return id_.Get();
}
inline void ACTOR::_internal_set_id(const std::string& value) {
  
  id_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* ACTOR::_internal_mutable_id() {
  
  return id_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* ACTOR::release_id() {
  // @@protoc_insertion_point(field_release:PROTOCOL.ACTOR.ID)
  return id_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void ACTOR::set_allocated_id(std::string* id) {
  if (id != nullptr) {
    
  } else {
    
  }
  id_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), id,
      GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (id_.IsDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited())) {
    id_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:PROTOCOL.ACTOR.ID)
}

// -------------------------------------------------------------------

// ACTORLIST

// repeated .PROTOCOL.ACTOR players = 1;
inline int ACTORLIST::_internal_players_size() const {
  return players_.size();
}
inline int ACTORLIST::players_size() const {
  return _internal_players_size();
}
inline void ACTORLIST::clear_players() {
  players_.Clear();
}
inline ::PROTOCOL::ACTOR* ACTORLIST::mutable_players(int index) {
  // @@protoc_insertion_point(field_mutable:PROTOCOL.ACTORLIST.players)
  return players_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::PROTOCOL::ACTOR >*
ACTORLIST::mutable_players() {
  // @@protoc_insertion_point(field_mutable_list:PROTOCOL.ACTORLIST.players)
  return &players_;
}
inline const ::PROTOCOL::ACTOR& ACTORLIST::_internal_players(int index) const {
  return players_.Get(index);
}
inline const ::PROTOCOL::ACTOR& ACTORLIST::players(int index) const {
  // @@protoc_insertion_point(field_get:PROTOCOL.ACTORLIST.players)
  return _internal_players(index);
}
inline ::PROTOCOL::ACTOR* ACTORLIST::_internal_add_players() {
  return players_.Add();
}
inline ::PROTOCOL::ACTOR* ACTORLIST::add_players() {
  ::PROTOCOL::ACTOR* _add = _internal_add_players();
  // @@protoc_insertion_point(field_add:PROTOCOL.ACTORLIST.players)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::PROTOCOL::ACTOR >&
ACTORLIST::players() const {
  // @@protoc_insertion_point(field_list:PROTOCOL.ACTORLIST.players)
  return players_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace PROTOCOL

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Struct3_2eproto
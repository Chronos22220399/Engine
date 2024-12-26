// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: query.proto
// Protobuf C++ Version: 5.28.3

#include "query.pb.h"

#include <algorithm>
#include <type_traits>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/generated_message_tctable_impl.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;

inline constexpr QueryResponse::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : docid_{},
        _docid_cached_byte_size_{0},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR QueryResponse::QueryResponse(::_pbi::ConstantInitialized)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(_class_data_.base()),
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(),
#endif  // PROTOBUF_CUSTOM_VTABLE
      _impl_(::_pbi::ConstantInitialized()) {
}
struct QueryResponseDefaultTypeInternal {
  PROTOBUF_CONSTEXPR QueryResponseDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~QueryResponseDefaultTypeInternal() {}
  union {
    QueryResponse _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 QueryResponseDefaultTypeInternal _QueryResponse_default_instance_;

inline constexpr QueryRequest::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : querycontent_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        querymode_{static_cast< ::QueryMode >(0)},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR QueryRequest::QueryRequest(::_pbi::ConstantInitialized)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(_class_data_.base()),
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(),
#endif  // PROTOBUF_CUSTOM_VTABLE
      _impl_(::_pbi::ConstantInitialized()) {
}
struct QueryRequestDefaultTypeInternal {
  PROTOBUF_CONSTEXPR QueryRequestDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~QueryRequestDefaultTypeInternal() {}
  union {
    QueryRequest _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 QueryRequestDefaultTypeInternal _QueryRequest_default_instance_;
static const ::_pb::EnumDescriptor* file_level_enum_descriptors_query_2eproto[1];
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_query_2eproto = nullptr;
const ::uint32_t
    TableStruct_query_2eproto::offsets[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
        protodesc_cold) = {
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::QueryRequest, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::QueryRequest, _impl_.querymode_),
        PROTOBUF_FIELD_OFFSET(::QueryRequest, _impl_.querycontent_),
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::QueryResponse, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::QueryResponse, _impl_.docid_),
};

static const ::_pbi::MigrationSchema
    schemas[] ABSL_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
        {0, -1, -1, sizeof(::QueryRequest)},
        {10, -1, -1, sizeof(::QueryResponse)},
};
static const ::_pb::Message* const file_default_instances[] = {
    &::_QueryRequest_default_instance_._instance,
    &::_QueryResponse_default_instance_._instance,
};
const char descriptor_table_protodef_query_2eproto[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
    protodesc_cold) = {
    "\n\013query.proto\"C\n\014QueryRequest\022\035\n\tqueryMo"
    "de\030\001 \001(\0162\n.QueryMode\022\024\n\014queryContent\030\002 \001"
    "(\t\"\036\n\rQueryResponse\022\r\n\005docId\030\001 \003(\r*%\n\tQu"
    "eryMode\022\n\n\006Normal\020\000\022\014\n\010Advanced\020\0012=\n\016Que"
    "ryProcessor\022+\n\nQueryDocId\022\r.QueryRequest"
    "\032\016.QueryResponseb\006proto3"
};
static ::absl::once_flag descriptor_table_query_2eproto_once;
PROTOBUF_CONSTINIT const ::_pbi::DescriptorTable descriptor_table_query_2eproto = {
    false,
    false,
    224,
    descriptor_table_protodef_query_2eproto,
    "query.proto",
    &descriptor_table_query_2eproto_once,
    nullptr,
    0,
    2,
    schemas,
    file_default_instances,
    TableStruct_query_2eproto::offsets,
    file_level_enum_descriptors_query_2eproto,
    file_level_service_descriptors_query_2eproto,
};
const ::google::protobuf::EnumDescriptor* QueryMode_descriptor() {
  ::google::protobuf::internal::AssignDescriptors(&descriptor_table_query_2eproto);
  return file_level_enum_descriptors_query_2eproto[0];
}
PROTOBUF_CONSTINIT const uint32_t QueryMode_internal_data_[] = {
    131072u, 0u, };
bool QueryMode_IsValid(int value) {
  return 0 <= value && value <= 1;
}
// ===================================================================

class QueryRequest::_Internal {
 public:
};

QueryRequest::QueryRequest(::google::protobuf::Arena* arena)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:QueryRequest)
}
inline PROTOBUF_NDEBUG_INLINE QueryRequest::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from, const ::QueryRequest& from_msg)
      : querycontent_(arena, from.querycontent_),
        _cached_size_{0} {}

QueryRequest::QueryRequest(
    ::google::protobuf::Arena* arena,
    const QueryRequest& from)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  QueryRequest* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_, from);
  _impl_.querymode_ = from._impl_.querymode_;

  // @@protoc_insertion_point(copy_constructor:QueryRequest)
}
inline PROTOBUF_NDEBUG_INLINE QueryRequest::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : querycontent_(arena),
        _cached_size_{0} {}

inline void QueryRequest::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  _impl_.querymode_ = {};
}
QueryRequest::~QueryRequest() {
  // @@protoc_insertion_point(destructor:QueryRequest)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void QueryRequest::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.querycontent_.Destroy();
  _impl_.~Impl_();
}

PROTOBUF_CONSTINIT
PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::google::protobuf::MessageLite::ClassDataFull
    QueryRequest::_class_data_ = {
        ::google::protobuf::Message::ClassData{
            &_QueryRequest_default_instance_._instance,
            &_table_.header,
            nullptr,  // OnDemandRegisterArenaDtor
            nullptr,  // IsInitialized
            &QueryRequest::MergeImpl,
#if defined(PROTOBUF_CUSTOM_VTABLE)
            ::google::protobuf::Message::GetDeleteImpl<QueryRequest>(),
            ::google::protobuf::Message::GetNewImpl<QueryRequest>(),
            ::google::protobuf::Message::GetClearImpl<QueryRequest>(), &QueryRequest::ByteSizeLong,
                &QueryRequest::_InternalSerialize,
#endif  // PROTOBUF_CUSTOM_VTABLE
            PROTOBUF_FIELD_OFFSET(QueryRequest, _impl_._cached_size_),
            false,
        },
        &QueryRequest::kDescriptorMethods,
        &descriptor_table_query_2eproto,
        nullptr,  // tracker
};
const ::google::protobuf::MessageLite::ClassData* QueryRequest::GetClassData() const {
  ::google::protobuf::internal::PrefetchToLocalCache(&_class_data_);
  ::google::protobuf::internal::PrefetchToLocalCache(_class_data_.tc_table);
  return _class_data_.base();
}
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<1, 2, 0, 33, 2> QueryRequest::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    2, 8,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967292,  // skipmap
    offsetof(decltype(_table_), field_entries),
    2,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    _class_data_.base(),
    nullptr,  // post_loop_handler
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::QueryRequest>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // string queryContent = 2;
    {::_pbi::TcParser::FastUS1,
     {18, 63, 0, PROTOBUF_FIELD_OFFSET(QueryRequest, _impl_.querycontent_)}},
    // .QueryMode queryMode = 1;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint32_t, offsetof(QueryRequest, _impl_.querymode_), 63>(),
     {8, 63, 0, PROTOBUF_FIELD_OFFSET(QueryRequest, _impl_.querymode_)}},
  }}, {{
    65535, 65535
  }}, {{
    // .QueryMode queryMode = 1;
    {PROTOBUF_FIELD_OFFSET(QueryRequest, _impl_.querymode_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kOpenEnum)},
    // string queryContent = 2;
    {PROTOBUF_FIELD_OFFSET(QueryRequest, _impl_.querycontent_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
  }},
  // no aux_entries
  {{
    "\14\0\14\0\0\0\0\0"
    "QueryRequest"
    "queryContent"
  }},
};

PROTOBUF_NOINLINE void QueryRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:QueryRequest)
  ::google::protobuf::internal::TSanWrite(&_impl_);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.querycontent_.ClearToEmpty();
  _impl_.querymode_ = 0;
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

#if defined(PROTOBUF_CUSTOM_VTABLE)
        ::uint8_t* QueryRequest::_InternalSerialize(
            const MessageLite& base, ::uint8_t* target,
            ::google::protobuf::io::EpsCopyOutputStream* stream) {
          const QueryRequest& this_ = static_cast<const QueryRequest&>(base);
#else   // PROTOBUF_CUSTOM_VTABLE
        ::uint8_t* QueryRequest::_InternalSerialize(
            ::uint8_t* target,
            ::google::protobuf::io::EpsCopyOutputStream* stream) const {
          const QueryRequest& this_ = *this;
#endif  // PROTOBUF_CUSTOM_VTABLE
          // @@protoc_insertion_point(serialize_to_array_start:QueryRequest)
          ::uint32_t cached_has_bits = 0;
          (void)cached_has_bits;

          // .QueryMode queryMode = 1;
          if (this_._internal_querymode() != 0) {
            target = stream->EnsureSpace(target);
            target = ::_pbi::WireFormatLite::WriteEnumToArray(
                1, this_._internal_querymode(), target);
          }

          // string queryContent = 2;
          if (!this_._internal_querycontent().empty()) {
            const std::string& _s = this_._internal_querycontent();
            ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
                _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "QueryRequest.queryContent");
            target = stream->WriteStringMaybeAliased(2, _s, target);
          }

          if (PROTOBUF_PREDICT_FALSE(this_._internal_metadata_.have_unknown_fields())) {
            target =
                ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
                    this_._internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
          }
          // @@protoc_insertion_point(serialize_to_array_end:QueryRequest)
          return target;
        }

#if defined(PROTOBUF_CUSTOM_VTABLE)
        ::size_t QueryRequest::ByteSizeLong(const MessageLite& base) {
          const QueryRequest& this_ = static_cast<const QueryRequest&>(base);
#else   // PROTOBUF_CUSTOM_VTABLE
        ::size_t QueryRequest::ByteSizeLong() const {
          const QueryRequest& this_ = *this;
#endif  // PROTOBUF_CUSTOM_VTABLE
          // @@protoc_insertion_point(message_byte_size_start:QueryRequest)
          ::size_t total_size = 0;

          ::uint32_t cached_has_bits = 0;
          // Prevent compiler warnings about cached_has_bits being unused
          (void)cached_has_bits;

          ::_pbi::Prefetch5LinesFrom7Lines(&this_);
           {
            // string queryContent = 2;
            if (!this_._internal_querycontent().empty()) {
              total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                              this_._internal_querycontent());
            }
            // .QueryMode queryMode = 1;
            if (this_._internal_querymode() != 0) {
              total_size += 1 +
                            ::_pbi::WireFormatLite::EnumSize(this_._internal_querymode());
            }
          }
          return this_.MaybeComputeUnknownFieldsSize(total_size,
                                                     &this_._impl_._cached_size_);
        }

void QueryRequest::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<QueryRequest*>(&to_msg);
  auto& from = static_cast<const QueryRequest&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:QueryRequest)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_querycontent().empty()) {
    _this->_internal_set_querycontent(from._internal_querycontent());
  }
  if (from._internal_querymode() != 0) {
    _this->_impl_.querymode_ = from._impl_.querymode_;
  }
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void QueryRequest::CopyFrom(const QueryRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:QueryRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}


void QueryRequest::InternalSwap(QueryRequest* PROTOBUF_RESTRICT other) {
  using std::swap;
  auto* arena = GetArena();
  ABSL_DCHECK_EQ(arena, other->GetArena());
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.querycontent_, &other->_impl_.querycontent_, arena);
  swap(_impl_.querymode_, other->_impl_.querymode_);
}

::google::protobuf::Metadata QueryRequest::GetMetadata() const {
  return ::google::protobuf::Message::GetMetadataImpl(GetClassData()->full());
}
// ===================================================================

class QueryResponse::_Internal {
 public:
};

QueryResponse::QueryResponse(::google::protobuf::Arena* arena)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:QueryResponse)
}
inline PROTOBUF_NDEBUG_INLINE QueryResponse::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from, const ::QueryResponse& from_msg)
      : docid_{visibility, arena, from.docid_},
        _docid_cached_byte_size_{0},
        _cached_size_{0} {}

QueryResponse::QueryResponse(
    ::google::protobuf::Arena* arena,
    const QueryResponse& from)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  QueryResponse* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_, from);

  // @@protoc_insertion_point(copy_constructor:QueryResponse)
}
inline PROTOBUF_NDEBUG_INLINE QueryResponse::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : docid_{visibility, arena},
        _docid_cached_byte_size_{0},
        _cached_size_{0} {}

inline void QueryResponse::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
}
QueryResponse::~QueryResponse() {
  // @@protoc_insertion_point(destructor:QueryResponse)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void QueryResponse::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.~Impl_();
}

PROTOBUF_CONSTINIT
PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::google::protobuf::MessageLite::ClassDataFull
    QueryResponse::_class_data_ = {
        ::google::protobuf::Message::ClassData{
            &_QueryResponse_default_instance_._instance,
            &_table_.header,
            nullptr,  // OnDemandRegisterArenaDtor
            nullptr,  // IsInitialized
            &QueryResponse::MergeImpl,
#if defined(PROTOBUF_CUSTOM_VTABLE)
            ::google::protobuf::Message::GetDeleteImpl<QueryResponse>(),
            ::google::protobuf::Message::GetNewImpl<QueryResponse>(),
            ::google::protobuf::Message::GetClearImpl<QueryResponse>(), &QueryResponse::ByteSizeLong,
                &QueryResponse::_InternalSerialize,
#endif  // PROTOBUF_CUSTOM_VTABLE
            PROTOBUF_FIELD_OFFSET(QueryResponse, _impl_._cached_size_),
            false,
        },
        &QueryResponse::kDescriptorMethods,
        &descriptor_table_query_2eproto,
        nullptr,  // tracker
};
const ::google::protobuf::MessageLite::ClassData* QueryResponse::GetClassData() const {
  ::google::protobuf::internal::PrefetchToLocalCache(&_class_data_);
  ::google::protobuf::internal::PrefetchToLocalCache(_class_data_.tc_table);
  return _class_data_.base();
}
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<0, 1, 0, 0, 2> QueryResponse::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    1, 0,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967294,  // skipmap
    offsetof(decltype(_table_), field_entries),
    1,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    _class_data_.base(),
    nullptr,  // post_loop_handler
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::QueryResponse>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // repeated uint32 docId = 1;
    {::_pbi::TcParser::FastV32P1,
     {10, 63, 0, PROTOBUF_FIELD_OFFSET(QueryResponse, _impl_.docid_)}},
  }}, {{
    65535, 65535
  }}, {{
    // repeated uint32 docId = 1;
    {PROTOBUF_FIELD_OFFSET(QueryResponse, _impl_.docid_), 0, 0,
    (0 | ::_fl::kFcRepeated | ::_fl::kPackedUInt32)},
  }},
  // no aux_entries
  {{
  }},
};

PROTOBUF_NOINLINE void QueryResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:QueryResponse)
  ::google::protobuf::internal::TSanWrite(&_impl_);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.docid_.Clear();
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

#if defined(PROTOBUF_CUSTOM_VTABLE)
        ::uint8_t* QueryResponse::_InternalSerialize(
            const MessageLite& base, ::uint8_t* target,
            ::google::protobuf::io::EpsCopyOutputStream* stream) {
          const QueryResponse& this_ = static_cast<const QueryResponse&>(base);
#else   // PROTOBUF_CUSTOM_VTABLE
        ::uint8_t* QueryResponse::_InternalSerialize(
            ::uint8_t* target,
            ::google::protobuf::io::EpsCopyOutputStream* stream) const {
          const QueryResponse& this_ = *this;
#endif  // PROTOBUF_CUSTOM_VTABLE
          // @@protoc_insertion_point(serialize_to_array_start:QueryResponse)
          ::uint32_t cached_has_bits = 0;
          (void)cached_has_bits;

          // repeated uint32 docId = 1;
          {
            int byte_size = this_._impl_._docid_cached_byte_size_.Get();
            if (byte_size > 0) {
              target = stream->WriteUInt32Packed(
                  1, this_._internal_docid(), byte_size, target);
            }
          }

          if (PROTOBUF_PREDICT_FALSE(this_._internal_metadata_.have_unknown_fields())) {
            target =
                ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
                    this_._internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
          }
          // @@protoc_insertion_point(serialize_to_array_end:QueryResponse)
          return target;
        }

#if defined(PROTOBUF_CUSTOM_VTABLE)
        ::size_t QueryResponse::ByteSizeLong(const MessageLite& base) {
          const QueryResponse& this_ = static_cast<const QueryResponse&>(base);
#else   // PROTOBUF_CUSTOM_VTABLE
        ::size_t QueryResponse::ByteSizeLong() const {
          const QueryResponse& this_ = *this;
#endif  // PROTOBUF_CUSTOM_VTABLE
          // @@protoc_insertion_point(message_byte_size_start:QueryResponse)
          ::size_t total_size = 0;

          ::uint32_t cached_has_bits = 0;
          // Prevent compiler warnings about cached_has_bits being unused
          (void)cached_has_bits;

          ::_pbi::Prefetch5LinesFrom7Lines(&this_);
           {
            // repeated uint32 docId = 1;
             {
              std::size_t data_size = ::_pbi::WireFormatLite::UInt32Size(
                  this_._internal_docid())
              ;
              this_._impl_._docid_cached_byte_size_.Set(
                  ::_pbi::ToCachedSize(data_size));
              std::size_t tag_size = data_size == 0
                  ? 0
                  : 1 + ::_pbi::WireFormatLite::Int32Size(
                                      static_cast<int32_t>(data_size))
              ;
              total_size += tag_size + data_size;
            }
          }
          return this_.MaybeComputeUnknownFieldsSize(total_size,
                                                     &this_._impl_._cached_size_);
        }

void QueryResponse::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<QueryResponse*>(&to_msg);
  auto& from = static_cast<const QueryResponse&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:QueryResponse)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_internal_mutable_docid()->MergeFrom(from._internal_docid());
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void QueryResponse::CopyFrom(const QueryResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:QueryResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}


void QueryResponse::InternalSwap(QueryResponse* PROTOBUF_RESTRICT other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.docid_.InternalSwap(&other->_impl_.docid_);
}

::google::protobuf::Metadata QueryResponse::GetMetadata() const {
  return ::google::protobuf::Message::GetMetadataImpl(GetClassData()->full());
}
// @@protoc_insertion_point(namespace_scope)
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::std::false_type
    _static_init2_ PROTOBUF_UNUSED =
        (::_pbi::AddDescriptors(&descriptor_table_query_2eproto),
         ::std::false_type{});
#include "google/protobuf/port_undef.inc"

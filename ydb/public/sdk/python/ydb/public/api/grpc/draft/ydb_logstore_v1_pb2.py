# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: ydb/public/api/grpc/draft/ydb_logstore_v1.proto
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from ydb.public.api.protos.draft import ydb_logstore_pb2 as ydb_dot_public_dot_api_dot_protos_dot_draft_dot_ydb__logstore__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='ydb/public/api/grpc/draft/ydb_logstore_v1.proto',
  package='Ydb.LogStore.V1',
  syntax='proto3',
  serialized_options=b'\n\032com.yandex.ydb.logstore.v1',
  create_key=_descriptor._internal_create_key,
  serialized_pb=b'\n/ydb/public/api/grpc/draft/ydb_logstore_v1.proto\x12\x0fYdb.LogStore.V1\x1a.ydb/public/api/protos/draft/ydb_logstore.proto2\x99\x05\n\x0fLogStoreService\x12[\n\x0e\x43reateLogStore\x12#.Ydb.LogStore.CreateLogStoreRequest\x1a$.Ydb.LogStore.CreateLogStoreResponse\x12\x61\n\x10\x44\x65scribeLogStore\x12%.Ydb.LogStore.DescribeLogStoreRequest\x1a&.Ydb.LogStore.DescribeLogStoreResponse\x12U\n\x0c\x44ropLogStore\x12!.Ydb.LogStore.DropLogStoreRequest\x1a\".Ydb.LogStore.DropLogStoreResponse\x12[\n\x0e\x43reateLogTable\x12#.Ydb.LogStore.CreateLogTableRequest\x1a$.Ydb.LogStore.CreateLogTableResponse\x12\x61\n\x10\x44\x65scribeLogTable\x12%.Ydb.LogStore.DescribeLogTableRequest\x1a&.Ydb.LogStore.DescribeLogTableResponse\x12U\n\x0c\x44ropLogTable\x12!.Ydb.LogStore.DropLogTableRequest\x1a\".Ydb.LogStore.DropLogTableResponse\x12X\n\rAlterLogTable\x12\".Ydb.LogStore.AlterLogTableRequest\x1a#.Ydb.LogStore.AlterLogTableResponseB\x1c\n\x1a\x63om.yandex.ydb.logstore.v1b\x06proto3'
  ,
  dependencies=[ydb_dot_public_dot_api_dot_protos_dot_draft_dot_ydb__logstore__pb2.DESCRIPTOR,])



_sym_db.RegisterFileDescriptor(DESCRIPTOR)


DESCRIPTOR._options = None

_LOGSTORESERVICE = _descriptor.ServiceDescriptor(
  name='LogStoreService',
  full_name='Ydb.LogStore.V1.LogStoreService',
  file=DESCRIPTOR,
  index=0,
  serialized_options=None,
  create_key=_descriptor._internal_create_key,
  serialized_start=117,
  serialized_end=782,
  methods=[
  _descriptor.MethodDescriptor(
    name='CreateLogStore',
    full_name='Ydb.LogStore.V1.LogStoreService.CreateLogStore',
    index=0,
    containing_service=None,
    input_type=ydb_dot_public_dot_api_dot_protos_dot_draft_dot_ydb__logstore__pb2._CREATELOGSTOREREQUEST,
    output_type=ydb_dot_public_dot_api_dot_protos_dot_draft_dot_ydb__logstore__pb2._CREATELOGSTORERESPONSE,
    serialized_options=None,
    create_key=_descriptor._internal_create_key,
  ),
  _descriptor.MethodDescriptor(
    name='DescribeLogStore',
    full_name='Ydb.LogStore.V1.LogStoreService.DescribeLogStore',
    index=1,
    containing_service=None,
    input_type=ydb_dot_public_dot_api_dot_protos_dot_draft_dot_ydb__logstore__pb2._DESCRIBELOGSTOREREQUEST,
    output_type=ydb_dot_public_dot_api_dot_protos_dot_draft_dot_ydb__logstore__pb2._DESCRIBELOGSTORERESPONSE,
    serialized_options=None,
    create_key=_descriptor._internal_create_key,
  ),
  _descriptor.MethodDescriptor(
    name='DropLogStore',
    full_name='Ydb.LogStore.V1.LogStoreService.DropLogStore',
    index=2,
    containing_service=None,
    input_type=ydb_dot_public_dot_api_dot_protos_dot_draft_dot_ydb__logstore__pb2._DROPLOGSTOREREQUEST,
    output_type=ydb_dot_public_dot_api_dot_protos_dot_draft_dot_ydb__logstore__pb2._DROPLOGSTORERESPONSE,
    serialized_options=None,
    create_key=_descriptor._internal_create_key,
  ),
  _descriptor.MethodDescriptor(
    name='CreateLogTable',
    full_name='Ydb.LogStore.V1.LogStoreService.CreateLogTable',
    index=3,
    containing_service=None,
    input_type=ydb_dot_public_dot_api_dot_protos_dot_draft_dot_ydb__logstore__pb2._CREATELOGTABLEREQUEST,
    output_type=ydb_dot_public_dot_api_dot_protos_dot_draft_dot_ydb__logstore__pb2._CREATELOGTABLERESPONSE,
    serialized_options=None,
    create_key=_descriptor._internal_create_key,
  ),
  _descriptor.MethodDescriptor(
    name='DescribeLogTable',
    full_name='Ydb.LogStore.V1.LogStoreService.DescribeLogTable',
    index=4,
    containing_service=None,
    input_type=ydb_dot_public_dot_api_dot_protos_dot_draft_dot_ydb__logstore__pb2._DESCRIBELOGTABLEREQUEST,
    output_type=ydb_dot_public_dot_api_dot_protos_dot_draft_dot_ydb__logstore__pb2._DESCRIBELOGTABLERESPONSE,
    serialized_options=None,
    create_key=_descriptor._internal_create_key,
  ),
  _descriptor.MethodDescriptor(
    name='DropLogTable',
    full_name='Ydb.LogStore.V1.LogStoreService.DropLogTable',
    index=5,
    containing_service=None,
    input_type=ydb_dot_public_dot_api_dot_protos_dot_draft_dot_ydb__logstore__pb2._DROPLOGTABLEREQUEST,
    output_type=ydb_dot_public_dot_api_dot_protos_dot_draft_dot_ydb__logstore__pb2._DROPLOGTABLERESPONSE,
    serialized_options=None,
    create_key=_descriptor._internal_create_key,
  ),
  _descriptor.MethodDescriptor(
    name='AlterLogTable',
    full_name='Ydb.LogStore.V1.LogStoreService.AlterLogTable',
    index=6,
    containing_service=None,
    input_type=ydb_dot_public_dot_api_dot_protos_dot_draft_dot_ydb__logstore__pb2._ALTERLOGTABLEREQUEST,
    output_type=ydb_dot_public_dot_api_dot_protos_dot_draft_dot_ydb__logstore__pb2._ALTERLOGTABLERESPONSE,
    serialized_options=None,
    create_key=_descriptor._internal_create_key,
  ),
])
_sym_db.RegisterServiceDescriptor(_LOGSTORESERVICE)

DESCRIPTOR.services_by_name['LogStoreService'] = _LOGSTORESERVICE

# @@protoc_insertion_point(module_scope)

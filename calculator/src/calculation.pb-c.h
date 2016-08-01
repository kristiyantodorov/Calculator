/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

#ifndef PROTOBUF_C_calculation_2eproto__INCLUDED
#define PROTOBUF_C_calculation_2eproto__INCLUDED

#include <google/protobuf-c/protobuf-c.h>

PROTOBUF_C_BEGIN_DECLS


typedef struct _Calculation Calculation;


/* --- enums --- */


/* --- messages --- */

struct  _Calculation
{
  ProtobufCMessage base;
  float left;
  char *operation;
  float right;
  int32_t pid;
};
#define CALCULATION__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&calculation__descriptor) \
    , 0, NULL, 0, 0 }


/* Calculation methods */
void   calculation__init
                     (Calculation         *message);
size_t calculation__get_packed_size
                     (const Calculation   *message);
size_t calculation__pack
                     (const Calculation   *message,
                      uint8_t             *out);
size_t calculation__pack_to_buffer
                     (const Calculation   *message,
                      ProtobufCBuffer     *buffer);
Calculation *
       calculation__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   calculation__free_unpacked
                     (Calculation *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Calculation_Closure)
                 (const Calculation *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor calculation__descriptor;

PROTOBUF_C_END_DECLS


#endif  /* PROTOBUF_calculation_2eproto__INCLUDED */

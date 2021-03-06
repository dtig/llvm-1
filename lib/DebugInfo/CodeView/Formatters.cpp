//===- Formatters.cpp -------------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "llvm/DebugInfo/CodeView/Formatters.h"

using namespace llvm;
using namespace llvm::codeview;
using namespace llvm::codeview::detail;

GuidAdapter::GuidAdapter(StringRef Guid)
    : FormatAdapter(makeArrayRef(Guid.bytes_begin(), Guid.bytes_end())) {}

GuidAdapter::GuidAdapter(ArrayRef<uint8_t> Guid)
    : FormatAdapter(std::move(Guid)) {}

void GuidAdapter::format(llvm::raw_ostream &Stream, StringRef Style) {
  static const char *Lookup = "0123456789ABCDEF";

  assert(Item.size() == 16 && "Expected 16-byte GUID");
  Stream << "{";
  for (int i = 0; i < 16;) {
    uint8_t Byte = Item[i];
    uint8_t HighNibble = (Byte >> 4) & 0xF;
    uint8_t LowNibble = Byte & 0xF;
    Stream << Lookup[HighNibble] << Lookup[LowNibble];
    ++i;
    if (i >= 4 && i <= 10 && i % 2 == 0)
      Stream << "-";
  }
  Stream << "}";
}

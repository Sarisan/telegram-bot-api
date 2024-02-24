//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2024
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "td/utils/common.h"
#include "td/utils/HashTableUtils.h"
#include "td/utils/StringBuilder.h"

#include <type_traits>

namespace td {

class QuickReplyShortcutId {
  int32 id = 0;

 public:
  QuickReplyShortcutId() = default;

  explicit constexpr QuickReplyShortcutId(int32 quick_reply_shortcut_id) : id(quick_reply_shortcut_id) {
  }
  template <class T, typename = std::enable_if_t<std::is_convertible<T, int32>::value>>
  QuickReplyShortcutId(T quick_reply_shortcut_id) = delete;

  int32 get() const {
    return id;
  }

  bool operator==(const QuickReplyShortcutId &other) const {
    return id == other.id;
  }

  bool operator!=(const QuickReplyShortcutId &other) const {
    return id != other.id;
  }

  bool is_valid() const {
    return id > 0;
  }

  template <class StorerT>
  void store(StorerT &storer) const {
    storer.store_int(id);
  }

  template <class ParserT>
  void parse(ParserT &parser) {
    id = parser.fetch_int();
  }
};

struct QuickReplyShortcutIdHash {
  uint32 operator()(QuickReplyShortcutId quick_reply_shortcut_id) const {
    return Hash<int32>()(quick_reply_shortcut_id.get());
  }
};

inline StringBuilder &operator<<(StringBuilder &string_builder, QuickReplyShortcutId quick_reply_shortcut_id) {
  return string_builder << "shortcut " << quick_reply_shortcut_id.get();
}

}  // namespace td

// Copyright 2023 The Centipede Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Centipede puzzle: use callstack features to reach deep recursion
// clang-format off
// RUN: Run --callstack_level=10 --use_cmp_features=0 --max_len=10 --num_runs=10000000 # NOLINT
// RUN: SolutionIs ABCDEF
// clang-format on
#include <sys/resource.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

// Deep recursion triggered by 'ABCDEF...'
void Recursive(const uint8_t *data, size_t size, size_t idx) {
  if (idx > 5) std::abort();
  if (idx >= size) return;
  if (data[idx] == 'A' + (idx % 26)) Recursive(data, size, idx + 1);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  Recursive(data, size, 0);
  return 0;
}

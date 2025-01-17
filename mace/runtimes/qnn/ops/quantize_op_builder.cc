// Copyright 2021 The MACE Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "mace/runtimes/qnn/op_builder.h"

#include "mace/core/proto/arg_helper.h"

namespace mace {

class QuantizeOpBuilder : public OpBuilder {
 public:
  explicit QuantizeOpBuilder(GraphBuilder *graph_builder)
      : OpBuilder(graph_builder) {}

  MaceStatus BuildOp(const OperatorDef &op) {
    const char *op_type = op.type().compare("Quantize") == 0
                              ? QNN_OP_QUANTIZE
                              : QNN_OP_DEQUANTIZE;
    SetOpType(op_type);
    SetOpName(op.name().c_str());

    AddInput(op.input(0));
    AddOutput(op.output(0));

    return MaceStatus::MACE_SUCCESS;
  }
};
namespace qnn {
void RegisterQuantize(OpRegistry *op_registry) {
  QNN_REGISTER_OP(op_registry, "Quantize", QuantizeOpBuilder);
  QNN_REGISTER_OP(op_registry, "Dequantize", QuantizeOpBuilder);
}
}  // namespace qnn
}  // namespace mace

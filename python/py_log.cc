// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "pybind11/pybind11.h"
#include "ppl/common/log.h"

namespace ppl { namespace common { namespace python {

void RegisterLog(pybind11::module* m) {
    m->attr("LOG_LEVEL_DEBUG") = (uint32_t)LOG_LEVEL_DEBUG;
    m->attr("LOG_LEVEL_INFO") = (uint32_t)LOG_LEVEL_INFO;
    m->attr("LOG_LEVEL_WARNING") = (uint32_t)LOG_LEVEL_WARNING;
    m->attr("LOG_LEVEL_ERROR") = (uint32_t)LOG_LEVEL_ERROR;
    m->attr("LOG_LEVEL_FATAL") = (uint32_t)LOG_LEVEL_FATAL;
    m->attr("LOG_LEVEL_MAX") = (uint32_t)LOG_LEVEL_MAX;
}

}}} // namespace ppl::common::python

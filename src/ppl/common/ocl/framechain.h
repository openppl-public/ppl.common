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

#ifndef _ST_HPC_PPL_COMMON_OCL_FRAMECHAIN_H_
#define _ST_HPC_PPL_COMMON_OCL_FRAMECHAIN_H_

#include <string.h>

#include "CL/cl.h"

#define NAME_LENGTH 32

namespace ppl { namespace common { namespace ocl {

class FrameChain {
  public:
    FrameChain();
    FrameChain(const cl_command_queue& queue);
    ~FrameChain();

    void setSource(char* source_string);
    void setFunctionName(const char* function_name);
    void setProgram(const cl_program& program);
    void setProfiling(const bool profiling) {profiling_ = profiling;}

    bool createDefaultOclFrame(bool profiling);
    bool queryDevice();
    bool queryContext();
    bool queryProfiling();
    
    char* getCodeString() const {
      return source_string_;
    }

    cl_platform_id getPlatformId() const {
        return platform_id_;
    }

    cl_device_id getDeviceId() const {
        return device_id_;
    }

    cl_context getContext() const {
        return context_;
    }

    cl_command_queue getQueue() const {
        return queue_;
    }

    cl_program getProgram() const {
        return program_;
    }

    bool isProfiling() const {
        return profiling_;
    }

  private:
    char* source_string_;
    char function_name_[NAME_LENGTH];
    cl_platform_id platform_id_;
    cl_device_id device_id_;
    cl_context context_;
    cl_command_queue queue_;
    cl_program program_;
    bool profiling_;
};

}}}

#endif
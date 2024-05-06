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

#include "ppl/common/page_manager.h"
#include "gtest/gtest.h"

using namespace std;
using namespace ppl::common;

TEST(PageManagerTest, test1) {
    PageManager page_manager;
    page_manager.Init(16);

    RetCode ret;
    vector<uint64_t> page_list1;
    ret = page_manager.Alloc(2, &page_list1);
    ASSERT_EQ(RC_SUCCESS, ret);

    vector<uint64_t> page_list2;
    ret = page_manager.Alloc(3, &page_list2);
    ASSERT_EQ(RC_SUCCESS, ret);

    vector<uint64_t> page_list3;
    ret = page_manager.Alloc(4, &page_list3);
    ASSERT_EQ(RC_SUCCESS, ret);

    vector<uint64_t> page_list4;
    ret = page_manager.Alloc(6, &page_list4);
    ASSERT_EQ(RC_SUCCESS, ret);

    ASSERT_EQ(1, page_manager.GetAvail());

    page_manager.Free(page_list1.data(), page_list1.size());
    page_manager.Free(page_list3.data(), page_list3.size());

    vector<uint64_t> page_list5;
    ret = page_manager.Alloc(7, &page_list5);

    ASSERT_EQ(std::vector<uint64_t>({5, 6, 7, 8, 0, 1, 15}), page_list5);

    page_manager.Free(page_list2.data(), page_list2.size());
    page_manager.Free(page_list4.data(), page_list4.size());
    page_manager.Free(page_list5.data(), page_list5.size());

    vector<uint64_t> page_list6;
    ret = page_manager.Alloc(16, &page_list6);
    ASSERT_EQ(RC_SUCCESS, ret);
    ASSERT_EQ(std::vector<uint64_t>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}), page_list6);

    vector<uint64_t> page_list7;
    ret = page_manager.Alloc(1, &page_list7);
    ASSERT_EQ(RC_OUT_OF_MEMORY, ret);

    page_manager.Free(page_list6.data(), page_list6.size());
}

TEST(PageManagerTest, test2) {
    PageManager page_manager;
    page_manager.Init(40);

    RetCode ret;
    vector<uint64_t> page_list1;
    ret = page_manager.Alloc(10, &page_list1);  // [0, 10)
    ASSERT_EQ(RC_SUCCESS, ret);

    vector<uint64_t> page_list2;
    ret = page_manager.Alloc(1, &page_list2);   // [10,11)
    ASSERT_EQ(RC_SUCCESS, ret);

    vector<uint64_t> page_list3;
    ret = page_manager.Alloc(9, &page_list3);   // [11:20)
    ASSERT_EQ(RC_SUCCESS, ret);

    vector<uint64_t> page_list4;
    ret = page_manager.Alloc(2, &page_list4);   // [20,22) 
    ASSERT_EQ(RC_SUCCESS, ret);

    vector<uint64_t> page_list5;
    ret = page_manager.Alloc(8, &page_list5);   // [22, 30)
    ASSERT_EQ(RC_SUCCESS, ret);

    vector<uint64_t> page_list6;
    ret = page_manager.Alloc(2, &page_list6);   // [30, 32)
    ASSERT_EQ(RC_SUCCESS, ret);
    ASSERT_EQ(std::vector<uint64_t>({30, 31}), page_list6);

    vector<uint64_t> page_list7;
    ret = page_manager.Alloc(8, &page_list7);   // [32, 40)
    ASSERT_EQ(RC_SUCCESS, ret);

    page_manager.Free(page_list2.data(), page_list2.size());
    page_manager.Free(page_list4.data(), page_list4.size());
    page_manager.Free(page_list6.data(), page_list6.size());

    ASSERT_EQ(5, page_manager.GetAvail());

    vector<uint64_t> page_list8;
    ret = page_manager.Alloc(2, &page_list8);
    ASSERT_EQ(RC_SUCCESS, ret);
    ASSERT_EQ(std::vector<uint64_t>({20 ,21}), page_list8);

    ASSERT_EQ(3, page_manager.GetAvail());
}

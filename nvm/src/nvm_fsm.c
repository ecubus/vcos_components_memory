/*
 * Copyright (c) 2025 Li Auto Inc. and its affiliates
 * Licensed under the Apache License, Version 2.0(the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdlib.h>
#include <string.h>
#include "nvm_fsm.h"

#define NVM_START_SEC_PRIVATE_BSS
#include "nvm_memmap.h"

VAR(nvm_block_info_type, NVM_PRIVATE_BSS) nvm_current_block_info;
VAR(nvm_job_t, NVM_PRIVATE_BSS) nvm_current_job;
VAR(nvm_fsm_state_type, NVM_PRIVATE_BSS) nvm_task_state;
VAR(nvm_fsm_state_type, NVM_PRIVATE_BSS) nvm_subtask_state;

#define NVM_STOP_SEC_PRIVATE_BSS
#include "nvm_memmap.h"

#define NVM_START_SEC_CONST
#include "nvm_memmap.h"
CONST(nvm_service_id_t, NVM_CONST)
nvm_service_table[NVM_INT_FID_INVALID_JOB + 1u] = {
	NVM_WRITE_BLOCK, NVM_READ_BLOCK_SID, NVM_RESTORE_BLOCK_DEFAULTS_SID, NVM_INVALIDATE_NV_BLOCK_SID, NVM_ERASE_BLOCK_SID,
	NVM_WRITE_ALL,	 NVM_READ_ALL_SID,	 NVM_MAIN_FUNCTION_SID,	     NVM_CANCEL_JOBS_SID
};

#define DUMMY_VALUE {{0xAA, 0x55, 0xAA}, { 0x55, 0xAA }}

static CONST(nvm_state_descr_type, NVM_CONST) nvm_state_descr_table_at[] = {
DUMMY_VALUE, DUMMY_VALUE, DUMMY_VALUE, DUMMY_VALUE, DUMMY_VALUE,
DUMMY_VALUE, DUMMY_VALUE, DUMMY_VALUE, DUMMY_VALUE, DUMMY_VALUE,
DUMMY_VALUE, DUMMY_VALUE, DUMMY_VALUE, DUMMY_VALUE, DUMMY_VALUE,
DUMMY_VALUE, DUMMY_VALUE, DUMMY_VALUE, DUMMY_VALUE, DUMMY_VALUE,
DUMMY_VALUE, DUMMY_VALUE, DUMMY_VALUE, DUMMY_VALUE, DUMMY_VALUE,
DUMMY_VALUE, DUMMY_VALUE, DUMMY_VALUE, DUMMY_VALUE, DUMMY_VALUE,
DUMMY_VALUE, DUMMY_VALUE};

#define NVM_STOP_SEC_CONST
#include "nvm_memmap.h"

#define NVM_START_SEC_CODE
#include "nvm_memmap.h"
static FUNC(boolean, NVM_CODE) nvm_fsm_event(nvm_event_type nvm_queries_at)
{
	return nvm_event_table[nvm_queries_at]();
}

static FUNC(void, NVM_CODE) nvm_fsm_action(nvm_state_action_type nvm_actions_at)
{
	nvm_action_table[nvm_actions_at]();
}

FUNC(void, NVM_CODE) nvm_fsm_init(void)
{
	nvm_current_block_info.internal_flags = 0u;

	nvm_current_job.job_service_id = NVM_INT_FID_NO_JOB_PENDING;
	nvm_current_job.job_block_id = 0u;
	nvm_current_job.ram_addr = NULL;
	nvm_current_block_info.retry_times = 0u;

	nvm_task_state = NVM_FSM_IDLE;
	nvm_subtask_state = NVM_FSM_FSM_FINISHED;
}

FUNC(void, NVM_CODE) nvm_fsm_deinit(void)
{
	(void)memset(&nvm_current_job, 0, sizeof(nvm_current_job));
	(void)memset(&nvm_current_block_info, 0, sizeof(nvm_current_block_info));
	nvm_task_state = NVM_FSM_UNINIT;
	nvm_subtask_state = NVM_FSM_UNINIT;
}

FUNC(nvm_fsm_state_type, NVM_CODE) nvm_fsm_excute(nvm_fsm_state_type nvm_current_state)
{
	nvm_fsm_state_type nvm_ret_state_tloc;
	const nvm_state_descr_type *current_state_ptloc = &nvm_state_descr_table_at[nvm_current_state];
	nvm_ret_state_tloc = current_state_ptloc->change_conditions.next_state;
	return nvm_ret_state_tloc;
}

#define NVM_STOP_SEC_CODE
#include "nvm_memmap.h"

#
# Arm SCP/MCP Software
# Copyright (c) 2021, Arm Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

set(SCP_MODULE "rcar-reset")

set(SCP_MODULE_TARGET "module-rcar-reset")

if(SCP_ENABLE_SCMI_RESET)
    list(APPEND SCP_MODULES "rcar-reset")
endif()
#pragma once

#include "tokenize/t_token_list/t_token_list.h"
#include "t_parser.h"

#include <stdbool.h>

t_error parse(const t_token_list* tokens);

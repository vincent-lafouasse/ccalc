#pragma once

#include "error/t_error.h"
#include "tokenize/t_token_list/t_token_list.h"

void log_token(t_token token);
void log_token_list(const t_token_list *tkl);
void log_error(t_error err);

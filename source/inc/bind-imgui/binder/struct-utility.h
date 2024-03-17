#pragma once

// clang-format off

// Classes
#define RW(struct_, var) def_readwrite(#var, &struct_::var)
#define RO(struct_, var) def_readonly(#var, &struct_::var)
#define DEF(struct_, func) #func, &struct_::func

// clang-format on
#ifndef M2L_MACROS_H
#define M2L_MACROS_H

#define UNUSED(x) ((void)(x))

#define STRINGIFY_A_(x) #x
#define STRINGIFY_A(x) STRINGIFY_A_(x)

#define STRINGIFY_W_(x) L ## #x
#define STRINGIFY_W(x) STRINGIFY_W_(x)

#endif

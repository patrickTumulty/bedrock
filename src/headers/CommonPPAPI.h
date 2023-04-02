//
// Created by Patrick Tumulty on 6/11/22.
//

#ifndef FRESCO_COMMONPPAPI_H
#define FRESCO_COMMONPPAPI_H

#define COMMON_PP_NAMESPACE_START namespace com {
#define COMMON_PP_NAMESPACE_END }

#ifdef LIB_VERSION
#define COMMON_PP_VERSION LIB_VERSION
#else
#define COMMON_PP_VERSION "0.0.0"
#endif

#endif //FRESCO_COMMONPPAPI_H

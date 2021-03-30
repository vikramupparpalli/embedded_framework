#include "constants_binary.h"

const bool constTrue = true;
const bool constFalse = false;

const bool * const on = &constTrue;
const bool * const off = &constFalse;

const bool * const set = &constTrue;
const bool * const clear = &constFalse;

const bool * const high = &constTrue;
const bool * const low = &constFalse;

const bool * const enabled = &constTrue;
const bool * const disabled = &constFalse;

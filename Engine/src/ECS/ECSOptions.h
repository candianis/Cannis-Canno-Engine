#pragma once

#include "ccpch.h"

const uint8_t MaxComponents = 32;
const uint8_t MaxEntities = 5000;
using Signature = std::bitset<MaxComponents>;

CANNIS_API Signature;
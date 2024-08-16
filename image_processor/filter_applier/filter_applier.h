#pragma once

#include <memory>
#include "../parsing/parser.h"
#include "../filters/negative/negative.h"
#include "../filters/grayscale/grayscale.h"
#include "../filters/crop/crop.h"
#include "../filters/sharp/sharp.h"
#include "../filters/edge/edge.h"
#include "../filters/blur/blur.h"
#include "../filters/mosaic/mosaic.h"

std::unique_ptr<Filter> CreateFilter(Argument argument);

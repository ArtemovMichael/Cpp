#include "../filter_applier/filter_applier.h"
#include "../filters/filter.h"
#include "../parsing/parser.h"
#include "../picture/picture.h"
#include "contrib/catch/catch.hpp"
#include <cassert>
#include <memory>
#include <typeinfo>

TEST_CASE("Parser Test No Argument Filters") {

  std::vector<Argument> arguments;

  const char *args[] = {"",    "test_image.bmp", "result.bmp", "-sharp", "-gs",
                        "-neg"};

  int argc = sizeof(args) / sizeof(char *);
  const char **argv = args;

  arguments = Parse(argc, argv);
  std::vector<Argument> ans_arguments;

  ans_arguments.push_back(Argument{FilterType::Sharpening, 0, 0, 0});
  ans_arguments.push_back(Argument{FilterType::Grayscale, 0, 0, 0});
  ans_arguments.push_back(Argument{FilterType::Negative, 0, 0, 0});

  REQUIRE(arguments.size() == ans_arguments.size());

  while (!arguments.empty()) {
    Argument arg = arguments[0];
    Argument ans_arg = ans_arguments[0];
    REQUIRE(arg.filter == ans_arg.filter);
    arguments.erase(arguments.begin());
    ans_arguments.erase(ans_arguments.begin());
  }
}

TEST_CASE("Parser Test Filters With Arguments") {

  std::vector<Argument> arguments;

  const char *args[] = {"",      "test_image.bmp", "result.bmp", "-blur", "0.1",
                        "-crop", "1000",           "500",        "-edge", "10"};

  int argc = sizeof(args) / sizeof(char *);
  const char **argv = args;

  arguments = Parse(argc, argv);
  std::vector<Argument> ans_arguments;

  ans_arguments.push_back(
      Argument{FilterType::GaussianBlur, 0, 0, 0.1});                // NOLINT
  ans_arguments.push_back(Argument{FilterType::Crop, 1000, 500, 0}); // NOLINT
  ans_arguments.push_back(
      Argument{FilterType::EdgeDetection, 0, 0, 10}); // NOLINT

  REQUIRE(arguments.size() == ans_arguments.size());

  while (!arguments.empty()) {
    Argument arg = arguments[0];
    Argument ans_arg = ans_arguments[0];
    REQUIRE(arg.filter == ans_arg.filter);
    REQUIRE(arg.Param1 == ans_arg.Param1);
    REQUIRE(arg.Param2 == ans_arg.Param2);
    REQUIRE(arg.DoubleParam == ans_arg.DoubleParam);
    arguments.erase(arguments.begin());
    ans_arguments.erase(ans_arguments.begin());
  }
}

TEST_CASE("Picture Read Test") {
  const Header header{19778, 694, 0, 0, 54};
  const InfoHeader info_header{40, 10, 20, 1, 24, 0, 0, 0, 0, 0, 0};
  const Pixels pixels = {{{187, 0, 0},  // NOLINT
                          {187, 0, 0},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0}}, // NOLINT
                         {{187, 0, 0},  // NOLINT
                          {187, 0, 0},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0}}, // NOLINT
                         {{187, 0, 0},  // NOLINT
                          {187, 0, 0},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0}}, // NOLINT
                         {{187, 0, 0},  // NOLINT
                          {187, 0, 0},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0}}, // NOLINT
                         {{187, 0, 0},  // NOLINT
                          {187, 0, 0},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0}}, // NOLINT
                         {{187, 0, 0},  // NOLINT
                          {187, 0, 0},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0}}, // NOLINT
                         {{187, 0, 0},  // NOLINT
                          {187, 0, 0},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0}}, // NOLINT
                         {{187, 0, 0},  // NOLINT
                          {187, 0, 0},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0}}, // NOLINT
                         {{187, 0, 0},  // NOLINT
                          {187, 0, 0},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0}}, // NOLINT
                         {{187, 0, 0},  // NOLINT
                          {187, 0, 0},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0}}, // NOLINT
                         {{187, 0, 0},  // NOLINT
                          {187, 0, 0},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0}}, // NOLINT
                         {{187, 0, 0},  // NOLINT
                          {187, 0, 0},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 187, 0},  // NOLINT
                          {0, 187, 0}}, // NOLINT
                         {{187, 0, 0},  // NOLINT
                          {187, 0, 0},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 187, 0}}, // NOLINT
                         {{187, 0, 0},  // NOLINT
                          {187, 0, 0},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255}}, // NOLINT
                         {{187, 0, 0},  // NOLINT
                          {187, 0, 0},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 255},  // NOLINT
                          {0, 0, 0}},
                         {{187, 0, 0}, // NOLINT
                          {187, 0, 0}, // NOLINT
                          {0, 0, 255}, // NOLINT
                          {0, 0, 255}, // NOLINT
                          {0, 0, 255}, // NOLINT
                          {0, 0, 255}, // NOLINT
                          {0, 0, 255}, // NOLINT
                          {0, 0, 255}, // NOLINT
                          {0, 0, 0},
                          {0, 0, 0}},
                         {{187, 0, 0}, // NOLINT
                          {187, 0, 0}, // NOLINT
                          {0, 0, 255}, // NOLINT
                          {0, 0, 255}, // NOLINT
                          {0, 0, 255}, // NOLINT
                          {0, 0, 255}, // NOLINT
                          {0, 0, 255}, // NOLINT
                          {0, 0, 0},
                          {0, 0, 0},
                          {0, 0, 0}},
                         {{187, 0, 0}, // NOLINT
                          {187, 0, 0}, // NOLINT
                          {0, 0, 255}, // NOLINT
                          {0, 0, 255}, // NOLINT
                          {0, 0, 255}, // NOLINT
                          {0, 0, 255}, // NOLINT
                          {0, 0, 0},
                          {0, 0, 0},
                          {0, 0, 0},
                          {0, 0, 0}},
                         {{187, 0, 0}, // NOLINT
                          {187, 0, 0}, // NOLINT
                          {0, 0, 255}, // NOLINT
                          {0, 0, 255}, // NOLINT
                          {0, 0, 255}, // NOLINT
                          {0, 0, 0},
                          {0, 0, 0},
                          {0, 0, 0},
                          {0, 0, 0},
                          {0, 0, 0}},
                         {{187, 0, 0}, // NOLINT
                          {187, 0, 0}, // NOLINT
                          {0, 0, 255}, // NOLINT
                          {0, 0, 255}, // NOLINT
                          {0, 0, 0},
                          {0, 0, 0},
                          {0, 0, 0},
                          {0, 0, 0},
                          {0, 0, 0},
                          {0, 0, 0}}}; // NOLINT

  Picture result_image("flags/flag.bmp");
  Picture test_image{header, info_header, pixels};

  REQUIRE(result_image == test_image);
}

TEST_CASE("Picture Writer Test") {

  Picture test_image("flags/flag.bmp");
  Picture result_image("flags/flag.bmp");

  const char *path_out = "flags/result.bmp";

  result_image.Write(path_out);

  REQUIRE(test_image == result_image);
}

TEST_CASE("Test Negative Filter") {

  Picture test_image("flags/flag.bmp");
  Picture ans_image("flags/flag_neg.bmp");

  std::make_unique<FilterNegative>()->ApplyFilter(test_image);

  REQUIRE(test_image == ans_image);
}

TEST_CASE("Test Grayscale Filter") {

  Picture test_image("flags/flag.bmp");
  Picture ans_image("flags/flag_gs.bmp");

  std::make_unique<FilterGrayscale>()->ApplyFilter(test_image);

  REQUIRE(test_image == ans_image);
}

TEST_CASE("Test Sharpening Filter") {

  Picture test_image("flags/flag.bmp");
  Picture ans_image("flags/flag_sharp.bmp");

  std::make_unique<FilterSharp>()->ApplyFilter(test_image);

  REQUIRE(test_image == ans_image);
}

TEST_CASE("Test Blur Filter") {

  Picture test_image("flags/flag.bmp");
  Picture ans_image("flags/flag_blur.bmp");

  std::make_unique<FilterBlur>(0.1)->ApplyFilter(test_image); // NOLINT

  REQUIRE(test_image == ans_image);
}

TEST_CASE("Test Crop Filter") {

  Picture test_image("flags/flag.bmp");
  Picture ans_image("flags/flag_crop.bmp");

  std::make_unique<FilterCrop>(10, 5)->ApplyFilter(test_image); // NOLINT

  REQUIRE(test_image == ans_image);
}

TEST_CASE("Test Edge Detection Filter") {

  Picture test_image("flags/flag.bmp");
  Picture ans_image("flags/flag_edge.bmp");

  std::make_unique<FilterEdge>(5)->ApplyFilter(test_image); // NOLINT

  REQUIRE(test_image == ans_image);
}

TEST_CASE("Test Mosaic Filter") {

  Picture test_image("flags/flag.bmp");
  Picture ans_image("flags/flag_mosaic.bmp");

  std::make_unique<FilterMosaic>(5)->ApplyFilter(test_image); // NOLINT

  REQUIRE(test_image == ans_image);
}

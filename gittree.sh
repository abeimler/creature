#!/bin/bash

git subtree add --prefix lib/benchpress git@github.com:abeimler/benchpress.git master --squash
git subtree add --prefix lib/better-enums https://github.com/aantron/better-enums.git master --squash
git subtree add --prefix lib/cereal https://github.com/USCiLab/cereal master --squash
git subtree add --prefix lib/clamp https://github.com/martinmoene/clamp master --squash
git subtree add --prefix lib/doctest https://github.com/onqtam/doctest.git master --squash
git subtree add --prefix lib/entityx https://github.com/alecthomas/entityx.git experimental/compile_time --squash
git subtree add --prefix lib/GSL https://github.com/Microsoft/GSL  master --squash
git subtree add --prefix lib/json https://github.com/nlohmann/json  master --squash


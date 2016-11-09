#!/bin/bash

git subtree pull --prefix backend/lib/benchpress https://github.com/abeimler/benchpress master --squash
git subtree pull --prefix backend/lib/better-enums https://github.com/aantron/better-enums.git master --squash
git subtree pull --prefix backend/lib/cereal https://github.com/USCiLab/cereal master --squash
git subtree pull --prefix backend/lib/clamp https://github.com/martinmoene/clamp master --squash
git subtree pull --prefix backend/lib/doctest https://github.com/onqtam/doctest.git master --squash
git subtree pull --prefix backend/lib/entityx https://github.com/alecthomas/entityx.git experimental/compile_time --squash
git subtree pull --prefix backend/lib/GSL https://github.com/Microsoft/GSL  master --squash
git subtree pull --prefix backend/lib/json https://github.com/nlohmann/json  master --squash


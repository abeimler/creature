#!/bin/bash

docker exec creature_${CONTAINER_NAME} /bin/bash ./scripts/build.sh
docker exec creature_${CONTAINER_NAME} /bin/bash ./scripts/run-tests.sh
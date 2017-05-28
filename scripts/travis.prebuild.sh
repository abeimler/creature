#!/bin/bash

docker-compose build $CONTAINER_NAME
docker-compose up -d $CONTAINER_NAME
docker exec -it creature_${CONTAINER_NAME} /bin/bash ./scripts/prebuild.sh
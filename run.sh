#!/bin/bash -eux

cd "$(dirname "$0")"

if [ $# -eq 0 ]; then
  set -- $(ls projects | grep -vx base)
fi

docker build -t census-base projects/base

for PROJECT in "$@"; do
  docker build -t "census-$PROJECT" "projects/$PROJECT"
  docker run --rm -v "$PWD:/census" "census-$PROJECT" "/census/projects/$PROJECT/build.sh"
done

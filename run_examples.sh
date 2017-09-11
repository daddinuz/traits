#!/usr/bin/env bash

set -e
shopt -s extglob

for e in example!(*fail); do
    echo -e "\n# Running: ${e}";
    ./${e};
done

#!/usr/bin/env bash
set -euo pipefail

# Defaults can be found in Makefile

cat <<EOF
STABLE_DOCKER_REGISTRY ${DOCKER_REGISTRY:-}
STABLE_DOCKER_REPOSITORY ${DOCKER_REPOSITORY:-}
STABLE_DOCKER_TAG ${DOCKER_TAG:-}
EOF


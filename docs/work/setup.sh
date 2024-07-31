#!/usr/bin/env bash

# work/setup.sh
# To setup all python (pip) dependencies

RED='\033[0;31m'
NC='\033[0m' # No Color

pip_packages=$(cat work/pip-packages.txt)

_pip3=$(which pip3 | wc -l)

# pip3 not found
if [[ $_pip3 -ne 1 ]]; then
  _pip=$(which pip | wc -l)

  # pip exist
  if [[ $_pip -eq 1 ]]; then
    _pip3=$(pip --version | grep "python 3" | wc -l)

    # pip3 exist as pip
    if [[ $_pip3 -eq 1 ]]; then
      pip install $pip_packages

    # pip is not pip3
    else
      echo -e "${RED}Python3 and pip3 are required!${NC}"
    fi

  # pip not found
  else
    echo -e "${RED}Python3 and pip3 are required!${NC}"
  fi

# pip3 exist
else
  pip3 install $pip_packages
fi

#!/usr/bin/env bash

# mike/serve.sh
# To serve mike's webpage at yours local ip with port=8000

ip=$(hostname -I | awk '{print $1}')
port=8000

address=$ip:$port

mike serve -b local/gh-pages -a $address

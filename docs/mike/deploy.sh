#!/usr/bin/env bash

# mike/deploy.sh
# To deploy mike's webpage at yours local/gh-pages branch

mike deploy -b local/gh-pages dev latest
mike set-default -b local/gh-pages latest

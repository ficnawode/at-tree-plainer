#!/bin/bash

CONFIG_PATH=$1
OUTPUT_DIR=$2

timestamp=$(date +"%Y%m%d_%H%M%S")
NEW_DIR_NAME="plain_${timestamp}"
RESULT_DIR=/lustre/cbm/users/$USER/pid_plain_trees/logs/$NEW_DIR_NAME
mkdir -p $RESULT_DIR
echo "created directory $RESULT_DIR"  

LOG_DIR=$RESULT_DIR/log
mkdir -p $LOG_DIR
mkdir -p $LOG_DIR/out
mkdir -p $LOG_DIR/error
echo "logs can be found at $LOG_DIR"


if [ $# -ne 2 ]; then
  echo "invalid number of parameters, overriding:"
  CONFIG_PATH=$PWD/configs/tof-vtx_1M.json
  echo "config path: $CONFIG_PATH"
  OUTPUT_DIR=/lustre/cbm/users/tfic/pid_plain_trees/trees/train
  echo "output directory: $OUTPUT_DIR"
fi

sbatch --job-name="at_plain"\
        -t 10:00:00 \
        --partition long\
        --output=$LOG_DIR/out/%j.out.log \
        --error=$LOG_DIR/error/%j.err.log \
        -- $PWD/plain_job.sh $CONFIG_PATH $OUTPUT_DIR

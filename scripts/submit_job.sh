#!/bin/bash

CONFIG_PATH=$1

timestamp=$(date +"%Y%m%d_%H%M%S")
NEW_DIR_NAME="plain_${timestamp}"
OUTPUT_DIR=/lustre/cbm/users/$USER/pid_plain_trees/logs/$NEW_DIR_NAME
mkdir -p $OUTPUT_DIR
echo "created directory $OUTPUT_DIR"  

LOG_DIR=$OUTPUT_DIR/log
mkdir -p $LOG_DIR
mkdir -p $LOG_DIR/out
mkdir -p $LOG_DIR/error
echo "intermediate tree will be in output directory: $OUTPUT_DIR"
echo "logs can be found at $LOG_DIR"


if [ $# -ne 1 ]; then
  echo "invalid number of parameters, overriding:"
  CONFIG_PATH=$PWD/configs/tof-vtx_1M.json
fi

sbatch --job-name="at_plain"\
        -t 10:00:00 \
        --partition long\
        --output=$LOG_DIR/out/%j.out.log \
        --error=$LOG_DIR/error/%j.err.log \
        -- $PWD/plain_job.sh $CONFIG_PATH $OUTPUT_DIR

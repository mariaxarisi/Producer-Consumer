#!/bin/bash

cd ..

# File to store the results
RESULT_FILE="./test/result.txt"
> "$RESULT_FILE"

make || { echo "Compilation failed. Exiting."; exit 1; }

# Run the program for different values of PRODUCERS and CONSUMERS
echo "Running the program with different PRODUCERS and CONSUMERS..."
for PRODUCERS in $(seq 1 5); do
    for CONSUMERS in $(seq 1 10); do
        echo "Running ./bin/prod-con $PRODUCERS $CONSUMERS"
        SUM=0
        for i in $(seq 1 30); do
            RESULT=$(./bin/prod-con "$PRODUCERS" "$CONSUMERS")
            SUM=$(echo "$SUM + $RESULT" | bc)
        done
        AVG=$(echo "scale=6; $SUM / 30" | bc)
        echo "Producers: $PRODUCERS, Consumers: $CONSUMERS, Average Time: $AVG sec" >> "$RESULT_FILE"
    done
done

make clean || { echo "Cleanup failed. Exiting."; exit 1; }
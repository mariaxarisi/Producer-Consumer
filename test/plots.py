import matplotlib.pyplot as plt
import os
import re

# Initialize a dictionary to store data
data = {}

RESULT_FILE = os.path.join(os.path.dirname(__file__), "result.txt")

# Read the result.txt file
with open(RESULT_FILE, "r") as file:
    for line in file:
        # Use regex to extract producers, consumers, and average time
        match = re.match(r"Producers: (\d+), Consumers: (\d+), Average Time: ([\d.]+) sec", line)
        if match:
            producers = int(match.group(1))
            consumers = int(match.group(2))
            avg_time = float(match.group(3))
            
            # Organize data by producers
            if producers not in data:
                data[producers] = {"consumers": [], "avg_times": []}
            data[producers]["consumers"].append(consumers)
            data[producers]["avg_times"].append(avg_time)


# Create individual plots for each number of producers
for producers, values in data.items():
    plt.figure(figsize=(10, 6))
    plt.plot(values["consumers"], values["avg_times"], marker='o')

    # Add labels, title, and grid
    plt.xlabel("Consumers")
    plt.ylabel("Average Time (sec)")
    plt.title(f"Average Time vs Consumers for {producers} Producers")
    plt.grid(True)

    # Save the plot as a PNG file
    individual_image_file = os.path.join(os.path.dirname(__file__), f"../img/{producers}_producers.png")
    plt.savefig(individual_image_file)
    plt.close()
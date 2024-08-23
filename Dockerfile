# Use an official image as a parent image
FROM ubuntu:20.04

# Set the working directory
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

# Install any needed packages specified in requirements.txt
RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    cppcheck \
    && rm -rf /var/lib/apt/lists/*

# Build the project
RUN cmake -S . -B build && cmake --build build

# Run the unit tests
CMD ["./build/unit_test"]

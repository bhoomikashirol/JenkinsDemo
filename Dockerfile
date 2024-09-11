# Use an official Jenkins base image
FROM jenkins/jenkins:lts

# Switch to the root user to install dependencies
USER root

# Install necessary packages
RUN apt-get update && \
    apt-get install -y \
    cmake \
    cppcheck \
    git \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# Install Google Test
RUN git clone https://github.com/google/googletest.git /usr/src/googletest && \
    cd /usr/src/googletest && \
    cmake . && \
    make && \
    make install

# Switch back to the Jenkins user
USER jenkins

# Copy the Jenkinsfile into the container (optional, if needed for reference)
COPY Jenkinsfile /var/lib/jenkins/workspace/PipelineDemo/

# Set the working directory
WORKDIR /var/lib/jenkins/workspace/PipelineDemo/

# Run the Jenkins agent
CMD ["jenkins-agent"]

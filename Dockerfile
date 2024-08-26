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

# Switch back to the Jenkins user
USER jenkins

# Set environment variables
ENV BUILD_DIR="/var/lib/jenkins/workspace/docker-integrate/build"
ENV TEST_DIR="/var/lib/jenkins/workspace/docker-integrate/Test/CRC_UT/test/UT"
ENV REPO_URL="https://github.com/bhoomikashirol/JenkinsDemo.git"
ENV GIT_CREDENTIALS_ID="github-pat"

# Copy the Jenkinsfile into the container
COPY Jenkinsfile /var/lib/jenkins/workspace/docker-integrate/

# Set the working directory
WORKDIR /var/lib/jenkins/workspace/docker-integrate/

# Run the Jenkins pipeline
CMD ["jenkins-agent"]

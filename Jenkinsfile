pipeline {
    agent any

    environment {
        BUILD_DIR = "/var/lib/jenkins/workspace/PipelineDemo/build"
    }

    stages {
        stage('Checkout') {
            steps {
                script {
                    // Checkout the main branch
                    checkout([$class: 'GitSCM', branches: [[name: '*/main']], userRemoteConfigs: [[url: 'https://github.com/bhoomikashirol/JenkinsDemo.git']]])
                    
                    // Checkout the Code branch
                    dir('Code') {
                        checkout([$class: 'GitSCM', branches: [[name: '*/Code']], userRemoteConfigs: [[url: 'https://github.com/bhoomikashirol/JenkinsDemo.git']]])
                    }
                    
                    // Checkout the Test branch
                    dir('Test') {
                        checkout([$class: 'GitSCM', branches: [[name: '*/Test']], userRemoteConfigs: [[url: 'https://github.com/bhoomikashirol/JenkinsDemo.git']]])
                    }
                }
            }
        }

        stage('Build') {
            steps {
                script {
                    // Create the build directory
                    sh 'mkdir -p ${BUILD_DIR}'
                    
                    // Run CMake and build
                    sh 'cmake -S . -B ${BUILD_DIR}'
                    sh 'cmake --build ${BUILD_DIR}'
                }
            }
        }

        stage('Cppcheck') {
            steps {
                script {
                    // Run Cppcheck
                    sh 'cppcheck --enable=all --xml --xml-version=2 . 2> cppcheck.xml'
                }
                // Publish Cppcheck results
                publishCppcheck pattern: 'cppcheck.xml'
            }
        }

        stage('Test') {
            steps {
                script {
                    // Run the unit tests
                    sh '${BUILD_DIR}/unit_test'
                }
            }
        }

        stage('Commit and Push Changes') {
            steps {
                script {
                    // Set Git user name and email
                    sh 'git config --global user.email "bhoomikas0552@gmail.com"'
                    sh 'git config --global user.name "bhoomikashirol"'
                    
                    // Add all changes
                    sh 'git add .'
                    
                    // Commit the changes
                    sh 'git commit -m "Automated commit message"'
                    
                    // Push the changes to the respective branch
                    sh 'git push https://github.com/bhoomikashirol/JenkinsDemo.git main'
                    sh 'git push https://github.com/bhoomikashirol/JenkinsDemo.git Test'
                }
            }
        }

        stage('Push Build to Main') {
            steps {
                script {
                    // Copy build files to a temporary directory
                    sh 'cp -r ${BUILD_DIR} /tmp/build'

                    // Checkout the main branch
                    checkout([$class: 'GitSCM', branches: [[name: '*/main']], userRemoteConfigs: [[url: 'https://github.com/bhoomikashirol/JenkinsDemo.git']]])

                    // Move the build files to the build directory in the main branch
                    sh 'mkdir -p build'
                    sh 'cp -r /tmp/build/* build/'

                    // Add and commit the build files
                    sh 'git add build'
                    sh 'git commit -m "Add build files to main branch"'

                    // Push the changes to the main branch
                    sh 'git push https://github.com/bhoomikashirol/JenkinsDemo.git main'
                }
            }
        }
    }

    post {
        always {
            // Archive the build files
            archiveArtifacts artifacts: 'build/**', allowEmptyArchive: true
        }
    }
}

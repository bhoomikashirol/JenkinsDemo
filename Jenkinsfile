pipeline {
    agent any

    environment {
        BUILD_DIR = "/var/lib/jenkins/workspace/PipelineDemo/build"
        REPO_URL = "https://github.com/bhoomikashirol/JenkinsDemo.git"
    }

    stages {
        stage('Checkout') {
            steps {
                script {
                    // Checkout the main branch
                    checkout([$class: 'GitSCM', branches: [[name: '*/main']], userRemoteConfigs: [[url: REPO_URL]]])
                    
                    // Checkout the Code branch
                    dir('Code') {
                        checkout([$class: 'GitSCM', branches: [[name: '*/Code']], userRemoteConfigs: [[url: REPO_URL]]])
                    }
                    
                    // Checkout the Test branch
                    dir('Test') {
                        checkout([$class: 'GitSCM', branches: [[name: '*/Test']], userRemoteConfigs: [[url: REPO_URL]]])
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

        stage('Push to Git') {
            steps {
                script {
                    // Navigate to the build directory
                    dir("${BUILD_DIR}") {
                        // Initialize Git repository if not already initialized
                        sh 'git init'
                        
                        // Check if remote origin already exists and update it if necessary
                        sh '''
                        if git remote | grep -q origin; then
                            git remote set-url origin ${REPO_URL}
                        else
                            git remote add origin ${REPO_URL}
                        fi
                        '''
                        
                        // Add files to staging area
                        sh 'git add .'
                        
                        // Commit the changes
                        sh 'git commit -m "Add build folder contents"'
                        
                        // Create the main branch if it doesn't exist
                        sh 'git branch -M main'
                        
                        // Push the changes to the main branch
                        sh 'git push -u origin main'
                    }
                }
            }
        }
    }
}

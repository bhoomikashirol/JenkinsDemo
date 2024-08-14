pipeline {
    agent any

    environment {
        BUILD_DIR = "${WORKSPACE}/build"
    }

    stages {
        stage('Checkout') {
            steps {
                script {
                    // Checkout the main branch
                    checkout([$class: 'GitSCM', branches: [[name: '*/main']], userRemoteConfigs: [[url: 'https://github.com/your-repo-url.git']]])
                    
                    // Checkout the Code branch
                    dir('Code') {
                        checkout([$class: 'GitSCM', branches: [[name: '*/Code']], userRemoteConfigs: [[url: 'https://github.com/your-repo-url.git']]])
                    }
                    
                    // Checkout the Test branch
                    dir('CRC_UT') {
                        checkout([$class: 'GitSCM', branches: [[name: '*/Test']], userRemoteConfigs: [[url: 'https://github.com/your-repo-url.git']]])
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

        stage('Test') {
            steps {
                script {
                    // Run the unit tests
                    sh '${BUILD_DIR}/unit_test'
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
